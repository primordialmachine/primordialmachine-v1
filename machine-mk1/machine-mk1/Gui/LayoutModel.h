/// @file Gui/LayoutModel.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_LAYOUTMODEL_H_INCLUDED)
#define MACHINE_GUI_LAYOUTMODEL_H_INCLUDED



#include "_Math.h"



/// @brief Denotes how elements layed out along an axis are justified along that axis.
typedef enum Machine_Gui_Layout_Justification {
  
  /// @brief Elements are packed towards the start of the axis.
  Machine_Gui_Layout_Justification_Start,
  
  /// @brief Elements are packed towards the center of the axis.
  Machine_Gui_Layout_Justification_Center,

  /// @brief Elements are packed towards the end of the axis.
  Machine_Gui_Layout_Justification_End,

} Machine_Gui_Layout_Justification;

/// @brief Denotes along which axis elements are layed out.
typedef enum Machine_Gui_Layout_Direction {

  /// @brief Axis from Top to bottom.
  /// Centered around the main axis.
  Machine_Gui_Layout_Direction_Column,
  
  /// @brief Axis from Bottom to top.
  /// Centered around the main axis.
  Machine_Gui_Layout_Direction_ColumnReverse,
  
  /// @brief Axis from Left to right.
  /// Centered around the main axis.
  Machine_Gui_Layout_Direction_Row,
  
  /// @brief Axis from Right to left.
  /// Centered around the main axis.
  Machine_Gui_Layout_Direction_RowReverse,

} Machine_Gui_Layout_Direction;

/// @brief Layout attributes.
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_LayoutModel)

struct Machine_Gui_LayoutModel_Class {
  Machine_Object_Class parent;
};

struct Machine_Gui_LayoutModel {

  Machine_Object parent;

  /// @brief The primary axis direction.
  Machine_Gui_Layout_Direction primaryDirection;

  /// @brief The primary axis justification.
  Machine_Gui_Layout_Justification primaryJustification;

  /// @brief The primary inter child spacing.
  Machine_Real primaryInterChildSpacing;

};



/// @brief Construct a layout model.
/// @param self This layout model.
/// @param numberOfArguments, arguments The arguments. Number of arguments must be @a 0.
/// @default The default direction is #Machine_Gui_Layout_Direction_Column.
/// @default The default justification is #Machine_Gui_Layout_Justification_Start.
void Machine_Gui_LayoutModel_construct(Machine_Gui_LayoutModel* self, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Create a layout model with default values.
/// @return The layout model.
Machine_Gui_LayoutModel* Machine_Gui_LayoutModel_create();



/// @brief Get the primary direction of this layout model.
/// @param self This layout model.
/// @return The primary direction.
Machine_Gui_Layout_Direction Machine_Gui_LayoutModel_getPrimaryDirection(Machine_Gui_LayoutModel const* self);

/// @brief Set the primary direction of this layout model.
/// @param self This layout model.
/// @param direction The primary direction.
void Machine_Gui_LayoutModel_setPrimaryDirection(Machine_Gui_LayoutModel* self, Machine_Gui_Layout_Direction primaryDirection);



Machine_Gui_Layout_Justification Machine_Gui_LayoutModel_getPrimaryJustification(Machine_Gui_LayoutModel const*self);

void Machine_Gui_LayoutModel_setPrimaryJustification(Machine_Gui_LayoutModel *self, Machine_Gui_Layout_Justification primaryJustifcation);



/// @brief Get the primary inter child spacing of this layout model.
/// @param self This layout model.
/// @return The primary inter child spacing.
Machine_Real Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(Machine_Gui_LayoutModel const* self);

/// @brief Set the primary inter child spacing of this layout model.
/// @param self This layout model.
/// @param width The primary inter child spacing.
void Machine_Gui_LayoutModel_setPrimaryInterChildspacing(Machine_Gui_LayoutModel* self, Machine_Real primaryInterChildSpacing);



#endif // MACHINE_GUI_LAYOUTMODEL_H_INCLUDED
