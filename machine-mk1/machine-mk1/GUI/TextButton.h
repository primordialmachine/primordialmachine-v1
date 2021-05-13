/// @file GUI/TextButton.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_TEXTBUTTON_H_INCLUDED)
#define MACHINE_GUI_TEXTBUTTON_H_INCLUDED

#include "./../Fonts.h"

/// @brief A button with text.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_TextButton)

/// @brief Create a label with default values.
/// @return The label.
Machine_GUI_TextButton* Machine_GUI_TextButton_create();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the text.
/// @param self This text label.
/// @param text The text.
void Machine_GUI_TextButton_setText(Machine_GUI_TextButton* self, Machine_String* text);

/// @brief Get the text.
/// @param self This text label.
/// @return The text.
Machine_String* Machine_GUI_TextButton_getText(Machine_GUI_TextButton* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the background color.
/// @param self This text label.
/// @param backgroundColor The background color.
void Machine_GUI_TextButton_setBackgroundColor(Machine_GUI_TextButton* self, const Machine_Math_Vector3* backgroundColor);

/// @brief Get the background color.
/// @param self This text label.
/// @return The background color.
const Machine_Math_Vector3* Machine_GUI_TextButton_getBackgroundColor(Machine_GUI_TextButton* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the foreground color.
/// @param self This text label.
/// @param foregroundColor The foreground color.
void Machine_GUI_TextButton_setForegroundColor(Machine_GUI_TextButton* self, const Machine_Math_Vector3* foregroundColor);

/// @brief Set the foreground color.
/// @param self This text label.
/// @return The foreground color.
const Machine_Math_Vector3* Machine_GUI_TextButton_getForegroundColor(Machine_GUI_TextButton* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextButton_addButtonListener(Machine_GUI_TextButton* self, void *context, void (*callback)(void *context));

void Machine_GUI_TextButton_removeButtonListener(Machine_GUI_TextButton* self, void* context, void (*callback)(void* context));

#endif // MACHINE_GUI_TEXTBUTTON_H_INCLUDED
