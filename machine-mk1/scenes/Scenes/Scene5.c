#include "Scene5.h"

#include <string.h>

#include "_Gui.h"
#include "_Images.h"
#include "_Text.h"
#include "_Video.h"

#include "_Fonts.h"
#include "_Graphics2.h"

static void Scene5_constructClass(Scene5_Class* self);

static void Scene5_destruct(Scene5* self);

static void Scene5_visit(Scene5* self);

struct Scene5_Class {
  Scene_Class __parent;
};

struct Scene5 {
  Scene __parent;
  //
  Machine_Gui_Context* guiContext;
  /// @brief The main menu (start game, options, exit, credits).
  Machine_Gui_GroupNode* mainMenu;
  /// @brief Header.
  Machine_Gui_Widget* header;
  /// @brief Footer.
  Machine_Gui_Widget* footer;
};

static void Scene5_visit(Scene5* self) {
  if (self->guiContext) {
    Machine_Gc_visit(self->guiContext);
  }
  if (self->mainMenu) {
    Machine_Gc_visit(self->mainMenu);
  }
  if (self->header) {
    Machine_Gc_visit(self->header);
  }
  if (self->footer) {
    Machine_Gc_visit(self->footer);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene5, Scene, &Scene5_visit, &Scene5_construct, NULL,
                         &Scene5_constructClass, NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Gui_Widget* loadWidget(Machine_Gui_Context* context, Machine_Gdl_Node* node) {
  Machine_Map* map = Machine_Gdl_Node_toMap(node, context->gdlContext->context);
  return Machine_Gui_Reader_readWidget(context, map);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Gui_Widget* loadWidgetByPath(Machine_Gui_Context* context, const char* path) {
  Machine_String* inputPath = Machine_String_create(path, strlen(path));
  Machine_ByteBuffer* inputText = Machine_getFileContents(inputPath);
  Machine_Gdl_Parser* parser = Machine_Gdl_Parser_create();
  Machine_Gdl_Node* node = Machine_Gdl_Parser_parse(parser, inputPath, inputText);
  MACHINE_ASSERT(node->kind == Machine_Gdl_NodeKind_CompilationUnit,
                 Machine_Status_SemanticalError);
  Machine_Value temporary = Machine_List_getAt(node->children, 0);
  node = (Machine_Gdl_Node*)Machine_Value_getObject(&temporary);
  MACHINE_ASSERT(node->kind == Machine_Gdl_NodeKind_Map, Machine_Status_SemanticalError);
  return loadWidget(context, node);
}

static void Scene5_startup(Scene5* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  //
  self->guiContext = Machine_Gui_Context_create(Machine_Gdl_Context_create(),
                                                Machine_Context2_create(videoContext));
  //
  self->mainMenu
      = (Machine_Gui_GroupNode*)loadWidgetByPath(self->guiContext, "scenes/scene5/mainMenu.txt");
  //
  self->header
      = (Machine_Gui_Widget*)loadWidgetByPath(self->guiContext, "scenes/scene5/header.txt");
  //
  self->footer
      = (Machine_Gui_Widget*)loadWidgetByPath(self->guiContext, "scenes/scene5/footer.txt");
  //
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void renderText1(Scene5* self) {
  Machine_Context2* context = self->guiContext->context2;
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->mainMenu, context);
}

static void updateText1(Scene5* self, Machine_CanvasSizeChangedEvent* event) {
  Machine_Math_Vector2* v = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(v, event->width, event->height);
  Machine_Gui_Context_setRootGroup(self->guiContext, self->mainMenu);
  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->mainMenu, v);

  Machine_Gui_Context_onRender(self->guiContext);
}

static void renderHeader(Scene5* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  Machine_Context2* context = self->guiContext->context2;
  Machine_Real width = Machine_Context2_getTargetWidth(context);
  Machine_Real height = Machine_Context2_getTargetHeight(context);
  Machine_Context2* tmp = Machine_Context2_create(videoContext);
  Machine_Context2_setTargetSize(tmp, width, height);
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->header, tmp);
}

Machine_Real Machine_Real_maxima(Machine_Real x, Machine_Real y) {
  return x > y ? x : y;
}

static void updateHeader(Scene5* self, Machine_CanvasSizeChangedEvent* event) {
  static Machine_Real const MARGIN_X = 5.f, MARGIN_Y = 5.f;

  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, MARGIN_X, MARGIN_Y);
  Machine_Math_Vector2* canvasSize = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(canvasSize, event->width, event->height);
  // Set the size to the best size.
  Machine_Math_Vector2 const* preferredSize = Machine_Gui_Widget_getPreferredSize(self->header);
  Machine_Math_Vector2* temporary = Machine_Math_Vector2_create();
  Machine_Real height = Machine_Math_Vector2_getY(canvasSize) * (1.f / 6.f);
  Machine_Math_Vector2_set(temporary,
                           Machine_Real_maxima(Machine_Math_Vector2_getX(preferredSize),
                                               Machine_Math_Vector2_getX(canvasSize))
                               - Machine_Math_Vector2_getX(MARGIN) * 2.f,
                           height);
  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->header, temporary);
  // Set the position to the margins.
  Machine_Gui_Widget_setPosition((Machine_Gui_Widget*)self->header, MARGIN);
}

static void renderFooter(Scene5* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  Machine_Context2* context = self->guiContext->context2;
  Machine_Real width = Machine_Context2_getTargetWidth(context);
  Machine_Real height = Machine_Context2_getTargetHeight(context);
  Machine_Context2* tmp = Machine_Context2_create(videoContext);
  Machine_Context2_setTargetSize(tmp, width, height);
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->footer, tmp);
}

static void updateFooter(Scene5* self, Machine_CanvasSizeChangedEvent* event) {
  static Machine_Real const MARGIN_X = 5.f, MARGIN_Y = 5.f;

  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, MARGIN_X, MARGIN_Y);
  Machine_Math_Vector2* canvasSize = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(canvasSize, event->width, event->height);
  // Set the size to the best size.
  Machine_Math_Vector2 const* preferredSize = Machine_Gui_Widget_getPreferredSize(self->footer);
  Machine_Math_Vector2* temporary = Machine_Math_Vector2_create();
  Machine_Real height = Machine_Math_Vector2_getY(canvasSize) * (1.f / 6.f);
  Machine_Math_Vector2_set(temporary,
                           Machine_Real_maxima(Machine_Math_Vector2_getX(preferredSize),
                                               Machine_Math_Vector2_getX(canvasSize))
                               - Machine_Math_Vector2_getX(MARGIN) * 2.f,
                           Machine_Math_Vector2_getY(canvasSize) * (1.f / 6.f));
  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->footer, temporary);
  // Set the position to the margins.
  Machine_Math_Vector2_set(temporary, Machine_Math_Vector2_getX(MARGIN),
                           Machine_Math_Vector2_getY(canvasSize) - height
                               - Machine_Math_Vector2_getY(MARGIN));
  Machine_Gui_Widget_setPosition((Machine_Gui_Widget*)self->footer, temporary);
}

static void Scene5_onCanvasSizeChanged(Scene5* self, Machine_CanvasSizeChangedEvent* event) {
  Machine_Gui_Context_onCanvasSizechanged(self->guiContext, event);
  updateText1(self, event);
  updateHeader(self, event);
  updateFooter(self, event);
}

static void Scene5_update(Scene5* self, Machine_Real width, Machine_Real height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(videoContext);

  renderText1(self);
  renderHeader(self);
  renderFooter(self);
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

void Scene5_construct(Scene5* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Scene5_getType());
}

void Scene5_destruct(Scene5* self) {
}

Scene5* Scene5_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = Scene5_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Machine_Value ARGUMENTS[1];
  Machine_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)videoContext);
  Scene5* self = (Scene5*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Ring2_jump();
  }
  return self;
}
