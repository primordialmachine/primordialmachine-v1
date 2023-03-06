/// @file Ring3/Graphics2/Rectangle2.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GRAPHICS2_PRIVATE (1)
#include "Ring3/Graphics2/Rectangle2.h"

#include "Ring3/Graphics2/Context2.h"
#undef RING3_GRAPHICS2_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_Rectangle2_visit
  (
    Ring3_Rectangle2* self
  )
{
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

static void
Ring3_Rectangle2_render
  (
    Ring3_Rectangle2* self,
    Ring3_Context2* context
  )
{
  Ring3_Math_Matrix4x4f32 const*wvp2 = Ring3_Context2_getModelSpaceToProjectiveSpaceMatrix(context);

  Ring2_Real32 l = Ring3_Math_Vector2f32_getX(self->position);
  Ring2_Real32 r = l + Ring3_Math_Vector2f32_getX(self->size);
  Ring2_Real32 b = Ring3_Math_Vector2f32_getY(self->position);
  Ring2_Real32 t = b + Ring3_Math_Vector2f32_getY(self->size);

  static const uint8_t indices[] = {
    0, 1, 2,
    2, 1, 3,
  };

  struct {
    Ring2_Real32 x, y;
  } VERTICES[] =
  {
    { l, b, }, // left/bottom
    { r, b, }, // right/bottom
    { l, t, }, // left/top
    { r, t, }, // right/top
  };
  Ring3_GpuBuffer_setData(context->vertices, sizeof(VERTICES), (void const*)VERTICES);
  Ring3_Binding_bindMatrix4(context->binding, Ring2_String_fromC(true, "modelToProjectionMatrix"), wvp2);
  Ring3_Binding_bindVector4(context->binding, Ring2_String_fromC(true, "meshColor"), self->color);
  Ring3_Binding_activate(context->binding);
  Ring3_VisualsContext_drawIndirect(context->visualsContext, 0, 6, indices);
}

static void
Ring3_Rectangle2_constructClass
  (
    Ring3_Rectangle2_Class* self
  )
{
  ((Ring3_Shape2_Class*)self)->render = (void(*)(Ring3_Shape2*, Ring3_Context2*)) & Ring3_Rectangle2_render;
}

void
Ring3_Rectangle2_construct
  (
    Ring3_Rectangle2* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Shape2_construct((Ring3_Shape2*)self, numberOfArguments, arguments);
  self->position = Ring3_Math_Vector2f32_create();
  self->size = Ring3_Math_Vector2f32_create();

  self->color = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(self->color, 1.f, 1.f, 1.f, 1.f);

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Rectangle2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Rectangle2,
                         Ring3_Shape2,
                         &Ring3_Rectangle2_visit,
                         &Ring3_Rectangle2_construct,
                         NULL,
                         &Ring3_Rectangle2_constructClass,
                         NULL)

Ring3_Rectangle2*
Ring3_Rectangle2_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Rectangle2_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Rectangle2* self = (Ring3_Rectangle2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Ring3_Rectangle2_setRectangle
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Rectangle2 const* rectangle
  )
{
  Ring3_Math_Vector2f32_copy(self->position, Ring3_Math_Rectangle2_getPosition(rectangle));
  Ring3_Math_Vector2f32_copy(self->size, Ring3_Math_Rectangle2_getSize(rectangle));
}

Ring3_Math_Rectangle2*
Ring3_Rectangle2_getRectangle
  (
    Ring3_Rectangle2 const* self
  )
{
  Ring3_Math_Rectangle2* rectangle = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(rectangle, self->position);
  Ring3_Math_Rectangle2_setSize(rectangle, self->size);
  return rectangle;
}

void
Ring3_Rectangle2_setColor
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Vector4f32 const* color
  )
{ Ring3_Math_Vector4f32_copy(self->color, color); }

Ring3_Math_Vector4f32*
Ring3_Rectangle2_getColor
  (
    Ring3_Rectangle2 const* self
  )
{ return Ring3_Math_Vector4f32_clone(self->color); }

void
Ring3_Rectangle2_setSize
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Vector2f32 const* size
  )
{ Ring3_Math_Vector2f32_copy(self->size, size); }

Ring3_Math_Vector2f32*
Ring3_Rectangle2_getSize
  (
    Ring3_Rectangle2 const* self
  )
{ return Ring3_Math_Vector2f32_clone(self->size); }

void
Ring3_Rectangle2_setPosition
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Vector2f32 const* position
  )
{ Ring3_Math_Vector2f32_copy(self->position, position); }

Ring3_Math_Vector2f32*
Machine_Rectangle2_getPosition
  (
    Ring3_Rectangle2 const* self
  )
{ return Ring3_Math_Vector2f32_clone(self->position); }
