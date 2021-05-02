#if !defined(MACHINE_SHAPE2_H_INCLUDED)
#define MACHINE_SHAPE2_H_INCLUDED

#include "./Machine.h"
#include "./Math/Vector2.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// C-level representation of a shape.
typedef struct Machine_Shape2 Machine_Shape2;

void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, const Machine_Value* arguments);

void Machine_Shape2_render(Machine_Shape2* self, float width, float height);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// C-level representation of a rectangle.
/// @extends Machine_Shape2
typedef struct Machine_Rectangle2 Machine_Rectangle2;

void Machine_Rectangle2_construct(Machine_Rectangle2* self, size_t numberOfArguments, const Machine_Value* arguments);

/// @todo Should be <code>..._create(Machine_Rectangle2* self, size_t numberOfArguments, const Machine_Value* arguments)</code>.
Machine_Rectangle2* Machine_Rectangle2_create();

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
/// @todo Validate arguments.
void Machine_Rectangle2_setSize(Machine_Rectangle2* self, Machine_Math_Vector2* size);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param position The position.
/// @todo Validate arguments.
void Machine_Rectangle2_setPosition(Machine_Rectangle2* self, Machine_Math_Vector2* position);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_SHAPE2_H_INCLUDED
