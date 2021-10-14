/// @file Graphics2/Rectangle2.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "./../Graphics2/Rectangle2.h"



#include "./../Graphics2/Context2.h"
#include <string.h>



static void Machine_Rectangle2_visit(Machine_Rectangle2* self) {
  if (self->position) {
    Machine_visit(self->position);
  }
  if (self->size) {
    Machine_visit(self->size);
  }
  if (self->color) {
    Machine_visit(self->color);
  }
}

static void Machine_Rectangle2_render(Machine_Rectangle2* self, Machine_Context2 *context) {
  Machine_Math_Matrix4 const*wvp2 = Machine_Context2_getModelSpaceToProjectiveSpaceMatrix(context);

  Machine_Real l = Machine_Math_Vector2_getX(self->position);
  Machine_Real r = l + Machine_Math_Vector2_getX(self->size);
  Machine_Real b = Machine_Math_Vector2_getY(self->position);
  Machine_Real t = b + Machine_Math_Vector2_getY(self->size);

  static const uint8_t indices[] = {
    0, 1, 2,
    2, 1, 3,
  };

  struct {
    Machine_Real x, y;
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
  Machine_Binding_bindMatrix4(context->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), wvp2);
  Machine_Binding_bindVector4(context->binding, Machine_String_create("mesh_color", strlen("mesh_color") + 1), self->color);

  Machine_VideoContext_drawIndirect(context->videoContext, 0, 6, indices);
}

static void Machine_Rectangle2_constructClass(Machine_Rectangle2_Class* self) {
  ((Machine_Shape2_Class*)self)->render = (void(*)(Machine_Shape2*, Machine_Context2*)) & Machine_Rectangle2_render;
}

void Machine_Rectangle2_construct(Machine_Rectangle2* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Shape2_construct((Machine_Shape2*)self, numberOfArguments, arguments);
  self->position = Machine_Math_Vector2_create();
  self->size = Machine_Math_Vector2_create();

  self->color = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(self->color, 1.f, 1.f, 1.f, 1.f);

  Machine_setClassType((Machine_Object*)self, Machine_Rectangle2_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Rectangle2, Machine_Shape2, &Machine_Rectangle2_visit, &Machine_Rectangle2_construct, NULL, &Machine_Rectangle2_constructClass)

Machine_Rectangle2* Machine_Rectangle2_create() {
  Machine_ClassType* ty = Machine_Rectangle2_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Rectangle2* self = (Machine_Rectangle2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Rectangle2_setRectangle(Machine_Rectangle2* self, Machine_Math_Rectangle2 const* rectangle) {
  Machine_Math_Vector2_copy(self->position, Machine_Math_Rectangle2_getPosition(rectangle));
  Machine_Math_Vector2_copy(self->size, Machine_Math_Rectangle2_getSize(rectangle));
}

Machine_Math_Rectangle2* Machine_Rectangle2_getRectangle(Machine_Rectangle2 const* self) {
  Machine_Math_Rectangle2* rectangle = Machine_Math_Rectangle2_create();
  Machine_Math_Rectangle2_setPosition(rectangle, self->position);
  Machine_Math_Rectangle2_setSize(rectangle, self->size);
  return rectangle;
}

void Machine_Rectangle2_setColor(Machine_Rectangle2* self, Machine_Math_Vector4 const* color) {
  Machine_Math_Vector4_copy(self->color, color);
}

Machine_Math_Vector4 const* Machine_Rectangle2_getColor(Machine_Rectangle2 const* self) {
  return self->color;
}

void Machine_Rectangle2_setSize(Machine_Rectangle2* self, Machine_Math_Vector2 const* size) {
  Machine_Math_Vector2_copy(self->size, size);
}

Machine_Math_Vector2 const* Machine_Rectangle2_getSize(Machine_Rectangle2 const* self) {
  return self->size;
}

void Machine_Rectangle2_setPosition(Machine_Rectangle2* self, Machine_Math_Vector2 const* position) {
  Machine_Math_Vector2_copy(self->position, position);
}

Machine_Math_Vector2 const* Machine_Rectangle2_getPosition(Machine_Rectangle2 const* self) {
  return self->position;
}
