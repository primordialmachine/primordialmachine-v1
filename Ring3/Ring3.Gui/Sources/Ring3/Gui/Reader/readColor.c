/// @file Ring3/Gui/Reader/readColor.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Reader/readColor.h"
#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/Reader/Reader.package.h"
#include "Ring3/Gui/Gdl/ListToVector.h"
#undef RING3_GUI_PRIVATE

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Gui_Gdl_Reader_readColor
  (
    Machine_Gui_Context* self,
    Ring2_String* name,
    Ring2_Collections_Map const* source
  )
{
  if (!Machine_Gui_Reader_hasList(self, source, name)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  Ring2_Collections_List* list = Machine_Gui_Reader_getList(self, source, name);
  switch (Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)list)) {
  case 3: {
    Ring3_Math_Vector3f32* u = Ring3_Gui_Gdl_listToVector3(list);
    Ring3_Math_Vector4f32* v = Ring3_Math_Vector4f32_create();
    Ring3_Math_Vector4f32_set(v, Ring3_Math_Vector3f32_getX(u),
                                 Ring3_Math_Vector3f32_getY(u),
                                 Ring3_Math_Vector3f32_getZ(u),
                                 1.f);
    if (!(0.f <= Ring3_Math_Vector4f32_getX(v) && Ring3_Math_Vector4f32_getX(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    if (!(0.f <= Ring3_Math_Vector4f32_getY(v) && Ring3_Math_Vector4f32_getY(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    if (!(0.f <= Ring3_Math_Vector4f32_getZ(v) && Ring3_Math_Vector4f32_getZ(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    if (!(0.f <= Ring3_Math_Vector4f32_getW(v) && Ring3_Math_Vector4f32_getW(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    return v;
  } break;
  case 4: {
    Ring3_Math_Vector4f32* v = Ring3_Gui_Gdl_listToVector4(list);
    if (!(0.f <= Ring3_Math_Vector4f32_getX(v) && Ring3_Math_Vector4f32_getX(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    if (!(0.f <= Ring3_Math_Vector4f32_getY(v) && Ring3_Math_Vector4f32_getY(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    if (!(0.f <= Ring3_Math_Vector4f32_getZ(v) && Ring3_Math_Vector4f32_getZ(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    if (!(0.f <= Ring3_Math_Vector4f32_getW(v) && Ring3_Math_Vector4f32_getW(v) <= 1.f)) {
      Ring1_Status_set(Ring1_Status_InvalidSemantics);
      Ring2_jump();
    }
    return v;
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  } break;
  };
}
