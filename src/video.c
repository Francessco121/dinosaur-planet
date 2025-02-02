#include "common.h"

UnkHeapVidStruct *D_800BCC10;
UnkVidStruct2 D_800BCC18[4]; // size:0x50

// func_8005BC38 is from segment_5C470
/**
 * If param1 isn't null, sets it to gPossiblyScreenWidthOrHeight.
 *
 * Returns gSomeVideoFlag.
 */
int func_8005BC38(u32*);
void func_8005D9D8();
void set_video_mode(s32 mode);
void initialize_framebuffers(int someBool, s32 width, s32 height);
void swap_framebuffer_pointers();
void set_custom_vi_mode();

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005C780.s")
#else
void func_8005C780() {
    s32 i;

    if (D_800BCC10 != NULL) {
        free(D_800BCC10);
    }

    D_800BCC10 = malloc(UNKNOWN_HEAP_VIDEO_STRUCT_SIZE, 0x13, 0);

    for (i = 0; i < UNKNOWN_VIDEO_STRUCTS_COUNT; i++)
    {
        gSPEndDisplayList(&gUnknownVideoStructs[i].dl);
        gUnknownVideoStructs[i].viMode = NULL;
        gUnknownVideoStructs[i].unk0x88 = 0;
    }

    for (i = 0; i < 4; i++)
    {
        D_800BCC18[i].unk0x10 = NULL;
        D_800BCC18[i].unk0x0 = 0;
        D_800BCC18[i].unk0x4 = 0;
        D_800BCC18[i].unk0x8 = 0;
        D_800BCC18[i].unk0xc = 0;
    }

    D_800BCC10->unk0x0 = -3.0f;
    D_800BCC10->unk0x4 = 0.0f;
    D_800BCC10->unk0x8 = -3.0f;
    D_800BCC10->unk0xc = -3.0f;
    D_800BCC10->unk0x10 = 0.0f;
    D_800BCC10->unk0x14 = 3.0f;
    
    D_800BCC10->unk0x18 = 3.0f;
    D_800BCC10->unk0x1c = 0.0f;
    D_800BCC10->unk0x20 = 3.0f;
    D_800BCC10->unk0x24 = 3.0f;
    D_800BCC10->unk0x28 = 0.0f;
    D_800BCC10->unk0x2c = -3.0f;
    
    D_800BCC10->unk0x30 = -3.0f;
    D_800BCC10->unk0x34 = 0.0f;
    D_800BCC10->unk0x38 = -3.0f;
    D_800BCC10->unk0x3c = -3.0f;
    D_800BCC10->unk0x40 = 0.0f;
    D_800BCC10->unk0x44 = 3.0f;
    
    D_800BCC10->unk0x48 = 3.0f;
    D_800BCC10->unk0x4c = 0.0f;
    D_800BCC10->unk0x50 = 3.0f;
    D_800BCC10->unk0x54 = 3.0f;
    D_800BCC10->unk0x58 = 0.0f;
    D_800BCC10->unk0x5c = -3.0f;

    D_800BCC68 = queue_load_texture_proxy(0x18);
    D_800BCC6C = queue_load_texture_proxy(0x19);
    D_800BCC70 = queue_load_texture_proxy(0x1a);

    D_800BCC78 = (u8)0;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005C998.s")
void func_8005C998();
#else
void func_8005C998() {
    s32 i;

    for (i = 0; i < UNKNOWN_VIDEO_STRUCTS_COUNT; i++) {
        gSPEndDisplayList(&gUnknownVideoStructs[i].dl);
        gUnknownVideoStructs[i].viMode = NULL;
        gUnknownVideoStructs[i].unk0x88 = 0;
    }

    for (i = 0; i < 4; i++) {
        D_800BCC18[i].unk0x10 = 0;
        D_800BCC18[i].unk0x0 = 0.0f;
        D_800BCC18[i].unk0x4 = 0.0f;
        D_800BCC18[i].unk0x8 = 0.0f;
        D_800BCC18[i].unk0xc = 0;
    }
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CA5C.s")
#else
void func_8005CA5C(u32 param1) {
    D_800BCC78 = param1;

    if (param1 == 0) {
        func_8005C998();
    }
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CA88.s")
#else
void func_8005CA88(f32 *a0, f32 *a1, u8 a2) {
    static s32 D_80092FF8 = 0;

    if (D_800BCC78 != 0) {
        D_800BCC18[D_80092FF8].unk0x10 = a0;
        D_800BCC18[D_80092FF8].unk0x0 = a1[0];
        D_800BCC18[D_80092FF8].unk0x4 = a0[4] + a1[1];
        D_800BCC18[D_80092FF8].unk0x8 = a1[2];
        D_800BCC18[D_80092FF8].unk0xc = a2;

        D_80092FF8 = D_80092FF8 + 1;

        if (D_80092FF8 == 4) {
            D_80092FF8 = 0;
        }
    }
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CB10.s")
#else
void func_8005CB10(Gfx **gdl, UnkVidStruct4 *param2) {
    s32 i;
    Texture *tex;

    switch (param2->unk0x46) {
        case 0:
            tex = D_800BCC68;
            break;
        case 0x1f:
            tex = D_800BCC6C;
            break;
        default:
            tex = D_800BCC68;
            break;
    }

    set_textures_on_gdl(gdl, tex, NULL, 0x1a, 0, 0, 1);

    i = 0;

    while (i < UNKNOWN_VIDEO_STRUCTS_COUNT) {
        if (param2 == gUnknownVideoStructs[i].unk0x80) {
            gSPDisplayList((*gdl)++, &gUnknownVideoStructs[i].dl);
        }

        i++;
    }
}
#endif

static s32 D_80092FFC = 1;
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CC74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CD80.s")

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CDFC.s")
#else
// Functionally equivalent, mainly regalloc, see TODO
void func_8005CDFC(int _) {
    float var1;
    float var2;
    s16 *var3;
    s32 i;

    for (i = 0; i < UNKNOWN_VIDEO_STRUCTS_COUNT; i++) {
        if (gUnknownVideoStructs[i].viMode == NULL) {
            continue;
        }

        // TODO: The order of loads and stores here are slightly out of order
        var1 = gWorldX - gUnknownVideoStructs[i].unk0x78;
        var2 = gWorldZ - gUnknownVideoStructs[i].unk0x7c;

        var3 = &gUnknownVideoStructs[i].unk0x48[0];

        gUnknownVideoStructs[i].unk0x78 += var1;
        gUnknownVideoStructs[i].unk0x7c += var2;
        
        gUnknownVideoStructs[i].unk0x18 -= var1;
        gUnknownVideoStructs[i].unk0x1c -= var2;
        gUnknownVideoStructs[i].unk0x28 -= var1;
        gUnknownVideoStructs[i].unk0x2c -= var2;
        gUnknownVideoStructs[i].unk0x38 -= var1;
        gUnknownVideoStructs[i].unk0x3c -= var2;

        var3[2] = var3[2] - var2;
        var3[0] = var3[0] - var1;
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005CF4C.s")

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005D3A4.s")
#else
// Note: Return type is void* because the real type is unclear
void *func_8005D3A4(int param) {
    switch (param) {
        case 1:
            return &D_80092EC4;
        case 2:
            return &D_80092F0C;
        case 3:
            return &D_80092F54;
        case 4:
            return &D_80092F9C;
        case 5:
            return &D_80092FE4;  
        case 0:
        default:
            return &D_80092F54;
    } 
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005D410.s")
#else
void func_8005D410(s32 videoMode, OSSched* scheduler, s32 someBool) {
    int i;
    u32 width;
    u32 height;
    
    if (osTvType == OS_TV_PAL) {
        gDisplayHertz = 50;
        aspectRatioFloat = gPalAspectRatio;
        D_800BCCB8 = D_8009AD68;
    } else if (osTvType == OS_TV_MPAL) {
        gDisplayHertz = 60;
        aspectRatioFloat = gMPalAspectRatio;
        D_800BCCB8 = 1.0f;
    } else {
        gDisplayHertz = 60;
        aspectRatioFloat = gNtscAspectRatio;
        D_800BCCB8 = 1.0f;
    }

    if (someBool && osTvType == OS_TV_PAL) {
        for (i = 0; i < VIDEO_RESOLUTIONS_COUNT; i++) {
            gResolutionArray[i].v += 20;
        }
    }

    func_8005D9D8();

    set_video_mode(videoMode);

    gFramebufferPointers[0] = NULL;
    gFramebufferPointers[1] = NULL;

    if (someBool) {
        osCreateMesgQueue(&OSMesgQueue_800bcce0, &D_800bccc0[0], 8);
        osScAddClient(scheduler, &D_800bce60, &OSMesgQueue_800bcce0, 2);
    }

    width = 320;
    height = 260;

    if (videoMode == OS_VI_PAL_LPN1) {
        width = 640;
        height = 480;
    }

    initialize_framebuffers(someBool, width, height);

    gFramebufferChoice = 1;

    swap_framebuffer_pointers();
    set_custom_vi_mode();

    D_800BCE14 = 0xc;

    osViBlack(TRUE);

    D_800BCE58 = 0;
    D_800BCE2C = 5;

    if (someBool) {
        D_800BCE18[0] = malloc(960, 2, NULL);
        D_800BCE18[1] = &D_800BCE18[0][480];
    }

    bzero(D_800BCE18[0], 960);

    D_800BCE20 = 0;
    D_800BCE22[0] = 0;
    D_800BCE22[1] = 0;
    D_800BCE34 = 1;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/set_video_mode.s")
#else
/**
 * Sets gVideoMode.
 */
void set_video_mode(s32 mode) {
    gVideoMode = mode;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/get_video_mode.s")
#else
/**
 * Returns gVideoMode.
 */
s32 get_video_mode() {
    return gVideoMode;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/get_addr_of_OSMesgQueue_8005D670.s")
#else
OSMesgQueue *get_addr_of_OSMesgQueue_8005D670() {
    return &OSMesgQueue_800bcce0;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/set_current_resolution_from_video_mode.s")
#else
/**
 * Sets gCurrentResolution*[framebufferIndex] to the resolution
 * specified by gVideoMode from gResolutionArray.
 */
void set_current_resolution_from_video_mode(int framebufferIndex) {
    // Note: framebufferIndex was decided on because another function calls this
    //       with gFramebufferChoice (which is either 0 or 1 presumably) and
    //       gCurrentResolutionH and gCurrentResolutionV both conveniently contain
    //       2 integers, which are likely for each framebuffer.
    gCurrentResolutionH[framebufferIndex] = gResolutionArray[gVideoMode & 7].h;
    gCurrentResolutionV[framebufferIndex] = gResolutionArray[gVideoMode & 7].v;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/get_some_resolution_encoded.s")
#else
/**
 * Returns a video resolution encoded as 0xVVVV_HHHH.
 *
 * If the result of func_8005BC38 is 0, then it will be the current framebuffer's resolution.
 */
u32 get_some_resolution_encoded() {
    u32 var1;
    int flag;

    flag = func_8005BC38(&var1);

    if (flag == FALSE) {
        return (gCurrentResolutionV[gFramebufferChoice] << 0x10) |
                gCurrentResolutionH[gFramebufferChoice];
    } else {
        // Turns 0x0000_XXXX into 0xXXXX_XXXX
        //
        // Maybe this is to default to a square resolution?
        // Say, var1 is 480, this encodes the res as 480x480
        return (var1 << 0x10) | var1;
    }
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/get_other_resolution_encoded.s")
#else
/**
 * Returns the resolution of the framebuffer not currently in use encoded as 0xVVVV_HHHH.
 *
 * Note: The resolution is found by gCurrentResolution*[gFramebufferChoice < 1]
 */
u32 get_other_resolution_encoded() {
    return (gCurrentResolutionV[gFramebufferChoice < 1] << 0x10) |
            gCurrentResolutionH[gFramebufferChoice < 1];
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/set_custom_vi_mode.s")
#else
void set_custom_vi_mode() {
    u8 viLpn;
    OSViMode *viMode;

    // Determine VI LPN from TV type
    viLpn = OS_VI_NTSC_LPN1;

    if (osTvType == OS_TV_PAL) {
        viLpn = OS_VI_PAL_LPN1;
    } else if (osTvType == OS_TV_MPAL) {
        viLpn = OS_VI_MPAL_LPN1;
    }

    // Determine VI mode from video mode and VI LPN
    switch (gVideoMode & 0x7) {
        case 0x1:
        default:
            viMode = &osViModeTable[2 + viLpn];
            break;
        case 0x6:
            viMode = &osViModeTable[11 + viLpn];
            break;
    }

    // Set gOSViModeCustom to the chosen VI mode
    bcopy(
        viMode,
        &gOSViModeCustom,
        sizeof(OSViMode)
    );

    // Make PAL-specific vStart adjustments
    if (osTvType == OS_TV_PAL) {
        gOSViModeCustom.fldRegs[0].vStart -= 0x180000;
        gOSViModeCustom.fldRegs[1].vStart -= 0x180000;
        gOSViModeCustom.fldRegs[0].vStart += 0x10;
        gOSViModeCustom.fldRegs[1].vStart += 0x10;
    }

    gOSViModeCustom.fldRegs[0].vStart += gVScaleMod * 0x20000;
    gOSViModeCustom.fldRegs[1].vStart += gVScaleMod * 0x20000;
    gOSViModeCustom.fldRegs[0].vStart += gVScaleMod * 0x2;
    gOSViModeCustom.fldRegs[1].vStart += gVScaleMod * 0x2;
    gOSViModeCustom.comRegs.hStart += gHStartMod * 0x20000;
    gOSViModeCustom.comRegs.hStart += gHStartMod * 0x2;

    // Use the custom VI mode and set some special features
    osViSetMode(&gOSViModeCustom);
    osViSetSpecialFeatures(OS_VI_DIVOT_ON);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/initialize_framebuffers.s")
#else
void initialize_framebuffers(int someBool, s32 width, s32 height) {
    VideoResolution *resPtr;
    u32 hRes;
    u32 vRes;
    
    // Get resolution by current video mode
    resPtr = &gResolutionArray[gVideoMode & 0x7];
    hRes = resPtr->h;
    vRes = resPtr->v;

    // Set current resolution
    gCurrentResolutionH[0] = hRes;
    gCurrentResolutionH[1] = hRes;
    gCurrentResolutionV[0] = vRes;
    gCurrentResolutionV[1] = vRes;

    if (osMemSize != 0x800000) {
        // No expansion pack detected
        gFramebufferPointers[0] = FRAMEBUFFER_ADDRESS_NO_EXP_PAK;
        gFramebufferPointers[1] = FRAMEBUFFER_ADDRESS_NO_EXP_PAK + ((width * height) * 2);
        
        gFramebufferStart = FRAMEBUFFER_ADDRESS_NO_EXP_PAK;
        return;
    }
    
    if (height == 480) {
        // PAL framebuffer height
        gFramebufferPointers[0] = FRAMEBUFFER_ADDRESS_EXP_PAK;
        gFramebufferPointers[1] = FRAMEBUFFER_ADDRESS_EXP_PAK + ((width * height) * 2);
        
        gFramebufferStart = FRAMEBUFFER_ADDRESS_EXP_PAK;
    } else {
        // NTSC/M-PAL framebuffer height
        gFramebufferPointers[0] = FRAMEBUFFER_ADDRESS_EXP_PAK;
        gFramebufferPointers[1] = FRAMEBUFFER_ADDRESS_EXP_PAK + ((width * height) * 2);
        
        gFramebufferEnd = ((int) (FRAMEBUFFER_ADDRESS_EXP_PAK + ((width * height) * 2))) + ((width * height) * 2);
        gFramebufferStart = 0x80200000;
    }
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005D9D8.s")
#else
void func_8005D9D8() {
    D_800BCE58 = 0;
    D_800BCE59 = 2;
    D_800BCE34 = 1;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005DA00.s")
#else
void func_8005DA00(u32 param1) {
    D_800BCE34 = param1;
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/video/video_func_returning_delay.s")

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005DC68.s")
#else
void func_8005DC68() {}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005DC70.s")
#else
void func_8005DC70(int _) {}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005DC7C.s")
#else
s32 func_8005DC7C() {
    return (s32)((f32)gDisplayHertz / (f32)D_800BCE59);
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/swap_framebuffer_pointers.s")
#else
/**
 * Swaps gFramebufferCurrent and gFramebufferNext.
 *
 * Uses gFramebufferChoice to keep track of the index for the next framebuffer to swap to.
 */
void swap_framebuffer_pointers() {
    // Set the current framebuffer to the one last chosen for framebufferNext (see below)
    gFramebufferCurrent = gFramebufferPointers[gFramebufferChoice];

    // TODO: what is this doing?
    D_800BCCB4 = gFramebufferStart; // D_800BCCB4 = &framebufferCurrent+8

    // Swap choice to the other framebuffer index
    //
    // Assuming there are 2 framebuffers, this will flip between 0 and 1:
    //   0 ^ 1 = 1
    //   1 ^ 1 = 0
    gFramebufferChoice = gFramebufferChoice ^ 1;

    // Set next framebuffer to the swapped index
    gFramebufferNext = gFramebufferPointers[gFramebufferChoice];

    // TODO: what is this doing?
    D_800BCCB0 = gFramebufferStart; // D_800BCCB0 = &framebufferCurrent+4
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/get_framebuffer_start.s")
#else
/**
 * Returns gFramebufferStart.
 */
u16 *get_framebuffer_start() {
    return gFramebufferStart;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/get_framebuffer_end.s")
#else
/**
 * Returns gFramebufferEnd.
 */
u32 *get_framebuffer_end() {
    return gFramebufferEnd;
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005DD4C.s")

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/is_size_smaller_than_resolution.s")
#else
/**
 * Returns whether the given width and height is smaller than the current framebuffer's resolution.
 *
 * Note: Both width AND height must be smaller for this to return true.
 */
int is_size_smaller_than_resolution(s32 width, s32 height) {
    return width >= 0
        && (u32)width < gCurrentResolutionH[gFramebufferChoice]
        && height >= 0
        && (u32)height < gCurrentResolutionV[gFramebufferChoice];
}
#endif

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/video/func_8005DEE8.s")
#else
// Kind of close? Might be worth starting this one over...
void func_8005DEE8() {
    u8 i;
    s32 v0;
    s32 *v1;
    u32 t5;
    UnkVidStruct3 *t4;

    v1 = D_800BCE18[D_800BCE20];

    for (i = 0; i < D_800BCE22[D_800BCE20]; ++i, v1 += 3) {
        v0 = v1[1];

        if (v0 >= 0) {
            t5 = gFramebufferStart[v0] >> 2;
            t4 = &D_80093068[(t5 >> 0xBu) & 7u];

            v1[0] = (((t5 & 0x7ff) << t4->unk0x0) + t4->unk0x4) >> 3;
        } else {
            v1[0] = 0;
        }
    }

    D_800BCE20 = D_800BCE20 ^ 1;
    D_800BCE22[D_800BCE20] = 0;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/some_video_setup.s")
#else
/**
 * Note: param1 is most likely a boolean
 */
void some_video_setup(int param1) {
    if (param1) {
        set_video_mode(7);
        initialize_framebuffers(1, gResolutionArray[7].h, gResolutionArray[7].v);

        set_custom_vi_mode();
        D_800BCE14 = 0xc;
        osViBlack(TRUE);
        D_800BCE58 = 0;
        D_800BCE2C = 0x5;
    } else {
        set_video_mode(1);
        initialize_framebuffers(1, gResolutionArray[0].h, gResolutionArray[0].v);

        set_custom_vi_mode();
        D_800BCE14 = 0xc;
        osViBlack(TRUE);
        D_800BCE58 = 0;
        D_800BCE2C = 0x5;
    }
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/video/modify_vi_mode.s")
#else
void modify_vi_mode(u8 a0, s8 hStartMod, s8 vScaleMod) {
    u8 viLpn;
    OSViMode *viMode;

    gHStartMod = hStartMod;
    gVScaleMod = vScaleMod;

    // If a0 is 0, don't set custom vi mode
    if (a0 == 0) {
        return;
    }

    // Determine VI LPN from TV type
    if (osTvType == OS_TV_PAL) {
        viLpn = OS_VI_PAL_LPN1;
    } else if (osTvType == OS_TV_MPAL) {
        viLpn = OS_VI_MPAL_LPN1;
    } else {
        viLpn = OS_VI_NTSC_LPN1;
    }

    // Determine VI mode from video mode and VI LPN
    if (gVideoMode == OS_VI_PAL_LPN1 /*0xe*/) {
        viMode = &osViModeTable[11 + viLpn];
    } else {
        viMode = &osViModeTable[2 + viLpn];
    }

    // Set gOSViModeCustom to the chosen VI mode
    bcopy(
        viMode,
        &gOSViModeCustom,
        sizeof(OSViMode)
    );

    // Make PAL-specific vStart adjustments
    if (osTvType == OS_TV_PAL) {
        gOSViModeCustom.fldRegs[0].vStart -= 0x180000;
        gOSViModeCustom.fldRegs[1].vStart -= 0x180000;
        gOSViModeCustom.fldRegs[0].vStart += 0x10;
        gOSViModeCustom.fldRegs[1].vStart += 0x10;
    }

    gOSViModeCustom.fldRegs[0].vStart += gVScaleMod * 0x20000;
    gOSViModeCustom.fldRegs[1].vStart += gVScaleMod * 0x20000;
    gOSViModeCustom.fldRegs[0].vStart += gVScaleMod * 0x2;
    gOSViModeCustom.fldRegs[1].vStart += gVScaleMod * 0x2;
    gOSViModeCustom.comRegs.hStart += gHStartMod * 0x20000;
    gOSViModeCustom.comRegs.hStart += gHStartMod * 0x2;

    D_80093060 = 3;
}
#endif
