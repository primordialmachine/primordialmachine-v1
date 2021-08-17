/// @file GUI/TextButton.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GUI/TextButton.h"



#include "_Graphics2.h"
#include "_Images.h"
#include "./../Video.h"
#include "./../Text/Layout.h"
#include "./../GUI/Context.h"
#include "./../GUI/Widget.h"
#include <string.h>



struct Machine_GUI_TextButton {
  Machine_GUI_Widget parent;

  /// @brief The layout for rendering the text.
  Machine_Text_Layout* foreground;

  /// @brief The shape for rendering the background.
  Machine_Rectangle2* background;

  bool childDirty;
};

static void Machine_GUI_TextButton_visit(Machine_GUI_TextButton* self) {
  if (self->foreground) {
    Machine_visit(self->foreground);
  }
  if (self->background) {
    Machine_visit(self->background);
  }
}

static void Machine_GUI_TextButton_setPosition(Machine_GUI_TextButton* self, const Machine_Math_Vector2* position);

static void Machine_GUI_TextButton_setSize(Machine_GUI_TextButton* self, const Machine_Math_Vector2* size);

static void Machine_GUI_TextButton_setRectangle(Machine_GUI_TextButton* self, const Machine_Math_Rectangle2* rectangle);

static const Machine_Math_Rectangle2* Machine_GUI_TextButton_getRectangle(const Machine_GUI_TextButton* self);

static const Machine_Math_Vector2* Machine_GUI_TextButton_getPreferredSize(const Machine_GUI_TextButton* self);

static void Machine_GUI_TextButton_render(Machine_GUI_TextButton* self, float width, float height);

static void Machine_GUI_TextButton_constructClass(Machine_GUI_TextButton_Class* self) {
  ((Machine_GUI_Widget_Class*)self)->render = (void (*)(Machine_GUI_Widget*, float, float)) & Machine_GUI_TextButton_render;
  ((Machine_GUI_Widget_Class*)self)->setRectangle = (void (*)(Machine_GUI_Widget*, const Machine_Math_Rectangle2*)) & Machine_GUI_TextButton_setRectangle;
  ((Machine_GUI_Widget_Class*)self)->getRectangle = (const Machine_Math_Rectangle2 * (*)(const Machine_GUI_Widget*)) & Machine_GUI_TextButton_getRectangle;
  ((Machine_GUI_Widget_Class*)self)->setPosition = (void (*)(Machine_GUI_Widget*, const Machine_Math_Vector2*)) & Machine_GUI_TextButton_setPosition;
  ((Machine_GUI_Widget_Class*)self)->setSize = (void (*)(Machine_GUI_Widget*, const Machine_Math_Vector2*)) & Machine_GUI_TextButton_setSize;
  ((Machine_GUI_Widget_Class*)self)->getPreferredSize = (const Machine_Math_Vector2 * (*)(const Machine_GUI_Widget*)) & Machine_GUI_TextButton_getPreferredSize;
}

void Machine_GUI_TextButton_construct(Machine_GUI_TextButton* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_GUI_Widget_construct((Machine_GUI_Widget*)self, numberOfArguments, arguments);
  Machine_Font* font = Machine_FontsContext_createFont(Machine_DefaultFonts_createContext(Machine_Video_getContext(), Machines_DefaultImages_createContext()),
                                                       Machine_String_create("RobotoSlab-Regular.ttf", strlen("RobotoSlab-Regular.ttf")), 20);
  self->foreground = Machine_Text_Layout_create(Machine_String_create("", strlen("")), font);
  self->background = Machine_Rectangle2_create();
  self->childDirty = true;
  Machine_GUI_TextButton_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_GUI_TextButton_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_TextButton, Machine_GUI_Widget, &Machine_GUI_TextButton_visit, &Machine_GUI_TextButton_construct, NULL)

Machine_GUI_TextButton* Machine_GUI_TextButton_create(Machine_GUI_Context* context) {
  Machine_ClassType* ty = Machine_GUI_TextButton_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value arguments[1];
  Machine_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_GUI_TextButton* self = (Machine_GUI_TextButton*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const Machine_Math_Vector2* Machine_GUI_TextButton_getPreferredSize(const Machine_GUI_TextButton* self) {
  return Machine_Math_Rectangle2_getSize(Machine_Text_Layout_getBounds(self->foreground));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextButton_setText(Machine_GUI_TextButton* self, Machine_String* text) {
  Machine_Text_Layout_setText(self->foreground, text);
  self->childDirty = true;
}

Machine_String* Machine_GUI_TextButton_getText(Machine_GUI_TextButton* self) {
  return Machine_Text_Layout_getText(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextButton_setBackgroundColor(Machine_GUI_TextButton* self, const Machine_Math_Vector4* backgroundColor) {
  Machine_Rectangle2_setColor(self->background, backgroundColor);
  self->childDirty = true;
}

const Machine_Math_Vector4* Machine_GUI_TextButton_getBackgroundColor(const Machine_GUI_TextButton* self) {
  return Machine_Rectangle2_getColor(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextButton_setForegroundColor(Machine_GUI_TextButton* self, const Machine_Math_Vector3* foregroundColor) {
  Machine_Text_Layout_setColor(self->foreground, foregroundColor);
  self->childDirty = true;
}

const Machine_Math_Vector3* Machine_GUI_TextButton_getForegroundColor(const Machine_GUI_TextButton* self) {
  return Machine_Text_Layout_getColor(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_GUI_TextButton_setPosition(Machine_GUI_TextButton* self, const Machine_Math_Vector2* position) {
  Machine_Rectangle2_setPosition(self->background, position);
  self->childDirty = true;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_GUI_TextButton_setSize(Machine_GUI_TextButton* self, const Machine_Math_Vector2* size) {
  Machine_Rectangle2_setSize(self->background, size);
  self->childDirty = true;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_GUI_TextButton_setRectangle(Machine_GUI_TextButton* self, const Machine_Math_Rectangle2* rectangle) {
  Machine_Rectangle2_setRectangle(self->background, rectangle);
  self->childDirty = true;
}

static const Machine_Math_Rectangle2* Machine_GUI_TextButton_getRectangle(const Machine_GUI_TextButton* self) {
  return Machine_Rectangle2_getRectangle(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_GUI_TextButton_render(Machine_GUI_TextButton* self, float width, float height) {
  if (self->childDirty) {
    // TODO: Only do this layouting if necessary.
    Machine_Math_Rectangle2* clipRect = Machine_Rectangle2_getRectangle(self->background);
    const Machine_Math_Vector2* widgetCenter = Machine_Math_Rectangle2_getCenter(Machine_Rectangle2_getRectangle(self->background));

    const Machine_Math_Rectangle2* textBounds = Machine_Text_Layout_getBounds(self->foreground);
    const Machine_Math_Vector2* textCenter = Machine_Math_Rectangle2_getCenter(textBounds);
    Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(widgetCenter, textCenter);
    const Machine_Math_Vector2* oldPosition = Machine_Text_Layout_getPosition(self->foreground);
    Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
    Machine_Text_Layout_setPosition(self->foreground, newPosition);
    Machine_Text_Layout_setClipRectangle(self->foreground, clipRect);

    self->childDirty = false;
  }
  Machine_Context2* context = ((Machine_GUI_Widget*)self)->context->context2;
  Machine_Context2_setTargetSize(context, width, height);
  Machine_Shape2_render((Machine_Shape2*)self->background, context);
  Machine_Text_Layout_render(self->foreground, Machine_Context2_getTargetWidth(context), Machine_Context2_getTargetHeight(context));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextButton_addButtonListener(Machine_GUI_TextButton* self, void* context, void (*callback)(void* context));

void Machine_GUI_TextButton_removeButtonListener(Machine_GUI_TextButton* self, void* context, void (*callback)(void* context));
