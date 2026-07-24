/*
 * File: code_profiling_utility_functions.c
 *
 * Code generated for instrumentation.
 *
 */

#include "code_profiling_utility_functions.h"

/* Code instrumentation offset(s) for model control */
#define taskTimeStart_control_offset   0
#define taskTimeEnd_control_offset     0

/* Code instrumentation offset(s) for model control */
#define profileStart_control_offset    4
#define profileEnd_control_offset      4

/* A function parameter may be intentionally unused */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)
# else
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

void xilUploadProfilingData(uint32_T sectionId)
{
  code_profiling_atomic_read_store(sectionId);
}

/* For real-time, multitasking case this function is stubbed out. */
#define xilProfilingTimerFreezeInternal() {}

void xilProfilingTimerFreeze(void)
{
}

#define xilProfilingTimerUnFreezeInternal() {}

void xilProfilingTimerUnFreeze(void)
{
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
void taskTimeStart_control(uint32_T sectionId)
{
  taskTimeStart(taskTimeStart_control_offset + sectionId);
}

void taskTimeEnd_control(uint32_T sectionId)
{
  taskTimeEnd(taskTimeEnd_control_offset + sectionId);
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
