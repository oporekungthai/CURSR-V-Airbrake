/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: control_private.h
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

#ifndef control_private_h_
#define control_private_h_
#include "rtwtypes.h"
#include "model_reference_types.h"
#include "control.h"
#include "control_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsSampleHit
#define rtmIsSampleHit(rtm, sti)       ((rtm)->timingBridge->taskCounter[(rtm)->Timing.mdlref_GlobalTID[sti]] == 0)
#endif

#ifndef rtmIsSpecialSampleHit
#define rtmIsSpecialSampleHit(rtm, sti, prom_sti) ( *(((rtm)->timingBridge->rateTransition)[(unsigned int)(rtm)->Timing.mdlref_GlobalTID[sti] + (rtm)->timingBridge->nTasks*( (unsigned int)(rtm)->Timing.mdlref_GlobalTID[prom_sti])]) )
#endif

/* Macros for accessing real-time model data structure */
#ifndef rtmGetClockTick0
#define rtmGetClockTick0(rtm)          ( *(((rtm)->timingBridge->clockTick[(rtm)->Timing.mdlref_GlobalTID[0]])) )
#endif

#ifndef rtmGetClockTick1
#define rtmGetClockTick1(rtm)          ( *(((rtm)->timingBridge->clockTick[(rtm)->Timing.mdlref_GlobalTID[1]])) )
#endif

#ifndef rtmGetClockTickH0
#define rtmGetClockTickH0(rtm)         ( *((rtm)->timingBridge->clockTickH[(rtm)->Timing.mdlref_GlobalTID[0]]) )
#endif

#ifndef rtmGetClockTickH1
#define rtmGetClockTickH1(rtm)         ( *((rtm)->timingBridge->clockTickH[(rtm)->Timing.mdlref_GlobalTID[1]]) )
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (*((rtm)->timingBridge->taskTime[0]))
#endif

extern P_control_T control_P;

#endif                                 /* control_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
