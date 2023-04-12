/// @file Ring3/Gui/Gdl/ValueToReal.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Gdl/ValueToReal.h"
#undef RING3_GUI_PRIVATE

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Gdl_valueToReal
  (
    Ring2_Value const* value
  )
{
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
