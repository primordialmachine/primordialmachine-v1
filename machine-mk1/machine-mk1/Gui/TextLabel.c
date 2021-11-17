/// @file Gui/TextLabel.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/TextLabel.h"



#include "_Graphics2.h"
#include "_Images.h"
#include "./../Video.h"
#include "./../Text/Layout.h"
#include "Gui/Context.h"
#include "Gui/Widget.h"
#include <string.h>



struct Machine_Gui_TextLabel_Class {
  Machine_GUI_Widget_Class __parent;
};

struct Machine_Gui_TextLabel {
  Machine_GUI_Widget __parent;

  /// @brief The layout for rendering the text.
  Machine_Text_Layout* foreground;

  /// @brief The shape for rendering the background.
  Machine_Rectangle2* background;

  bool childDirty;
};

static void Machine_Gui_TextLabel_visit(Machine_Gui_TextLabel* self) {
  if (self->foreground) {
    Machine_Gc_visit(self->foreground);
  }
  if (self->background) {
    Machine_Gc_visit(self->background);
  }
}

static Machine_Math_Vector2 const* Machine_Gui_TextLabel_getPreferredSize(Machine_Gui_TextLabel const* self);

static void Machine_Gui_TextLabel_render(Machine_Gui_TextLabel* self, Machine_Context2* ctx2);

static Machine_Value boundsChangedCallback(size_t numberOfArguments, Machine_Value const* arguments) {
  MACHINE_ASSERT(numberOfArguments == 1, Machine_Status_InvalidNumberOfArguments);
  Machine_Gui_TextLabel* self = (Machine_Gui_TextLabel*)Machine_Value_getObject(&arguments[0]);
  self->childDirty = true;
  Machine_Value result;
  Machine_Value_setVoid(&result, Machine_Void_Void);
  return result;
}

static void Machine_Gui_TextLabel_constructClass(Machine_Gui_TextLabel_Class* self) {
  ((Machine_GUI_Widget_Class*)self)->render = (void (*)(Machine_GUI_Widget*, Machine_Context2*)) & Machine_Gui_TextLabel_render;
  ((Machine_GUI_Widget_Class*)self)->getPreferredSize = (Machine_Math_Vector2 const* (*)(Machine_GUI_Widget const*)) & Machine_Gui_TextLabel_getPreferredSize;
}

void Machine_Gui_TextLabel_construct(Machine_Gui_TextLabel* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_GUI_Widget_construct((Machine_GUI_Widget*)self, numberOfArguments, arguments);
  Machine_FontsContext* fontsContext = Machine_DefaultFonts_createContext(Machine_getVideoContext(), Machines_DefaultImages_createContext());
  Machine_Font *font = Machine_FontsContext_createFont(fontsContext, Machine_String_create("RobotoSlab-Regular.ttf", strlen("RobotoSlab-Regular.ttf")), 20);
  self->foreground = Machine_Text_Layout_create(Machine_String_create("", strlen("")), font);
  self->background = Machine_Rectangle2_create();
  self->childDirty = true;
  Machine_GUI_Widget_subscribe((Machine_GUI_Widget*)self, ((Machine_GUI_Widget*)self)->context->signalsContext->PositionChanged, (Machine_Object *)self, &boundsChangedCallback);
  Machine_GUI_Widget_subscribe((Machine_GUI_Widget*)self, ((Machine_GUI_Widget*)self)->context->signalsContext->SizeChanged, (Machine_Object*)self, &boundsChangedCallback);
  Machine_setClassType((Machine_Object*)self, Machine_Gui_TextLabel_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_TextLabel, Machine_GUI_Widget, &Machine_Gui_TextLabel_visit, &Machine_Gui_TextLabel_construct, NULL, &Machine_Gui_TextLabel_constructClass)

Machine_Gui_TextLabel* Machine_Gui_TextLabel_create(Machine_Gui_Context* context) {
  Machine_ClassType* ty = Machine_Gui_TextLabel_getClassType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Machine_Value arguments[1] = { Machine_Value_StaticInitializerVoid() };
  Machine_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_Gui_TextLabel* self = (Machine_Gui_TextLabel*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Math_Vector2 const* Machine_Gui_TextLabel_getPreferredSize(Machine_Gui_TextLabel const* self) {
  return Machine_Math_Rectangle2_getSize(Machine_Text_Layout_getBounds(self->foreground));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextLabel_setText(Machine_Gui_TextLabel* self, Machine_String* text) {
  Machine_Text_Layout_setText(self->foreground, text);
  Machine_GUI_Widget_emitPositionChangedSignal((Machine_GUI_Widget*)self);
  Machine_GUI_Widget_emitSizeChangedSignal((Machine_GUI_Widget*)self);
}

Machine_String* Machine_Gui_TextLabel_getText(Machine_Gui_TextLabel const* self) {
  return Machine_Text_Layout_getText(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextLabel_setBackgroundColor(Machine_Gui_TextLabel* self, Machine_Math_Vector4 const* backgroundColor) {
  Machine_Rectangle2_setColor(self->background, backgroundColor);
  Machine_GUI_Widget_emitPositionChangedSignal((Machine_GUI_Widget*)self);
  Machine_GUI_Widget_emitSizeChangedSignal((Machine_GUI_Widget*)self);
}

Machine_Math_Vector4 const* Machine_Gui_TextLabel_getBackgroundColor(Machine_Gui_TextLabel const* self) {
  return Machine_Rectangle2_getColor(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_TextLabel_setForegroundColor(Machine_Gui_TextLabel* self, Machine_Math_Vector3 const* foregroundColor) {
  Machine_Text_Layout_setColor(self->foreground, foregroundColor);
  Machine_GUI_Widget_emitPositionChangedSignal((Machine_GUI_Widget*)self);
  Machine_GUI_Widget_emitSizeChangedSignal((Machine_GUI_Widget*)self);
}

Machine_Math_Vector3 const* Machine_Gui_TextLabel_getForegroundColor(Machine_Gui_TextLabel const* self) {
  return Machine_Text_Layout_getColor(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Gui_TextLabel_render2(Machine_Gui_TextLabel* self, Machine_Real width, Machine_Real height) {
  Machine_Context2* ctx2 = ((Machine_GUI_Widget*)self)->context->context2;
  Machine_Context2_setTargetSize(ctx2, width, height);
  if (self->childDirty) {
    Machine_Gui_Context* ctx = ((Machine_GUI_Widget*)self)->context;
    Machine_Rectangle2_setRectangle(self->background, ((Machine_GUI_Widget*)self)->rectangle);
    // TODO: Only do this layouting if necessary.
    Machine_Math_Rectangle2* clipRect = Machine_Rectangle2_getRectangle(self->background);
    Machine_Math_Vector2 const* widgetCenter = Machine_Math_Rectangle2_getCenter(Machine_Rectangle2_getRectangle(self->background));

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

void Machine_Gui_TextLabel_render(Machine_Gui_TextLabel* self, Machine_Context2* ctx2) {
  Machine_Gui_TextLabel_render2(self, Machine_Context2_getTargetWidth(ctx2), Machine_Context2_getTargetHeight(ctx2));
}
