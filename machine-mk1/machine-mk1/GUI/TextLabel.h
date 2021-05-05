#if !defined(MACHINE_GUI_TEXTLABEL_H_INCLUDED)
#define MACHINE_GUI_TEXTLABEL_H_INCLUDED

#include "./../Fonts.h"

/// @brief A label to display a text or an image.
typedef struct Machine_GUI_TextLabel Machine_GUI_TextLabel;

/// @brief Create a label with default values.
/// @return The label.
Machine_GUI_TextLabel* Machine_GUI_TextLabel_create();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Math_Vector2* Machine_GUI_TextLabel_getBestSize(Machine_GUI_TextLabel* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the text.
/// @param self This text label.
/// @param text The text.
void Machine_GUI_TextLabel_setText(Machine_GUI_TextLabel* self, Machine_String* text);

/// @brief Get the text.
/// @param self This text label.
/// @return The text.
Machine_String* Machine_GUI_TextLabel_getText(Machine_GUI_TextLabel* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the background color.
/// @param self This text label.
/// @param backgroundColor The background color.
void Machine_GUI_TextLabel_setBackgroundColor(Machine_GUI_TextLabel* self, const Machine_Math_Vector3* backgroundColor);

/// @brief Get the background color.
/// @param self This text label.
/// @return The background color.
const Machine_Math_Vector3* Machine_GUI_TextLabel_getBackgroundColor(Machine_GUI_TextLabel *self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the foreground color.
/// @param self This text label.
/// @param foregroundColor The foreground color.
void Machine_GUI_TextLabel_setForegroundColor(Machine_GUI_TextLabel* self, const Machine_Math_Vector3* foregroundColor);

/// @brief Set the foreground color.
/// @param self This text label.
/// @return The foreground color.
const Machine_Math_Vector3* Machine_GUI_TextLabel_getForegroundColor(Machine_GUI_TextLabel* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the position.
/// @param self This text label.
/// @param position The position.
void Machine_GUI_TextLabel_setPosition(Machine_GUI_TextLabel* self, const Machine_Math_Vector2* position);

/// @brief Get the position.
/// @param self This text label.
/// @return The position.
const Machine_Math_Vector2* Machine_GUI_TextLabel_getPosition(Machine_GUI_TextLabel* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the size.
/// @param self This text label.
/// @param size The size.
void Machine_GUI_TextLabel_setSize(Machine_GUI_TextLabel* self, const Machine_Math_Vector2* size);

/// @brief Get the size.
/// @param self This text label.
/// @return The size.
const Machine_Math_Vector2* Machine_GUI_TextLabel_getSize(Machine_GUI_TextLabel* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the bounds.
/// @param self This text label.
/// @param rectangle The rectangle.
void Machine_GUI_TextLabel_setRectangle(Machine_GUI_TextLabel* self, Machine_Math_Rectangle2* rectangle);

/// @brief Get the bounds.
/// @param self This text label.
/// @return The rectangle.
const Machine_Math_Rectangle2* Machine_GUI_TextLabel_getRectangle(Machine_GUI_TextLabel* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_render(Machine_GUI_TextLabel* self, float width, float height);

#endif // MACHINE_GUI_TEXTLABEL_H_INCLUDED
