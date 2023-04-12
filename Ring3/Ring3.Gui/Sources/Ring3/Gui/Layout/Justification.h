#if !defined(RING3_GUI_JUSTIFICATION_H_INCLUDED)
#define RING3_GUI_JUSTIFICATION_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Layout/Justification.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

/// @brief Denotes how elements layed out along an axis are justified along that axis.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_Gui_Layout_Justification)

enum Ring3_Gui_Layout_Justification {

  /// @brief Elements are packed towards the start of the axis.
  Ring3_Gui_Layout_Justification_Start,

  /// @brief Elements are packed towards the center of the axis.
  Ring3_Gui_Layout_Justification_Center,

  /// @brief Elements are packed towards the end of the axis.
  Ring3_Gui_Layout_Justification_End,

#if 0
  /// @brief The space is evenly distributed between the elements.
  /// If there are at least two items:
  /// The first item's start is at the start of the axis.
  /// The last item's end is at the end of the box.
  /// If there is one item:
  /// Equivalent to Ring3_Gui_Layout_Justification_Start.
  Ring3_Gui_Layout_Justification_SpaceBetween,
#endif
};

/// @brief
/// @a source must be one of <code>start</code>, <code>center</code>, or <code>end</code>
/// which is mapped as follows
/// - <code>start</code> is mapped to <code>Ring3_Gui_Layout_Justification_Start</code>
/// - <code>center</code> is mapped to <code>Ring3_Gui_Layout_Justification_Center</code>
/// - <code>end</code> is mapped to <code>Ring3_Gui_Layout_Justification_End</code>
/// @param source The string.
/// @error #Ring1_Status_InvalidArgument @a source is a null pointer
/// @errror #Ring1_Status_InvalidSemantics @a source is none of the values specified above.
/// @return The justification.
Ring1_NoDiscardReturn() Ring3_Gui_Layout_Justification
Ring3_Gui_Layout_Justification_parse
  (
    Ring2_String* source
  );

/// @brief
/// @a source is mapped as follows
/// - <code>Ring3_Gui_Layout_Justification_Start</code> is mapped to <code>start</code>
/// - <code>Ring3_Gui_Layout_Justification_Center</code> is mapped to <code>center</code>
/// - <code>Ring3_Gui_Layout_Justification_End</code> is mapped to <code>end</code>
/// @param source The justification.
/// @return The string.
Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_Layout_Justification_unparse
  (
    Ring3_Gui_Layout_Justification source
  );

#endif // RING3_GUI_JUSTIFICATION_H_INCLUDED
