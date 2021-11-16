/// @file Gui/BorderModel.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_BORDERMODEL_H_INCLUDED)
#define MACHINE_GUI_BORDERMODEL_H_INCLUDED



#include "_Math.h"



/// @brief Border attributes.
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_BorderModel)

struct Machine_GUI_BorderModel_Class {
  Machine_Object_Class __parent;
};

struct Machine_GUI_BorderModel {
  Machine_Object __parent;
  
  /// @brief The color of the border.
  Machine_Math_Vector4* color;
  
  /// @brief The width of the left border.
  Machine_Real leftWidth;
  /// @brief The width of the right border.
  Machine_Real rightWidth;
  /// @brief The width of the top border.
  Machine_Real topWidth;
  /// @brief The width of the bottom border.
  Machine_Real bottomWidth;
};

/// @brief Construct a border model.
/// @param self This border model.
/// @param numberOfArguments, arguments The arguments. Number of arguments must be @a 0.
/// @default The default border color is <code>(0.1, 0.1, 0.1, 1.0)</code>.
/// @default The default border width for alles sides is <code>0</code>.
void Machine_GUI_BorderModel_construct(Machine_GUI_BorderModel* self, size_t numberOfArguments, const Machine_Value *arguments);

/// @brief Create a border model with default values.
/// @return The border model.
Machine_GUI_BorderModel *Machine_GUI_BorderModel_create();

/// @brief Get the color of this border model.
/// @param self This border model.
/// @return The color.
const Machine_Math_Vector4* Machine_GUI_BorderModel_getColor(const Machine_GUI_BorderModel* self);

/// @brief Set the color of this border model.
/// @param self This border model.
/// @param color The color.
void Machine_GUI_BorderModel_setColor(Machine_GUI_BorderModel *self, const Machine_Math_Vector4 *color);

/// @brief Get the width of the left border.
/// @param self This border model.
/// @return The width.
Machine_Real Machine_GUI_BorderModel_getLeftWidth(const Machine_GUI_BorderModel* self);

/// @brief Set the width of the left border.
/// @param self This border model.
/// @param width The width.
void Machine_GUI_BorderModel_setLeftWidth(Machine_GUI_BorderModel* self, Machine_Real width);

/// @brief Get the width of the right border.
/// @param self This border model.
/// @return The width.
Machine_Real Machine_GUI_BorderModel_getRightWidth(const Machine_GUI_BorderModel* self);

/// @brief Set the width of the right border.
/// @param self This border model.
/// @param width The width.
void Machine_GUI_BorderModel_setRightWidth(Machine_GUI_BorderModel* self, Machine_Real width);

/// @brief Get the width of the top border.
/// @param self This border model.
/// @return The width.
Machine_Real Machine_GUI_BorderModel_getTopWidth(const Machine_GUI_BorderModel* self);

/// @brief Set the width of the top border.
/// @param self This border model.
/// @param width The width.
void Machine_GUI_BorderModel_setTopWidth(Machine_GUI_BorderModel* self, Machine_Real width);

/// @brief Get the width of the bottom border.
/// @param self This border model.
/// @return The width.
Machine_Real Machine_GUI_BorderModel_getBottomWidth(const Machine_GUI_BorderModel* self);

/// @brief Set the width of the bottom border.
/// @param self This border model.
/// @param width The width.
void Machine_GUI_BorderModel_setBottomWidth(Machine_GUI_BorderModel* self, Machine_Real width);

/// @brief Set the width of this border model.
/// @param self This border model.
/// @param width The width.
void Machine_GUI_BorderModel_setWidth(Machine_GUI_BorderModel* self, Machine_Real width);

#endif // MACHINE_GUI_BORDERMODEL_H_INCLUDED
