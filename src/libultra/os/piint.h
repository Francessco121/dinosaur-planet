#ifndef _LIBULTRA_PIINT_H
#define _LIBULTRA_PIINT_H
#include <PR/os.h>

extern OSDevMgr __osPiDevMgr;

OSMesgQueue *osPiGetCmdQueue(void);

#endif
