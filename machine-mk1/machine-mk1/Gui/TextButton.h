/// @file Gui/TextButton.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_TEXTBUTTON_H_INCLUDED)
#define MACHINE_GUI_TEXTBUTTON_H_INCLUDED



#include "Gui/Widget.h"
#include "_Fonts.h"



/// @brief A button with text.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_TextButton)

/// @brief Create a text button with default values.
/// @param context The GUI context the text button belongs to.
/// @return The text button.
Machine_Gui_TextButton* Machine_Gui_TextButton_create(Machine_Gui_Context* context);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the text.
/// @param self This text label.
/// @param text The text.
void Machine_Gui_TextButton_setText(Machine_Gui_TextButton* self, Machine_String* text);

/// @brief Get the text.
/// @param self This text label.
/// @return The text.
Machine_String* Machine_Gui_TextButton_getText(Machine_Gui_TextButton* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the background color.
/// @param self This text label.
/// @param backgroundColor The background color.
void Machine_Gui_TextButton_setBackgroundColor(Machine_Gui_TextButton* self, Machine_Math_Vector4 const* backgroundColor);

/// @brief Get the background color.
/// @param self This text label.
/// @return The background color.
Machine_Math_Vector4 const* Machine_Gui_TextButton_getBackgroundColor(Machine_Gui_TextButton const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the foreground color.
/// @param self This text label.
/// @param foregroundColor The foreground color.
void Machine_Gui_TextButton_setForegroundColor(Machine_Gui_TextButton* self, Machine_Math_Vector3 const* foregroundColor);

/// @brief Set the foreground color.
/// @param self This text label.
/// @return The foreground color.
Machine_Math_Vector3 const* Machine_Gui_TextButton_getForegroundColor(Machine_Gui_TextButton const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextButton_addButtonListener(Machine_Gui_TextButton* self, void *context, void (*callback)(void *context));

void Machine_Gui_TextButton_removeButtonListener(Machine_Gui_TextButton* self, void* context, void (*callback)(void* context));

#endif // MACHINE_GUI_TEXTBUTTON_H_INCLUDED
