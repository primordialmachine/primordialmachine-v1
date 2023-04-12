/// @file Ring3/Gui/WidgetBase.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/WidgetBase.h"

#include "Ring3/Gui/Context.h"
#undef RING3_GUI_PRIVATE


static void
Ring3_Gui_WidgetBase_constructClass
  (
    Ring3_Gui_WidgetBase_Class* self
  );

static void
Ring3_Gui_WidgetBase_visit
  (
    Ring3_Gui_WidgetBase* self
  );

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getPositionImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_WidgetBase_getRectangleImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getSizeImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static void
Ring3_Gui_WidgetBase_setPositionImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Vector2f32 const* position
  );

static void
Ring3_Gui_WidgetBase_setRectangleImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Rectangle2 const* rectangle
  );

static void
Ring3_Gui_WidgetBase_setSizeImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Vector2f32 const* size
  );

static void
Ring3_Gui_WidgetBase_emitImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static void
Ring3_Gui_WidgetBase_subscribeImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

static void
Ring3_Gui_WidgetBase_unsubscribeImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

static void
Ring3_Gui_WidgetBase_layoutImpl
  (
    Ring3_Gui_WidgetBase* self
  );

static void
Ring3_Gui_WidgetBase_translateImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Vector2f32 const* t
  );

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getAbsolutePositionImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getAbsoluteSizeImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_WidgetBase_getAbsoluteRectangleImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_WidgetBase_getNameImpl
  (
    Ring3_Gui_WidgetBase const* self
  );

static void
Ring3_Gui_WidgetBase_setNameImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name
  );

static void
Ring3_Gui_WidgetBase_implement_Ring3_Gui_Widget
  (
    Ring3_Gui_Widget_Dispatch* self
  )
{ 
  self->getPosition = (Ring3_Math_Vector2f32* (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getPositionImpl;
  self->getRectangle = (Ring3_Math_Rectangle2 * (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getRectangleImpl;
  self->getSize = (Ring3_Math_Vector2f32 * (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getSizeImpl;
  self->setPosition = (void (*)(Ring3_Gui_Widget*, Ring3_Math_Vector2f32 const*)) & Ring3_Gui_WidgetBase_setPositionImpl;
  self->setRectangle = (void (*)(Ring3_Gui_Widget*, Ring3_Math_Rectangle2 const*)) & Ring3_Gui_WidgetBase_setRectangleImpl;
  self->setSize = (void (*)(Ring3_Gui_Widget*, Ring3_Math_Vector2f32 const*)) & Ring3_Gui_WidgetBase_setSizeImpl;
  self->emit = (void (*)(Ring3_Gui_Widget*, Ring2_String*, size_t, Ring2_Value const*)) & Ring3_Gui_WidgetBase_emitImpl;
  self->subscribe = (void (*)(Ring3_Gui_Widget*, Ring2_String *, Machine_Object*, Ring2_ForeignProcedure*)) & Ring3_Gui_WidgetBase_subscribeImpl;
  self->unsubscribe = (void (*)(Ring3_Gui_Widget*, Ring2_String*, Machine_Object *, Ring2_ForeignProcedure*)) & Ring3_Gui_WidgetBase_unsubscribeImpl;
  self->layout = (void (*)(Ring3_Gui_Widget*)) & Ring3_Gui_WidgetBase_layoutImpl;
  self->translate = (void (*)(Ring3_Gui_Widget*, Ring3_Math_Vector2f32 const*)) & Ring3_Gui_WidgetBase_translateImpl;
  self->getAbsolutePosition = (Ring3_Math_Vector2f32 * (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getAbsolutePositionImpl;
  self->getAbsoluteSize = (Ring3_Math_Vector2f32 * (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getAbsoluteSizeImpl;
  self->getAbsoluteRectangle = (Ring3_Math_Rectangle2 * (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getAbsoluteRectangleImpl;
  self->getName = (Ring2_String * (*)(Ring3_Gui_Widget const*)) & Ring3_Gui_WidgetBase_getNameImpl;
  self->setName = (void (*)(Ring3_Gui_Widget*, Ring2_String*)) & Ring3_Gui_WidgetBase_setNameImpl;
}

static void
Ring3_Gui_WidgetBase_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement
    (
      self,
      Ring3_Gui_Widget_getType(),
      (Machine_InterfaceConstructCallback*)&Ring3_Gui_WidgetBase_implement_Ring3_Gui_Widget
    );
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_WidgetBase,
                         Machine_Object,
                         &Ring3_Gui_WidgetBase_visit,
                         &Ring3_Gui_WidgetBase_construct,
                         NULL,
                         &Ring3_Gui_WidgetBase_constructClass,
                         &Ring3_Gui_WidgetBase_implementInterfaces)

static void
Ring3_Gui_WidgetBase_visit
  (
    Ring3_Gui_WidgetBase* self
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
Ring3_Gui_WidgetBase_setRectangleImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Rectangle2 const* rectangle
  )
{
  Ring3_Math_Rectangle2_copy(self->rectangle, rectangle);
  Ring3_Gui_WidgetBase_emitPositionChangedSignal(self);
  Ring3_Gui_WidgetBase_emitSizeChangedSignal(self);
}

static void
Ring3_Gui_WidgetBase_setPositionImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Vector2f32 const* position
  )
{
  Ring3_Math_Rectangle2_setPosition(self->rectangle, position);
  Ring3_Gui_WidgetBase_emitPositionChangedSignal(self);
}

static void
Ring3_Gui_WidgetBase_setSizeImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Vector2f32 const* size
  )
{
  Ring3_Math_Rectangle2_setSize(self->rectangle, size);
  Ring3_Gui_WidgetBase_emitSizeChangedSignal(self);
}

static Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_WidgetBase_getRectangleImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{ return Ring3_Math_Rectangle2_clone(self->rectangle); }

static Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_WidgetBase_getCanvasRectangleImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{ return Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget const*)self); }

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getPositionImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{ return Ring3_Math_Rectangle2_getPosition(Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget const*)self)); }

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getSizeImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{ return Ring3_Math_Rectangle2_getSize(Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget const*)self)); }

static void
Ring3_Gui_WidgetBase_emitImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{ Machine_Signals_Signal_emit(self->signal, name, numberOfArguments, arguments); }

void
Ring3_Gui_WidgetBase_subscribeImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{ Machine_Signals_Signal_subscribe(self->signal, name, context, callback); }

static void
Ring3_Gui_WidgetBase_unsubscribeImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{ Machine_Signals_Signal_unsubscribe(self->signal, name, context, callback); }

static Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getAbsolutePositionImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{
  Ring3_Math_Vector2f32* position = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget*)self);
  if (self->parent) {
    Ring3_Math_Vector2f32_add(position, Ring3_Gui_Widget_getAbsolutePosition((Ring3_Gui_Widget*)self->parent), position);
  }
  return position;
}

static Ring3_Math_Vector2f32*
Ring3_Gui_WidgetBase_getAbsoluteSizeImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{ return Ring3_Gui_Widget_getSize((Ring3_Gui_Widget*)self); }

static Ring3_Math_Rectangle2*
Ring3_Gui_WidgetBase_getAbsoluteRectangleImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{
  Ring3_Math_Rectangle2* rectangle = Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget const*)self);
  if (self->parent) {
    Ring3_Math_Rectangle2_translate(rectangle, Ring3_Gui_Widget_getAbsolutePosition((Ring3_Gui_Widget*)self->parent));
  }
  return rectangle;
}

static void
Ring3_Gui_WidgetBase_layoutImpl
  (
    Ring3_Gui_WidgetBase* self
  )
{}

static Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_WidgetBase_getNameImpl
  (
    Ring3_Gui_WidgetBase const* self
  )
{ return self->name; }

static void
Ring3_Gui_WidgetBase_setNameImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* name
  )
{ self->name = name; }

static void
Ring3_Gui_WidgetBase_constructClass
  (
    Ring3_Gui_WidgetBase_Class* self
  )
{ }

void
Ring3_Gui_WidgetBase_construct
  (
    Ring3_Gui_WidgetBase* self,
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
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Gui_WidgetBase_getType());
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Ring3_Gui_WidgetBase_translateImpl
  (
    Ring3_Gui_WidgetBase* self,
    Ring3_Math_Vector2f32 const* t
  )
{
  Ring3_Math_Vector2f32* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget*)self);
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_sum(oldPosition, t);
  Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)self, newPosition);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Ring3_Gui_WidgetBase_emitPositionChangedSignal
  (
    Ring3_Gui_WidgetBase* self
  )
{
  Machine_Gui_Signals_Context* signalsContext = self->context->signalsContext;
  Ring3_Gui_WidgetBase_emitPropertyChanged(self, signalsContext->PositionChanged);
}

void
Ring3_Gui_WidgetBase_emitSizeChangedSignal
  (
    Ring3_Gui_WidgetBase* self
  )
{
  Machine_Gui_Signals_Context* signalsContext = self->context->signalsContext;
  Ring3_Gui_WidgetBase_emitPropertyChanged(self, signalsContext->SizeChanged);
}

void
Ring3_Gui_WidgetBase_emitPropertyChanged
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* propertyName
  )
{
  Machine_Gui_Signals_Context* signalsContext = self->context->signalsContext;
  size_t numberOfArguments = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)self);
  Ring3_Gui_Widget_emit((Ring3_Gui_Widget*)self, propertyName, numberOfArguments, arguments);
}
