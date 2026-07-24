/*
 * File: xil_interface.c
 *
 * PIL generated interface for code: "control"
 *
 */

#include <stddef.h>
#include "control.h"
#include "control_private.h"
#include "xil_interface.h"
#include "xil_instrumentation.h"

/* Functions with a C call interface */
#ifdef __cplusplus

extern "C"
{

#endif

#include "xil_data_stream.h"
#include "codeinstr_data_stream.h"
#ifdef __cplusplus

}

#endif

#include <string.h>

/* interface data */
real_T i_Vz;

/* interface data */
real_T i_h;

/* interface data */
boolean_T i_logic;

/* interface data */
real_T i_pitch;

/* interface data */
real_T o_Out1;

/* interface data */
real_T rtP_C_b[26];

/* interface data */
real_T rtP_Cdr_off[370];

/* interface data */
real_T rtP_M_b[26];

/* interface data */
real_T rtP_M_off[370];

#define mdlref_TID0                    0
#define mdlref_TID1                    1

/* initialize error status as a null pointer */
static const char_T * rt_errorStatus_tgt_var = ((const char_T *) 0);
static const char_T ** rt_errorStatus = &rt_errorStatus_tgt_var;

/* define timingBridge */
static rtTimingBridge timingBridge_tgt_var;
static const rtTimingBridge * timingBridge = &timingBridge_tgt_var;

/* define Timing structure */
static struct {
  struct {
    uint32_T TID[2];
  } TaskCounters;

  struct {
    boolean_T TID0_1;
  } RateInteraction;
} XILTimingData;

static uint32_T InitialTaskCounterOffset[2];

/* XILFirstInitCond will be updated by xilInitialize and xilSystemInitialize */
static boolean_T XILFirstInitCond = 0;

/* interface data */
MdlrefDW_control_T control_MdlrefDW;

/* interface (pointer) data */
RT_MODEL_control_T * RTModel_ptr = &(control_MdlrefDW.rtm);
static XILIOData xil_fcnid0_task1_output_u[5];
static XILIOData xil_fcnid0_task1_y[2];
static XILIOData xil_fcnid0_task1_s[4];
static XILIOData xil_fcnid0_init_u[3];
static XILIOData xil_fcnid0_init_y[2];
static XILIOData xil_fcnid0_ws_params[5];
static XILIOData xil_fcnid0_disable_y[2];
static XILIOData xil_fcnid0_system_initialize_y[2];

/* In-the-Loop Interface functions - see xil_interface.h */
XIL_INTERFACE_ERROR_CODE xilProcessParams(uint32_T xilFcnId)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return XIL_INTERFACE_SUCCESS;
}

void xilUploadCodeInstrData(void * pData, uint32_T numMemUnits, uint32_T
  sectionId)
{
  /* Send code instrumentation data to host */
  if (codeInstrWriteData((MemUnit_T *) &numMemUnits, sizeof(numMemUnits)) !=
      XIL_DATA_STREAM_SUCCESS) {
    for (;;) ;
  }

  if (codeInstrWriteData((MemUnit_T *) &sectionId, sizeof(uint32_T)) !=
      XIL_DATA_STREAM_SUCCESS) {
    for (;;) ;
  }

  if (codeInstrWriteData((MemUnit_T *) pData, numMemUnits) !=
      XIL_DATA_STREAM_SUCCESS) {
    for (;;) ;
  }
}

XIL_INTERFACE_ERROR_CODE xilGetDataTypeInfo(void)
{
  {
    /* send response id code */
    MemUnit_T memUnitData = XIL_RESPONSE_TYPE_SIZE;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* send type id */
    memUnitData = 0;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* PIL_DOUBLE_SIZE should only be already defined for MathWorks testing */
#ifndef PIL_DOUBLE_SIZE
#define PIL_DOUBLE_SIZE                sizeof(double)
#endif

    /* send size in bytes */
    memUnitData = (MemUnit_T) PIL_DOUBLE_SIZE;

#ifndef HOST_WORD_ADDRESSABLE_TESTING

    /* convert MemUnits to bytes */
    memUnitData *= MEM_UNIT_BYTES;

#endif

    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilInitialize(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* initialize XILTimingData */
  (void) memset((void *) &XILTimingData, 0, sizeof(XILTimingData));

  {
    memcpy(XILTimingData.TaskCounters.TID, InitialTaskCounterOffset, sizeof
           (InitialTaskCounterOffset));
    static uint32_T *taskCounterPtrs;
    static boolean_T *rateTransitionPtrs[(2 * 2)];
    taskCounterPtrs = &(XILTimingData.TaskCounters.TID[0]);
    timingBridge_tgt_var.taskCounter = taskCounterPtrs;
    rateTransitionPtrs[0*2 + 1] = &(XILTimingData.RateInteraction.TID0_1);
    timingBridge_tgt_var.rateTransition = rateTransitionPtrs;
    timingBridge_tgt_var.clockTick = (uint32_T **) 0;
    timingBridge_tgt_var.clockTickH = (uint32_T **) 0;
    timingBridge_tgt_var.nTasks = 2;
  }

  timingBridge_tgt_var.firstInitCond = &XILFirstInitCond;

  /* firstInitCond should be true until after the first InitCond call */
  XILFirstInitCond = 1;

  {
  }

  /* initialize output storage owned by In-the-Loop */
  {
    o_Out1 = 0;
  }

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    /* Call all Set class methods */
    taskTimeStart_control(1U);
    control_initialize(rt_errorStatus, timingBridge, mdlref_TID0, mdlref_TID1,
                       RTModel_ptr);
    taskTimeEnd_control(1U);

    /* Call all Get class methods */
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilPause(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
  if (xilFcnId == 0) {
    /* Nothing to do */
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }                                    /* if */

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilSystemInitialize(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    taskTimeStart_control(2U);
    control_Init(&(control_MdlrefDW.rtb), &(control_MdlrefDW.rtdw));
    taskTimeEnd_control(2U);
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  /* firstInitCond should be false after the first InitCond call */
  XILFirstInitCond = 0;
  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilSystemReset(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    /* No Function to Call */
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilGetHostToTargetData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
  *xilIOData = 0;

  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }

  switch (xilCommandType) {
   case XIL_INITIALIZE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(InitialTaskCounterOffset[0]);
          xil_fcnid0_init_u[tableIdx].memUnitLength = 1 * sizeof(uint32_T);
          xil_fcnid0_init_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InitialTaskCounterOffset[1]);
          xil_fcnid0_init_u[tableIdx].memUnitLength = 1 * sizeof(uint32_T);
          xil_fcnid0_init_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_init_u[tableIdx].memUnitLength = 0;
        xil_fcnid0_init_u[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }                                /* if */

      *xilIOData = &xil_fcnid0_init_u[0];
      break;
    }

   case XIL_PROCESS_PARAMS_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(rtP_C_b[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 26 * sizeof(real_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(rtP_Cdr_off[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 370 * sizeof(real_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(rtP_M_b[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 26 * sizeof(real_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(rtP_M_off[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 370 * sizeof(real_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_ws_params[tableIdx].memUnitLength = 0;
        xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }                                /* if */

      *xilIOData = &xil_fcnid0_ws_params[0];
      break;
    }

   case XIL_OUTPUT_COMMAND:
    {
      switch (xilCommandIdx) {
       case 1:
        {
          static int initComplete = 0;
          if (!initComplete) {
            uint32_T tableIdx = 0;

            {
              void * dataAddress = (void *) &(i_Vz);
              xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
                (real_T);
              xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
                dataAddress;
            }

            {
              void * dataAddress = (void *) &(i_h);
              xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
                (real_T);
              xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
                dataAddress;
            }

            {
              void * dataAddress = (void *) &(i_logic);
              xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
                (boolean_T);
              xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
                dataAddress;
            }

            {
              void * dataAddress = (void *) &(i_pitch);
              xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
                (real_T);
              xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
                dataAddress;
            }

            xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 0;
            xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *) 0;
            initComplete = 1;
          }                            /* if */

          *xilIOData = &xil_fcnid0_task1_output_u[0];
          break;
        }

       default:
        errorCode = XIL_INTERFACE_UNKNOWN_TID;
        break;
      }
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilGetTargetToHostPreData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData, MemUnit_T responseId, uint32_T serverFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
  *xilIOData = 0;
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }                                    /* if */

  switch (xilCommandType) {
   case XIL_OUTPUT_COMMAND:
    {
      switch (xilCommandIdx) {
       case 1:
        {
          static int initComplete = 0;
          if (!initComplete) {
            uint32_T tableIdx = 0;

            {
              /* State Logging address access: DSTATE */
              void * dataAddress = (void*)(&control_MdlrefDW.rtdw.Delay_DSTATE);
              xil_fcnid0_task1_s[tableIdx].memUnitLength = 4 * sizeof(real_T);
              xil_fcnid0_task1_s[tableIdx++].address = (MemUnit_T *) dataAddress;
            }

            {
              /* State Logging address access: DSTATE */
              void * dataAddress = (void*)(&control_MdlrefDW.rtdw.Delay1_DSTATE);
              xil_fcnid0_task1_s[tableIdx].memUnitLength = 2 * sizeof(real_T);
              xil_fcnid0_task1_s[tableIdx++].address = (MemUnit_T *) dataAddress;
            }

            {
              /* State Logging address access: DSTATE */
              void * dataAddress = (void*)(&control_MdlrefDW.rtdw.Delay2_DSTATE);
              xil_fcnid0_task1_s[tableIdx].memUnitLength = 2 * sizeof(real_T);
              xil_fcnid0_task1_s[tableIdx++].address = (MemUnit_T *) dataAddress;
            }

            xil_fcnid0_task1_s[tableIdx].memUnitLength = 0;
            xil_fcnid0_task1_s[tableIdx++].address = (MemUnit_T *) 0;
            initComplete = 1;
          }                            /* if */

          {
            if (xilWriteData(&responseId, sizeof(responseId)) !=
                XIL_DATA_STREAM_SUCCESS) {
              return XIL_INTERFACE_COMMS_FAILURE;
            }                          /* if */

            if (responseId == XIL_RESPONSE_CS_REQUEST_SERVICE) {
              if (xilWriteData((MemUnit_T *) &serverFcnId, sizeof(serverFcnId))
                  != XIL_DATA_STREAM_SUCCESS) {
                return XIL_INTERFACE_COMMS_FAILURE;
              }                        /* if */
            }                          /* if */
          }

          *xilIOData = &xil_fcnid0_task1_s[0];
          break;
        }

       default:
        errorCode = XIL_INTERFACE_UNKNOWN_TID;
        break;
      }
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  return errorCode;
}

static void rate_scheduler(void)
{
  /* To ensure a safe and deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid(s) */
  /* slow tid: 1 */
  XILTimingData.RateInteraction.TID0_1 =
    (XILTimingData.TaskCounters.TID[1] == 0);

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */

  /* sample time: [0.02s, 0s] */
  if (++XILTimingData.TaskCounters.TID[1] == 20) {
    XILTimingData.TaskCounters.TID[1] = 0;
  }
}

XIL_INTERFACE_ERROR_CODE xilOutput(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  switch (xilTID) {
   case 1:
    /* Call all Set class methods */
    taskTimeStart_control(3U);

    /* call scheduler */
    rate_scheduler();
    controlTID0(RTModel_ptr, &(i_Vz), &(i_h), &(i_logic), &(i_pitch), &(o_Out1),
                &(control_MdlrefDW.rtb), &(control_MdlrefDW.rtdw));
    taskTimeEnd_control(3U);

    /* Call all Get class methods */
    break;

   case 2:
    /* Call all Set class methods */
    taskTimeStart_control(4U);
    controlTID1(&(control_MdlrefDW.rtb), &(control_MdlrefDW.rtdw));
    taskTimeEnd_control(4U);

    /* Call all Get class methods */
    break;

   default:
    return XIL_INTERFACE_UNKNOWN_TID;
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilUpdate(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  /* No Update Function */
  UNUSED_PARAMETER(xilTID);
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilGetTargetToHostData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData, MemUnit_T responseId, uint32_T serverFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  *xilIOData = 0;
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }

  switch (xilCommandType) {
   case XIL_INITIALIZE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(o_Out1);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_init_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }                                /* if */

      {
        if (xilWriteData(&responseId, sizeof(responseId)) !=
            XIL_DATA_STREAM_SUCCESS) {
          return XIL_INTERFACE_COMMS_FAILURE;
        }                              /* if */

        if (responseId == XIL_RESPONSE_CS_REQUEST_SERVICE) {
          if (xilWriteData((MemUnit_T *) &serverFcnId, sizeof(serverFcnId)) !=
              XIL_DATA_STREAM_SUCCESS) {
            return XIL_INTERFACE_COMMS_FAILURE;
          }                            /* if */
        }                              /* if */
      }

      *xilIOData = &xil_fcnid0_init_y[0];
      break;
    }

   case XIL_OUTPUT_COMMAND:
    {
      switch (xilCommandIdx) {
       case 1:
        {
          static int initComplete = 0;
          if (!initComplete) {
            uint32_T tableIdx = 0;

            {
              void * dataAddress = (void *) &(o_Out1);
              xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real_T);
              xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
            }

            xil_fcnid0_task1_y[tableIdx].memUnitLength = 0;
            xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) 0;
            initComplete = 1;
          }                            /* if */

          {
            if (xilWriteData(&responseId, sizeof(responseId)) !=
                XIL_DATA_STREAM_SUCCESS) {
              return XIL_INTERFACE_COMMS_FAILURE;
            }                          /* if */

            if (responseId == XIL_RESPONSE_CS_REQUEST_SERVICE) {
              if (xilWriteData((MemUnit_T *) &serverFcnId, sizeof(serverFcnId))
                  != XIL_DATA_STREAM_SUCCESS) {
                return XIL_INTERFACE_COMMS_FAILURE;
              }                        /* if */
            }                          /* if */
          }

          *xilIOData = &xil_fcnid0_task1_y[0];
          break;
        }

       default:
        errorCode = XIL_INTERFACE_UNKNOWN_TID;
        break;
      }
      break;
    }

   case XIL_DISABLE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(o_Out1);
          xil_fcnid0_disable_y[tableIdx].memUnitLength = 1 * sizeof(real_T);
          xil_fcnid0_disable_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_disable_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_disable_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }                                /* if */

      {
        if (xilWriteData(&responseId, sizeof(responseId)) !=
            XIL_DATA_STREAM_SUCCESS) {
          return XIL_INTERFACE_COMMS_FAILURE;
        }                              /* if */

        if (responseId == XIL_RESPONSE_CS_REQUEST_SERVICE) {
          if (xilWriteData((MemUnit_T *) &serverFcnId, sizeof(serverFcnId)) !=
              XIL_DATA_STREAM_SUCCESS) {
            return XIL_INTERFACE_COMMS_FAILURE;
          }                            /* if */
        }                              /* if */
      }

      *xilIOData = &xil_fcnid0_disable_y[0];
      break;
    }

   case XIL_SYSTEM_INITIALIZE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(o_Out1);
          xil_fcnid0_system_initialize_y[tableIdx].memUnitLength = 1 * sizeof
            (real_T);
          xil_fcnid0_system_initialize_y[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        xil_fcnid0_system_initialize_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_system_initialize_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }                                /* if */

      {
        if (xilWriteData(&responseId, sizeof(responseId)) !=
            XIL_DATA_STREAM_SUCCESS) {
          return XIL_INTERFACE_COMMS_FAILURE;
        }                              /* if */

        if (responseId == XIL_RESPONSE_CS_REQUEST_SERVICE) {
          if (xilWriteData((MemUnit_T *) &serverFcnId, sizeof(serverFcnId)) !=
              XIL_DATA_STREAM_SUCCESS) {
            return XIL_INTERFACE_COMMS_FAILURE;
          }                            /* if */
        }                              /* if */
      }

      *xilIOData = &xil_fcnid0_system_initialize_y[0];
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilTerminate(uint32_T xilFcnId)
{
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }                                    /* if */

  /* Invoke any terminate Function */
  /* No Function to Call */

  /* Free Opaque Region Based Data */
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilInitTargetData(void)
{
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilEnable(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  UNUSED_PARAMETER(xilTID);

  /* No Enable Function - this function should never be called */
  return XIL_INTERFACE_UNKNOWN_TID;
}

XIL_INTERFACE_ERROR_CODE xilDisable(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  switch (xilTID) {
   case 0:
    taskTimeStart_control(5U);
    control_Disable(&(control_MdlrefDW.rtdw));
    taskTimeEnd_control(5U);
    break;

   default:
    return XIL_INTERFACE_UNKNOWN_TID;
  }

  return XIL_INTERFACE_SUCCESS;
}
