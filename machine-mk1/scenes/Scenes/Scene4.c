#include "Scene4.h"


#include "Ring1/All/_Include.h"
#include "Ring3/Gdl/_Include.h"
#include "_Gui.h"
#include "_Images.h"
#include "_Text.h"
#include "_Video.h"
#include "_Fonts.h"
#include "_Graphics2.h"


#define FONT_FILE "fonts/RobotoSlab/RobotoSlab-Regular.ttf"
#define FONT_SIZE 20

static void Scene4_destruct(Scene4* self);

static void Scene4_visit(Scene4* self);

static void Scene4_constructClass(Scene4_Class* self);

struct Scene4_Class {
  Scene_Class __parent;
};

struct Scene4 {
  Scene __parent;

  //
  Machine_Gui_Context* guiContext;
  //
  Machine_Font* font;
  /// @brief Text layout #1.
  Machine_Text_Layout* text1;
  /// @brief Text layout #2.
  Machine_Text_Layout* text2;
  /// @brief Text node #1.
  Machine_Gui_TextNode* textNode1;
};

static void Scene4_destruct(Scene4* self);

static void Scene4_constructClass(Scene4_Class* self);

static void Scene4_visit(Scene4* self) {
  if (self->guiContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->guiContext);
  }
  if (self->font) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->font);
  }
  if (self->text1) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->text1);
  }
  if (self->text2) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->text2);
  }
  if (self->textNode1) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->textNode1);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene4, Scene, &Scene4_visit, &Scene4_construct, NULL,
                         &Scene4_constructClass, NULL)

static void Scene4_onStartup(Scene4* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  //
  self->guiContext = Machine_Gui_Context_create(Machine_Gdl_Context_create(),
                                                Machine_Context2_create(videoContext));
  //
  Machine_ImagesContext *imagesContext = Machines_DefaultImages_createContext();
  //
  Machine_FontsContext* fontsContext = Machine_DefaultFonts_createContext(videoContext, imagesContext);
  //
  self->font = Machine_FontsContext_createFont(fontsContext, Ring2_String_fromC(FONT_FILE), FONT_SIZE);
  //
  self->text1 = Machine_Text_Layout_create(Ring2_String_fromC(""), self->font);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Text_Layout_setText(self->text1, Ring2_String_fromC(text));
  }
  //
  self->text2 = Machine_Text_Layout_create(Ring2_String_fromC(""), self->font);
  {
    const char* text = "13 of 18 units\n7 of 9 units";
    Machine_Text_Layout_setText(self->text2, Ring2_String_fromC(text));
  }
  //
  self->textNode1 = Machine_Gui_TextNode_create(self->guiContext);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Gui_TextNode_setText(self->textNode1, Ring2_String_fromC(text));
  }
  //
  Ring3_Math_Vector4* c = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void alignLeftTop(Machine_Text_Layout* layout, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_Math_Vector2* MARGIN = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(MARGIN, 5.f, 5.f);

  const Ring3_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  const Ring3_Math_Vector2* position = Ring3_Math_Rectangle2_getPosition(bounds);
  Ring3_Math_Vector2* delta = Ring3_Math_Vector2_difference(MARGIN, position);
  Ring3_Math_Vector2* position2
      = Ring3_Math_Vector2_sum(Machine_Text_Layout_getPosition(layout), delta);
  Machine_Text_Layout_setPosition(layout, position2);
}

static void alignCenter(Machine_Text_Layout* layout, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_Math_Vector2* HALF = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(HALF, 0.5f, 0.5f);
  Ring3_Math_Vector2* CANVAS_SIZE = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(CANVAS_SIZE, width, height);
  Ring3_Math_Vector2* CANVAS_HALF_SIZE = Ring3_Math_Vector2_product(CANVAS_SIZE, HALF);
  Ring3_Math_Vector2* CANVAS_CENTER = Ring3_Math_Vector2_clone(CANVAS_HALF_SIZE);

  const Ring3_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  const Ring3_Math_Vector2* center = Ring3_Math_Rectangle2_getCenter(bounds);
  Ring3_Math_Vector2* delta = Ring3_Math_Vector2_difference(CANVAS_CENTER, center);
  const Ring3_Math_Vector2* oldPosition = Machine_Text_Layout_getPosition(layout);
  Ring3_Math_Vector2* newPosition = Ring3_Math_Vector2_sum(oldPosition, delta);
  Machine_Text_Layout_setPosition(layout, newPosition);
}

static void updateText1(Scene4* self, Ring2_Real32 width, Ring2_Real32 height) {
  alignCenter(self->text1, width, height);
}

static void updateText2(Scene4* self, Ring2_Real32 width, Ring2_Real32 height) {
  alignLeftTop(self->text2, width, height);
}

static void updateText3(Scene4* self, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_Math_Vector2* MARGIN = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(MARGIN, 5.f, height * 0.5f);
  Ring3_Math_Vector2* SIZE = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(SIZE, 64, 64);

  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->textNode1, SIZE);
  const Ring3_Math_Rectangle2* bounds
      = Machine_Gui_Widget_getRectangle((Machine_Gui_Widget*)self->textNode1);
  const Ring3_Math_Vector2* leftTop = Ring3_Math_Rectangle2_getPosition(bounds);
  Ring3_Math_Vector2* delta = Ring3_Math_Vector2_difference(MARGIN, leftTop);
  const Ring3_Math_Vector2* oldPosition
      = Machine_Gui_Widget_getPosition((Machine_Gui_Widget*)self->textNode1);
  const Ring3_Math_Vector2* newPosition = Ring3_Math_Vector2_sum(oldPosition, delta);
  Machine_Gui_Widget_setPosition((Machine_Gui_Widget*)self->textNode1, newPosition);
}

static void Scene4_onCanvasSizeChanged(Scene4* self, Ring3_CanvasSizeChangedEvent* event) {
  Machine_Gui_Context_onCanvasSizechanged(self->guiContext, event);
  updateText1(self, event->width, event->height);
  updateText2(self, event->width, event->height);
  updateText3(self, event->width, event->height);
}

static void Scene4_onUpdate(Scene4* self, Ring2_Real32 width, Ring2_Real32 height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(videoContext);

  Machine_Context2* context2 = Machine_Context2_create(videoContext);
  Machine_Context2_setTargetSize(context2, width, height);
  Machine_Text_Layout_render(self->text1, context2);
  Machine_Text_Layout_render(self->text2, context2);
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->textNode1, context2);
}

static void Scene4_onShutdown(Scene4* self) {
  self->font = NULL;
}

static void Scene4_constructClass(Scene4_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&Scene4_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene4_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene4_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene4_onShutdown;
}

void Scene4_construct(Scene4* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scene4_getType());
}

void Scene4_destruct(Scene4* self) {
  self->font = NULL;
}

Scene4* Scene4_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = Scene4_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)videoContext);
  Scene4* self = (Scene4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Ring2_jump();
  }
  return self;
}
