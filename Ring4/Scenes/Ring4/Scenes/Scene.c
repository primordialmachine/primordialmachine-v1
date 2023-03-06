#include "Ring4/Scenes/Scene.h"


#include "Ring1/All/_Include.h"
#include "Ring3/Visuals/_Include.h"


static void
onMousePointerEvent
  (
    Scene* self,
    Ring3_MousePointerEvent* event
  );

static void
onMouseButtonEvent
  (
    Scene* self,
    Ring3_MouseButtonEvent* event
  );

static void
onKeyboardKeyEvent
  (
    Scene* self,
    Ring3_KeyboardKeyEvent* event
  );

static void
Scene_destruct
  (
    Scene* self
  );

static void
Scene_visit
  (
    Scene* self
  );

static void
Scene_constructClass
  (
    Scene_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Scene,
                         Machine_Object,
                         &Scene_visit,
                         &Scene_construct,
                         &Scene_destruct,
                         &Scene_constructClass,
                         NULL)

static void
onMousePointerEvent
  (
    Scene* self,
    Ring3_MousePointerEvent* event
  )
{/*Intentionally empty.*/}

static void
onMouseButtonEvent
  (
    Scene* self,
    Ring3_MouseButtonEvent* event
  )
{/*Intentionally empty.*/}

static void
onKeyboardKeyEvent
  (
    Scene* self,
    Ring3_KeyboardKeyEvent* event
  )
{/*Intentionally empty.*/}

static void
Scene_constructClass
  (
    Scene_Class* self
  )
{
  self->onMouseButtonEvent = &onMouseButtonEvent;
  self->onMousePointerEvent = &onMousePointerEvent;
  self->onKeyboardKeyEvent = &onKeyboardKeyEvent;
}

static void
Scene_destruct
  (
    Scene* self
  )
{/*Intentionally empty.*/}

static void
Scene_visit
  (
    Scene* self
  )
{
  if (self->visualsContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->visualsContext);
  }
  if (self->imagesContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->imagesContext);
  }
  if (self->fontsContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->fontsContext);
  }
}

void
Scene_construct
  (
    Scene* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->visualsContext = (Ring3_VisualsContext*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                      arguments,
                                                                                      0,
                                                                                      Ring3_VisualsContext_getType());
  self->imagesContext = (Ring3_ImagesContext*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                    arguments,
                                                                                    1,
                                                                                    Ring3_ImagesContext_getType());
  self->fontsContext = (Ring3_FontsContext*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                  arguments,
                                                                                  2,
                                                                                  Ring3_FontsContext_getType());
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Scene_getType());
}

void
Scene_onStartup
  (
    Scene* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Scene, onStartup); }

void
Scene_onCanvasSizeChanged
  (
    Scene* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onCanvasSizeChanged, event); }

void
Scene_onMousePointerEvent
  (
    Scene* self,
    Ring3_MousePointerEvent* event
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onMousePointerEvent, event); }

void
Scene_onMouseButtonEvent
  (
    Scene* self,
    Ring3_MouseButtonEvent* event
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onMouseButtonEvent, event); }

void
Scene_onKeyboardKeyEvent
  (
    Scene* self,
    Ring3_KeyboardKeyEvent* event
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onKeyboardKeyEvent, event); }

void
Scene_onUpdate
  (
    Scene* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onUpdate, width, height); }

void
Scene_onShutdown
  (
    Scene* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Scene, onShutdown); }

Ring1_NoDiscardReturn() Ring3_VisualsContext*
Scene_getVisualsContext
  (
    Scene* self
  )
{ return self->visualsContext; }

Ring1_NoDiscardReturn() Ring3_FontsContext*
Scene_getFontsContext
  (
    Scene* self
  )
{ return self->fontsContext; }

Ring1_NoDiscardReturn() Ring3_ImagesContext*
Scene_getImagesContext
  (
    Scene* self
  )
{ return self->imagesContext; }
