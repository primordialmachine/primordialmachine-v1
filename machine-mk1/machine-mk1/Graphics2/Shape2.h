#if !defined(MACHINE_SHAPE2_H_INCLUDED)
#define MACHINE_SHAPE2_H_INCLUDED


#include "_Math.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// C-level representation of a shape.
MACHINE_DECLARE_CLASSTYPE(Machine_Shape2);

void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, const Machine_Value* arguments);

void Machine_Shape2_render(Machine_Shape2* self, float width, float height);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// C-level representation of a rectangle.
/// The default position is (0,0).
/// The default size is (0,0).
/// The default color is (1,1,1,1).
/// @extends Machine_Shape2
MACHINE_DECLARE_CLASSTYPE(Machine_Rectangle2);

void Machine_Rectangle2_construct(Machine_Rectangle2* self, size_t numberOfArguments, const Machine_Value* arguments);

/// @todo Should be <code>..._create(Machine_Rectangle2* self, size_t numberOfArguments, const Machine_Value* arguments)</code>.
Machine_Rectangle2* Machine_Rectangle2_create();

/// @brief Set  the rectangle.
/// @param self This rectangle.
/// @param rectangle The rectangle.
void Machine_Rectangle2_setRectangle(Machine_Rectangle2* self, const Machine_Math_Rectangle2* rectangle);

/// @brief Get the rectangle.
/// @param self This rectangle.
/// @return The rectangle.
Machine_Math_Rectangle2* Machine_Rectangle2_getRectangle(const Machine_Rectangle2* self);

/// @brief Set the color of this rectangle.
/// @param self This rectangle. 
/// @param color The color.
void Machine_Rectangle2_setColor(Machine_Rectangle2* self, const Machine_Math_Vector4* color);

/// @brief Get the color of this rectangle.
/// @param self This rectangle.
/// @return The color.
const Machine_Math_Vector4* Machine_Rectangle2_getColor(const Machine_Rectangle2* self);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
/// @todo Validate arguments.
void Machine_Rectangle2_setSize(Machine_Rectangle2* self, const Machine_Math_Vector2* size);

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size.
/// @todo Validate arguments.
const Machine_Math_Vector2* Machine_Rectangle2_getSize(const Machine_Rectangle2* self);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param position The position.
/// @todo Validate arguments.
void Machine_Rectangle2_setPosition(Machine_Rectangle2* self, const Machine_Math_Vector2* position);

/// @brief Get the position of this rectangle.
/// @param self This rectangle.
/// @return The position.
/// @todo Validate arguments.
const Machine_Math_Vector2* Machine_Rectangle2_getPosition(const Machine_Rectangle2* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_SHAPE2_H_INCLUDED
