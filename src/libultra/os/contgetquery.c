#include "PR/os_internal.h"
#include "common.h"

//from: http://en64.shoutwiki.com/wiki/SI_Registers_Detailed#CONT_CMD_Usage
#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_READ_BUTTON 1
#define CONT_CMD_READ_MEMPACK 2
#define CONT_CMD_WRITE_MEMPACK 3
#define CONT_CMD_READ_EEPROM 4
#define CONT_CMD_WRITE_EEPROM 5
#define CONT_CMD_RESET 0xff

typedef struct
{
    /* 0x0 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam;

extern u8 __osContLastCmd;
extern OSPifRam __osContPifRam;

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/os/contgetquery/osContStartQuery.s")
#else
void __osSiGetAccess(void);
void __osSiRelAccess(void);
void __osPackRequestData(u8 cmd);

s32 osContStartQuery(OSMesgQueue *mq)
{
    s32 ret;
    ret = 0;

    __osSiGetAccess();
    if (__osContLastCmd != CONT_CMD_REQUEST_STATUS)
    {
        __osPackRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }
    ret = __osSiRawStartDma(OS_READ, &__osContPifRam);
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
    __osSiRelAccess();
    return ret;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/os/contgetquery/osContGetQuery.s")
#else
void __osContGetInitData(u8 *pattern, OSContStatus *data);

void osContGetQuery(OSContStatus *data) {
    u8 pattern;
    __osContGetInitData(&pattern, data);
}
#endif
