/// @file GUI/Border.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GUI/Border.h"



#include "./../_Graphics2.h"
#include "./../GUI/BorderModel.h"



struct Machine_GUI_Border {
  Machine_GUI_Widget parent;
  Machine_Math_Vector3* color;
  float width;
  Machine_Math_Rectangle2* rectangle;
  Machine_GUI_Widget* child;
  /// @brief When the child changes or the rectangle changes,
  /// we need to update the childs rectangle accordingly.
  bool childDirty;
  Machine_Rectangle2* borderRectangle;
};

static void Machine_GUI_Border_visit(Machine_GUI_Border* self);

static void Machine_GUI_Border_construct(Machine_GUI_Border* self, size_t numberOfArguments, const Machine_Value* arguments);

static const Machine_Math_Rectangle2* Machine_GUI_Border_getRectangle(const Machine_GUI_Border* self);

static void Machine_GUI_Border_setRectangle(Machine_GUI_Border* self, const Machine_Math_Rectangle2* rectangle);

static void Machine_GUI_Border_setPosition(Machine_GUI_Border* self, const Machine_Math_Vector2* position);

static void Machine_GUI_Border_setSize(Machine_GUI_Border* self, const Machine_Math_Vector2* size);

static const Machine_Math_Vector2* Machine_GUI_Border_getPreferredSize(const Machine_GUI_Border* self);

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_Border, Machine_GUI_Widget, &Machine_GUI_Border_visit, &Machine_GUI_Border_construct, NULL)

static void Machine_GUI_Border_visit(Machine_GUI_Border* self) {
  if (self->color) {
    Machine_visit(self->color);
  }
  if (self->child) {
    Machine_visit(self->child);
  }
  if (self->rectangle) {
    Machine_visit(self->rectangle);
  }
  if (self->borderRectangle) {
    Machine_visit(self->borderRectangle);
  }
}

static void Machine_GUI_Border_render(Machine_GUI_Border* self, float width, float height) {
  if (self->child) {
    Machine_Context2* context = Machine_Context2_create();
    Machine_Context2_setTargetSize(context, width, height);
    if (self->childDirty) {
      Machine_Math_Rectangle2* rectangle = Machine_Math_Rectangle2_clone(self->rectangle);
      Machine_Math_Rectangle2_inset(rectangle, self->width, self->width, self->width, self->width);
      Machine_GUI_Widget_setRectangle(self->child, rectangle);
      self->childDirty = false;
    }
    Machine_GUI_Widget_render(self->child, width, height);
    
    {
      Machine_Math_Vector4* temporary = Machine_Math_Vector4_create();
      Machine_Math_Vector4_set(temporary, Machine_Math_Vector3_getX(self->color), Machine_Math_Vector3_getY(self->color), Machine_Math_Vector3_getZ(self->color), 1.f);
      Machine_Rectangle2_setColor(self->borderRectangle, temporary);
    }
    if (self->width > 0.f) {
      float lw = self->width, tw = self->width;
      float rw = self->width, bw = self->width;
      Machine_Math_Rectangle2 const* R = Machine_GUI_Widget_getRectangle((Machine_GUI_Widget*)self);
      { // left/top
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R), Machine_Math_Rectangle2_getMinY(R));

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, lw, tw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // right/top
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMaxX(R) - rw, Machine_Math_Rectangle2_getMinY(R));

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, rw, tw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // left/bottom
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R), Machine_Math_Rectangle2_getMaxY(R) - bw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, lw, bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // right/bottom
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMaxX(R) - rw, Machine_Math_Rectangle2_getMaxY(R) - bw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, rw, bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // left side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R), Machine_Math_Rectangle2_getMinY(R) + tw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, lw, Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(R)) - tw - bw);
        
        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2 *)self->borderRectangle, context);
      }
      { // right side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMaxX(R) - rw, Machine_Math_Rectangle2_getMinY(R) + tw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, rw, Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(R)) - tw - bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // top side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R) + lw, Machine_Math_Rectangle2_getMinY(R));

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(R)) - lw - rw, tw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // bottom side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R) + lw, Machine_Math_Rectangle2_getMaxY(R) - bw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(size, Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(R)) - lw - rw, bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
    }
  }
}

static void Machine_GUI_Border_constructClass(Machine_GUI_Border_Class* self) {
  ((Machine_GUI_Widget_Class*)self)->render = (void (*)(Machine_GUI_Widget*, float, float)) & Machine_GUI_Border_render;
  ((Machine_GUI_Widget_Class*)self)->setRectangle = (void (*)(Machine_GUI_Widget*, const Machine_Math_Rectangle2*)) & Machine_GUI_Border_setRectangle;
  ((Machine_GUI_Widget_Class*)self)->getRectangle = (const Machine_Math_Rectangle2 * (*)(const Machine_GUI_Widget*)) & Machine_GUI_Border_getRectangle;
  ((Machine_GUI_Widget_Class*)self)->setPosition = (void (*)(Machine_GUI_Widget*, const Machine_Math_Vector2*)) & Machine_GUI_Border_setPosition;
  ((Machine_GUI_Widget_Class*)self)->setSize = (void (*)(Machine_GUI_Widget*, const Machine_Math_Vector2*)) & Machine_GUI_Border_setSize;
  ((Machine_GUI_Widget_Class*)self)->getPreferredSize = (const Machine_Math_Vector2 * (*)(const Machine_GUI_Widget*)) & Machine_GUI_Border_getPreferredSize;
}

static void Machine_GUI_Border_construct(Machine_GUI_Border* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_GUI_Widget_construct((Machine_GUI_Widget*)self, numberOfArguments, arguments);
  self->width = 1.f;
  self->color = Machine_Math_Vector3_create(0.1f, 0.1f, 0.1f);
  self->rectangle = Machine_Math_Rectangle2_create();
  self->borderRectangle = Machine_Rectangle2_create();
  self->childDirty = true;
  Machine_GUI_Border_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_GUI_Border_getClassType());
}

Machine_GUI_Border* Machine_GUI_Border_create(Machine_GUI_Context* context) {
  Machine_ClassType* ty = Machine_GUI_Border_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value arguments[1];
  Machine_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_GUI_Border* self = (Machine_GUI_Border*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

Machine_GUI_Widget* Machine_GUI_Widget_getChild(Machine_GUI_Border* self) {
  return self->child;
}

void Machine_GUI_Border_setChild(Machine_GUI_Border* self, Machine_GUI_Widget *child) {
  if (self->child != child) {
    self->child = child;
    self->childDirty = true;
  }
}

const Machine_Math_Vector4* Machine_GUI_Border_getBorderColor(const Machine_GUI_Border* self) {
  Machine_Math_Vector4* temporary = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(temporary, Machine_Math_Vector3_getX(self->color), Machine_Math_Vector3_getY(self->color), Machine_Math_Vector3_getZ(self->color), 1.f);
  return temporary;
}

void Machine_GUI_Border_setBorderColor(Machine_GUI_Border* self, const Machine_Math_Vector4* color) {
  Machine_Math_Vector3_set(self->color, Machine_Math_Vector4_getX(color), Machine_Math_Vector4_getY(color), Machine_Math_Vector4_getZ(color));
}

float Machine_GUI_Border_getBorderWidth(const Machine_GUI_Border* self) {
  return self->width;
}

void Machine_GUI_Border_setBorderWidth(Machine_GUI_Border* self, float width) {
  self->width = width;
}

static const Machine_Math_Rectangle2* Machine_GUI_Border_getRectangle(const Machine_GUI_Border* self) {
  return self->rectangle;
}

static void Machine_GUI_Border_setRectangle(Machine_GUI_Border* self, const Machine_Math_Rectangle2* rectangle) {
  Machine_Math_Rectangle2_copy(self->rectangle, rectangle);
  self->childDirty = true;
}

static void Machine_GUI_Border_setPosition(Machine_GUI_Border* self, const Machine_Math_Vector2* position) {
  Machine_Math_Rectangle2_setPosition(self->rectangle, position);
  self->childDirty = true;
}

static void Machine_GUI_Border_setSize(Machine_GUI_Border* self, const Machine_Math_Vector2* size) {
  Machine_Math_Rectangle2_setSize(self->rectangle, size);
  self->childDirty = true;
}

static const Machine_Math_Vector2* Machine_GUI_Border_getPreferredSize(const Machine_GUI_Border* self) {
  const Machine_Math_Vector2* preferredSize = self->child ? Machine_GUI_Widget_getPreferredSize(self->child) : Machine_Math_Vector2_create();
  Machine_Math_Vector2* borderSize = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(borderSize, self->width * 2.f, self->width * 2.f);
  return Machine_Math_Vector2_sum(preferredSize, borderSize);
}
