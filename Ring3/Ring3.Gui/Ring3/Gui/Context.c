/// @file Ring3/Gui/Context.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Context.h"
#undef RING3_GUI_PRIVATE


static void
Machine_Gui_Context_visit
  (
    Machine_Gui_Context* self
  )
{
  if (self->gdlContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->gdlContext);
  }
  if (self->signalsContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->signalsContext);
  }
  if (self->rootWidget) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rootWidget);
  }
  if (self->context2) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->context2);
  }
  if (self->defaultFontFile) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->defaultFontFile);
  }
}

static void
Machine_Gui_Context_construct
  (
    Machine_Gui_Context* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->gdlContext = Ring3_Gui_Gdl_Context_create(
      (Machine_Gdl_Context*)Ring2_Value_getObject(&arguments[0]));
  self->signalsContext = Machine_Gui_Signals_Context_create();
  self->context2 = (Ring3_Context2*)Ring2_Value_getObject(&arguments[1]);
  static const char* FONT_FILE = "fonts/RobotoSlab/RobotoSlab-Regular.ttf";
  static const int FONT_SIZE = 16;
  self->defaultFontFile = Ring2_String_create(FONT_FILE, crt_strlen(FONT_FILE));
  self->defaultFontSize = FONT_SIZE;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Context,
                         Machine_Object,
                         &Machine_Gui_Context_visit,
                         &Machine_Gui_Context_construct,
                         NULL,
                         NULL,
                         NULL)

  Ring1_NoDiscardReturn() Machine_Gui_Context*
  Machine_Gui_Context_create
    (
      Machine_Gdl_Context* gdlContext,
      Ring3_Context2* context2
    )
{
  Machine_ClassType* ty = Machine_Gui_Context_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[2];
  Ring2_Value_setObject(&ARGUMENTS[0], (Machine_Object*)gdlContext);
  Ring2_Value_setObject(&ARGUMENTS[1], (Machine_Object*)context2);
  Machine_Gui_Context* self = (Machine_Gui_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Machine_Gui_Context_onCanvasSizechanged
  (
    Machine_Gui_Context* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{ Ring3_Context2_setTargetSize(self->context2, event->width, event->height); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Context_getCanvasWidth
  (
    Machine_Gui_Context* self
  )
{ return Ring3_Context2_getTargetWidth(self->context2); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Context_getCanvasHeight
  (
    Machine_Gui_Context* self
  )
{ return Ring3_Context2_getTargetHeight(self->context2); }

void
Machine_Gui_Context_setRootWidget
  (
    Machine_Gui_Context* self,
    Machine_Gui_Widget* rootWidget
  )
{ self->rootWidget = rootWidget; }

Ring1_NoDiscardReturn() Machine_Gui_Widget*
Machine_Gui_Context_getRootWidget
  (
    Machine_Gui_Context const* self
  )
{ return self->rootWidget; }

void
Machine_Gui_Context_onRender
  (
    Machine_Gui_Context* self
  )
{
  Ring2_Real32 targetWidth = Ring3_Context2_getTargetWidth(self->context2),
               targetHeight = Ring3_Context2_getTargetHeight(self->context2);
  Ring3_Math_Vector2f32* canvasSize = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(canvasSize, targetWidth, targetHeight);
  if (targetWidth > 0.f && targetHeight > 0.f && self->rootWidget) {
    Machine_Gui_Widget_setSize(self->rootWidget, canvasSize);
    Machine_Gui_Widget_layout(self->rootWidget);
  }
}
