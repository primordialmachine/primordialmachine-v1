/// @file Graphics2/Rectangle2.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "Graphics2/Rectangle2.h"


#include "Ring1/Intrinsic.h"
#include "Graphics2/Context2.h"


static void Machine_Rectangle2_visit(Machine_Rectangle2* self) {
  if (self->position) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->position);
  }
  if (self->size) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->size);
  }
  if (self->color) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->color);
  }
}

static void Machine_Rectangle2_render(Machine_Rectangle2* self, Machine_Context2 *context) {
  Ring3_Math_Matrix4 const*wvp2 = Machine_Context2_getModelSpaceToProjectiveSpaceMatrix(context);

  Ring2_Real32 l = Ring3_Math_Vector2_getX(self->position);
  Ring2_Real32 r = l + Ring3_Math_Vector2_getX(self->size);
  Ring2_Real32 b = Ring3_Math_Vector2_getY(self->position);
  Ring2_Real32 t = b + Ring3_Math_Vector2_getY(self->size);

  static const uint8_t indices[] = {
    0, 1, 2,
    2, 1, 3,
  };

  struct {
    Ring2_Real32 x, y;
  }
  VERTICES[] =
  {
    { l, b, }, // left/bottom
    { r, b, }, // right/bottom
    { l, t, }, // left/top
    { r, t, }, // right/top
  };

  Machine_VideoBuffer_setData(context->vertices, sizeof(VERTICES), (void const*)VERTICES);

  Machine_Binding_activate(context->binding);
  Machine_Binding_bindMatrix4(context->binding, Ring2_String_create("modelToProjectionMatrix", crt_strlen("modelToProjectionMatrix") + 1), wvp2);
  Machine_Binding_bindVector4(context->binding, Ring2_String_create("mesh_color", crt_strlen("mesh_color") + 1), self->color);

  Machine_VideoContext_drawIndirect(context->videoContext, 0, 6, indices);
}

static void Machine_Rectangle2_constructClass(Machine_Rectangle2_Class* self) {
  ((Machine_Shape2_Class*)self)->render = (void(*)(Machine_Shape2*, Machine_Context2*)) & Machine_Rectangle2_render;
}

void Machine_Rectangle2_construct(Machine_Rectangle2* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Shape2_construct((Machine_Shape2*)self, numberOfArguments, arguments);
  self->position = Ring3_Math_Vector2_create();
  self->size = Ring3_Math_Vector2_create();

  self->color = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_set(self->color, 1.f, 1.f, 1.f, 1.f);

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Rectangle2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Rectangle2, Machine_Shape2, &Machine_Rectangle2_visit,
                         &Machine_Rectangle2_construct, NULL, &Machine_Rectangle2_constructClass,
                         NULL)

Machine_Rectangle2* Machine_Rectangle2_create() {
  Machine_ClassType* ty = Machine_Rectangle2_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Rectangle2* self = (Machine_Rectangle2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Rectangle2_setRectangle(Machine_Rectangle2* self, Ring3_Math_Rectangle2 const* rectangle) {
  Ring3_Math_Vector2_copy(self->position, Ring3_Math_Rectangle2_getPosition(rectangle));
  Ring3_Math_Vector2_copy(self->size, Ring3_Math_Rectangle2_getSize(rectangle));
}

Ring3_Math_Rectangle2* Machine_Rectangle2_getRectangle(Machine_Rectangle2 const* self) {
  Ring3_Math_Rectangle2* rectangle = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(rectangle, self->position);
  Ring3_Math_Rectangle2_setSize(rectangle, self->size);
  return rectangle;
}

void Machine_Rectangle2_setColor(Machine_Rectangle2* self, Ring3_Math_Vector4 const* color) {
  Ring3_Math_Vector4_copy(self->color, color);
}

Ring3_Math_Vector4 const* Machine_Rectangle2_getColor(Machine_Rectangle2 const* self) {
  return self->color;
}

void Machine_Rectangle2_setSize(Machine_Rectangle2* self, Ring3_Math_Vector2 const* size) {
  Ring3_Math_Vector2_copy(self->size, size);
}

Ring3_Math_Vector2 const* Machine_Rectangle2_getSize(Machine_Rectangle2 const* self) {
  return self->size;
}

void Machine_Rectangle2_setPosition(Machine_Rectangle2* self, Ring3_Math_Vector2 const* position) {
  Ring3_Math_Vector2_copy(self->position, position);
}

Ring3_Math_Vector2 const* Machine_Rectangle2_getPosition(Machine_Rectangle2 const* self) {
  return self->position;
}
