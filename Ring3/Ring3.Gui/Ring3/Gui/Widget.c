/// @file Ring3/Gui/Widget.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Widget.h"

#include "Ring3/Gui/Context.h"
#undef RING3_GUI_PRIVATE


static void
Machine_Gui_Widget_constructClass
  (
    Machine_Gui_Widget_Class* self
  );

static void
Machine_Gui_Widget_visit
  (
    Machine_Gui_Widget* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Widget,
                         Machine_Object,
                         &Machine_Gui_Widget_visit,
                         &Machine_Gui_Widget_construct,
                         NULL,
                         &Machine_Gui_Widget_constructClass,
                         NULL)

static void
Machine_Gui_Widget_visit
  (
    Machine_Gui_Widget* self
  )
{
  if (self->parent) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->parent);
  }
  if (self->context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->context);
  }
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
  if (self->rectangle) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rectangle);
  }
  if (self->signal) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->signal);
  }
}

static void
Machine_Gui_Widget_setRectangleImpl
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Rectangle2 const* rectangle
  )
{
  Ring3_Math_Rectangle2_copy(self->rectangle, rectangle);
  Machine_Gui_Widget_emitPositionChangedSignal(self);
  Machine_Gui_Widget_emitSizeChangedSignal(self);
}

static void
Machine_Gui_Widget_setPositionImpl
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* position
  )
{
  Ring3_Math_Rectangle2_setPosition(self->rectangle, position);
  Machine_Gui_Widget_emitPositionChangedSignal(self);
}

static void
Machine_Gui_Widget_setSizeImpl
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* size
  )
{
  Ring3_Math_Rectangle2_setSize(self->rectangle, size);
  Machine_Gui_Widget_emitSizeChangedSignal(self);
}

static Ring3_Math_Rectangle2 const*
Machine_Gui_Widget_getRectangleImpl
  (
    Machine_Gui_Widget const* self
  )
{ return self->rectangle; }

static Ring3_Math_Rectangle2 const*
Machine_Gui_Widget_getCanvasRectangleImpl
  (
    Machine_Gui_Widget const* self
  )
{ return Machine_Gui_Widget_getRectangle(self); }

static Ring3_Math_Vector2f32*
Machine_Gui_Widget_getPositionImpl
  (
    Machine_Gui_Widget const* self
  )
{ return Ring3_Math_Rectangle2_getPosition(Machine_Gui_Widget_getRectangle(self)); }

static Ring3_Math_Vector2f32*
Machine_Gui_Widget_getSizeImpl
  (
    Machine_Gui_Widget const* self
  )
{ return Ring3_Math_Rectangle2_getSize(Machine_Gui_Widget_getRectangle(self)); }

static Ring3_Math_Vector2f32*
Machine_Gui_Widget_getAbsolutePositionImpl
  (
    Machine_Gui_Widget const* self
  )
{
  Ring3_Math_Vector2f32* position = Machine_Gui_Widget_getPosition(self);
  if (self->parent) {
    Ring3_Math_Vector2f32_add(position, Machine_Gui_Widget_getAbsolutePosition(self->parent), position);
  }
  return position;
}

static Ring3_Math_Rectangle2 const*
Machine_Gui_Widget_getAbsoluteRectangleImpl
  (
    Machine_Gui_Widget const* self
  )
{
  Ring3_Math_Rectangle2* rectangle = Machine_Gui_Widget_getRectangle(self);
  if (self->parent) {
    Ring3_Math_Rectangle2_translate(rectangle, Machine_Gui_Widget_getAbsolutePosition(self->parent));
  }
  return rectangle;
}

static Ring3_Math_Rectangle2 const*
Machine_Gui_Widget_getAbsoluteCanvasRectangleImpl
  (
    Machine_Gui_Widget const* self
  )
{
  Ring3_Math_Rectangle2* rectangle = Machine_Gui_Widget_getCanvasRectangle(self);
  if (self->parent) {
    Ring3_Math_Rectangle2_translate
      (
        rectangle,
        Ring3_Math_Rectangle2_getPosition
          (
            Machine_Gui_Widget_getAbsoluteCanvasRectangle(self->parent)
          )
      );
  }
  return rectangle;
}

static void
Machine_Gui_Widget_layoutImpl
  (
    Machine_Gui_Widget* self
  )
{}

static void
Machine_Gui_Widget_constructClass
  (
    Machine_Gui_Widget_Class* self
  )
{
  self->getRectangle = (Ring3_Math_Rectangle2 const* (*)(Machine_Gui_Widget const*))
                       & Machine_Gui_Widget_getRectangleImpl;
  self->getPosition = (Ring3_Math_Vector2f32* (*)(Machine_Gui_Widget const*))
                      & Machine_Gui_Widget_getPositionImpl;
  self->getSize = (Ring3_Math_Vector2f32* (*)(Machine_Gui_Widget const*))
                  & Machine_Gui_Widget_getSizeImpl;
  self->getCanvasRectangle = (Ring3_Math_Rectangle2* (*)(Machine_Gui_Widget const*))
                             & Machine_Gui_Widget_getCanvasRectangleImpl;
  self->getAbsolutePosition = (Ring3_Math_Vector2f32* (*)(Machine_Gui_Widget const*))
                              & Machine_Gui_Widget_getAbsolutePositionImpl;
  self->getAbsoluteRectangle = (Ring3_Math_Rectangle2* (*)(Machine_Gui_Widget const*))
                               & Machine_Gui_Widget_getAbsoluteRectangleImpl;
  self->getAbsoluteCanvasRectangle = (Ring3_Math_Rectangle2* (*)(Machine_Gui_Widget const*))
                                     & Machine_Gui_Widget_getAbsoluteCanvasRectangleImpl;
  self->setRectangle = &Machine_Gui_Widget_setRectangleImpl;
  self->setPosition = &Machine_Gui_Widget_setPositionImpl;
  self->setSize = &Machine_Gui_Widget_setSizeImpl;
  self->layout = &Machine_Gui_Widget_layoutImpl;
}

void
Machine_Gui_Widget_construct
  (
    Machine_Gui_Widget* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Ring2_assert(numberOfArguments == 1, Ring1_Status_InvalidNumberOfArguments);
  self->context = (Machine_Gui_Context*)Ring2_Value_getObject(&arguments[0]);
  self->rectangle = Ring3_Math_Rectangle2_create();
  self->parent = NULL;
  self->signal = Machine_Signals_Signal_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_Widget_getType());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_render
  (
    Machine_Gui_Widget* self,
    Ring3_Gui_RenderContext* renderContext
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Gui_Widget, render, renderContext); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_setPosition
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* position
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Gui_Widget, setPosition, position); }

Ring3_Math_Vector2f32*
Machine_Gui_Widget_getPosition
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getPosition); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_setSize
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* size
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Gui_Widget, setSize, size); }

Ring3_Math_Vector2f32*
Machine_Gui_Widget_getSize
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getSize); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_setRectangle
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Rectangle2 const* rectangle
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Gui_Widget, setRectangle, rectangle); }

Ring3_Math_Rectangle2*
Machine_Gui_Widget_getRectangle
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getRectangle); }

Ring3_Math_Rectangle2*
Machine_Gui_Widget_getCanvasRectangle
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getCanvasRectangle); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring3_Math_Vector2f32*
Machine_Gui_Widget_getPreferredSize
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getPreferredSize); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring3_Math_Vector2f32*
Machine_Gui_Widget_getAbsolutePosition
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getAbsolutePosition); }

Ring3_Math_Rectangle2*
Machine_Gui_Widget_getAbsoluteRectangle
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getAbsoluteRectangle); }

Ring3_Math_Rectangle2*
Machine_Gui_Widget_getAbsoluteCanvasRectangle
  (
    Machine_Gui_Widget const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Gui_Widget, getAbsoluteCanvasRectangle); }


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NoDiscardReturn() Ring2_String*
Machine_Gui_Widget_getName
  (
    Machine_Gui_Widget* self
  )
{ return self->name; }

void
Machine_Gui_Widget_setName
  (
    Machine_Gui_Widget* self,
    Ring2_String* name
  )
{ self->name = name; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_layout
  (
    Machine_Gui_Widget* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Gui_Widget, layout); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_subscribe
  (
    Machine_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{ Machine_Signals_Signal_subscribe(self->signal, name, context, callback); }

void
Machine_Gui_Widget_unsubscribe
  (
    Machine_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{ Machine_Signals_Signal_unsubscribe(self->signal, name, context, callback); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_emitSignal
  (
    Machine_Gui_Widget* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{ Machine_Signals_Signal_emit(self->signal, name, numberOfArguments, arguments); }

void
Machine_Gui_Widget_emitPositionChangedSignal
  (
    Machine_Gui_Widget* self
  )
{
  Machine_Gui_Signals_Context* signalsContext = self->context->signalsContext;
  size_t numberOfArguments = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)self);
  Machine_Gui_Widget_emitSignal(self, signalsContext->PositionChanged, numberOfArguments,
                                arguments);
}

void
Machine_Gui_Widget_emitSizeChangedSignal
  (
    Machine_Gui_Widget* self
  )
{
  Machine_Gui_Signals_Context* signalsContext = self->context->signalsContext;
  size_t numberOfArguments = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)self);
  Machine_Gui_Widget_emitSignal(self, signalsContext->SizeChanged, numberOfArguments, arguments);
}
