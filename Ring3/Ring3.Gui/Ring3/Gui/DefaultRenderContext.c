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

static Ring1_NoDiscardReturn() Ring3_Context2*
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
  if (self->context2) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->context2);
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
  self->context2 = (Ring3_Context2*)Ring2_Value_getObject(&arguments[0]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Gui_DefaultRenderContext_getType());
}

static Ring1_NoDiscardReturn() Ring3_Context2*
Ring3_Gui_DefaultRenderContext_getContext2
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{ return self->context2; }


static Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_DefaultRenderContext_getCanvasWidth
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{ return Ring3_Context2_getTargetWidth(self->context2); }

static Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_DefaultRenderContext_getCanvasHeight
  (
    Ring3_Gui_DefaultRenderContext* self
  )
{ return Ring3_Context2_getTargetHeight(self->context2); }



static void
implement_Ring3_Gui_RenderContext
  (
    Ring3_Gui_RenderContext_Dispatch* self
  )
{
  self->getContext2 = (Ring3_Context2* (*)(Ring3_Gui_RenderContext*)) & Ring3_Gui_DefaultRenderContext_getContext2;
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
    Ring3_Context2* context2
  )
{
  Machine_ClassType* ty = Ring3_Gui_DefaultRenderContext_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context2);
  Ring3_Gui_DefaultRenderContext* self = (Ring3_Gui_DefaultRenderContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
