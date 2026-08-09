#include "common.h"
#include "sys/objtype.h"
#include "sys/objmsg.h"

typedef struct {
    ObjSetup base;
    s8 unk18;
    u8 unk19[0x1A - 0x19];
    s16 unk1A;
    u8 unk1C[0x1E - 0x1C];
    s16 unk1E;
} RobotAnimPatrol_Setup;

typedef struct {
    u8 unk0;
} RobotAnimPatrol_Data_31C;

typedef struct {
    Object* unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 _unk12[0x18 - 0x12];
    Vec3f unk18;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 _unk30[0x34 - 0x30];
    s16 unk34;
    s16 unk36;
    s16 unk38;
    u8 _unk3A[0x3C - 0x3A];
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    u8 _unk44[0x50 - 0x44];
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 _unk54[0x9C - 0x54];
    s32 unk9C;
    s32 unkA0;
    s16 unkA4;
    s16 unkA6;
    u8 _unkA8[0xAA - 0xA8];
    u8 unkAA;
    u8 unkAB;
    u8 _unkAC[0xB4 - 0xAC];
    f32 unkB4;
    f32 unkB8;
    DLL27_Data unkBC;
    RobotAnimPatrol_Data_31C unk31C;
    u8 _unk31D[0x358 - 0x31D];
    u8 unk358;
    u8 unk359;
} RobotAnimPatrol_Data;

/*0x0*/ static u32 data_0[] = {
    0x40000201, 0x00000000, 0x00000000, 0x00000000, 
    0x40020103, 0x00000000, 0x00000000, 0x00000000
};
/*0x20*/ static Vec3f data_20[] = {
    VEC3F(0.0f, 0.0f, 0.0f)
};
/*0x2C*/ static f32 data_2C[] = {7.0f};

/*0x0*/ static Texture* bss_0; // red laser beam
/*0x4*/ static Texture* bss_4; // blue laser beam
/*0x8*/ static Texture* bss_8; // blue fireball?

int dll_381_func_BC4(Object* self, Object* animObj, AnimObj_Data* animObjData, s8);
void dll_381_func_2E9C(RobotAnimPatrol_Data_31C*);

// offset: 0x0 | ctor
void dll_381_ctor(void* dll) { }

// offset: 0xC | dtor
void dll_381_dtor(void* dll) {
    if (bss_0 != NULL) {
        texFreeTexture(bss_0);
        bss_0 = NULL;
    }
    if (bss_4 != NULL) {
        texFreeTexture(bss_4);
        bss_4 = NULL;
    }
    if (bss_8 != NULL) {
        texFreeTexture(bss_8);
        bss_8 = NULL;
    }
}

// offset: 0xB0 | func: 0 | export: 0
#ifndef NON_MATCHING
void dll_381_obj_Setup(Object* self, ObjSetup* setup, s32 reset);
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_obj_Setup.s")
#else
void dll_381_obj_Setup(Object* self, RobotAnimPatrol_Setup* setup, s32 reset) {
    RobotAnimPatrol_Data* temp_s0;
    ObjSetup* temp_v0;
    Object* temp_v0_2;
    ObjectShadow* temp_v0_3;
    s32 _pad[7];
    u8 sp3B;

    temp_s0 = self->data;
    sp3B = 5;
    temp_s0->unk358 = 0;
    if ((setup->unk1E != -1) && (mainGetBits(setup->unk1E) != 0)) {
        temp_s0->unk358 |= 1;
        return;
    }
    temp_s0->unk358 &= ~0x1;
    objInitMesgQueue(self, 4);
    self->animCallback = dll_381_func_BC4;
    if (bss_0 == NULL) {
        bss_0 = texLoadTexture(TEXTABLE_127);
    }
    if (bss_4 == NULL) {
        bss_4 = texLoadTexture(TEXTABLE_16B);
    }
    if (bss_8 == NULL) {
        bss_8 = texLoadTexture(TEXTABLE_16E);
    }
    if (temp_s0->unk0 == NULL) {
        temp_v0 = objAllocSetup(sizeof(ObjSetup), OBJ_RobotBeam2);
        temp_v0->x = self->srt.transl.x;
        temp_v0->y = self->srt.transl.y;
        temp_v0->z = self->srt.transl.z;
        temp_v0->objId = OBJ_RobotBeam2;
        temp_v0->loadFlags = 2;
        temp_v0->byte5 = 4;
        temp_v0->fadeDistance = 0xFF;
        temp_v0_2 = objSetupObject(temp_v0, 0, -1, -1, self->parent);
        temp_s0->unk0 = temp_v0_2;
        temp_v0_2->srt.scale = 0.35f;
    }
    camGetObjectChildPosition(temp_s0->unk0, 
        &temp_s0->unk0->globalPosition.x, 
        &temp_s0->unk0->globalPosition.y, 
        &temp_s0->unk0->globalPosition.z);
    temp_v0_3 = temp_s0->unk0->shadow;
    if (temp_v0_3 != NULL) {
        temp_v0_3->flags |= 0x50;
        temp_v0_3->r = 0xC0;
        temp_v0_3->g = 0xFF;
        temp_v0_3->b = 0xFF;
        temp_v0_3->a = 0x1E;
        temp_v0_3->scale = 3.5f;
    }
    temp_s0->unk18.x = setup->base.x;
    temp_s0->unk18.y = setup->base.y;
    temp_s0->unk18.z = setup->base.z;
    temp_s0->unk36 = setup->unk18 << 8;
    temp_s0->unk38 = setup->unk1A;
    temp_s0->unk24 = 0.2f;
    temp_s0->unk3C = 0;
    temp_s0->unk52 = 0;
    temp_s0->unk40 = mathRnd(240, 600);
    temp_s0->unk4 = 0;
    temp_s0->unk10 = 0;
    temp_s0->unk11 = 0;
    temp_s0->unk51 = 0;
    temp_s0->unk50 = 1;
    temp_s0->unkA0 = self->srt.yaw;
    temp_s0->unk9C = 0;
    temp_s0->unkA4 = 0;
    temp_s0->unk34 = 0x400;
    temp_s0->unkAA = 0;
    temp_s0->unkAB = 0;
    temp_s0->unk359 = 0;
    temp_s0->unk8 = 0;
    temp_s0->unkC = 0;
    temp_s0->unk2C = 2.0f;
    temp_s0->unkB4 = 0.0f;
    temp_s0->unkB8 = 0.0f;
    objAnimSet(self, 0, 1.0f, 0);
    gDLL_27->vtbl->init(&temp_s0->unkBC, 0, 0x40083, 1);
    gDLL_27->vtbl->setup_terrain_collider(&temp_s0->unkBC, 1, data_20, data_2C, &sp3B);
    objAddObjectType(self, OBJTYPE_24);
    objAddObjectType(self, OBJTYPE_Baddie);
    dll_381_func_2E9C(&temp_s0->unk31C);
    func_8002674C(self);
}
#endif

// offset: 0x484 | func: 1 | export: 1
#ifndef NON_MATCHING
void dll_381_obj_Control(Object* self);
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_obj_Control.s")
#else
void dll_381_func_2890(Object*, void*, u8);     /* extern */
void dll_381_func_3040(Object*, void*);                /* extern */

void dll_381_obj_Control(Object* self) {
    RobotAnimPatrol_Data* temp_a3;
    u8 temp_v0;

    temp_a3 = self->data;
    diPrintf(" ROBO not Overriden \0RobotAnimPatrol Beam Error!!\n"); // TODO: split string
    if (!(temp_a3->unk358 & 1)) {
        temp_v0 = temp_a3->unkAB;
        temp_a3->unk50 = (u8) gUpdateRate;
        if (temp_v0 != 0) {
            dll_381_func_2890(self, temp_a3, temp_v0);
        } else {
            if (self->unkE0 == 0) {
                self->srt.transl.x = temp_a3->unk18.x;
                self->srt.transl.y = temp_a3->unk18.y;
                self->srt.transl.z = temp_a3->unk18.z;
                self->srt.yaw = temp_a3->unk36;
                self->unkE0 = 1;
            }
            dll_381_func_3040(self, &temp_a3->unk31C);
        }
    }
}
#endif

// offset: 0x56C | func: 2 | export: 2
void dll_381_obj_Update(Object* self);
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_obj_Update.s")

// offset: 0x740 | func: 3 | export: 3
void dll_381_obj_Print(Object* self, Gfx** gdl, Mtx** mtxs, Vertex** vtxs, Triangle** pols, s8 visibility);
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_obj_Print.s")

// offset: 0xA74 | func: 4 | export: 4
void dll_381_obj_Free(Object* self, s32 onlySelf);
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_obj_Free.s")

// offset: 0xBA0 | func: 5 | export: 5
u32 dll_381_obj_GetModelFlags(Object* self);
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_obj_GetModelFlags.s")

// offset: 0xBB0 | func: 6 | export: 6
u32 dll_381_obj_GetDataSize(Object* self, u32 offsetAddr) {
    return sizeof(RobotAnimPatrol_Data);
}

// offset: 0xBC4 | func: 7
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_BC4.s")

// offset: 0x16FC | func: 8
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_16FC.s")

// offset: 0x1928 | func: 9
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_1928.s")

// offset: 0x1B08 | func: 10
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_1B08.s")

// offset: 0x1BD4 | func: 11
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_1BD4.s")

// offset: 0x1D04 | func: 12
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_1D04.s")

// offset: 0x1F60 | func: 13
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_1F60.s")

// offset: 0x24E8 | func: 14
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_24E8.s")

// offset: 0x2784 | func: 15
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_2784.s")

// offset: 0x2890 | func: 16
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_2890.s")

// offset: 0x2E9C | func: 17
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_2E9C.s")

// offset: 0x2EAC | func: 18
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_2EAC.s")

// offset: 0x3040 | func: 19
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_3040.s")

// offset: 0x334C | func: 20
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_334C.s")

// offset: 0x33E8 | func: 21
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_33E8.s")

// offset: 0x34D4 | func: 22
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_34D4.s")

// offset: 0x35B0 | func: 23
#pragma GLOBAL_ASM("asm/nonmatchings/dlls/objects/381_RobotAnimPatrol/dll_381_func_35B0.s")
