/// @file Ring3/Gui/DefaultRenderContext.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/DefaultRenderContext.h"

#include "Ring3/Gui/RenderContext.h"
#undef RING3_GUI_PRIVATE



static void
Ring3_Gui_DefaultRenderContext_visit
  (
    Ring3_Gui_DefaultRenderContext* self
  );

static void
Ring3_Gui_DefaultRenderContext_construct
  (
    Ring3_Gui_DefaultRenderContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static Ring1_NoDiscardReturn() Ring3_Graphics2_Context*
Ring3_Gui_DefaultRenderContext_getContext2
  (
    Ring3_Gui_DefaultRenderContext* self
  );

static Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_DefaultRenderContext_getCanvasWidth
  (
    Ring3_Gui_DefaultRenderContext* self
  );

static Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_DefaultRenderContext_getCanvasHeight
  (
    Ring3_Gui_DefaultRenderContext* self
  );

static void
Ring3_Gui_DefaultRenderContext_visit
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{
  if (self->graphics2Context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->graphics2Context);
  }
}

static void
Ring3_Gui_DefaultRenderContext_construct
  (
    Ring3_Gui_DefaultRenderContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->graphics2Context = (Ring3_Graphics2_Context*)Ring2_Value_getObject(&arguments[0]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Gui_DefaultRenderContext_getType());
}

static Ring1_NoDiscardReturn() Ring3_Graphics2_Context*
Ring3_Gui_DefaultRenderContext_getContext2
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{ return self->graphics2Context; }

static Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_DefaultRenderContext_getCanvasWidth
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{ return Ring3_Graphics2_Context_getTargetWidth(self->graphics2Context); }

static Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_DefaultRenderContext_getCanvasHeight
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{ return Ring3_Graphics2_Context_getTargetHeight(self->graphics2Context); }

static void
implement_Ring3_Gui_RenderContext
  (
    Ring3_Gui_RenderContext_Dispatch* self
  )
{
  self->getContext2 = (Ring3_Graphics2_Context * (*)(Ring3_Gui_RenderContext*)) & Ring3_Gui_DefaultRenderContext_getContext2;
  self->getCanvasWidth = (Ring2_Real32 (*)(Ring3_Gui_RenderContext*)) & Ring3_Gui_DefaultRenderContext_getCanvasWidth;
  self->getCanvasHeight = (Ring2_Real32 (*)(Ring3_Gui_RenderContext*)) & Ring3_Gui_DefaultRenderContext_getCanvasHeight;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring3_Gui_RenderContext_getType(),
    (Machine_InterfaceConstructCallback*)&implement_Ring3_Gui_RenderContext);
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_DefaultRenderContext /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring3_Gui_DefaultRenderContext_visit /*visit*/,
                         &Ring3_Gui_DefaultRenderContext_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructclass*/,
                         &implementInterfaces /*implementInterfaces*/)

Ring1_NoDiscardReturn() Ring3_Gui_DefaultRenderContext*
Ring3_Gui_DefaultRenderContext_create
  (
    Ring3_Graphics2_Context* graphics2Context
  )
{
  Machine_Type* ty = Ring3_Gui_DefaultRenderContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,graphics2Context));
  Ring3_Gui_DefaultRenderContext* self = Ring1_cast(Ring3_Gui_DefaultRenderContext*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
