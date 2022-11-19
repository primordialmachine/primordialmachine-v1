/// @file Graphics2/Rectangle2.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GRAPHICS2_RECTANGLE2_H_INCLUDED)
#define MACHINE_GRAPHICS2_RECTANGLE2_H_INCLUDED



#if !defined(MACHINE_GRAPHICS2_PRIVATE)
#error("Do not include `Graphics2/Rectangle2.h` directly. Include `_Graphics2.h` instead.")
#endif
#include "Graphics2/Shape2.h"



/// C-level representation of a rectangle.
/// The default position is (0,0).
/// The default size is (0,0).
/// The default color is opaque white.
/// @extends Machine_Shape2
MACHINE_DECLARE_CLASSTYPE(Machine_Rectangle2);

struct Machine_Rectangle2_Class {
  Machine_Shape2_Class __parent;
};

struct Machine_Rectangle2 {
  Machine_Shape2 __parent;
  Ring3_Math_Vector2* position;
  Ring3_Math_Vector2* size;
  Ring3_Math_Vector4* color;
};

void Machine_Rectangle2_construct(Machine_Rectangle2* self, size_t numberOfArguments, const Ring2_Value* arguments);

/// @todo Should be <code>..._create(Machine_Rectangle2* self, size_t numberOfArguments, const Ring2_Value* arguments)</code>.
Machine_Rectangle2* Machine_Rectangle2_create();

/// @brief Set  the rectangle.
/// @param self This rectangle.
/// @param rectangle The rectangle.
void Machine_Rectangle2_setRectangle(Machine_Rectangle2* self, Ring3_Math_Rectangle2 const* rectangle);

/// @brief Get the rectangle.
/// @param self This rectangle.
/// @return The rectangle.
Ring3_Math_Rectangle2* Machine_Rectangle2_getRectangle(Machine_Rectangle2 const* self);

/// @brief Set the color of this rectangle.
/// @param self This rectangle. 
/// @param color The color.
void Machine_Rectangle2_setColor(Machine_Rectangle2* self, Ring3_Math_Vector4 const* color);

/// @brief Get the color of this rectangle.
/// @param self This rectangle.
/// @return The color.
Ring3_Math_Vector4 const* Machine_Rectangle2_getColor(Machine_Rectangle2 const* self);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
/// @todo Validate arguments.
void Machine_Rectangle2_setSize(Machine_Rectangle2* self, Ring3_Math_Vector2 const* size);

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size.
/// @todo Validate arguments.
Ring3_Math_Vector2 const* Machine_Rectangle2_getSize(Machine_Rectangle2 const* self);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param position The position.
/// @todo Validate arguments.
void Machine_Rectangle2_setPosition(Machine_Rectangle2* self, Ring3_Math_Vector2 const* position);

/// @brief Get the position of this rectangle.
/// @param self This rectangle.
/// @return The position.
/// @todo Validate arguments.
Ring3_Math_Vector2 const* Machine_Rectangle2_getPosition(Machine_Rectangle2 const* self);



#endif // MACHINE_GRAPHICS2_RECTANGLE2_H_INCLUDED
