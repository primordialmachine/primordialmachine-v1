/// @file Ring3/Gui/Gdl/ValueToReal.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_GDL_VALUETOREAL_H_INCLUDED)
#define MACHINE_GUI_GDL_VALUETOREAL_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Gdl/ValueToReal.h` directly, include `Ring/Gui/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

/// @brief
/// Convert
/// a value of type <code>Integer</code> or <code>Real</code>
/// to
/// a value of type <code>Real</code>.
/// @param value A pointer to a value.
/// @return The value of type <code>Real</code>.
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Gdl_valueToReal
  (
    Ring2_Value const* value
  );

#endif // MACHINE_GUI_GDL_VALUETOREAL_H_INCLUDED
