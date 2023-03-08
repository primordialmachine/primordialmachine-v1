#include "Ring4/Scenes/Gui/Layout1.h"


#include "Ring1/All/_Include.h"
#include "Ring3/Gdl/_Include.h"
#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Text/_Include.h"
#include "Ring3/Visuals/_Include.h"
#include "Ring3/Gui/_Include.h"


static void
Ring4_Scenes_Gui_Layout1_constructClass
  (
    Ring4_Scenes_Gui_Layout1_Class* self
  );

static void
Ring4_Scenes_Gui_Layout1_destruct
  (
    Ring4_Scenes_Gui_Layout1* self
  );

static void
Ring4_Scenes_Gui_Layout1_visit
  (
    Ring4_Scenes_Gui_Layout1* self
  );

struct Ring4_Scenes_Gui_Layout1_Class {
  Scene_Class __parent;
};

typedef Ring2_Integer Ring4_Scenes_Gui_Layout1_Mode;
#define Ring4_Scenes_Gui_Layout1_Mode_DirectionColumn (0)
#define Ring4_Scenes_Gui_Layout1_Mode_DirectionRow (1)

struct Ring4_Scenes_Gui_Layout1 {
  Scene __parent;
  //
  Machine_Gui_Context* guiContext;
  Machine_Gui_Widget* help;
  Ring4_Scenes_Gui_Layout1_Mode mode;
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationCenter == 1
  /// @brief Direction column. Justification center.
  Machine_Gui_Widget* directionColumnJustificationCenter;
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationCenter == 1
  /// @brief Direction row. Justification center.
  Machine_Gui_Widget* directionRowJustificationCenter;
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationStart == 1
  /// @brief Direction column. Justification start.
  Machine_Gui_Widget* directionColumnJustificationStart;
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationStart == 1
  /// @brief Direction row. Justification start.
  Machine_Gui_Widget* directionRowJustificationStart;
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationEnd == 1
  /// @brief Direction column. Justification end.
  Machine_Gui_Widget* directionColumnJustificationEnd;
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationEnd == 1
  /// @brief Direction row. Justification end.
  Machine_Gui_Widget* directionRowJustificationEnd;
#endif
};

static void
Ring4_Scenes_Gui_Layout1_visit
  (
    Ring4_Scenes_Gui_Layout1* self
  )
{
  if (self->guiContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->guiContext);
  }
  if (self->help) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->help);
  }
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationCenter == 1
  if (self->directionColumnJustificationCenter) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->directionColumnJustificationCenter);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationCenter == 1
  if (self->directionRowJustificationCenter) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->directionRowJustificationCenter);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationStart == 1
  if (self->directionColumnJustificationStart) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->directionColumnJustificationStart);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationStart == 1
  if (self->directionRowJustificationStart) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->directionRowJustificationStart);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationEnd == 1
  if (self->directionColumnJustificationEnd) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->directionColumnJustificationEnd);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationEnd == 1
  if (self->directionRowJustificationEnd) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->directionRowJustificationEnd);
  }
#endif
}

MACHINE_DEFINE_CLASSTYPE(Ring4_Scenes_Gui_Layout1,
                         Scene,
                         &Ring4_Scenes_Gui_Layout1_visit,
                         &Ring4_Scenes_Gui_Layout1_construct,
                         NULL,
                         &Ring4_Scenes_Gui_Layout1_constructClass,
                         NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Gui_Widget*
loadWidget
  (
    Machine_Gui_Context* context,
    Machine_Gdl_Node* node
  )
{
  Ring2_Collections_Map* map = Machine_Gdl_Node_toMap(node, context->gdlContext->context);
  return Machine_Gui_Reader_readWidget(context, map);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Gui_Widget*
loadWidgetByPath
  (
    Machine_Gui_Context* context,
    const char* path
  )
{
  Ring2_String* inputPath = Ring2_String_fromC(false, path);
  Ring2_ByteBuffer* inputText = Machine_getFileContentsAsByteBuffer(inputPath);
  Machine_Gdl_Parser* parser = Machine_Gdl_Parser_create();
  Machine_Gdl_Node* node = Machine_Gdl_Parser_parse(parser, inputPath, inputText);
  Ring2_assert(node->kind == Machine_Gdl_NodeKind_CompilationUnit,
               Ring1_Status_InvalidSemantics);
  Ring2_Value temporary = Ring2_Collections_List_getAt(node->children, 0);
  node = (Machine_Gdl_Node*)Ring2_Value_getObject(&temporary);
  Ring2_assert(node->kind == Machine_Gdl_NodeKind_Map, Ring1_Status_InvalidSemantics);
  return loadWidget(context, node);
}

static void
Ring4_Scenes_Gui_Layout1_startup
  (
    Ring4_Scenes_Gui_Layout1* self
  )
{
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);
  Ring3_ImagesContext* imagesContext = Scene_getImagesContext((Scene*)self);
  Ring3_FontsContext* fontsContext = Scene_getFontsContext((Scene*)self);
  //
  self->mode = Ring4_Scenes_Gui_Layout1_Mode_DirectionRow;
  //
  self->guiContext = Machine_Gui_Context_create(Machine_Gdl_Context_create(),
                                                Ring3_Graphics2_Context_create(visualsContext, imagesContext, fontsContext));
  //
  self->help = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/help.txt");
  //
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationCenter == 1
  self->directionColumnJustificationCenter = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/direction-column-justification-center.txt");
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationCenter == 1
  self->directionRowJustificationCenter = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/direction-row-justification-center.txt");
#endif
  //
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationStart == 1
  self->directionColumnJustificationStart = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/direction-column-justification-start.txt");
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationStart == 1
  self->directionRowJustificationStart = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/direction-row-justification-start.txt");
#endif
  //
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationEnd == 1
  self->directionColumnJustificationEnd = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/direction-column-justification-end.txt");
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationEnd == 1
  self->directionRowJustificationEnd = loadWidgetByPath(self->guiContext, "Ring4/Scenes/Gui/Layout1/direction-row-justification-end.txt");
#endif
  //
  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Ring3_VisualsContext_setClearColor(visualsContext, c);
}

static void
updateHelp
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 4.f, event->height / 2.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, Machine_Gui_Widget_getPreferredSize(self->help));

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, event->width, event->height);

  Ring3_Math_Rectangle2_alignMaxXMaxY(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->help, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->help);
}

#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationCenter == 1
static void
updateDirectionColumnJustificationCenter
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 4.f, event->height / 2.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);
  
  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, s);

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, event->width / 2.f, event->height / 2.f);

  Ring3_Math_Rectangle2_alignCenter(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->directionColumnJustificationCenter, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->directionColumnJustificationCenter);
}
#endif

#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationCenter == 1
static void
updateDirectionRowJustificationCenter
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 2.f, event->height / 4.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, s);

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, event->width / 2.f, event->height / 2.f);

  Ring3_Math_Rectangle2_alignCenter(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->directionRowJustificationCenter, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->directionRowJustificationCenter);
}
#endif

#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationStart == 1
static void
updateDirectionColumnJustificationStart
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 4.f, event->height / 2.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, s);

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, 0.f, event->height / 2.f);

  Ring3_Math_Rectangle2_alignMinXCenterY(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->directionColumnJustificationStart, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->directionColumnJustificationStart);
}
#endif

#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationStart == 1
static void
updateDirectionRowJustificationStart
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 2.f, event->height / 4.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, s);

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, event->width / 2.f, 0.f);

  Ring3_Math_Rectangle2_alignCenterXMinY(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->directionRowJustificationStart, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->directionRowJustificationStart);
}
#endif

#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationEnd == 1
static void
updateDirectionColumnJustificationEnd
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 4.f, event->height / 2.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, s);

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, event->width, event->height / 2.f);

  Ring3_Math_Rectangle2_alignMaxXCenterY(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->directionColumnJustificationEnd, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->directionColumnJustificationEnd);
}
#endif

#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationEnd == 1
static void
updateDirectionRowJustificationEnd
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* s = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(s, event->width / 2.f, event->height / 4.f);

  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, 0.f, 0.f);

  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(r, p);
  Ring3_Math_Rectangle2_setSize(r, s);

  Ring3_Math_Vector2f32* c = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(c, event->width / 2.f, event->height);

  Ring3_Math_Rectangle2_alignCenterXMaxY(r, c);

  Machine_Gui_Widget_setRectangle((Machine_Gui_Widget*)self->directionRowJustificationEnd, r);

  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->directionRowJustificationEnd);
}
#endif

static void
Ring4_Scenes_Gui_Layout1_onCanvasSizeChanged
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Machine_Gui_Context_onCanvasSizechanged(self->guiContext, event);
  updateHelp(self, event);
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationCenter == 1
  updateDirectionColumnJustificationCenter(self, event);
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationCenter == 1
  updateDirectionRowJustificationCenter(self, event);
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationStart == 1
  updateDirectionColumnJustificationStart(self, event);
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationStart == 1
  updateDirectionRowJustificationStart(self, event);
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationEnd == 1
  updateDirectionColumnJustificationEnd(self, event);
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationEnd == 1
  updateDirectionRowJustificationEnd(self, event);
#endif
}

static void 
Ring4_Scenes_Gui_Layout1_update
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);

  // Set the viewport and clear its color buffer.
  Ring3_VisualsContext_setViewportRectangle(visualsContext, 0, 0, width, height);
  Ring3_VisualsContext_clearColorBuffer(visualsContext);

  Ring3_Gui_RenderContext* renderContext = (Ring3_Gui_RenderContext*)Ring3_Gui_DefaultRenderContext_create(self->guiContext->context2);

  Machine_Gui_Widget_render(self->help, renderContext);
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationCenter == 1
  if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionColumn) {
    Machine_Gui_Widget_render(self->directionColumnJustificationCenter, renderContext);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationCenter == 1
  if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionRow) {
    Machine_Gui_Widget_render(self->directionRowJustificationCenter, renderContext);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationStart == 1
  if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionColumn) {
    Machine_Gui_Widget_render(self->directionColumnJustificationStart, renderContext);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationStart == 1
  if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionRow) {
    Machine_Gui_Widget_render(self->directionRowJustificationStart, renderContext);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionColumnJustificationEnd == 1
  if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionColumn) {
    Machine_Gui_Widget_render(self->directionColumnJustificationEnd, renderContext);
  }
#endif
#if Ring4_Scenes_Gui_Layout1_withDirectionRowJustificationEnd == 1
  if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionRow) {
    Machine_Gui_Widget_render(self->directionRowJustificationEnd, renderContext);
  }
#endif
}

static void
Ring4_Scenes_Gui_Layout1_shutdown
  (
    Ring4_Scenes_Gui_Layout1* self
  )
{}

static void
Ring4_Scenes_Gui_Layout1_onKeyboardKeyEvent
  (
    Ring4_Scenes_Gui_Layout1* self,
    Ring3_KeyboardKeyEvent* event
  )
{
  if (event->action == Ring3_KeyboardKeyAction_Release && event->key == Ring3_KeyboardKey_F1) {
    if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionColumn) {
      self->mode = Ring4_Scenes_Gui_Layout1_Mode_DirectionRow;
    } else if (self->mode == Ring4_Scenes_Gui_Layout1_Mode_DirectionRow) {
      self->mode = Ring4_Scenes_Gui_Layout1_Mode_DirectionColumn;
    } else {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
  }
}

static void
Ring4_Scenes_Gui_Layout1_constructClass
  (
    Ring4_Scenes_Gui_Layout1_Class* self
  )
{
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Ring4_Scenes_Gui_Layout1_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Ring4_Scenes_Gui_Layout1_startup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Ring4_Scenes_Gui_Layout1_update;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Ring4_Scenes_Gui_Layout1_shutdown;
  ((Scene_Class*)self)->onKeyboardKeyEvent = (Scene_OnKeyboardKeyEventCallback*)&Ring4_Scenes_Gui_Layout1_onKeyboardKeyEvent;
}

void
Ring4_Scenes_Gui_Layout1_construct
  (
    Ring4_Scenes_Gui_Layout1* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring4_Scenes_Gui_Layout1_getType());
}

void
Ring4_Scenes_Gui_Layout1_destruct
  (
    Ring4_Scenes_Gui_Layout1* self
  )
{}

Ring1_NoDiscardReturn() Ring4_Scenes_Gui_Layout1*
Ring4_Scenes_Gui_Layout1_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  )
{
  Machine_Type* ty = Ring4_Scenes_Gui_Layout1_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&(arguments[0]), Ring1_cast(Machine_Object*,visualsContext));
  Ring2_Value_setObject(&(arguments[1]), Ring1_cast(Machine_Object*,imagesContext));
  Ring2_Value_setObject(&(arguments[2]), Ring1_cast(Machine_Object*,fontsContext));
  Ring4_Scenes_Gui_Layout1* self = Ring1_cast(Ring4_Scenes_Gui_Layout1*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
