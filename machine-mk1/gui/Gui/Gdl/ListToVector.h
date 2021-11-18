/// @file Gui/Gdl/ListToVector.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_GDL_LISTTOVECTOR3_H_INCLUDED)
#define MACHINE_GUI_GDL_LISTTOVECTOR3_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "_Collections.h"
#include "_Math.h"
#include "_Runtime.h"

/// @brief
/// Convert
/// a list with 3 values of type <code>Integer</code> or <code>Real</code>
/// to
/// a value of type <code>Math.Vector3</code>.
/// @param value A pointer to a value.
/// @return The value of type <code>Real</code>.
Machine_Math_Vector3* Machine_Gui_Gdl_listToVector3(Machine_List const* list);

/// @brief
/// Convert
/// a list with 4 values of type <code>Integer</code> or <code>Real</code>
/// to
/// a value of type <code>Math.Vector4</code>.
/// @param value A pointer to a value.
/// @return The value of type <code>Real</code>.
Machine_Math_Vector4* Machine_Gui_Gdl_listToVector4(Machine_List const* list);

#endif // MACHINE_GUI_GDL_LISTTOVECTOR3_H_INCLUDED
