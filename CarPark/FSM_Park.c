/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FSM_Park.c
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

#include "FSM_Park.h"
#include "FSM_Park_private.h"

/* Named constants for Chart: '<S1>/Chart' */
#define FSM_Park_IN_Accept_Arrivals    ((uint8_T)1U)
#define FSM_Park_IN_Accept_Departure   ((uint8_T)2U)
#define FSM_Park_IN_Free               ((uint8_T)3U)
#define FSM_Park_IN_Parked             ((uint8_T)4U)
#define FSM_Park_event_BAccept         (1)
#define FSM_Park_event_ttick           (0)

/* Forward declaration for local functions */
static void FSM_Park_chartstep_c3_FSM_Park(const int32_T *sfEvent, boolean_T
  FSM_Park_U_arrived, boolean_T *FSM_Park_Y_free_p, boolean_T *FSM_Park_Y_accept,
  uint8_T *FSM_Park_Y_hours, uint8_T *FSM_Park_Y_minutes, DW_FSM_Park_T
  *FSM_Park_DW);

/* Function for Chart: '<S1>/Chart' */
static void FSM_Park_chartstep_c3_FSM_Park(const int32_T *sfEvent, boolean_T
  FSM_Park_U_arrived, boolean_T *FSM_Park_Y_free_p, boolean_T *FSM_Park_Y_accept,
  uint8_T *FSM_Park_Y_hours, uint8_T *FSM_Park_Y_minutes, DW_FSM_Park_T
  *FSM_Park_DW)
{
  int32_T tmp;

  /* During: FSM_Park/Chart */
  /* During 'control': '<S2>:3' */
  switch (FSM_Park_DW->is_control) {
   case FSM_Park_IN_Accept_Arrivals:
    /* During 'Accept_Arrivals': '<S2>:65' */
    /* '<S2>:70:1' sf_internal_predicateOutput = ... */
    /* '<S2>:70:1' BAccept; */
    if (*sfEvent == FSM_Park_event_BAccept) {
      /* Transition: '<S2>:70' */
      /* Exit 'Accept_Arrivals': '<S2>:65' */
      /* '<S2>:65:1' accept = false */
      *FSM_Park_Y_accept = false;

      /* '<S2>:70:1' hours = uint8(0); */
      *FSM_Park_Y_hours = 0U;

      /* '<S2>:70:1' minutes = uint8(0) */
      *FSM_Park_Y_minutes = 0U;
      FSM_Park_DW->is_control = FSM_Park_IN_Parked;

      /* Entry 'Parked': '<S2>:75' */
      /* '<S2>:75:1' free = false */
      *FSM_Park_Y_free_p = false;
    } else {
      /* Inport: '<Root>/arrived' */
      /* '<S2>:93:1' sf_internal_predicateOutput = ... */
      /* '<S2>:93:1' arrived == false; */
      if (!FSM_Park_U_arrived) {
        /* Transition: '<S2>:93' */
        /* Exit 'Accept_Arrivals': '<S2>:65' */
        /* '<S2>:65:1' accept = false */
        *FSM_Park_Y_accept = false;
        FSM_Park_DW->is_control = FSM_Park_IN_Free;
      }
    }
    break;

   case FSM_Park_IN_Accept_Departure:
    /* During 'Accept_Departure': '<S2>:74' */
    /* '<S2>:81:1' sf_internal_predicateOutput = ... */
    /* '<S2>:81:1' BAccept; */
    if (*sfEvent == FSM_Park_event_BAccept) {
      /* Transition: '<S2>:81' */
      /* Exit 'Accept_Departure': '<S2>:74' */
      /* '<S2>:74:1' accept = false; */
      *FSM_Park_Y_accept = false;

      /* '<S2>:74:2' free = true; */
      *FSM_Park_Y_free_p = true;

      /* '<S2>:81:1' hours = uint8(0); */
      *FSM_Park_Y_hours = 0U;

      /* '<S2>:81:1' minutes = uint8(0) */
      *FSM_Park_Y_minutes = 0U;
      FSM_Park_DW->is_control = FSM_Park_IN_Free;
    } else {
      /* Inport: '<Root>/arrived' */
      /* '<S2>:82:1' sf_internal_predicateOutput = ... */
      /* '<S2>:82:1' (BAccept) && (arrived == true); */
      if ((*sfEvent == FSM_Park_event_BAccept) && FSM_Park_U_arrived) {
        /* Transition: '<S2>:82' */
        /* Exit 'Accept_Departure': '<S2>:74' */
        /* '<S2>:74:1' accept = false; */
        /* '<S2>:74:2' free = true; */
        *FSM_Park_Y_free_p = true;
        FSM_Park_DW->is_control = FSM_Park_IN_Accept_Arrivals;

        /* Entry 'Accept_Arrivals': '<S2>:65' */
        /* '<S2>:65:1' accept = true */
        *FSM_Park_Y_accept = true;
      }
    }
    break;

   case FSM_Park_IN_Free:
    /* Inport: '<Root>/arrived' */
    /* During 'Free': '<S2>:62' */
    /* '<S2>:66:1' sf_internal_predicateOutput = ... */
    /* '<S2>:66:1' arrived==true; */
    if (FSM_Park_U_arrived) {
      /* Transition: '<S2>:66' */
      FSM_Park_DW->is_control = FSM_Park_IN_Accept_Arrivals;

      /* Entry 'Accept_Arrivals': '<S2>:65' */
      /* '<S2>:65:1' accept = true */
      *FSM_Park_Y_accept = true;
    }
    break;

   default:
    /* Inport: '<Root>/arrived' */
    /* During 'Parked': '<S2>:75' */
    /* '<S2>:77:1' sf_internal_predicateOutput = ... */
    /* '<S2>:77:1' arrived==false; */
    if (!FSM_Park_U_arrived) {
      /* Transition: '<S2>:77' */
      FSM_Park_DW->is_control = FSM_Park_IN_Accept_Departure;

      /* Entry 'Accept_Departure': '<S2>:74' */
      /* '<S2>:74:1' accept = true; */
      *FSM_Park_Y_accept = true;
    }
    break;
  }

  /* During 'time': '<S2>:20' */
  /* During 'timecount': '<S2>:23' */
  /* '<S2>:32:1' sf_internal_predicateOutput = ... */
  /* '<S2>:32:1' ttick; */
  if (*sfEvent == FSM_Park_event_ttick) {
    /* Transition: '<S2>:32' */
    /* '<S2>:32:1' minutes=mod(minutes+1,60) */
    tmp = (int32_T)(*FSM_Park_Y_minutes + 1U);
    if ((uint32_T)tmp > 255U) {
      tmp = 255;
    }

    *FSM_Park_Y_minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)((uint8_T)
      tmp / 60U * 60U));

    /* '<S2>:28:1' sf_internal_predicateOutput = ... */
    /* '<S2>:28:1' minutes==0; */
    if (*FSM_Park_Y_minutes == 0) {
      /* Transition: '<S2>:28' */
      /* '<S2>:28:1' hours=mod(hours+1, 24) */
      tmp = (int32_T)(*FSM_Park_Y_hours + 1U);
      if ((uint32_T)tmp > 255U) {
        tmp = 255;
      }

      *FSM_Park_Y_hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)((uint8_T)
        tmp / 24U * 24U));
    } else {
      /* Transition: '<S2>:98' */
    }
  }
}

/* Model step function */
void FSM_Park_step(RT_MODEL_FSM_Park_T *const FSM_Park_M, boolean_T
                   FSM_Park_U_ttick, boolean_T FSM_Park_U_BAccept, boolean_T
                   FSM_Park_U_arrived, boolean_T *FSM_Park_Y_free_p, boolean_T
                   *FSM_Park_Y_accept, uint8_T *FSM_Park_Y_hours, uint8_T
                   *FSM_Park_Y_minutes)
{
  DW_FSM_Park_T *FSM_Park_DW = ((DW_FSM_Park_T *) FSM_Park_M->dwork);
  PrevZCX_FSM_Park_T *FSM_Park_PrevZCX = ((PrevZCX_FSM_Park_T *)
    FSM_Park_M->prevZCSigState);
  int32_T sfEvent;
  boolean_T zcEvent_idx_0;
  boolean_T zcEvent_idx_1;

  /* Chart: '<S1>/Chart' incorporates:
   *  TriggerPort: '<S2>/input events'
   */
  /* Inport: '<Root>/ttick' */
  zcEvent_idx_0 = (FSM_Park_U_ttick && (FSM_Park_PrevZCX->Chart_Trig_ZCE[0] !=
    POS_ZCSIG));

  /* Inport: '<Root>/BAccept' */
  zcEvent_idx_1 = (FSM_Park_U_BAccept && (FSM_Park_PrevZCX->Chart_Trig_ZCE[1] !=
    POS_ZCSIG));
  if (zcEvent_idx_0 || zcEvent_idx_1) {
    /* Gateway: FSM_Park/Chart */
    if (zcEvent_idx_0) {
      /* Event: '<S2>:54' */
      sfEvent = FSM_Park_event_ttick;
      FSM_Park_chartstep_c3_FSM_Park(&sfEvent, FSM_Park_U_arrived,
        FSM_Park_Y_free_p, FSM_Park_Y_accept, FSM_Park_Y_hours,
        FSM_Park_Y_minutes, FSM_Park_DW);
    }

    if (zcEvent_idx_1) {
      /* Event: '<S2>:72' */
      sfEvent = FSM_Park_event_BAccept;
      FSM_Park_chartstep_c3_FSM_Park(&sfEvent, FSM_Park_U_arrived,
        FSM_Park_Y_free_p, FSM_Park_Y_accept, FSM_Park_Y_hours,
        FSM_Park_Y_minutes, FSM_Park_DW);
    }
  }

  /* Inport: '<Root>/ttick' */
  FSM_Park_PrevZCX->Chart_Trig_ZCE[0] = FSM_Park_U_ttick;

  /* Inport: '<Root>/BAccept' */
  FSM_Park_PrevZCX->Chart_Trig_ZCE[1] = FSM_Park_U_BAccept;
}

/* Model initialize function */
void FSM_Park_initialize(RT_MODEL_FSM_Park_T *const FSM_Park_M, boolean_T
  *FSM_Park_U_ttick, boolean_T *FSM_Park_U_BAccept, boolean_T
  *FSM_Park_U_arrived, boolean_T *FSM_Park_Y_free_p, boolean_T
  *FSM_Park_Y_accept, uint8_T *FSM_Park_Y_hours, uint8_T *FSM_Park_Y_minutes)
{
  DW_FSM_Park_T *FSM_Park_DW = ((DW_FSM_Park_T *) FSM_Park_M->dwork);
  PrevZCX_FSM_Park_T *FSM_Park_PrevZCX = ((PrevZCX_FSM_Park_T *)
    FSM_Park_M->prevZCSigState);

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)FSM_Park_DW, 0,
                sizeof(DW_FSM_Park_T));

  /* external inputs */
  *FSM_Park_U_ttick = false;
  *FSM_Park_U_BAccept = false;
  *FSM_Park_U_arrived = false;

  /* external outputs */
  (*FSM_Park_Y_free_p) = false;
  (*FSM_Park_Y_accept) = false;
  (*FSM_Park_Y_hours) = 0U;
  (*FSM_Park_Y_minutes) = 0U;
  FSM_Park_PrevZCX->Chart_Trig_ZCE[0] = POS_ZCSIG;
  FSM_Park_PrevZCX->Chart_Trig_ZCE[1] = POS_ZCSIG;

  /* SystemInitialize for Outport: '<Root>/free' incorporates:
   *  SystemInitialize for Chart: '<S1>/Chart'
   */
  /* Entry: FSM_Park/Chart */
  /* Entry Internal: FSM_Park/Chart */
  /* Entry Internal 'control': '<S2>:3' */
  /* Transition: '<S2>:63' */
  /* '<S2>:63:1' free = true; */
  *FSM_Park_Y_free_p = true;

  /* SystemInitialize for Outport: '<Root>/accept' incorporates:
   *  SystemInitialize for Chart: '<S1>/Chart'
   */
  /* '<S2>:63:1' accept = false */
  *FSM_Park_Y_accept = false;

  /* SystemInitialize for Chart: '<S1>/Chart' */
  FSM_Park_DW->is_control = FSM_Park_IN_Free;

  /* SystemInitialize for Outport: '<Root>/hours' incorporates:
   *  SystemInitialize for Chart: '<S1>/Chart'
   */
  /* Entry Internal 'time': '<S2>:20' */
  /* Transition: '<S2>:30' */
  /* '<S2>:30:1' hours=uint8(0); */
  *FSM_Park_Y_hours = 0U;

  /* SystemInitialize for Outport: '<Root>/minutes' incorporates:
   *  SystemInitialize for Chart: '<S1>/Chart'
   */
  /* '<S2>:30:1' minutes=uint8(0); */
  *FSM_Park_Y_minutes = 0U;
}

/* Model terminate function */
void FSM_Park_terminate(RT_MODEL_FSM_Park_T *const FSM_Park_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FSM_Park_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
