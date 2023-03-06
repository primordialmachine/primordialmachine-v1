/// @file Ring3/Gui/Gdl/ListToVector.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Gdl/ListToVector.h"

#include "Ring3/Gui/Gdl/ValueToReal.h"
#undef RING3_GUI_PRIVATE


#include "Ring2/Library/_Include.h"


Ring3_Math_Vector3f32* Ring3_Gui_Gdl_listToVector3(Ring2_Collections_List const* list) {
  int64_t size = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection const*)list);
  Ring2_assert(size == 3, Ring1_Status_InvalidArgument);
  Ring2_Value values[] = {
    Ring2_Collections_List_getAt(list, 0),
    Ring2_Collections_List_getAt(list, 1),
    Ring2_Collections_List_getAt(list, 2),
  };
  Ring3_Math_Vector3f32* vector = Ring3_Math_Vector3f32_create();
  Ring3_Math_Vector3f32_set(vector,
                            Machine_Gui_Gdl_valueToReal(&values[0]),
                            Machine_Gui_Gdl_valueToReal(&values[1]),
                            Machine_Gui_Gdl_valueToReal(&values[2]));
  return vector;
}

Ring3_Math_Vector4f32* Ring3_Gui_Gdl_listToVector4(Ring2_Collections_List const* list) {
  int64_t size = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection const*)list);
  Ring2_assert(size == 4, Ring1_Status_InvalidArgument);
  Ring2_Value values[] = {
    Ring2_Collections_List_getAt(list, 0),
    Ring2_Collections_List_getAt(list, 1),
    Ring2_Collections_List_getAt(list, 2),
    Ring2_Collections_List_getAt(list, 3),
  };
  Ring3_Math_Vector4f32* vector = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(vector, Machine_Gui_Gdl_valueToReal(&values[0]), Machine_Gui_Gdl_valueToReal(&values[1]),
                                    Machine_Gui_Gdl_valueToReal(&values[2]), Machine_Gui_Gdl_valueToReal(&values[3]));
  return vector;
}
