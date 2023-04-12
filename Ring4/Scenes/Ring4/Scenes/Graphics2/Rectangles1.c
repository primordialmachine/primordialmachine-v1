#include "Ring4/Scenes/Graphics2/Rectangles1.h"


#include "Ring1/All/_Include.h"
#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Text/_Include.h"
#include "Ring3/Visuals/_Include.h"
#include "Ring3/Gui/_Include.h"


static void
Scenes_Graphics2_Rectangles1_onCanvasSizeChanged
  (
    Scenes_Graphics2_Rectangles1* self,
    Ring3_CanvasSizeChangedEvent* event
  );

static void
Scenes_Graphics2_Rectangles1_constructClass
  (
    Scenes_Graphics2_Rectangles1_Class* self
  );

static void
Scenes_Graphics2_Rectangles1_destruct
  (
    Scenes_Graphics2_Rectangles1* self
  );

static void
Scenes_Graphics2_Rectangles1_onShutdown
  (
    Scenes_Graphics2_Rectangles1* self
  );

static void
Scenes_Graphics2_Rectangles1_onStartup
  (
    Scenes_Graphics2_Rectangles1* self
  );

static void
Scenes_Graphics2_Rectangles1_onUpdate
  (
    Scenes_Graphics2_Rectangles1* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  );

static void
Scenes_Graphics2_Rectangles1_destruct
  (
    Scenes_Graphics2_Rectangles1* self
  );

static void
Scenes_Graphics2_Rectangles1_visit
  (
    Scenes_Graphics2_Rectangles1* self
  );

struct Scenes_Graphics2_Rectangles1_Class {
  Scene_Class parent;
};

struct Scenes_Graphics2_Rectangles1 {
  Scene parent;
  // The graphics 2 context.
  Ring3_Graphics2_Context * graphics2Context;
  // The first rectangle.
  Ring3_Graphics2_Rectangle* rectangle1;
  // The second rectangle.
  Ring3_Graphics2_Rectangle* rectangle2;
};

static void
Scenes_Graphics2_Rectangles1_visit
  (
    Scenes_Graphics2_Rectangles1* self
  )
{
  if (self->graphics2Context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->graphics2Context);
  }
  if (self->rectangle1) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rectangle1);
  }
  if (self->rectangle2) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rectangle2);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scenes_Graphics2_Rectangles1,
                         Scene,
                         &Scenes_Graphics2_Rectangles1_visit,
                         &Scenes_Graphics2_Rectangles1_construct,
                         NULL,
                         &Scenes_Graphics2_Rectangles1_constructClass,
                         NULL)


static void
Scenes_Graphics2_Rectangles1_constructClass
  (
    Scenes_Graphics2_Rectangles1_Class* self
  )
{
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scenes_Graphics2_Rectangles1_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scenes_Graphics2_Rectangles1_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scenes_Graphics2_Rectangles1_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scenes_Graphics2_Rectangles1_onShutdown;
}

static void
Scenes_Graphics2_Rectangles1_destruct
  (
    Scenes_Graphics2_Rectangles1* self
  )
{
  self->rectangle1 = NULL;
  self->rectangle2 = NULL;
  self->graphics2Context = NULL;
}

static void
Scenes_Graphics2_Rectangles1_onCanvasSizeChanged
  (
    Scenes_Graphics2_Rectangles1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);
  // Set the 2D context's target size.
  Ring3_Graphics2_Context_setTargetSize(self->graphics2Context, event->width, event->height);
  // Set the viewport rectangle.
  Ring3_VisualsContext_setViewportRectangle(visualsContext, 0, 0, event->width, event->height);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
  // Resize the first rectangle.
  r = Ring3_Math_Rectangle2_create();
  v = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(v, event->width / 2.f - event->width / 4.f,
                               event->height / 2.f - event->height / 4.f);
  Ring3_Math_Rectangle2_setPosition(r, v);
  Ring3_Math_Vector2f32_set(v, event->width / 2.f, event->height / 2.f);
  Ring3_Math_Rectangle2_setSize(r, v);
  Ring3_Graphics2_Rectangle_setRectangle(self->rectangle1, r);

  // Resize the first rectangle.
  r = Ring3_Math_Rectangle2_create();
  v = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(v, event->width - event->width / 4.f,
                               event->height - event->height / 4.f);
  Ring3_Math_Rectangle2_setPosition(r, v);
  Ring3_Math_Vector2f32_set(v, event->width / 4.f, event->height / 4.f);
  Ring3_Math_Rectangle2_setSize(r, v);
  Ring3_Graphics2_Rectangle_setRectangle(self->rectangle2, r);
}

static void
Scenes_Graphics2_Rectangles1_onUpdate
  (
    Scenes_Graphics2_Rectangles1* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);
  Scenes_Graphics2_Rectangles1_onCanvasSizeChanged(self, Ring3_CanvasSizeChangedEvent_create(width, height));
  // Clear color buffer.
  Ring3_VisualsContext_clearColorBuffer(visualsContext);
  // Render the rectangles.
  Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->rectangle1, self->graphics2Context);
  Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->rectangle2, self->graphics2Context);
}

static void
Scenes_Graphics2_Rectangles1_onShutdown
  (
    Scenes_Graphics2_Rectangles1* self
  )
{
  self->rectangle2 = NULL;
  self->rectangle1 = NULL;
  self->graphics2Context = NULL;
}

static void
Scenes_Graphics2_Rectangles1_onStartup
  (
    Scenes_Graphics2_Rectangles1* self
  )
{
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);
  Ring3_ImagesContext* imagesContext = Scene_getImagesContext((Scene*)self);
  Ring3_FontsContext* fontsContext = Scene_getFontsContext((Scene*)self);
  // Create the 2D context.
  self->graphics2Context = Ring3_Graphics2_Context_create(visualsContext, imagesContext, fontsContext);
  // Create the rectangles.
  self->rectangle1 = Ring3_Graphics2_Rectangle_create();
  self->rectangle2 = Ring3_Graphics2_Rectangle_create();
  // Set the clear color.
  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Ring3_VisualsContext_setClearColor(visualsContext, c);
}

void
Scenes_Graphics2_Rectangles1_construct
  (
    Scenes_Graphics2_Rectangles1* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scenes_Graphics2_Rectangles1_getType());
}

Ring1_NoDiscardReturn() Scenes_Graphics2_Rectangles1*
Scenes_Graphics2_Rectangles1_create
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  )
{
  Machine_Type* ty = Scenes_Graphics2_Rectangles1_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&(arguments[0]), Ring1_cast(Machine_Object*,videoContext));
  Ring2_Value_setObject(&(arguments[1]), Ring1_cast(Machine_Object*,imagesContext));
  Ring2_Value_setObject(&(arguments[2]), Ring1_cast(Machine_Object*,fontsContext));
  Scenes_Graphics2_Rectangles1* self = Ring1_cast(Scenes_Graphics2_Rectangles1*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
