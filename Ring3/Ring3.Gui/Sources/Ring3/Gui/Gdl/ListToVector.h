/// @file Ring3/Gui/Gdl/ListToVector.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_GDL_LISTTOVECTOR3_H_INCLUDED)
#define RING3_GUI_GDL_LISTTOVECTOR3_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Gdl/ListToVector.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"
#include "Ring3/Math/_Include.h"

/// @brief
/// Convert a list of three integer/real values to a <code>Ring3.Math.Vector3f32</code> object.
/// @param list The list.
/// @return A pointer to the <code>Ring3.Math.Vector3f32</code> object.
Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Gui_Gdl_listToVector3
  (
    Ring2_Collections_List const* list
  );

/// @brief
/// Convert a list of four integer/real values to a <code>Ring3.Math.Vector3f32</code> object.
/// @param list The list.
/// @return A pointer to the <code>Ring3.Math.Vector4f32</code> object.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Gui_Gdl_listToVector4
  (
    Ring2_Collections_List const* list
  );

#endif // RING3_GUI_GDL_LISTTOVECTOR3_H_INCLUDED
