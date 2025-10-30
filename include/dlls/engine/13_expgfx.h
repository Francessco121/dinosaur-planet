#ifndef _DLLS_13_EXPGFX_H__
#define _DLLS_13_EXPGFX_H__

#include "PR/ultratypes.h"
#include "PR/gbi.h"
#include "game/objects/object.h"
#include "dll_def.h"
#include "types.h"

DLL_INTERFACE(DLL_13_expgfx) {
    /*:*/ DLL_INTERFACE_BASE(DLL);
    /*0*/ void (*func0)(void);
    /*1*/ UnknownDLLFunc func1;
    /*2*/ void (*func2)(s32 arg0, u8 updateRate, s32 arg2, s32 arg3);
    /*3*/ UnknownDLLFunc func3;
    /*4*/ UnknownDLLFunc func4;
    /*5*/ void (*func5)(Object *arg0);
    /*6*/ void (*func6)(Object *arg0, Gfx **gdl, Mtx **mtxs, Vertex **vertices, s32 arg4, s32 arg5, s32 arg6);
    /*7*/ UnknownDLLFunc func7;
    /*8*/ UnknownDLLFunc func8;
    /*9*/ void (*func9)(Object *arg0);
    /*10*/ s8 (*func10)(Object *obj);
};

#endif //_DLLS_13_EXPGFX_H__
