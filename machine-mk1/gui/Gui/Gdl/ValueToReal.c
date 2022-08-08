/// @file Gui/Gdl/ValueToReal.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Gdl/ValueToReal.h"

Ring2_Real32 Machine_Gui_Gdl_valueToReal(Machine_Value const* value) {
  if (!Machine_Value_isInteger(value) && !Machine_Value_isReal32(value)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  if (Machine_Value_isInteger(value)) {
    return (Ring2_Real32)Machine_Value_getInteger(value);
  } else {
    return Machine_Value_getReal32(value);
  }
}
