#ifndef _LIBULTRA_CONTROLLER_H
#define _LIBULTRA_CONTROLLER_H
#include <PR/os_internal.h>
#include <PR/rcp.h>

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof(x[0])))
#define CHNL_ERR(format) ((format.rxsize & CHNL_ERR_MASK) >> 4)

typedef struct
{
    /* 0x0 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam;

typedef struct
{
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u8 typeh;
    /* 0x5 */ u8 typel;
    /* 0x6 */ u8 status;
    /* 0x7 */ u8 dummy1;
} __OSContRequesFormat;

//from: http://en64.shoutwiki.com/wiki/SI_Registers_Detailed#CONT_CMD_Usage
#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_READ_BUTTON 1
#define CONT_CMD_READ_MEMPACK 2
#define CONT_CMD_WRITE_MEMPACK 3
#define CONT_CMD_READ_EEPROM 4
#define CONT_CMD_WRITE_EEPROM 5
#define CONT_CMD_RESET 0xff

#define CONT_CMD_REQUEST_STATUS_TX 1
#define CONT_CMD_READ_BUTTON_TX 1
#define CONT_CMD_READ_MEMPACK_TX 3
#define CONT_CMD_WRITE_MEMPACK_TX 35
#define CONT_CMD_READ_EEPROM_TX 2
#define CONT_CMD_WRITE_EEPROM_TX 10
#define CONT_CMD_RESET_TX 1

#define CONT_CMD_REQUEST_STATUS_RX 3
#define CONT_CMD_READ_BUTTON_RX 4
#define CONT_CMD_READ_MEMPACK_RX 33
#define CONT_CMD_WRITE_MEMPACK_RX 1
#define CONT_CMD_READ_EEPROM_RX 8
#define CONT_CMD_WRITE_EEPROM_RX 1
#define CONT_CMD_RESET_RX 3

#define CONT_CMD_NOP 0xff
#define CONT_CMD_END 0xfe //indicates end of a command
#define CONT_CMD_EXE 1    //set pif ram status byte to this to do a command

extern u8 __osContLastCmd;
extern OSPifRam __osContPifRam;

void __osContGetInitData(u8 *pattern, OSContStatus *data);
void __osPackRequestData(u8 cmd);
#endif
