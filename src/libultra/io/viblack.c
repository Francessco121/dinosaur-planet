// @DECOMP_OPT_FLAGS=-O1
#include <PR/os_internal.h>
#include "libultra/io/viint.h"

void osViBlack(u8 active)
{
    register u32 saveMask = __osDisableInt();
    if (active)
        __osViNext->state |= VI_STATE_BLACK;
    else
        __osViNext->state &= ~VI_STATE_BLACK;
    __osRestoreInt(saveMask);
}
