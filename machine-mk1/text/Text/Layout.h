#if !defined(MACHINE_TEXT_LAYOUT_H_INCLUDED)
#define MACHINE_TEXT_LAYOUT_H_INCLUDED



#if !defined(MACHINE_TEXT_PRIVATE)
#error("Do not include this file directly, include `_Text.h` instead.")
#endif
#include "_Collections.h"
#include "_Math.h"
#include "_Graphics2.h"



/// @brief 
/// @details A layout has several global attributes which are applied to the whole range.
/// - <code>color</color>:   The color.
/// - <code>font</code>:     The font.
/// - <code>position</code>: The position of the cursor at which the first symbol of the first line is rendered.
MACHINE_DECLARE_CLASSTYPE(Machine_Text_Layout);

#define LINES_DIRTY (1)
#define LINE_BOUNDS_DIRTY (2)
#define BOUNDS_DIRTY (4)

struct Machine_Text_Layout_Class {
  Machine_Object_Class parent;
};

struct Machine_Text_Layout {
  Machine_Object parent;
  /// @brief The position of this layout.
  Machine_Math_Vector2* position;
  /// @brief The color of this layout.
  Machine_Math_Vector3* color;
  /// @brief The font of this layout.
  Machine_Font* font;
  Ring2_String* text;
  Machine_PointerArray* lines;
  bool yup;

  /// @brief Combination of layout flags.
  uint8_t flags;

  /// @brief Pointer to the clip rectangle or the null pointer.
  /// Default is the null pointer.
  Machine_Math_Rectangle2* clipRectangle;


  /// @brief If rendering visual bounds is enabled.
  /// Default is @a false.
  bool renderVisualBounds;
  /// @brief Shape used to render the visual bounds.
  Machine_Rectangle2* visualBounds;
};

void Machine_Text_Layout_construct(Machine_Text_Layout* self, size_t numberOfArguments, Ring2_Value const* arguments);

/// @brief Create a layout with the specified text.
/// Default position is <code>(0,0)</code>.
/// Default color is <code>(0,0,0)</code>.
/// @param text The text.
/// @param font The font.
Machine_Text_Layout* Machine_Text_Layout_create(Ring2_String* text, Machine_Font* font);

/// @brief Get the bounds of this text layout.
/// @param self This text layout.
/// @return The bounds of this text layout.
const Machine_Math_Rectangle2* Machine_Text_Layout_getBounds(Machine_Text_Layout* self);

/// @brief Render this text layout.
/// @param self This text layout.
/// @param context2 The 2D context.
void Machine_Text_Layout_render(Machine_Text_Layout* self, Machine_Context2* context2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the text of this text layout.
/// @param self This text layout.
/// @param text The text.
void Machine_Text_Layout_setText(Machine_Text_Layout* self, Ring2_String* text);

/// @brief Get the text of this text layout.
/// @param self This text layout.
/// @return The text.
Ring2_String* Machine_Text_Layout_getText(Machine_Text_Layout* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the position of this text layout.
/// @param self This text layout.
/// @param position The position.
void Machine_Text_Layout_setPosition(Machine_Text_Layout* self, Machine_Math_Vector2 *position);

/// @brief Get the position of this text layout.
/// @param self This text layout.
/// @return The position.
const Machine_Math_Vector2* Machine_Text_Layout_getPosition(Machine_Text_Layout* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the color of this text layout.
/// @param self This text layout.
/// @param color The color.
void Machine_Text_Layout_setColor(Machine_Text_Layout* self, const Machine_Math_Vector3* color);

/// @brief Get the color of this text layout.
/// @param self This text layout.
/// @return The color.
const Machine_Math_Vector3* Machine_Text_Layout_getColor(Machine_Text_Layout* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set if visual bounds shall be rendered.
/// @param self This text layout.
/// @param @a true if visual bounds shall be rendered, @a false otherwise.
void Machine_Text_Layout_setRenderVisualBoundsEnabled(Machine_Text_Layout* self, bool renderVisualBounds);

/// @brief Get if visual bounds shall be rendered.
/// @param self This text layout.
/// @return @a true if visual bounds shall be rendered, @a false otherwise.
/// @default @a false
bool Machine_Text_Layout_getRenderVisualBoundsEnabled(Machine_Text_Layout* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setClipRectangle(Machine_Text_Layout* self, Machine_Math_Rectangle2* clipRectangle);

Machine_Math_Rectangle2* Machine_Text_Layout_getClipRectangle(Machine_Text_Layout* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_TEXT_LAYOUT_H_INCLUDED
