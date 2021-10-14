#include "Scene5.h"



#include <string.h>

#include "_GUI.h"
#include "_Images.h"
#include "_Video.h"

#include "_Fonts.h"
#include "_Graphics2.h"
#include "Video.h"

static void Scene5_constructClass(Scene5_Class* self);

static void Scene5_destruct(Scene5* self);

static void Scene5_visit(Scene5* self);

struct Scene5_Class {
  Scene_Class __parent;
};

struct Scene5 {
  Scene __parent;
  //
  Machine_GUI_Context* guiContext;
  //
  Machine_Font* font;
  /// @brief The main menu (start game, options, exit, credits).
  Machine_GUI_Group* mainMenu;
  /// @brief Header.
  Machine_GUI_Widget* header;
  /// @brief Footer.
  Machine_GUI_Widget* footer;
};

static void Scene5_visit(Scene5* self) {
  if (self->guiContext) {
    Machine_visit(self->guiContext);
  }
  if (self->font) {
    Machine_visit(self->font);
  }
  if (self->mainMenu) {
    Machine_visit(self->mainMenu);
  }
  if (self->header) {
    Machine_visit(self->header);
  }
  if (self->footer) {
    Machine_visit(self->footer);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene5, Scene, &Scene5_visit, &Scene5_construct, NULL, &Scene5_constructClass)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_GUI_Widget* loadWidget(Machine_GUI_Context* context, Machine_GDL_Node* node) {
  Machine_Map* map = Machine_GDL_Node_toMap(node, context->gdlContext->context);
  return Machine_GUI_Reader_readWidget(context, map);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_GUI_Widget* loadWidgetByPath(Machine_GUI_Context *context, const char* path) {
  Machine_String* inputPath = Machine_String_create(path, strlen(path));
  Machine_ByteBuffer* inputText = Machine_getFileContents(inputPath);
  Machine_GDL_Parser* parser = Machine_GDL_Parser_create();
  Machine_GDL_Node* node = Machine_GDL_Parser_parse(parser, inputPath, inputText);
  MACHINE_ASSERT(node->kind == Machine_GDL_NodeKind_CompilationUnit, Machine_Status_SemanticalError);
  Machine_Value temporary = Machine_List_getAt(node->children, 0);
  node = (Machine_GDL_Node*)Machine_Value_getObject(&temporary);
  MACHINE_ASSERT(node->kind == Machine_GDL_NodeKind_Map, Machine_Status_SemanticalError);
  return loadWidget(context, node);
}

static void Scene5_startup(Scene5* scene) {
  //
  scene->guiContext = Machine_GUI_Context_create(Machine_GDL_Context_create(), Machine_Context2_create(Machine_Video_getContext()));
  //
  Machine_FontsContext* fontsContext = Machine_DefaultFonts_createContext(Machine_Video_getContext(), Machines_DefaultImages_createContext());
  scene->font = Machine_FontsContext_createFont(fontsContext, Machine_String_create("RobotoSlab-Regular.ttf", strlen("RobotoSlab-Regular.ttf")), 20);
  //
  scene->mainMenu = (Machine_GUI_Group*)loadWidgetByPath(scene->guiContext, "scenes/scene5/mainMenu.txt");
  //
  scene->header = (Machine_GUI_Widget*)loadWidgetByPath(scene->guiContext, "scenes/scene5/header.txt");
  //
  scene->footer = (Machine_GUI_Widget*)loadWidgetByPath(scene->guiContext, "scenes/scene5/footer.txt");
  //
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(Machine_Video_getContext(), c);
}

static void renderText1(Scene5* self) {
  Machine_Context2* context = self->guiContext->context2;
  Machine_GUI_Widget_render((Machine_GUI_Widget*)self->mainMenu, context);
}

static void updateText1(Scene5* scene, Machine_CanvasSizeChangedEvent* event) {
  Machine_Math_Vector2* v = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(v, event->width, event->height);
  Machine_GUI_Context_setRootGroup(scene->guiContext, scene->mainMenu);
  Machine_GUI_Widget_setSize((Machine_GUI_Widget *)scene->mainMenu, v);

  Machine_GUI_Context_onRender(scene->guiContext);
}

static void renderHeader(Scene5* self) {
  Machine_Context2* context = self->guiContext->context2;
  float width = Machine_Context2_getTargetWidth(context);
  float height = Machine_Context2_getTargetHeight(context);
  Machine_Context2* tmp = Machine_Context2_create(Machine_Video_getContext());
  Machine_Context2_setTargetSize(tmp, width, height);
  Machine_GUI_Widget_render((Machine_GUI_Widget*)self->header, tmp);
}

Machine_Real Machine_Real_maxima(Machine_Real x, Machine_Real y) {
  return x > y ? x : y;
}

static void updateHeader(Scene5* scene, Machine_CanvasSizeChangedEvent* event) {
  static const float MARGIN_X = 5.f,
                     MARGIN_Y = 5.f;

  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, MARGIN_X, MARGIN_Y);
  Machine_Math_Vector2* canvasSize = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(canvasSize, event->width, event->height);
  // Set the size to the best size.
  const Machine_Math_Vector2* preferredSize = Machine_GUI_Widget_getPreferredSize(scene->header);
  Machine_Math_Vector2* temporary = Machine_Math_Vector2_create();
  float height = Machine_Math_Vector2_getY(canvasSize) * (1.f / 6.f);
  Machine_Math_Vector2_set(temporary, Machine_Real_maxima(Machine_Math_Vector2_getX(preferredSize),Machine_Math_Vector2_getX(canvasSize)) - Machine_Math_Vector2_getX(MARGIN)*2.f,
                                      height);
  Machine_GUI_Widget_setSize((Machine_GUI_Widget*)scene->header, temporary);
  // Set the position to the margins.
  Machine_GUI_Widget_setPosition((Machine_GUI_Widget*)scene->header, MARGIN);
}

static void renderFooter(Scene5* self) {
  Machine_Context2* context = self->guiContext->context2;
  float width = Machine_Context2_getTargetWidth(context);
  float height = Machine_Context2_getTargetHeight(context);
  Machine_Context2* tmp = Machine_Context2_create(Machine_Video_getContext());
  Machine_Context2_setTargetSize(tmp, width, height);
  Machine_GUI_Widget_render((Machine_GUI_Widget*)self->footer, tmp);
}

static void updateFooter(Scene5* scene, Machine_CanvasSizeChangedEvent *event) {
  static const float MARGIN_X = 5.f,
                     MARGIN_Y = 5.f;

  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, MARGIN_X, MARGIN_Y);
  Machine_Math_Vector2* canvasSize = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(canvasSize, event->width, event->height);
  // Set the size to the best size.
  const Machine_Math_Vector2* preferredSize = Machine_GUI_Widget_getPreferredSize(scene->footer);
  Machine_Math_Vector2* temporary = Machine_Math_Vector2_create();
  float height = Machine_Math_Vector2_getY(canvasSize) * (1.f / 6.f);
  Machine_Math_Vector2_set(temporary, Machine_Real_maxima(Machine_Math_Vector2_getX(preferredSize), Machine_Math_Vector2_getX(canvasSize)) - Machine_Math_Vector2_getX(MARGIN) * 2.f,
                           Machine_Math_Vector2_getY(canvasSize) * (1.f / 6.f));
  Machine_GUI_Widget_setSize((Machine_GUI_Widget*)scene->footer, temporary);
  // Set the position to the margins.
  Machine_Math_Vector2_set(temporary, Machine_Math_Vector2_getX(MARGIN), Machine_Math_Vector2_getY(canvasSize) - height - Machine_Math_Vector2_getY(MARGIN));
  Machine_GUI_Widget_setPosition((Machine_GUI_Widget*)scene->footer, temporary);
}

static void Scene5_onCanvasSizeChanged(Scene5* self, Machine_CanvasSizeChangedEvent* event) {
  Machine_GUI_Context_onCanvasSizechanged(self->guiContext, event);
  updateText1(self, event);
  updateHeader(self, event);
  updateFooter(self, event);
}

static void Scene5_update(Scene5* self, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(Machine_Video_getContext(), 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(Machine_Video_getContext());

  renderText1(self);
  renderHeader(self);
  renderFooter(self);
}

static void Scene5_shutdown(Scene5* scene) {
  scene->font = NULL;
}

static void Scene5_constructClass(Scene5_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene5_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene5_startup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene5_update;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene5_shutdown;
}

void Scene5_construct(Scene5* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Scene5_getClassType());
}

void Scene5_destruct(Scene5* self) {
  self->font = NULL;
}

Scene5* Scene5_create() {
  Machine_ClassType* ty = Scene5_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene5* scene = (Scene5*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
