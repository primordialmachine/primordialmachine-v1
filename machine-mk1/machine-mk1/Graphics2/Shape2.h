#if !defined(MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED)
#define MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED



#if !defined(MACHINE_GRAPHICS2_PRIVATE)
#error("Do not include this file directly, include `_Graphics2.h` instead.")
#endif
#include "_Math.h"


/// C-level representation of a shape.
MACHINE_DECLARE_CLASSTYPE(Machine_Shape2);

struct Machine_Shape2 {
  Machine_Object parent;
  void (*render)(Machine_Shape2* self, float width, float height);
};

void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, const Machine_Value* arguments);

void Machine_Shape2_render(Machine_Shape2* self, float width, float height);



#endif // MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED
