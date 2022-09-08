/// @file Gui/Gdl/ValueToReal.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Gdl/ValueToReal.h"

Ring2_Real32 Machine_Gui_Gdl_valueToReal(Ring2_Value const* value) {
  if (!Ring2_Value_isInteger(value) && !Ring2_Value_isReal32(value)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  if (Ring2_Value_isInteger(value)) {
    return (Ring2_Real32)Ring2_Value_getInteger(value);
  } else {
    return Ring2_Value_getReal32(value);
  }
}
