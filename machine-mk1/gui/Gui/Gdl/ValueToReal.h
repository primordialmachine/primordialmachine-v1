/// @file Gui/Gdl/ValueToReal.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_GDL_VALUETOREAL_H_INCLUDED)
#define MACHINE_GUI_GDL_VALUETOREAL_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "_Runtime.h"

/// @brief
/// Convert
/// a value of type <code>Integer</code> or <code>Real</code>
/// to
/// a value of type <code>Real</code>.
/// @param value A pointer to a value.
/// @return The value of type <code>Real</code>.
Ring2_Real32 Machine_Gui_Gdl_valueToReal(Ring2_Value const* value);

#endif // MACHINE_GUI_GDL_VALUETOREAL_H_INCLUDED
