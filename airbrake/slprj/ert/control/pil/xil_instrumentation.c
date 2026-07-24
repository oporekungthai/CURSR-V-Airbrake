/*
 * File: xil_instrumentation.c
 *
 * Code generated for instrumentation.
 *
 */

#include "xil_instrumentation.h"

/* Code instrumentation offset(s) for model control */
#define profileStart_control_offset    5
#define profileEnd_control_offset      5

/* Code instrumentation offset(s) for model control */
#define taskTimeStart_control_offset   0
#define taskTimeEnd_control_offset     0

/* A function parameter may be intentionally unused */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)
# else
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

#define SIZEOF_TIMER_TYPE              sizeof(uint32_T)

static uint32_T xsd_xil_timer_corrected = 0;
static uint32_T xsd_xil_timer_unfreeze = 0;
static uint32_T xsd_xil_freezing_busy = 0;
void xilUploadProfilingData(uint32_T sectionId)
{
  xilUploadCodeInstrData((void *)(&xsd_xil_timer_corrected), (uint32_T)
    (SIZEOF_TIMER_TYPE), sectionId);
}

/* The internal freeze and unfreeze methods cannot be nested.
 * The customer-visible implementation avoids nesting problems.
 * Update the value of the corrected timer to exclude time
 * spent in the instrumentation code
 */
#define xilProfilingTimerFreezeInternal() { \
 xsd_xil_timer_corrected = xsd_xil_timer_corrected + (((uint32_T)(profileTimerRead())) - xsd_xil_timer_unfreeze); \
}
#define xilProfilingTimerUnFreezeInternal() { \
 xsd_xil_timer_unfreeze = (uint32_T) (profileTimerRead()); \
}

void xilProfilingTimerFreeze(void)
{
  if (xsd_xil_freezing_busy == 0) {
    xilProfilingTimerFreezeInternal();
  }                                    /* if */
}

void xilProfilingTimerUnFreeze(void)
{
  if (xsd_xil_freezing_busy == 0) {
    xilProfilingTimerUnFreezeInternal();
  }                                    /* if */
}

/* Tic/Toc methods for task profiling */
#define taskTimeStart(id)              { \
 xilUploadProfilingData(id); \
 xilProfilingTimerUnFreezeInternal(); \
}
#define taskTimeEnd(id)                { \
 uint32_T sectionIdNeg = id; \
 sectionIdNeg = ~sectionIdNeg; \
 xilProfilingTimerFreezeInternal(); \
 xilUploadProfilingData(sectionIdNeg); \
}

/* Tic/Toc methods for function profiling */
#define profileStart(id)               { \
 xilProfilingTimerFreezeInternal(); \
 xilUploadProfilingData(id); \
 xilProfilingTimerUnFreezeInternal(); \
}
#define profileEnd(id)                 { \
 uint32_T sectionIdNeg = id; \
 sectionIdNeg = ~sectionIdNeg; \
 xilProfilingTimerFreezeInternal(); \
 xilUploadProfilingData(sectionIdNeg); \
 xilProfilingTimerUnFreezeInternal(); \
}

/* Code instrumentation method(s) for model control */
void profileStart_control(uint32_T sectionId)
{
  profileStart(profileStart_control_offset + sectionId);
}

void profileEnd_control(uint32_T sectionId)
{
  profileEnd(profileEnd_control_offset + sectionId);
}

/* Code instrumentation method(s) for model control */
void taskTimeStart_control(uint32_T sectionId)
{
  taskTimeStart(taskTimeStart_control_offset + sectionId);
}

void taskTimeEnd_control(uint32_T sectionId)
{
  taskTimeEnd(taskTimeEnd_control_offset + sectionId);
}
