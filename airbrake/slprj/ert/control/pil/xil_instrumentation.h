/*
 * File: xil_instrumentation.h
 *
 * Code generated for instrumentation.
 *
 */

/* Functions with a C call interface */
#ifdef __cplusplus

extern "C"
{

#endif

#include "profiler_timer.h"
#ifdef __cplusplus

}

#endif

#include "rtwtypes.h"

/* Upload code instrumentation data point */
void xilUploadCodeInstrData(
  void* pData, uint32_T numMemUnits, uint32_T sectionId);

/* Uploads data */
void xilUploadProfilingData(uint32_T sectionId);

/* Pause/restart the timer while running code associated with storing and uploading the data. */
void xilProfilingTimerFreeze(void);
void xilProfilingTimerUnFreeze(void);

/* Code instrumentation method(s) for model control */
void profileStart_control(uint32_T sectionId);
void profileEnd_control(uint32_T sectionId);

/* Code instrumentation method(s) for model control */
void taskTimeStart_control(uint32_T sectionId);
void taskTimeEnd_control(uint32_T sectionId);
