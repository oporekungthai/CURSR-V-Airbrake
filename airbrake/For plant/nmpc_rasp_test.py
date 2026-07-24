import numpy as np
import pandas as pd
from scipy.interpolate import interp1d
import time
import csv

    
# --- 1. CONFIGURATION ---
m = 25.142
Ar = 0.01824146925
Ab = 0.0063812
g = 9.81
dt_sim = 0.1
h_target = 28000 * 0.3048
TARGET_RATE = 100        # Hz (Sample Rate)
DT_FIXED    = 1.0 / TARGET_RATE

# Load Lookups

df_b = pd.read_csv(r"C:\Users\simil\MATLAB Drive\sim_airbrake\For plant\Airbrake_Cd.csv", header=None, names=['Mach', 'Cd'])
df_off = pd.read_csv(r"C:\Users\simil\MATLAB Drive\sim_airbrake\For plant\D11_poweroff.csv", header=None, names=['Mach', 'Cd'])
# The Python equivalent of interp1
interp_b = interp1d(df_b['Mach'], df_b['Cd'], kind='linear', fill_value='extrapolate')
interp_off = interp1d(df_off['Mach'], df_off['Cd'], kind='linear', fill_value='extrapolate')

# --- 2. THE MPC FUNCTION ---
def RK2(h, v_stream, pitch, u_val):
   
    v1 = v_stream*np.cos(pitch)
    h1 = h
    dt = 0.1
    
    while v1 >= 0:
        # --- RK2 STEP 1 (k1) ---
        v_stream1 = v1/np.cos(pitch)
        T1 = 288.15 - 0.0065 * h1
        P1 = 101325 * (T1 / 288.15)**5.2558
        rho1 = P1 / (287.05 * T1)
        c1 = np.sqrt(1.4 * 287.05 * T1)
        mach1 = v_stream1 / c1
        
        # Get Cd
        Cdb1 = float(interp_b(mach1))
        Cdr1 = float(interp_off(mach1))
        
        # Acceleration 1
        drag1 = 0.5 * rho1 * v_stream1**2 * ((Cdr1*Ar) + (Cdb1*Ab*u_val))
        a1 = (-drag1* np.cos(pitch) / m) - (g * np.cos(pitch))
        
        # Midpoint
        
        h2 = h1 + v1 * (dt / 2)
        v2 = v1 + a1 * (dt / 2)
        
        # --- RK2 STEP 2 (k2) ---
        v_stream2 = v2/np.cos(pitch)
        T2 = 288.15 - 0.0065 * h2
        P2 = 101325 * (T2 / 288.15)**5.2558
        rho2 = P2 / (287.05 * T2)
        c2 = np.sqrt(1.4 * 287.05 * T2)
        mach2 = v_stream2 / c2
        
        # Get Cd
        Cdb2 = float(interp_b(mach2))
        Cdr2 = float(interp_off(mach2))
        
        # Acceleration 2 
        drag2 = 0.5 * rho2 * v_stream2**2 * ((Cdr2*Ar) + (Cdb2*Ab*u_val))
        a2 = (-drag2 * np.cos(pitch) / m) - (g * np.cos(pitch))
        
        # Final Update
        
        v1 += a2 * dt
        h1 += v2 * dt
        
        if h1 > 12000: break # Safety
        
    return h1

def NMPC(h, v, pitch):
    if np.isnan(h) or np.isnan(v):
        return 0.0

    # --- BOUNDARY CHECK (0 1)
    
    pred_min = RK2(h, v, pitch, 0.0)
    if pred_min < h_target:
        return 0.0  # TRUE ZERO (Don't bother searching)

    
    pred_max = RK2(h, v, pitch, 1.0)
    if pred_max > h_target:
        return 1.0 # TRUE ONE 

    # --- BINARY SEARCH (Only runs if solution is between 0 and 1) ---
    u_low = 0.0
    u_high = 1.0
    u_mid = 0.5
    
    for _ in range(5):
        
        h_sim = RK2(h, v, pitch, u_mid)
        
        if h_sim > h_target:
            u_low = u_mid   # Overshooting -> More Drag Needed
        else:
            u_high = u_mid  # Undershooting -> Less Drag Needed
            
        u_mid = (u_low + u_high) / 2
        
    return u_mid


# --- 3. PSEUDO FLIGHT ---
flight_data = pd.read_csv(r"C:\Users\simil\MATLAB Drive\sim_airbrake\For plant\STM_flightsim.csv", header=None, names=['time', 'h', 'v', 'mach', 'pitch'])
u_current = 0.0
results = []
h_debounce_counter = 0   # Acts as the "Tapped Delay"
altitude_latched = False # Acts as the "S-R Flip-Flop" (Q output)
was_active = False
next_loop_time = time.time() + DT_FIXED
print("Starting Simulation...")
output_filename = "simulation_results.csv"
with open(output_filename, mode='w', newline='') as f:
    writer = csv.writer(f)
    
    # Write the Header Row
    writer.writerow(["Time", "Height", "Logic", "U_Level"])
    
#------Reading and flight goin on!------
    for i in range(len(flight_data)):
        
        t_loop_start = time.time() #time activation counter
        row = flight_data.iloc[i]
        t_now   = float(row['time'])
        h_in    = float(row['h'])
        v_in    = float(row['v'])
        mach_in = float(row['mach'])
        pitch_in = float(row['pitch'])
        
        
    # --- 4. Airbrake activation ---

        cond_time = (t_now > 3.997)
        cond_mach = (mach_in < 0.8)
        cond_climb = (v_in >= 0) 

        if h_in >= 6000:
            h_debounce_counter += 1 # Count consecutive samples
        else:
            h_debounce_counter = 0  # Reset if signal drops (noise filtering)

        if h_debounce_counter >= 4:
            altitude_latched = True
        is_active = (cond_time and cond_mach and cond_climb and altitude_latched)
        
    #----100 ms
        if is_active:
            # CONDITION 1: Standard 10Hz heartbeat
            timer_trigger = (i % 10 == 0)
            
            # CONDITION 2: "Interrupt" - We just turned ON this very instant!
            just_triggered = (is_active and not was_active)
            
            if timer_trigger or just_triggered:
                u_current = NMPC(h_in, v_in, pitch_in)
                # Alignment fix: If we triggered off-beat (e.g. at 15.55), 
                # this aligns the result immediately.
                
        else:
            u_current = 0.0

        # Update history for the next loop
        was_active = is_active

        # Store result to verify later
        results.append(u_current)
        data_row = [f"{t_now:.2f}", f"{h_in:.0f}", int(is_active), f"{u_current:.4f}"]
        writer.writerow(data_row)
        # Optional: Debug Print every 1 second (every 100th sample)
        if i % 100 == 0:
            print(f"{t_now:.2f},{h_in:.0f},{int(is_active)},{u_current:.4f}")
    # ------ RATE LIMITER (Enforce 100Hz on Real Hardware)
        t_now_real = time.time()
        sleep_duration = next_loop_time - t_now_real
        if sleep_duration > 0:
            time.sleep(sleep_duration)
        next_loop_time += DT_FIXED
print("Simulation Complete.")