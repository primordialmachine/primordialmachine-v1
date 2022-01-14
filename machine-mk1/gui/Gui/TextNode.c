/// @file Gui/TextNode.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/TextNode.h"

#include "Gui/Context.h"
#include "Gui/Widget.h"
#include "_Graphics2.h"
#include "_Images.h"
#include "_Text.h"
#include "_Video.h"
#include <string.h>

struct Machine_Gui_TextNode_Class {
  Machine_Gui_Widget_Class __parent;
};

struct Machine_Gui_TextNode {
  Machine_Gui_Widget __parent;

  /// @brief The layout for rendering the text.
  Machine_Text_Layout* foreground;

  /// @brief The shape for rendering the background.
  Machine_Rectangle2* background;

  bool childDirty;
};

static void Machine_Gui_TextNode_visit(Machine_Gui_TextNode* self) {
  if (self->foreground) {
    Machine_Gc_visit(self->foreground);
  }
  if (self->background) {
    Machine_Gc_visit(self->background);
  }
}

static Machine_Math_Vector2 const* Machine_Gui_TextNode_getPreferredSize(
    Machine_Gui_TextNode const* self);

static void Machine_Gui_TextNode_render(Machine_Gui_TextNode* self, Machine_Context2* ctx2);

static Machine_Value boundsChangedCallback(size_t numberOfArguments,
                                           Machine_Value const* arguments) {
  MACHINE_ASSERT(numberOfArguments == 2, Machine_Status_InvalidNumberOfArguments);
  Machine_Gui_TextNode* self = (Machine_Gui_TextNode*)Machine_Value_getObject(&arguments[0]);
  self->childDirty = true;
  Machine_Value result;
  Machine_Value_setVoid(&result, Machine_Void_Void);
  return result;
}

static void Machine_Gui_TextNode_constructClass(Machine_Gui_TextNode_Class* self) {
  ((Machine_Gui_Widget_Class*)self)->render
      = (void (*)(Machine_Gui_Widget*, Machine_Context2*)) & Machine_Gui_TextNode_render;
  ((Machine_Gui_Widget_Class*)self)->getPreferredSize
      = (Machine_Math_Vector2 const* (*)(Machine_Gui_Widget const*))
        & Machine_Gui_TextNode_getPreferredSize;
}

void Machine_Gui_TextNode_construct(Machine_Gui_TextNode* self, size_t numberOfArguments,
                                    Machine_Value const* arguments) {
  Machine_Gui_Widget_construct((Machine_Gui_Widget*)self, numberOfArguments, arguments);
  Machine_Gui_Context* guiContext = (Machine_Gui_Context*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 0, Machine_Gui_Context_getType());
  Machine_FontsContext* fontsContext = Machine_DefaultFonts_createContext(
      guiContext->context2->videoContext, Machines_DefaultImages_createContext());
  Machine_Font* font = Machine_FontsContext_createFont(fontsContext, guiContext->defaultFontFile, guiContext->defaultFontSize);
  self->foreground = Machine_Text_Layout_create(Machine_String_create("", strlen("")), font);
  self->background = Machine_Rectangle2_create();
  self->childDirty = true;
  Machine_Gui_Widget_subscribe(
      (Machine_Gui_Widget*)self,
      ((Machine_Gui_Widget*)self)->context->signalsContext->PositionChanged, (Machine_Object*)self,
      &boundsChangedCallback);
  Machine_Gui_Widget_subscribe((Machine_Gui_Widget*)self,
                               ((Machine_Gui_Widget*)self)->context->signalsContext->SizeChanged,
                               (Machine_Object*)self, &boundsChangedCallback);
  Machine_setClassType((Machine_Object*)self, Machine_Gui_TextNode_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_TextNode, Machine_Gui_Widget, &Machine_Gui_TextNode_visit,
                         &Machine_Gui_TextNode_construct, NULL,
                         &Machine_Gui_TextNode_constructClass, NULL)

Machine_Gui_TextNode* Machine_Gui_TextNode_create(Machine_Gui_Context* context) {
  Machine_ClassType* ty = Machine_Gui_TextNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Machine_Value arguments[1] = { Machine_Value_StaticInitializerVoid() };
  Machine_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_Gui_TextNode* self
      = (Machine_Gui_TextNode*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Math_Vector2 const* Machine_Gui_TextNode_getPreferredSize(
    Machine_Gui_TextNode const* self) {
  return Machine_Math_Rectangle2_getSize(Machine_Text_Layout_getBounds(self->foreground));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextNode_setText(Machine_Gui_TextNode* self, Machine_String* text) {
  Machine_Text_Layout_setText(self->foreground, text);
  Machine_Gui_Widget_emitPositionChangedSignal((Machine_Gui_Widget*)self);
  Machine_Gui_Widget_emitSizeChangedSignal((Machine_Gui_Widget*)self);
}

Machine_String* Machine_Gui_TextNode_getText(Machine_Gui_TextNode const* self) {
  return Machine_Text_Layout_getText(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextNode_setBackgroundColor(Machine_Gui_TextNode* self,
                                             Machine_Math_Vector4 const* backgroundColor) {
  Machine_Rectangle2_setColor(self->background, backgroundColor);
  Machine_Gui_Widget_emitPositionChangedSignal((Machine_Gui_Widget*)self);
  Machine_Gui_Widget_emitSizeChangedSignal((Machine_Gui_Widget*)self);
}

Machine_Math_Vector4 const* Machine_Gui_TextNode_getBackgroundColor(
    Machine_Gui_TextNode const* self) {
  return Machine_Rectangle2_getColor(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextNode_setForegroundColor(Machine_Gui_TextNode* self,
                                             Machine_Math_Vector3 const* foregroundColor) {
  Machine_Text_Layout_setColor(self->foreground, foregroundColor);
  Machine_Gui_Widget_emitPositionChangedSignal((Machine_Gui_Widget*)self);
  Machine_Gui_Widget_emitSizeChangedSignal((Machine_Gui_Widget*)self);
}

Machine_Math_Vector3 const* Machine_Gui_TextNode_getForegroundColor(
    Machine_Gui_TextNode const* self) {
  return Machine_Text_Layout_getColor(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Gui_TextNode_render2(Machine_Gui_TextNode* self, Machine_Real width,
                                         Machine_Real height) {
  Machine_Context2* ctx2 = ((Machine_Gui_Widget*)self)->context->context2;
  Machine_Context2_setTargetSize(ctx2, width, height);
  if (self->childDirty) {
    Machine_Gui_Context* ctx = ((Machine_Gui_Widget*)self)->context;
    Machine_Rectangle2_setRectangle(self->background, ((Machine_Gui_Widget*)self)->rectangle);
    // TODO: Only do this layouting if necessary.
    Machine_Math_Rectangle2* clipRect = Machine_Rectangle2_getRectangle(self->background);
    Machine_Math_Vector2 const* widgetCenter
        = Machine_Math_Rectangle2_getCenter(Machine_Rectangle2_getRectangle(self->background));

    Machine_Math_Rectangle2 const* textBounds = Machine_Text_Layout_getBounds(self->foreground);
    Machine_Math_Vector2 const* textCenter = Machine_Math_Rectangle2_getCenter(textBounds);
    Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(widgetCenter, textCenter);
    Machine_Math_Vector2 const* oldPosition = Machine_Text_Layout_getPosition(self->foreground);
    Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
    Machine_Text_Layout_setPosition(self->foreground, newPosition);
    Machine_Text_Layout_setClipRectangle(self->foreground, clipRect);

    self->childDirty = false;
  }
  Machine_Shape2_render((Machine_Shape2*)self->background, ctx2);
  Machine_Text_Layout_render(self->foreground, ctx2);
}

static void Machine_Gui_TextNode_render(Machine_Gui_TextNode* self, Machine_Context2* ctx2) {
  Machine_Gui_TextNode_render2(self, Machine_Context2_getTargetWidth(ctx2),
                               Machine_Context2_getTargetHeight(ctx2));
}
