/// @file Ring3/Gui/LayoutModel.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_LAYOUTMODEL_H_INCLUDED)
#define MACHINE_GUI_LAYOUTMODEL_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/LayoutModel.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/Layout/Direction.h"
#include "Ring3/Gui/Layout/Justification.h"

/// @brief Layout attributes.
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_LayoutModel)

struct Machine_Gui_LayoutModel_Class {
  Machine_Object_Class parent;
};

struct Machine_Gui_LayoutModel {

  Machine_Object parent;

  /// @brief The primary axis direction.
  Ring3_Gui_Layout_Direction primaryDirection;

  /// @brief The primary axis justification.
  Ring3_Gui_Layout_Justification primaryJustification;

  /// @brief The primary inter child spacing.
  Ring2_Real32 primaryInterChildSpacing;
};

/// @brief Construct a layout model.
/// @param self This layout model.
/// @param numberOfArguments, arguments The arguments. Number of arguments must be @a 0.
/// @default The default direction is #Ring3_Gui_Layout_Direction_Column.
/// @default The default justification is #Ring3_Gui_Layout_Justification_Start.
void
Machine_Gui_LayoutModel_construct
  (
    Machine_Gui_LayoutModel* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a layout model with default values.
/// @return The layout model.
Ring1_NoDiscardReturn() Machine_Gui_LayoutModel*
Machine_Gui_LayoutModel_create
  (
  );

/// @brief Get the primary direction of this layout model.
/// @param self This layout model.
/// @return The primary direction. Default is #Ring3_Gui_Layout_Direction_Column.
Ring1_NoDiscardReturn() Ring3_Gui_Layout_Direction
Machine_Gui_LayoutModel_getPrimaryDirection
  (
    Machine_Gui_LayoutModel const* self
  );

/// @brief Set the primary direction of this layout model.
/// @param self This layout model.
/// @param direction The primary direction.
void
Machine_Gui_LayoutModel_setPrimaryDirection
  (
    Machine_Gui_LayoutModel* self,
    Ring3_Gui_Layout_Direction primaryDirection
  );

/// @brief Get the justification along the primary axis.
/// @param self A pointer to this layout model.
/// @return The justification along the primary axis. Default is #Ring3_Gui_Layout_Justification_Start.
Ring1_NoDiscardReturn() Ring3_Gui_Layout_Justification
Machine_Gui_LayoutModel_getPrimaryJustification
  (
    Machine_Gui_LayoutModel const* self
  );

/// @brief Set the justification along the primary axis.
/// @param self A pointer to this layout model.
/// @param justification The justification along the primary axis.
void
Machine_Gui_LayoutModel_setPrimaryJustification
  (
    Machine_Gui_LayoutModel* self,
    Ring3_Gui_Layout_Justification primaryJustifcation
  );

/// @brief Get the primary inter child spacing of this layout model.
/// @param self This layout model.
/// @return The primary inter child spacing.
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_LayoutModel_getPrimaryInterChildSpacing
  (
    Machine_Gui_LayoutModel const* self
  );

/// @brief Set the primary inter child spacing of this layout model.
/// @param self This layout model.
/// @param width The primary inter child spacing.
void
Machine_Gui_LayoutModel_setPrimaryInterChildspacing
  (
    Machine_Gui_LayoutModel* self,
    Ring2_Real32 primaryInterChildSpacing
  );

#endif // MACHINE_GUI_LAYOUTMODEL_H_INCLUDED
