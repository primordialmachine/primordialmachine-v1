/// @file Gui/Widget.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/Widget.h"



#include "Gui/Context.h"



static void Machine_GUI_Widget_constructClass(Machine_GUI_Widget_Class* self);

static void Machine_GUI_Widget_visit(Machine_GUI_Widget* self);

MACHINE_DEFINE_CLASSTYPE(Machine_GUI_Widget, Machine_Object, &Machine_GUI_Widget_visit, &Machine_GUI_Widget_construct, NULL, &Machine_GUI_Widget_constructClass)

static void Machine_GUI_Widget_visit(Machine_GUI_Widget *self) {
  if (self->parent) {
    Machine_Gc_visit(self->parent);
  }
  if (self->rectangle) {
    Machine_Gc_visit(self->rectangle);
  }
  if (self->signal) {
    Machine_Gc_visit(self->signal);
  }
  if (self->context) {
    Machine_Gc_visit(self->context);
  }
}

static void Machine_GUI_Widget_setRectangleImpl(Machine_GUI_Widget* self, Machine_Math_Rectangle2 const* rectangle) {
  Machine_Math_Rectangle2_copy(self->rectangle, rectangle);
  Machine_GUI_Widget_emitPositionChangedSignal(self);
  Machine_GUI_Widget_emitSizeChangedSignal(self);
}

static void Machine_GUI_Widget_setPositionImpl(Machine_GUI_Widget* self, Machine_Math_Vector2 const* position) {
  Machine_Math_Rectangle2_setPosition(self->rectangle, position);
  Machine_GUI_Widget_emitPositionChangedSignal(self);
}

static void Machine_GUI_Widget_setSizeImpl(Machine_GUI_Widget* self, Machine_Math_Vector2 const* size) {
  Machine_Math_Rectangle2_setSize(self->rectangle, size);
  Machine_GUI_Widget_emitSizeChangedSignal(self);
}

static Machine_Math_Rectangle2 const* Machine_GUI_Widget_getRectangleImpl(Machine_GUI_Widget const* self) {
  return self->rectangle;
}

static Machine_Math_Rectangle2 const* Machine_GUI_Widget_getCanvasRectangleImpl(Machine_GUI_Widget const* self) {
  return Machine_GUI_Widget_getRectangle(self);
}

static Machine_Math_Vector2 const* Machine_GUI_Widget_getPositionImpl(Machine_GUI_Widget const* self) {
  return Machine_Math_Rectangle2_getPosition(Machine_GUI_Widget_getRectangle(self));
}

static Machine_Math_Vector2 const* Machine_GUI_Widget_getSizeImpl(Machine_GUI_Widget const* self) {
  return Machine_Math_Rectangle2_getSize(Machine_GUI_Widget_getRectangle(self));
}

static Machine_Math_Vector2 const* Machine_GUI_Widget_getAbsolutePositionImpl(Machine_GUI_Widget const* self) {
  Machine_Math_Vector2 const* position = Machine_GUI_Widget_getPosition(self);
  if (self->parent) {
    Machine_Math_Vector2* position_ = Machine_Math_Vector2_clone(position);
    Machine_Math_Vector2_add(position_, position_, Machine_GUI_Widget_getAbsolutePosition(self->parent));
    return position_;
  } else {
    return position;
  }
}

static Machine_Math_Rectangle2 const* Machine_GUI_Widget_getAbsoluteRectangleImpl(Machine_GUI_Widget const* self) {
  Machine_Math_Rectangle2 const* rectangle = Machine_GUI_Widget_getRectangle(self);
  if (self->parent) {
    Machine_Math_Rectangle2* rectangle_ = Machine_Math_Rectangle2_clone(rectangle);
    Machine_Math_Rectangle2_translate(rectangle_, Machine_GUI_Widget_getAbsolutePosition(self->parent));
    return rectangle_;
  } else {
    return rectangle;
  }
}

static Machine_Math_Rectangle2 const* Machine_GUI_Widget_getAbsoluteCanvasRectangleImpl(Machine_GUI_Widget const* self) {
  Machine_Math_Rectangle2 const* rectangle = Machine_GUI_Widget_getCanvasRectangle(self);
  if (self->parent) {
    Machine_Math_Rectangle2* rectangle_ = Machine_Math_Rectangle2_clone(rectangle);
    Machine_Math_Rectangle2_translate(rectangle_, Machine_Math_Rectangle2_getPosition(Machine_GUI_Widget_getAbsoluteCanvasRectangle(self->parent)));
    return rectangle_;
  } else {
    return rectangle;
  }
}

static void Machine_GUI_Widget_constructClass(Machine_GUI_Widget_Class* self) {
  self->getRectangle = (Machine_Math_Rectangle2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getRectangleImpl;
  self->getPosition = (Machine_Math_Vector2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getPositionImpl;
  self->getSize = (Machine_Math_Vector2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getSizeImpl;
  self->getCanvasRectangle = (Machine_Math_Rectangle2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getCanvasRectangleImpl;
  self->getAbsolutePosition = (Machine_Math_Vector2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getAbsolutePositionImpl;
  self->getAbsoluteRectangle = (Machine_Math_Rectangle2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getAbsoluteRectangleImpl;
  self->getAbsoluteCanvasRectangle = (Machine_Math_Rectangle2 const* (*)(Machine_GUI_Widget const*)) & Machine_GUI_Widget_getAbsoluteCanvasRectangleImpl;
  self->setRectangle = &Machine_GUI_Widget_setRectangleImpl;
  self->setPosition = &Machine_GUI_Widget_setPositionImpl;
  self->setSize = &Machine_GUI_Widget_setSizeImpl;
}

void Machine_GUI_Widget_construct(Machine_GUI_Widget* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  MACHINE_ASSERT(numberOfArguments == 1, Machine_Status_InvalidNumberOfArguments);
  self->context = (Machine_GUI_Context*)Machine_Value_getObject(&arguments[0]);
  self->rectangle = Machine_Math_Rectangle2_create();
  self->parent = NULL;
  self->signal = Machine_Signals_Signal_create();
  Machine_setClassType((Machine_Object*)self, Machine_GUI_Widget_getClassType());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_render(Machine_GUI_Widget* self, Machine_Context2* ctx2) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_GUI_Widget, render, ctx2);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setPosition(Machine_GUI_Widget* self, Machine_Math_Vector2 const* position) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_GUI_Widget, setPosition, position);
}

Machine_Math_Vector2 const* Machine_GUI_Widget_getPosition(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getPosition);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setSize(Machine_GUI_Widget* self, Machine_Math_Vector2 const* size) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_GUI_Widget, setSize, size);
}

Machine_Math_Vector2 const* Machine_GUI_Widget_getSize(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getSize);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setRectangle(Machine_GUI_Widget* self, Machine_Math_Rectangle2 const* rectangle) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_GUI_Widget, setRectangle, rectangle);
}

Machine_Math_Rectangle2 const* Machine_GUI_Widget_getRectangle(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getRectangle);
}

Machine_Math_Rectangle2 const* Machine_GUI_Widget_getCanvasRectangle(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getCanvasRectangle);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Math_Vector2 const* Machine_GUI_Widget_getPreferredSize(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getPreferredSize);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Math_Vector2 const* Machine_GUI_Widget_getAbsolutePosition(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getAbsolutePosition);
}

Machine_Math_Rectangle2 const* Machine_GUI_Widget_getAbsoluteRectangle(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getAbsoluteRectangle);
}

Machine_Math_Rectangle2 const* Machine_GUI_Widget_getAbsoluteCanvasRectangle(Machine_GUI_Widget const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_GUI_Widget, getAbsoluteCanvasRectangle);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_subscribe(Machine_GUI_Widget* self, Machine_String* name, Machine_Object* context, Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, name, context, callback);
}

void Machine_GUI_Widget_unsubscribe(Machine_GUI_Widget* self, Machine_String* name, Machine_Object* context, Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_unsubscribe(self->signal, name, context, callback);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_emitSignal(Machine_GUI_Widget* self, Machine_String* name, size_t numberOfArguments, Machine_Value const*arguments) {
  Machine_Signals_Signal_emit(self->signal, name, numberOfArguments, arguments);
}

void Machine_GUI_Widget_emitPositionChangedSignal(Machine_GUI_Widget* self) {
  Machine_GUI_Signals_Context* signalsContext = self->context->signalsContext;
  size_t numberOfArguments = 1;
  Machine_Value arguments[1];
  Machine_Value_setObject(&arguments[0], (Machine_Object *)self);
  Machine_GUI_Widget_emitSignal(self, signalsContext->PositionChanged, numberOfArguments, arguments);
}

void Machine_GUI_Widget_emitSizeChangedSignal(Machine_GUI_Widget* self) {
  Machine_GUI_Signals_Context* signalsContext = self->context->signalsContext;
  size_t numberOfArguments = 1;
  Machine_Value arguments[1];
  Machine_Value_setObject(&arguments[0], (Machine_Object*)self);
  Machine_GUI_Widget_emitSignal(self, signalsContext->SizeChanged, numberOfArguments, arguments);
}
