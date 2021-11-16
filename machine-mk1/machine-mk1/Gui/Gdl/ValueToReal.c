/// @file Gui/Gdl/ValueToReal.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/Gdl/ValueToReal.h"

Machine_Real Machine_GUI_GDL_valueToReal(const Machine_Value* value) {
  if (!Machine_Value_isInteger(value) && !Machine_Value_isReal(value)) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  if (Machine_Value_isInteger(value)) {
    return (Machine_Real)Machine_Value_getInteger(value);
  }
  else {
    return Machine_Value_getReal(value);
  }
}
