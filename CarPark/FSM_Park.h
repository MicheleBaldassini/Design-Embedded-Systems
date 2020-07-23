/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FSM_Park.h
 *
 * Code generated for Simulink model 'FSM_Park'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Tue Feb 14 17:35:34 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FSM_Park_h_
#define RTW_HEADER_FSM_Park_h_
#include <string.h>
#ifndef FSM_Park_COMMON_INCLUDES_
# define FSM_Park_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* FSM_Park_COMMON_INCLUDES_ */

#include "FSM_Park_types.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_control;                  /* '<S1>/Chart' */
} DW_FSM_Park_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Chart_Trig_ZCE[2];        /* '<S1>/Chart' */
} PrevZCX_FSM_Park_T;

/* Real-time Model Data Structure */
struct tag_RTM_FSM_Park_T {
  const char_T * volatile errorStatus;
  PrevZCX_FSM_Park_T *prevZCSigState;
  DW_FSM_Park_T *dwork;
};

/* Model entry point functions */
extern void FSM_Park_initialize(RT_MODEL_FSM_Park_T *const FSM_Park_M, boolean_T
  *FSM_Park_U_ttick, boolean_T *FSM_Park_U_BAccept, boolean_T
  *FSM_Park_U_arrived, boolean_T *FSM_Park_Y_free_p, boolean_T
  *FSM_Park_Y_accept, uint8_T *FSM_Park_Y_hours, uint8_T *FSM_Park_Y_minutes);
extern void FSM_Park_step(RT_MODEL_FSM_Park_T *const FSM_Park_M, boolean_T
  FSM_Park_U_ttick, boolean_T FSM_Park_U_BAccept, boolean_T FSM_Park_U_arrived,
  boolean_T *FSM_Park_Y_free_p, boolean_T *FSM_Park_Y_accept, uint8_T
  *FSM_Park_Y_hours, uint8_T *FSM_Park_Y_minutes);
extern void FSM_Park_terminate(RT_MODEL_FSM_Park_T *const FSM_Park_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('ParkSensor/FSM_Park')    - opens subsystem ParkSensor/FSM_Park
 * hilite_system('ParkSensor/FSM_Park/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ParkSensor'
 * '<S1>'   : 'ParkSensor/FSM_Park'
 * '<S2>'   : 'ParkSensor/FSM_Park/Chart'
 */
#endif                                 /* RTW_HEADER_FSM_Park_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
