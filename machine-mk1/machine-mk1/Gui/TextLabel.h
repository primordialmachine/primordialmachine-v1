/// @file Gui/TextLabel.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_TEXTLABEL_H_INCLUDED)
#define MACHINE_GUI_TEXTLABEL_H_INCLUDED



#include "Gui/Widget.h"
#include "_Fonts.h"



/// @brief A label with text.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_TextLabel)

/// @brief Create a text label with default values.
/// @param context The GUI context the text label belongs to.
/// @return The text label.
Machine_Gui_TextLabel* Machine_Gui_TextLabel_create(Machine_Gui_Context* context);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the text.
/// @param self This text label.
/// @param text The text.
void Machine_Gui_TextLabel_setText(Machine_Gui_TextLabel* self, Machine_String* text);

/// @brief Get the text.
/// @param self This text label.
/// @return The text.
Machine_String* Machine_Gui_TextLabel_getText(Machine_Gui_TextLabel const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the background color.
/// @param self This text label.
/// @param backgroundColor The background color.
void Machine_Gui_TextLabel_setBackgroundColor(Machine_Gui_TextLabel* self, Machine_Math_Vector4 const* backgroundColor);

/// @brief Get the background color.
/// @param self This text label.
/// @return The background color.
Machine_Math_Vector4 const* Machine_Gui_TextLabel_getBackgroundColor(Machine_Gui_TextLabel const*self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the foreground color.
/// @param self This text label.
/// @param foregroundColor The foreground color.
void Machine_Gui_TextLabel_setForegroundColor(Machine_Gui_TextLabel* self, Machine_Math_Vector3 const* foregroundColor);

/// @brief Set the foreground color.
/// @param self This text label.
/// @return The foreground color.
Machine_Math_Vector3 const* Machine_Gui_TextLabel_getForegroundColor(Machine_Gui_TextLabel const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_GUI_TEXTLABEL_H_INCLUDED
