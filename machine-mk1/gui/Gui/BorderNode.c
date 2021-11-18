/// @file Gui/BorderNode.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/BorderNode.h"

#include "Gui/BorderModel.h"
#include "Gui/Context.h"
#include "_Graphics2.h"
#include "_Video.h"

struct Machine_Gui_BorderNode_Class {
  Machine_Gui_Widget_Class __parent;
};

struct Machine_Gui_BorderNode {
  Machine_Gui_Widget __parent;

  Machine_Gui_BorderModel* borderModel;
  Machine_Gui_Widget* child;
  /// @brief When the child changes or the rectangle changes,
  /// we need to update the childs rectangle accordingly.
  bool childDirty;
  Machine_Rectangle2* borderRectangle;
};

static void Machine_Gui_BorderNode_constructClass(Machine_Gui_BorderNode_Class* self);

static void Machine_Gui_BorderNode_visit(Machine_Gui_BorderNode* self);

static void Machine_Gui_BorderNode_construct(Machine_Gui_BorderNode* self, size_t numberOfArguments,
                                             Machine_Value const* arguments);

static Machine_Math_Vector2 const* Machine_Gui_BorderNode_getPreferredSize(
    Machine_Gui_BorderNode const* self);

static Machine_Math_Rectangle2 const* Machine_Gui_BorderNode_getCanvasRectangle(
    Machine_Gui_BorderNode const* self);

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_BorderNode, Machine_Gui_Widget, &Machine_Gui_BorderNode_visit,
                         &Machine_Gui_BorderNode_construct, NULL,
                         &Machine_Gui_BorderNode_constructClass)

static void Machine_Gui_BorderNode_visit(Machine_Gui_BorderNode* self) {
  if (self->child) {
    Machine_Gc_visit(self->child);
  }
  if (self->borderRectangle) {
    Machine_Gc_visit(self->borderRectangle);
  }
  if (self->borderModel) {
    Machine_Gc_visit(self->borderModel);
  }
}

static Machine_Math_Rectangle2 const* Machine_Gui_BorderNode_getCanvasRectangle(
    Machine_Gui_BorderNode const* self) {
  Machine_Math_Rectangle2* rectangle
      = Machine_Math_Rectangle2_clone(Machine_Gui_Widget_getRectangle((Machine_Gui_Widget*)self));
  Machine_Math_Rectangle2_inset(rectangle, Machine_Gui_BorderModel_getLeftWidth(self->borderModel),
                                Machine_Gui_BorderModel_getTopWidth(self->borderModel),
                                Machine_Gui_BorderModel_getRightWidth(self->borderModel),
                                Machine_Gui_BorderModel_getBottomWidth(self->borderModel));
  return rectangle;
}

static void Machine_Gui_BorderNode_render(Machine_Gui_BorderNode* self, Machine_Context2* ctx2) {
  if (self->child) {

    Machine_Context2* context = ((Machine_Gui_Widget*)self)->context->context2;
    Machine_Context2_setTargetSize(context, Machine_Context2_getTargetWidth(ctx2),
                                   Machine_Context2_getTargetHeight(ctx2));
    if (self->childDirty) {
      Machine_Math_Rectangle2 const* canvasRectangle
          = Machine_Gui_Widget_getCanvasRectangle((Machine_Gui_Widget*)self);
      Machine_Gui_Widget_setRectangle(self->child, canvasRectangle);
      self->childDirty = false;
    }
    Machine_Gui_Widget_render(self->child, context);

    {
      Machine_Math_Vector4 const* c = Machine_Gui_BorderModel_getColor(self->borderModel);
      Machine_Rectangle2_setColor(self->borderRectangle, c);
    }
    Machine_Real lw = Machine_Gui_BorderModel_getLeftWidth(self->borderModel),
                 tw = Machine_Gui_BorderModel_getTopWidth(self->borderModel),
                 rw = Machine_Gui_BorderModel_getRightWidth(self->borderModel),
                 bw = Machine_Gui_BorderModel_getBottomWidth(self->borderModel);
    if (lw > 0.f || tw > 0.f || rw > 0.f || bw > 0.f) {
      Machine_Math_Rectangle2 const* R = Machine_Gui_Widget_getRectangle(
          (Machine_Gui_Widget*)self); // TODO: Should be: getAbsoluteRectangle.
      {                               // left/top
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R),
                                 Machine_Math_Rectangle2_getMinY(R));

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
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMaxX(R) - rw,
                                 Machine_Math_Rectangle2_getMinY(R));

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
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R),
                                 Machine_Math_Rectangle2_getMaxY(R) - bw);

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
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMaxX(R) - rw,
                                 Machine_Math_Rectangle2_getMaxY(R) - bw);

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
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R),
                                 Machine_Math_Rectangle2_getMinY(R) + tw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(
            size, lw, Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(R)) - tw - bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // right side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMaxX(R) - rw,
                                 Machine_Math_Rectangle2_getMinY(R) + tw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(
            size, rw, Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(R)) - tw - bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // top side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R) + lw,
                                 Machine_Math_Rectangle2_getMinY(R));

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(
            size, Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(R)) - lw - rw, tw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
      { // bottom side
        Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();

        //
        Machine_Math_Vector2* position = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(position, Machine_Math_Rectangle2_getMinX(R) + lw,
                                 Machine_Math_Rectangle2_getMaxY(R) - bw);

        //
        Machine_Math_Vector2* size = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(
            size, Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(R)) - lw - rw, bw);

        Machine_Math_Rectangle2_setPosition(r, position);
        Machine_Math_Rectangle2_setSize(r, size);

        Machine_Rectangle2_setRectangle(self->borderRectangle, r);
        Machine_Shape2_render((Machine_Shape2*)self->borderRectangle, context);
      }
    }
  }
}

static Machine_Value boundsChangedCallback(size_t numberOfArguments,
                                           Machine_Value const* arguments) {
  MACHINE_ASSERT(numberOfArguments == 1, Machine_Status_InvalidNumberOfArguments);
  Machine_Gui_BorderNode* self = (Machine_Gui_BorderNode*)Machine_Value_getObject(&arguments[0]);
  self->childDirty = true;
  Machine_Value result;
  Machine_Value_setVoid(&result, Machine_Void_Void);
  return result;
}

static void Machine_Gui_BorderNode_constructClass(Machine_Gui_BorderNode_Class* self) {
  ((Machine_Gui_Widget_Class*)self)->render
      = (void (*)(Machine_Gui_Widget*, Machine_Context2*)) & Machine_Gui_BorderNode_render;
  ((Machine_Gui_Widget_Class*)self)->getPreferredSize
      = (Machine_Math_Vector2 const* (*)(Machine_Gui_Widget const*))
        & Machine_Gui_BorderNode_getPreferredSize;
  ((Machine_Gui_Widget_Class*)self)->getCanvasRectangle
      = (Machine_Math_Rectangle2 const* (*)(Machine_Gui_Widget const*))
        & Machine_Gui_BorderNode_getCanvasRectangle;
}

static void Machine_Gui_BorderNode_construct(Machine_Gui_BorderNode* self, size_t numberOfArguments,
                                             Machine_Value const* arguments) {
  Machine_Gui_Widget_construct((Machine_Gui_Widget*)self, numberOfArguments, arguments);
  self->borderModel = Machine_Gui_BorderModel_create();
  Machine_Gui_BorderModel_setWidth(self->borderModel, 1.f);
  self->borderRectangle = Machine_Rectangle2_create();
  self->childDirty = true;
  Machine_Gui_Widget_subscribe(
      (Machine_Gui_Widget*)self,
      ((Machine_Gui_Widget*)self)->context->signalsContext->PositionChanged, (Machine_Object*)self,
      &boundsChangedCallback);
  Machine_Gui_Widget_subscribe((Machine_Gui_Widget*)self,
                               ((Machine_Gui_Widget*)self)->context->signalsContext->SizeChanged,
                               (Machine_Object*)self, &boundsChangedCallback);
  Machine_setClassType((Machine_Object*)self, Machine_Gui_BorderNode_getClassType());
}

Machine_Gui_BorderNode* Machine_Gui_BorderNode_create(Machine_Gui_Context* context) {
  Machine_ClassType* ty = Machine_Gui_BorderNode_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value arguments[1];
  Machine_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_Gui_BorderNode* self
      = (Machine_Gui_BorderNode*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

Machine_Gui_Widget* Machine_Gui_BorderNode_getChild(Machine_Gui_BorderNode* self) {
  return self->child;
}

void Machine_Gui_BorderNode_setChild(Machine_Gui_BorderNode* self, Machine_Gui_Widget* child) {
  if (self->child == child) {
    return;
  }
  if (self->child != NULL) {
    self->child->parent = NULL;
  }
  self->child = child;
  if (self->child) {
    child->parent = (Machine_Gui_Widget*)self;
  }
  self->childDirty = true;
}

Machine_Math_Vector4 const* Machine_Gui_BorderNode_getBorderColor(
    Machine_Gui_BorderNode const* self) {
  return Machine_Gui_BorderModel_getColor(self->borderModel);
}

void Machine_Gui_BorderNode_setBorderColor(Machine_Gui_BorderNode* self,
                                           Machine_Math_Vector4 const* color) {
  Machine_Gui_BorderModel_setColor(self->borderModel, color);
}

Machine_Real Machine_Gui_BorderNode_getBorderLeftWidth(Machine_Gui_BorderNode const* self) {
  return Machine_Gui_BorderModel_getLeftWidth(self->borderModel);
}

Machine_Real Machine_Gui_BorderNode_getBorderRightWidth(Machine_Gui_BorderNode const* self) {
  return Machine_Gui_BorderModel_getRightWidth(self->borderModel);
}

Machine_Real Machine_Gui_BorderNode_getBorderTopWidth(Machine_Gui_BorderNode const* self) {
  return Machine_Gui_BorderModel_getTopWidth(self->borderModel);
}

Machine_Real Machine_Gui_BorderNode_getBorderBottomWidth(Machine_Gui_BorderNode const* self) {
  return Machine_Gui_BorderModel_getBottomWidth(self->borderModel);
}

void Machine_Gui_BorderNode_setBorderWidth(Machine_Gui_BorderNode* self, Machine_Real width) {
  Machine_Gui_BorderModel_setWidth(self->borderModel, width);
}

void Machine_Gui_BorderNode_setLeftBorderWidth(Machine_Gui_BorderNode* self, Machine_Real width) {
  Machine_Gui_BorderModel_setLeftWidth(self->borderModel, width);
}

void Machine_Gui_BorderNode_setRightBorderWidth(Machine_Gui_BorderNode* self, Machine_Real width) {
  Machine_Gui_BorderModel_setRightWidth(self->borderModel, width);
}

void Machine_Gui_BorderNode_setTopBorderWidth(Machine_Gui_BorderNode* self, Machine_Real width) {
  Machine_Gui_BorderModel_setTopWidth(self->borderModel, width);
}

void Machine_Gui_BorderNode_setBottomBorderWidth(Machine_Gui_BorderNode* self, Machine_Real width) {
  Machine_Gui_BorderModel_setBottomWidth(self->borderModel, width);
}

static Machine_Math_Vector2 const* Machine_Gui_BorderNode_getPreferredSize(
    Machine_Gui_BorderNode const* self) {
  Machine_Math_Vector2 const* preferredSize = self->child
                                                  ? Machine_Gui_Widget_getPreferredSize(self->child)
                                                  : Machine_Math_Vector2_create();
  Machine_Math_Vector2* borderSize = Machine_Math_Vector2_create();
  Machine_Real w = Machine_Gui_BorderModel_getLeftWidth(self->borderModel)
                   + Machine_Gui_BorderModel_getRightWidth(self->borderModel);
  Machine_Real h = Machine_Gui_BorderModel_getTopWidth(self->borderModel)
                   + Machine_Gui_BorderModel_getBottomWidth(self->borderModel);
  Machine_Math_Vector2_set(borderSize, w, h);
  return Machine_Math_Vector2_sum(preferredSize, borderSize);
}