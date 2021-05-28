#ifndef _LIBULTRA_OSINT_H
#define _LIBULTRA_OSINT_H
#include <PR/ultratypes.h>
#include <PR/os.h>

extern struct __osThreadTail
{
    OSThread *next;
    OSPri priority;
} __osThreadTail;

extern void __osDequeueThread(OSThread **, OSThread *);
extern void __osDispatchThread(void);

extern OSThread *__osRunningThread;
extern OSThread *__osActiveQueue;

extern s32 osViClock;
extern s32 __osAiDeviceBusy(void);

#endif
