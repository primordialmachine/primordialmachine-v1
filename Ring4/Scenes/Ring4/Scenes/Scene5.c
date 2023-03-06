#include "Ring4/Scenes/Scene5.h"


#include "Ring1/All/_Include.h"
#include "Ring3/Gdl/_Include.h"
#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Text/_Include.h"
#include "Ring3/Visuals/_Include.h"
#include "Ring3/Gui/_Include.h"


static void
Scene5_constructClass
  (
    Scene5_Class* self
  );

static void
Scene5_destruct
  (
    Scene5* self
  );

static void
Scene5_visit
  (
    Scene5* self
  );

struct Scene5_Class {
  Scene_Class __parent;
};

struct Scene5 {
  Scene __parent;
  //
  Machine_Gui_Context* guiContext;
  /// @brief The main menu (start game, options, exit, credits).
  Machine_Gui_Widget* mainMenu;
  /// @brief Header.
  Machine_Gui_Widget* header;
  /// @brief Footer.
  Machine_Gui_Widget* footer;
  // @brief The group containing the.
  Machine_Gui_GroupNode* group;
};

static void
Scene5_visit
  (
    Scene5* self
  )
{
  if (self->guiContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->guiContext);
  }
  if (self->group) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->group);
  }
  if (self->mainMenu) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->mainMenu);
  }
  if (self->header) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->header);
  }
  if (self->footer) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->footer);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene5,
                         Scene,
                         &Scene5_visit,
                         &Scene5_construct,
                         NULL,
                         &Scene5_constructClass,
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
Scene5_startup
  (
    Scene5* self
  )
{
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);
  Ring3_ImagesContext* imagesContext = Scene_getImagesContext((Scene*)self);
  Ring3_FontsContext* fontsContext = Scene_getFontsContext((Scene*)self);
  //
  self->guiContext = Machine_Gui_Context_create(Machine_Gdl_Context_create(),
                                                Ring3_Context2_create(visualsContext, imagesContext, fontsContext));
  //
  self->mainMenu = loadWidgetByPath(self->guiContext, "scenes/scene5/mainMenu.txt");
  //
  self->header = loadWidgetByPath(self->guiContext, "scenes/scene5/header.txt");
  //
  self->footer = loadWidgetByPath(self->guiContext, "scenes/scene5/footer.txt");
  self->group = Machine_Gui_GroupNode_create(self->guiContext);
  Ring2_Value v;
  {
    Ring2_Value_setObject(&v, (Machine_Object*)self->header);
    Ring2_Collections_List_append((Ring2_Collections_List*)self->group->children, v);
  }
  {
    Ring2_Value_setObject(&v, (Machine_Object*)self->mainMenu);
    Ring2_Collections_List_append((Ring2_Collections_List*)self->group->children, v);
  }
  {
    Ring2_Value_setObject(&v, (Machine_Object*)self->footer);
    Ring2_Collections_List_append((Ring2_Collections_List*)self->group->children, v);
  }
  //
  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Ring3_VisualsContext_setClearColor(visualsContext, c);
}

static void
updateMainMenu
  (
    Scene5* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(v, event->width, event->height);
  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->mainMenu, v);
  Machine_Gui_Widget_layout((Machine_Gui_Widget*)self->mainMenu);
}

static void
updateHeader
  (
    Scene5* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  static Ring2_Real32 const MARGIN_X = 5.f, MARGIN_Y = 5.f;

  Ring3_Math_Vector2f32* MARGIN = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(MARGIN, MARGIN_X, MARGIN_Y);
  Ring3_Math_Vector2f32* canvasSize = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(canvasSize, event->width, event->height);
  // Set the size to the best size.
  Ring3_Math_Vector2f32 const* preferredSize = Machine_Gui_Widget_getPreferredSize(self->header);
  Ring3_Math_Vector2f32* temporary = Ring3_Math_Vector2f32_create();
  Ring2_Real32 height = Ring3_Math_Vector2f32_getY(canvasSize) * (1.f / 6.f);
  Ring3_Math_Vector2f32_set(temporary,
                            Ring2_Real32_greatest(Ring3_Math_Vector2f32_getX(preferredSize),
                                                  Ring3_Math_Vector2f32_getX(canvasSize))
                            - Ring3_Math_Vector2f32_getX(MARGIN) * 2.f,
                            height);
  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->header, temporary);
  // Set the position to the margins.
  Machine_Gui_Widget_setPosition((Machine_Gui_Widget*)self->header, MARGIN);
}

static void
updateFooter
  (
    Scene5* self,
    Ring3_CanvasSizeChangedEvent* event
  )
{
  static Ring2_Real32 const MARGIN_X = 5.f, MARGIN_Y = 5.f;

  Ring3_Math_Vector2f32* MARGIN = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(MARGIN, MARGIN_X, MARGIN_Y);
  Ring3_Math_Vector2f32* canvasSize = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(canvasSize, event->width, event->height);
  // Set the size to the best size.
  Ring3_Math_Vector2f32 const* preferredSize = Machine_Gui_Widget_getPreferredSize(self->footer);
  Ring3_Math_Vector2f32* temporary = Ring3_Math_Vector2f32_create();
  Ring2_Real32 height = Ring3_Math_Vector2f32_getY(canvasSize) * (1.f / 6.f);
  Ring3_Math_Vector2f32_set(temporary,
                            Ring2_Real32_greatest(Ring3_Math_Vector2f32_getX(preferredSize),
                                                  Ring3_Math_Vector2f32_getX(canvasSize))
                            - Ring3_Math_Vector2f32_getX(MARGIN) * 2.f,
                            Ring3_Math_Vector2f32_getY(canvasSize) * (1.f / 6.f));
  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->footer, temporary);
  // Set the position to the margins.
  Ring3_Math_Vector2f32_set(temporary, Ring3_Math_Vector2f32_getX(MARGIN),
                            Ring3_Math_Vector2f32_getY(canvasSize) - height
                            - Ring3_Math_Vector2f32_getY(MARGIN));
  Machine_Gui_Widget_setPosition((Machine_Gui_Widget*)self->footer, temporary);
}

static void Scene5_onCanvasSizeChanged(Scene5* self, Ring3_CanvasSizeChangedEvent* event) {
  Machine_Gui_Context_onCanvasSizechanged(self->guiContext, event);
  updateMainMenu(self, event);
  updateHeader(self, event);
  updateFooter(self, event);
}

static void Scene5_update(Scene5* self, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);

  // Set the viewport and clear its color buffer.
  Ring3_VisualsContext_setViewportRectangle(visualsContext, 0, 0, width, height);
  Ring3_VisualsContext_clearColorBuffer(visualsContext);

  Ring3_Gui_RenderContext* renderContext = (Ring3_Gui_RenderContext*)Ring3_Gui_DefaultRenderContext_create(self->guiContext->context2);

  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->mainMenu, renderContext);
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->header, renderContext);
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->footer, renderContext);
}

static void Scene5_shutdown(Scene5* self) {
}

static void Scene5_constructClass(Scene5_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&Scene5_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene5_startup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene5_update;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene5_shutdown;
}

void Scene5_construct(Scene5* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scene5_getType());
}

void Scene5_destruct(Scene5* self) {
}

Scene5*
Scene5_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  )
{
  Machine_ClassType* ty = Scene5_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)visualsContext);
  Ring2_Value_setObject(&(ARGUMENTS[1]), (Machine_Object*)imagesContext);
  Ring2_Value_setObject(&(ARGUMENTS[2]), (Machine_Object*)fontsContext);
  Scene5* self = (Scene5*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Ring2_jump();
  }
  return self;
}
