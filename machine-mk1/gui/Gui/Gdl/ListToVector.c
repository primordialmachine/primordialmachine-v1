/// @file Gui/Gdl/ListToVector.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Gdl/ListToVector.h"

#include "Gui/Gdl/ValueToReal.h"
#include "Ring2/Library/_Include.h"

Machine_Math_Vector3* Machine_Gui_Gdl_listToVector3(Ring2_List const* list) {
  int64_t size = Ring2_Collection_getSize((Ring2_Collection const*)list);
  Ring2_assert(size == 3, Ring1_Status_InvalidArgument);
  Ring2_Value values[] = {
    Ring2_List_getAt(list, 0),
    Ring2_List_getAt(list, 1),
    Ring2_List_getAt(list, 2),
  };
  Machine_Math_Vector3* vector = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(vector,
                           Machine_Gui_Gdl_valueToReal(&values[0]),
                           Machine_Gui_Gdl_valueToReal(&values[1]),
                           Machine_Gui_Gdl_valueToReal(&values[2]));
  return vector;
}

Machine_Math_Vector4* Machine_Gui_Gdl_listToVector4(Ring2_List const* list) {
  int64_t size = Ring2_Collection_getSize((Ring2_Collection const*)list);
  Ring2_assert(size == 4, Ring1_Status_InvalidArgument);
  Ring2_Value values[] = {
    Ring2_List_getAt(list, 0),
    Ring2_List_getAt(list, 1),
    Ring2_List_getAt(list, 2),
    Ring2_List_getAt(list, 3),
  };
  Machine_Math_Vector4* vector = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(
      vector, Machine_Gui_Gdl_valueToReal(&values[0]), Machine_Gui_Gdl_valueToReal(&values[1]),
      Machine_Gui_Gdl_valueToReal(&values[2]), Machine_Gui_Gdl_valueToReal(&values[3]));
  return vector;
}
