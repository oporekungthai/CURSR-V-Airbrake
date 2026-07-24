/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: control.c
 *
 * Code generated for Simulink model 'control'.
 *
 * Model version                  : 1.23
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Jun  1 18:24:35 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "control.h"
#include "rtwtypes.h"
#include "control_private.h"
#include "rt_nonfinite.h"
#include <math.h>
#include "control_types.h"

P_control_T control_P = {
  /* Computed Parameter: u0_Y0
   * Referenced by: '<S2>/u0'
   */
  0.0,

  /* Computed Parameter: b0_Y0
   * Referenced by: '<S2>/b0'
   */
  0.0,

  /* Computed Parameter: f0_Y0
   * Referenced by: '<S2>/f0'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S2>/Delay'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S2>/Delay1'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S2>/Delay2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<Root>/Delay'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<Root>/Delay2'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<Root>/Delay1'
   */
  0.0,

  /* Expression: 0
   * Referenced by:
   */
  0.0,

  /* Expression: 0
   * Referenced by:
   */
  0.0,

  /* Expression: 0
   * Referenced by:
   */
  0.0
};

/* Forward declaration for local functions */
static real_T control_fast_interp(const real_T xd[12], const real_T yd[12],
  real_T x);
static real_T control_fast_interp_a(const real_T xd[26], const real_T yd[26],
  real_T x);
static real_T control_fast_interp_a2(const real_T xd[370], const real_T yd[370],
  real_T x);
static void control_RK2(real_T h, real_T v, real_T pitch, real_T u_val, const
  real_T M_b[26], const real_T C_b[26], const real_T M_off[370], const real_T
  Cdr_off[370], real_T *h_final, real_T *bf, real_T *f);

/* Function for MATLAB Function: '<S2>/NAP Function' */
static real_T control_fast_interp(const real_T xd[12], const real_T yd[12],
  real_T x)
{
  real_T y;
  if (x <= xd[0]) {
    y = yd[0];
  } else if (x >= xd[11]) {
    y = yd[11];
  } else {
    int32_T i;
    i = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (i < 11) {
        real_T tmp;
        tmp = xd[i + 1];
        if (tmp >= x) {
          y = (x - xd[i]) / (tmp - xd[i]) * (yd[i + 1] - yd[i]) + yd[i];
          exitg1 = 1;
        } else {
          i++;
        }
      } else {
        y = yd[11];
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

/* Function for MATLAB Function: '<S2>/NAP Function' */
static real_T control_fast_interp_a(const real_T xd[26], const real_T yd[26],
  real_T x)
{
  real_T y;
  if (x <= xd[0]) {
    y = yd[0];
  } else if (x >= xd[25]) {
    y = yd[25];
  } else {
    int32_T i;
    i = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (i < 25) {
        real_T tmp;
        tmp = xd[i + 1];
        if (tmp >= x) {
          y = (x - xd[i]) / (tmp - xd[i]) * (yd[i + 1] - yd[i]) + yd[i];
          exitg1 = 1;
        } else {
          i++;
        }
      } else {
        y = yd[25];
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

/* Function for MATLAB Function: '<S2>/NAP Function' */
static real_T control_fast_interp_a2(const real_T xd[370], const real_T yd[370],
  real_T x)
{
  real_T y;
  if (x <= xd[0]) {
    y = yd[0];
  } else if (x >= xd[369]) {
    y = yd[369];
  } else {
    int32_T i;
    i = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (i < 369) {
        real_T tmp;
        tmp = xd[i + 1];
        if (tmp >= x) {
          y = (x - xd[i]) / (tmp - xd[i]) * (yd[i + 1] - yd[i]) + yd[i];
          exitg1 = 1;
        } else {
          i++;
        }
      } else {
        y = yd[369];
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

/* Function for MATLAB Function: '<S2>/NAP Function' */
static void control_RK2(real_T h, real_T v, real_T pitch, real_T u_val, const
  real_T M_b[26], const real_T C_b[26], const real_T M_off[370], const real_T
  Cdr_off[370], real_T *h_final, real_T *bf, real_T *f)
{
  real_T tmp[12];
  real_T tmp_0[12];
  real_T tmp_1[12];
  real_T cos_pitch;
  real_T mach0;
  real_T stream0;
  real_T stream1;
  real_T stream2;
  real_T v1;
  int32_T i;
  int32_T iter_rk;
  static const real_T b[12] = { 1.225, 1.112, 1.007, 0.909, 0.819, 0.736, 0.66,
    0.59, 0.526, 0.467, 0.414, 0.365 };

  cos_pitch = cos(pitch);
  *h_final = h;
  v1 = v;
  stream0 = v / cos_pitch;
  for (i = 0; i < 12; i++) {
    tmp[i] = 1000.0 * (real_T)i;
  }

  mach0 = stream0 / sqrt((288.15 - 0.0065 * h) * 401.8739);
  stream0 = -0.5 * control_fast_interp(tmp, b, h) * (stream0 * stream0);
  *bf = stream0 * control_fast_interp_a(M_b, C_b, mach0) * 0.002222324 / 25.142 *
    cos_pitch;
  *f = stream0 * control_fast_interp_a2(M_off, Cdr_off, mach0) *
    0.013478217882063612 / 25.142 * cos_pitch - 9.81;
  iter_rk = 0;
  if ((!(v <= 0.1)) && (!(h > 12000.0))) {
    for (i = 0; i < 12; i++) {
      stream0 = 1000.0 * (real_T)i;
      tmp_0[i] = stream0;
      tmp_1[i] = stream0;
    }
  }

  while ((iter_rk < 100) && (!(v1 <= 0.1)) && (!(*h_final > 12000.0))) {
    stream1 = v1 / cos_pitch;
    stream0 = stream1 / sqrt((288.15 - 0.0065 * *h_final) * 401.8739);
    mach0 = v1 * 0.2 + *h_final;
    stream1 = -0.5 * control_fast_interp(tmp_0, b, *h_final) * (stream1 *
      stream1);
    stream0 = ((stream1 * control_fast_interp_a2(M_off, Cdr_off, stream0) *
                0.013478217882063612 / 25.142 * cos_pitch - 9.81) + stream1 *
               control_fast_interp_a(M_b, C_b, stream0) * 0.002222324 / 25.142 *
               cos_pitch * u_val) * 0.2 + v1;
    stream2 = stream0 / cos_pitch;
    stream1 = stream2 / sqrt((288.15 - 0.0065 * mach0) * 401.8739);
    mach0 = -0.5 * control_fast_interp(tmp_1, b, mach0) * (stream2 * stream2);
    v1 += ((mach0 * control_fast_interp_a2(M_off, Cdr_off, stream1) *
            0.013478217882063612 / 25.142 * cos_pitch - 9.81) + mach0 *
           control_fast_interp_a(M_b, C_b, stream1) * 0.002222324 / 25.142 *
           cos_pitch * u_val) * 0.4;
    *h_final += stream0 * 0.4;
    iter_rk++;
  }
}

/* System initialize for referenced model: 'control' */
void control_Init(B_control_c_T *localB, DW_control_f_T *localDW)
{
  /* Start for RateTransition generated from: '<Root>/Enabled Subsystem' */
  localB->TmpRTBAtEnabledSubsystemOutport =
    control_P.TmpRTBAtEnabledSubsystemOutport;

  /* Start for RateTransition generated from: '<Root>/Enabled Subsystem' */
  localB->TmpRTBAtEnabledSubsystemOutpo_o =
    control_P.TmpRTBAtEnabledSubsystemOutpo_j;

  /* Start for RateTransition generated from: '<Root>/Enabled Subsystem' */
  localB->TmpRTBAtEnabledSubsystemOutpo_f =
    control_P.TmpRTBAtEnabledSubsystemOutp_jx;

  /* InitializeConditions for Delay: '<Root>/Delay' */
  localDW->Delay_DSTATE[0] = control_P.Delay_InitialCondition_g;
  localDW->Delay_DSTATE[1] = control_P.Delay_InitialCondition_g;
  localDW->Delay_DSTATE[2] = control_P.Delay_InitialCondition_g;
  localDW->Delay_DSTATE[3] = control_P.Delay_InitialCondition_g;

  /* InitializeConditions for Delay: '<Root>/Delay2' */
  localDW->Delay2_DSTATE[0] = control_P.Delay2_InitialCondition_c;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  localDW->Delay1_DSTATE[0] = control_P.Delay1_InitialCondition_j;

  /* InitializeConditions for Delay: '<Root>/Delay2' */
  localDW->Delay2_DSTATE[1] = control_P.Delay2_InitialCondition_c;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  localDW->Delay1_DSTATE[1] = control_P.Delay1_InitialCondition_j;

  /* InitializeConditions for RateTransition generated from: '<Root>/Enabled Subsystem' */
  localDW->TmpRTBAtEnabledSubsystemOutport =
    control_P.TmpRTBAtEnabledSubsystemOutport;

  /* InitializeConditions for RateTransition generated from: '<Root>/Enabled Subsystem' */
  localDW->TmpRTBAtEnabledSubsystemOutpo_h =
    control_P.TmpRTBAtEnabledSubsystemOutpo_j;

  /* InitializeConditions for RateTransition generated from: '<Root>/Enabled Subsystem' */
  localDW->TmpRTBAtEnabledSubsystemOutpo_m =
    control_P.TmpRTBAtEnabledSubsystemOutp_jx;

  /* SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  /* InitializeConditions for Delay: '<S2>/Delay' */
  localDW->Delay_DSTATE_h[0] = control_P.Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S2>/Delay1' */
  localDW->Delay1_DSTATE_h[0] = control_P.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S2>/Delay2' */
  localDW->Delay2_DSTATE_i[0] = control_P.Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S2>/Delay' */
  localDW->Delay_DSTATE_h[1] = control_P.Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S2>/Delay1' */
  localDW->Delay1_DSTATE_h[1] = control_P.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S2>/Delay2' */
  localDW->Delay2_DSTATE_i[1] = control_P.Delay2_InitialCondition;

  /* SystemInitialize for MATLAB Function: '<S2>/NAP Function' */
  localDW->bf_store = -4.5;
  localDW->f_store = -9.81;

  /* SystemInitialize for Delay: '<S2>/Delay' incorporates:
   *  Outport: '<S2>/u0'
   */
  localB->Delay = control_P.u0_Y0;

  /* SystemInitialize for Delay: '<S2>/Delay1' incorporates:
   *  Outport: '<S2>/b0'
   */
  localB->Delay1 = control_P.b0_Y0;

  /* SystemInitialize for Delay: '<S2>/Delay2' incorporates:
   *  Outport: '<S2>/f0'
   */
  localB->Delay2 = control_P.f0_Y0;

  /* End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem' */
}

/* Disable for referenced model: 'control' */
void control_Disable(DW_control_f_T *localDW)
{
  /* Disable for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  if (localDW->EnabledSubsystem_MODE) {
    localDW->EnabledSubsystem_MODE = false;
  }

  /* End of Disable for SubSystem: '<Root>/Enabled Subsystem' */
}

/* Output and update for referenced model: 'control' */
void controlTID0(RT_MODEL_control_T * const control_M, const real_T *rtu_Vz,
                 const real_T *rtu_h, const boolean_T *rtu_logic, const real_T
                 *rtu_pitch, real_T *rty_Out1, B_control_c_T *localB,
                 DW_control_f_T *localDW)
{
  int_T tid = 0;
  real_T b0;
  real_T e;
  real_T f0;
  real_T rtb_pitchpass;
  real_T u0;

  /* RateTransition generated from: '<Root>/Delay' incorporates:
   *  Delay: '<Root>/Delay'
   */
  if (rtmIsSpecialSampleHit(control_M, 1, 0)) {
    localDW->TmpRTBAtDelayOutport1_Buffer[0] = localDW->Delay_DSTATE[0];
    localDW->TmpRTBAtDelayOutport1_Buffer[1] = localDW->Delay_DSTATE[1];
  }

  /* End of RateTransition generated from: '<Root>/Delay' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Delay: '<Root>/Delay2'
   */
  if (*rtu_logic) {
    *rty_Out1 = localDW->Delay2_DSTATE[0];
  } else {
    *rty_Out1 = control_P.Constant_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* RateTransition generated from: '<Root>/Enabled Subsystem' incorporates:
   *  Delay: '<Root>/Delay1'
   */
  if (rtmIsSpecialSampleHit(control_M, 1, 0)) {
    localDW->TmpRTBAtEnabledSubsystemInport3 = localDW->Delay1_DSTATE[0];

    /* RateTransition generated from: '<Root>/Enabled Subsystem' incorporates:
     *  Delay: '<Root>/Delay1'
     */
    localB->TmpRTBAtEnabledSubsystemOutport =
      localDW->TmpRTBAtEnabledSubsystemOutport;

    /* RateTransition generated from: '<Root>/Enabled Subsystem' */
    localB->TmpRTBAtEnabledSubsystemOutpo_o =
      localDW->TmpRTBAtEnabledSubsystemOutpo_h;

    /* RateTransition generated from: '<Root>/Enabled Subsystem' */
    localB->TmpRTBAtEnabledSubsystemOutpo_f =
      localDW->TmpRTBAtEnabledSubsystemOutpo_m;
  }

  /* End of RateTransition generated from: '<Root>/Enabled Subsystem' */

  /* MATLAB Function: '<Root>/ESO Function' */
  u0 = localB->TmpRTBAtEnabledSubsystemOutport;
  b0 = localB->TmpRTBAtEnabledSubsystemOutpo_o;
  f0 = localB->TmpRTBAtEnabledSubsystemOutpo_f;
  rtb_pitchpass = *rtu_pitch;
  if (rtIsNaN(localB->TmpRTBAtEnabledSubsystemOutport)) {
    u0 = 0.0;
  }

  if (rtIsNaN(localB->TmpRTBAtEnabledSubsystemOutpo_o)) {
    b0 = -5.0;
  } else if (localB->TmpRTBAtEnabledSubsystemOutpo_o == 0.0) {
    b0 = -5.0;
  }

  if (rtIsNaN(localB->TmpRTBAtEnabledSubsystemOutpo_f)) {
    f0 = -9.81;
  }

  if (!localDW->z1_not_empty) {
    localDW->z1 = 892.0;
    localDW->z1_not_empty = true;
    localDW->z2 = 0.0;
    localDW->z3 = -9.81;
    localDW->u_prev = 0.0;
    if (!rtIsNaN(*rtu_h)) {
      localDW->z1 = *rtu_h;
    }

    if (!rtIsNaN(*rtu_Vz)) {
      localDW->z2 = *rtu_Vz;
    }

    if (!rtIsNaN(f0)) {
      localDW->z3 = f0;
    }
  }

  if (rtIsNaN(*rtu_h) || rtIsNaN(*rtu_Vz)) {
  } else {
    e = localDW->z1 - *rtu_h;
    localDW->u_prev = fmax(0.0, fmin(1.0, fmax(fmin((fmax(-0.5, fmin(0.5,
      -localDW->z3 / b0)) + u0) - localDW->u_prev, 0.3), -0.3) + localDW->u_prev));
    localDW->z1 += (localDW->z2 - 18.0 * e) * 0.001;
    localDW->z2 += (((localDW->z3 + f0) - 108.0 * e) + b0 * localDW->u_prev) *
      0.001;
    localDW->z3 += -216.0 * e * 0.001;
  }

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (*rtu_logic) {
    if (!localDW->EnabledSubsystem_MODE) {
      localDW->EnabledSubsystem_MODE = true;
    }
  } else if (localDW->EnabledSubsystem_MODE) {
    localDW->EnabledSubsystem_MODE = false;
  }

  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */

  /* Update for Delay: '<Root>/Delay' */
  localDW->Delay_DSTATE[0] = localDW->Delay_DSTATE[2];
  localDW->Delay_DSTATE[1] = localDW->Delay_DSTATE[3];
  localDW->Delay_DSTATE[2] = localDW->z1;
  localDW->Delay_DSTATE[3] = localDW->z2;

  /* Update for Delay: '<Root>/Delay2' incorporates:
   *  MATLAB Function: '<Root>/ESO Function'
   */
  localDW->Delay2_DSTATE[0] = localDW->Delay2_DSTATE[1];
  localDW->Delay2_DSTATE[1] = localDW->u_prev;

  /* Update for Delay: '<Root>/Delay1' */
  localDW->Delay1_DSTATE[0] = localDW->Delay1_DSTATE[1];
  localDW->Delay1_DSTATE[1] = rtb_pitchpass;

  /* If subsystem generates rate grouping Output functions,
   * when tid is used in Output function for one rate,
   * all Output functions include tid as a local variable.
   * As result, some Output functions may have unused tid.
   */
  (void) (tid);
}

/* Output and update for referenced model: 'control' */
void controlTID1(B_control_c_T *localB, DW_control_f_T *localDW)
{
  int_T tid = 1;
  real_T rtb_bf;
  real_T rtb_f_nominal;
  real_T rtb_u_out;
  real_T u_mid;
  boolean_T guard1;

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (localDW->EnabledSubsystem_MODE) {
    /* Delay: '<S2>/Delay' */
    localB->Delay = localDW->Delay_DSTATE_h[0];

    /* Delay: '<S2>/Delay1' */
    localB->Delay1 = localDW->Delay1_DSTATE_h[0];

    /* Delay: '<S2>/Delay2' */
    localB->Delay2 = localDW->Delay2_DSTATE_i[0];
  }

  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */

  /* RateTransition generated from: '<Root>/Enabled Subsystem' */
  localDW->TmpRTBAtEnabledSubsystemOutport = localB->Delay;

  /* RateTransition generated from: '<Root>/Enabled Subsystem' */
  localDW->TmpRTBAtEnabledSubsystemOutpo_h = localB->Delay1;

  /* RateTransition generated from: '<Root>/Enabled Subsystem' */
  localDW->TmpRTBAtEnabledSubsystemOutpo_m = localB->Delay2;

  /* Update for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (localDW->EnabledSubsystem_MODE) {
    /* MATLAB Function: '<S2>/NAP Function' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S2>/Constant1'
     *  Constant: '<S2>/Constant2'
     *  Constant: '<S2>/Constant3'
     *  RateTransition generated from: '<Root>/Delay'
     *  RateTransition generated from: '<Root>/Enabled Subsystem'
     */
    rtb_u_out = 0.0;
    rtb_bf = -4.5;
    rtb_f_nominal = -9.81;
    if ((!rtIsNaN(localDW->TmpRTBAtDelayOutport1_Buffer[0])) && (!rtIsNaN
         (localDW->TmpRTBAtDelayOutport1_Buffer[1]))) {
      guard1 = false;
      if (localDW->tick <= 0.0) {
        control_RK2(localDW->TmpRTBAtDelayOutport1_Buffer[0],
                    localDW->TmpRTBAtDelayOutport1_Buffer[1],
                    localDW->TmpRTBAtEnabledSubsystemInport3, 0.0, rtP_M_b,
                    rtP_C_b, rtP_M_off, rtP_Cdr_off, &u_mid, &rtb_bf,
                    &rtb_f_nominal);
        if (u_mid < 11072.32) {
        } else {
          control_RK2(localDW->TmpRTBAtDelayOutport1_Buffer[0],
                      localDW->TmpRTBAtDelayOutport1_Buffer[1],
                      localDW->TmpRTBAtEnabledSubsystemInport3, 1.0, rtP_M_b,
                      rtP_C_b, rtP_M_off, rtP_Cdr_off, &rtb_u_out, &rtb_bf,
                      &rtb_f_nominal);
          if (rtb_u_out > 11072.32) {
            rtb_u_out = 1.0;
          } else {
            rtb_bf = 0.0;
            rtb_f_nominal = 1.0;
            control_RK2(localDW->TmpRTBAtDelayOutport1_Buffer[0],
                        localDW->TmpRTBAtDelayOutport1_Buffer[1],
                        localDW->TmpRTBAtEnabledSubsystemInport3, 0.5, rtP_M_b,
                        rtP_C_b, rtP_M_off, rtP_Cdr_off, &rtb_u_out,
                        &localDW->bf_store, &localDW->f_store);
            if (rtb_u_out > 11072.32) {
              rtb_bf = 0.5;
            } else {
              rtb_f_nominal = 0.5;
            }

            u_mid = (rtb_bf + rtb_f_nominal) / 2.0;
            control_RK2(localDW->TmpRTBAtDelayOutport1_Buffer[0],
                        localDW->TmpRTBAtDelayOutport1_Buffer[1],
                        localDW->TmpRTBAtEnabledSubsystemInport3, u_mid, rtP_M_b,
                        rtP_C_b, rtP_M_off, rtP_Cdr_off, &rtb_u_out,
                        &localDW->bf_store, &localDW->f_store);
            if (rtb_u_out > 11072.32) {
              rtb_bf = u_mid;
            } else {
              rtb_f_nominal = u_mid;
            }

            u_mid = (rtb_bf + rtb_f_nominal) / 2.0;
            control_RK2(localDW->TmpRTBAtDelayOutport1_Buffer[0],
                        localDW->TmpRTBAtDelayOutport1_Buffer[1],
                        localDW->TmpRTBAtEnabledSubsystemInport3, u_mid, rtP_M_b,
                        rtP_C_b, rtP_M_off, rtP_Cdr_off, &rtb_u_out,
                        &localDW->bf_store, &localDW->f_store);
            if (rtb_u_out > 11072.32) {
              rtb_bf = u_mid;
            } else {
              rtb_f_nominal = u_mid;
            }

            localDW->u_store = (rtb_bf + rtb_f_nominal) / 2.0;
            localDW->tick = 10.0;
            guard1 = true;
          }
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        localDW->tick--;
        rtb_u_out = localDW->u_store;
        rtb_bf = localDW->bf_store;
        rtb_f_nominal = localDW->f_store;
      }
    }

    /* End of MATLAB Function: '<S2>/NAP Function' */

    /* Update for Delay: '<S2>/Delay' */
    localDW->Delay_DSTATE_h[0] = localDW->Delay_DSTATE_h[1];
    localDW->Delay_DSTATE_h[1] = rtb_u_out;

    /* Update for Delay: '<S2>/Delay1' */
    localDW->Delay1_DSTATE_h[0] = localDW->Delay1_DSTATE_h[1];
    localDW->Delay1_DSTATE_h[1] = rtb_bf;

    /* Update for Delay: '<S2>/Delay2' */
    localDW->Delay2_DSTATE_i[0] = localDW->Delay2_DSTATE_i[1];
    localDW->Delay2_DSTATE_i[1] = rtb_f_nominal;
  }

  /* End of Update for SubSystem: '<Root>/Enabled Subsystem' */

  /* If subsystem generates rate grouping Output functions,
   * when tid is used in Output function for one rate,
   * all Output functions include tid as a local variable.
   * As result, some Output functions may have unused tid.
   */
  (void) (tid);
}

/* Model initialize function */
void control_initialize(const char_T **rt_errorStatus, const rtTimingBridge
  *timingBridge, int_T mdlref_TID0, int_T mdlref_TID1, RT_MODEL_control_T *const
  control_M)
{
  /* Registration code */

  /* setup the global timing engine */
  control_M->Timing.mdlref_GlobalTID[0] = mdlref_TID0;
  control_M->Timing.mdlref_GlobalTID[1] = mdlref_TID1;
  control_M->timingBridge = (timingBridge);

  /* initialize error status */
  rtmSetErrorStatusPointer(control_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
