#if !defined(RING3_GUI_DIRECTION_H_INCLUDED)
#define RING3_GUI_DIRECTION_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Layout/Direction.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

/// @brief Denotes along which axis elements are layed out.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_Gui_Layout_Direction)

enum Ring3_Gui_Layout_Direction {

  /// @brief Axis from Top to bottom.
  /// Centered around the main axis.
  Ring3_Gui_Layout_Direction_Column,

  /// @brief Axis from Bottom to top.
  /// Centered around the main axis.
  Ring3_Gui_Layout_Direction_ColumnReverse,

  /// @brief Axis from Left to right.
  /// Centered around the main axis.
  Ring3_Gui_Layout_Direction_Row,

  /// @brief Axis from Right to left.
  /// Centered around the main axis.
  Ring3_Gui_Layout_Direction_RowReverse,

};

/// @brief
/// @a source must be one of <code>column</code>, <code>columnReverse</code>, <code>row</code>, or <code>rowReverse</code>
/// which is mapped as follows
/// - <code>column</code> is mapped to <code>Ring3_Gui_Layout_Direction_Column</code>
/// - <code>columnReverse</code> is mapped to <code>Ring3_Gui_Layout_Direction_ColumnReverse</code>
/// - <code>row</code> is mapped to <code>Ring3_Gui_Layout_Direction_Row</code>
/// - <code>rowReverse</code> is mapped to <code>Ring3_Gui_Layout_Direction_RowReverse</code>
/// @param source The string.
/// @error #Ring1_Status_InvalidArgument @a source is a null pointer
/// @errror #Ring1_Status_InvalidSemantics @a source is none of the values specified above.
/// @return The direction.
Ring1_NoDiscardReturn() Ring3_Gui_Layout_Direction
Ring3_Gui_Layout_Direction_parse
  (
    Ring2_String* source
  );

/// @brief
/// @a source is mapped as follows
/// - <code>Ring3_Gui_Layout_Direction_Column</code> is mapped to <code>column</code>
/// - <code>Ring3_Gui_Layout_Direction_ColumnReverse</code> is mapped to <code>columnReverse</code>
/// - <code>Ring3_Gui_Layout_Direction_Row</code> is mapped to <code>row</code>
/// - <code>Ring3_Gui_Layout_Direction_RowReverse</code> is mapped to <code>rowReverse</code>
/// @param source The direction.
/// @return The string.
Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_Layout_Direction_unparse
  (
    Ring3_Gui_Layout_Direction source
  );

#endif // RING3_GUI_DIRECTION_H_INCLUDED
