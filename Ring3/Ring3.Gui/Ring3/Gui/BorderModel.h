/// @file Ring3/Gui/BorderModel.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_BORDERMODEL_H_INCLUDED)
#define MACHINE_GUI_BORDERMODEL_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/BorderModel.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Math/_Include.h"

/// @brief Border attributes.
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_BorderModel)

struct Machine_Gui_BorderModel_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gui_BorderModel {
  Machine_Object __parent;

  /// @brief The color of the border.
  Ring3_Math_Vector4f32* color;

  /// @brief The width of the left border.
  Ring2_Real32 leftWidth;
  /// @brief The width of the right border.
  Ring2_Real32 rightWidth;
  /// @brief The width of the top border.
  Ring2_Real32 topWidth;
  /// @brief The width of the bottom border.
  Ring2_Real32 bottomWidth;
};

/// @brief Construct a border model.
/// @param self This border model.
/// @param numberOfArguments, arguments The arguments. Number of arguments must be @a 0.
/// @default The default border color is <code>(0.1, 0.1, 0.1, 1.0)</code>.
/// @default The default border width for alles sides is <code>0</code>.
void
Machine_Gui_BorderModel_construct
  (
    Machine_Gui_BorderModel* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a border model with default values.
/// @return The border model.
Ring1_NoDiscardReturn() Machine_Gui_BorderModel*
Machine_Gui_BorderModel_create
  (
  );

/// @brief Get the color of this border model.
/// @param self This border model.
/// @return The color.
/// @remarks A copy of the stored object is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_BorderModel_getColor
  (
    Machine_Gui_BorderModel const* self
  );

/// @brief Set the color of this border model.
/// @param self This border model.
/// @param color The color.
void
Machine_Gui_BorderModel_setColor
  (
    Machine_Gui_BorderModel* self,
    Ring3_Math_Vector4f32 const* color
  );

/// @brief Get the width of the left border.
/// @param self This border model.
/// @return The width.
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getLeftWidth
  (
    Machine_Gui_BorderModel const* self
  );

/// @brief Set the width of the left border.
/// @param self This border model.
/// @param width The width.
void
Machine_Gui_BorderModel_setLeftWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  );

/// @brief Get the width of the right border.
/// @param self This border model.
/// @return The width.
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getRightWidth
  (
    Machine_Gui_BorderModel const* self
  );

/// @brief Set the width of the right border.
/// @param self This border model.
/// @param width The width.
void
Machine_Gui_BorderModel_setRightWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  );

/// @brief Get the width of the top border.
/// @param self This border model.
/// @return The width.
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getTopWidth
  (
    Machine_Gui_BorderModel const* self
  );

/// @brief Set the width of the top border.
/// @param self This border model.
/// @param width The width.
void
Machine_Gui_BorderModel_setTopWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  );

/// @brief Get the width of the bottom border.
/// @param self This border model.
/// @return The width.
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getBottomWidth
  (
    Machine_Gui_BorderModel const* self
  );

/// @brief Set the width of the bottom border.
/// @param self This border model.
/// @param width The width.
void
Machine_Gui_BorderModel_setBottomWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  );

/// @brief Set the width of this border model.
/// @param self This border model.
/// @param width The width.
void
Machine_Gui_BorderModel_setWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  );

#endif // MACHINE_GUI_BORDERMODEL_H_INCLUDED
