#include "./../GUI/TextLabel.h"
#include "./../Shape2.h"

struct Machine_GUI_TextLabel {
  Machine_Text_Layout* foreground;
  Machine_Rectangle2* background;
};

static void Machine_GUI_TextLabel_visit(Machine_GUI_TextLabel* self) {
  if (self->foreground) {
    Machine_visit(self->foreground);
  }
  if (self->background) {
    Machine_visit(self->background);
  }
}

void Machine_GUI_TextLabel_construct(Machine_GUI_TextLabel* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Fonts_Font *font = Machine_Fonts_createFont("RobotoSlab-Regular.ttf", 20);
  self->foreground = Machine_Text_Layout_create(Machine_String_create("", strlen("")), font);
  self->background = Machine_Rectangle2_create();
}

Machine_ClassType* Machine_GUI_TextLabel_getClassType() {
  return
    Machine_createClassType
      (
        NULL,
        sizeof(Machine_GUI_TextLabel),
        (Machine_ClassObjectVisitCallback*)&Machine_GUI_TextLabel_visit,
        (Machine_ClassObjectConstructCallback*)&Machine_GUI_TextLabel_construct,
        (Machine_ClassObjectDestructCallback*)NULL
      );
}

Machine_GUI_TextLabel* Machine_GUI_TextLabel_create() {
  Machine_ClassType* ty = Machine_GUI_TextLabel_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_GUI_TextLabel* self = (Machine_GUI_TextLabel*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_setText(Machine_GUI_TextLabel* self, Machine_String* text) {
  Machine_Text_Layout_setText(self->foreground, text);
}

Machine_String* Machine_GUI_TextLabel_getText(Machine_GUI_TextLabel* self) {
  return Machine_Text_Layout_getText(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_setBackgroundColor(Machine_GUI_TextLabel* self, const Machine_Math_Vector3* backgroundColor) {
  Machine_Rectangle2_setColor(self->background, backgroundColor);
}

const Machine_Math_Vector3* Machine_GUI_TextLabel_getBackgroundColor(Machine_GUI_TextLabel* self) {
  return Machine_Rectangle2_getColor(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_setForegroundColor(Machine_GUI_TextLabel* self, const Machine_Math_Vector3* foregroundColor) {
  Machine_Text_Layout_setColor(self->foreground, foregroundColor);
}

const Machine_Math_Vector3* Machine_GUI_TextLabel_getForegroundColor(Machine_GUI_TextLabel* self) {
  return Machine_Text_Layout_getColor(self->foreground);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_setPosition(Machine_GUI_TextLabel* self, const Machine_Math_Vector2* position) {
  Machine_Rectangle2_setPosition(self->background, position);
}

const Machine_Math_Vector2* Machine_GUI_TextLabel_getPosition(Machine_GUI_TextLabel* self) {
  return Machine_Rectangle2_getPosition(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_setSize(Machine_GUI_TextLabel* self, const Machine_Math_Vector2* size) {
  Machine_Rectangle2_setSize(self->background, size);
}

const Machine_Math_Vector2* Machine_GUI_TextLabel_getSize(Machine_GUI_TextLabel* self) {
  return Machine_Rectangle2_getSize(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const Machine_Math_Rectangle2* Machine_GUI_TextLabel_getRectangle(Machine_GUI_TextLabel* self) {
  return Machine_Rectangle2_getRectangle(self->background);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_TextLabel_render(Machine_GUI_TextLabel* self, float width, float height) {

  // TODO: Only do this layouting if necessary.
  Machine_Math_Rectangle2* clipRect = Machine_Rectangle2_getRectangle(self->background);
  Machine_Math_Vector2* widgetCenter = Machine_Math_Rectangle2_getCenter(Machine_Rectangle2_getRectangle(self->background));

  Machine_Math_Rectangle2* textBounds = Machine_Text_Layout_getBounds(self->foreground);
  Machine_Math_Vector2* textCenter = Machine_Math_Rectangle2_getCenter(textBounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(widgetCenter, textCenter);
  Machine_Math_Vector2* oldPosition = Machine_Text_Layout_getPosition(self->foreground);
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_Text_Layout_setPosition(self->foreground, newPosition);

  Machine_Shape2_render((Machine_Shape2 *)self->background, width, height);

  Machine_Text_Layout_setClipRectangle(self->foreground, clipRect);
  Machine_Text_Layout_render(self->foreground, width, height);
}
