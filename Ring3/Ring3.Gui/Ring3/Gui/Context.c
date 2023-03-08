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
  if (self->graphics2Context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->graphics2Context);
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
  self->graphics2Context = (Ring3_Graphics2_Context*)Ring2_Value_getObject(&arguments[1]);
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
      Ring3_Graphics2_Context* context2
    )
{
  Machine_Type* ty = Machine_Gui_Context_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,gdlContext));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,context2));
  Machine_Gui_Context* self = Ring1_cast(Machine_Gui_Context*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

void
Machine_Gui_Context_onCanvasSizechanged
  (
    Machine_Gui_Context* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{ Ring3_Graphics2_Context_setTargetSize(self->graphics2Context, event->width, event->height); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Context_getCanvasWidth
  (
    Machine_Gui_Context* self
  )
{ return Ring3_Graphics2_Context_getTargetWidth(self->graphics2Context); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Context_getCanvasHeight
  (
    Machine_Gui_Context* self
  )
{ return Ring3_Graphics2_Context_getTargetHeight(self->graphics2Context); }

Ring1_NoDiscardReturn() Ring3_Graphics2_Context*
Machine_Gui_Context_getContext2
  (
    Machine_Gui_Context* self
  )
{ return self->graphics2Context; }
