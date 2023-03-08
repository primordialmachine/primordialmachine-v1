/// @file Ring3/Gui/BorderNode.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/BorderNode.h"

#include "Ring3/Gui/BorderModel.h"
#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/RenderContext.h"
#undef RING3_GUI_PRIVATE


#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Visuals/_Include.h"


struct Machine_Gui_BorderNode_Class {
  Ring3_Gui_WidgetBase_Class __parent;
};

struct Machine_Gui_BorderNode {
  Ring3_Gui_WidgetBase __parent;

  Machine_Gui_BorderModel* borderModel;
  Ring3_Gui_Widget* child;
  /// @brief When the child changes or the rectangle changes,
  /// we need to update the childs rectangle accordingly.
  bool childDirty;
  Ring3_Graphics2_Rectangle* borderRectangle;
};

static void
boundsChangedCallback
  (
    Ring2_Context* context,
    Ring2_Value* result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static void
Machine_Gui_BorderNode_construct
  (
    Machine_Gui_BorderNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static void
Machine_Gui_BorderNode_constructClass
  (
    Machine_Gui_BorderNode_Class* self
  );

static void
Machine_Gui_BorderNode_visit
  (
    Machine_Gui_BorderNode* self
  );

static  Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Gui_BorderNode_getPreferredSizeImpl
  (
    Machine_Gui_BorderNode const* self
  );

static void
Machine_Gui_BorderNode_renderImpl
  (
    Machine_Gui_BorderNode* self,
    Ring3_Gui_RenderContext* renderContext
  );

static Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gui_BorderNode_getChildrenImpl
  (
    Machine_Gui_BorderNode const* self
  );

static void
Machine_Gui_BorderNode_implement_Ring3_Gui_Widget
  (
    Ring3_Gui_Widget_Dispatch* self
  )
{
  self->render = (void (*)(Ring3_Gui_Widget*, Ring3_Gui_RenderContext*)) & Machine_Gui_BorderNode_renderImpl;
  self->getPreferredSize = (Ring3_Math_Vector2f32 * (*)(Ring3_Gui_Widget const*)) & Machine_Gui_BorderNode_getPreferredSizeImpl;
  self->getChildren = (Ring2_Collections_List * (*)(Ring3_Gui_Widget const*)) & Machine_Gui_BorderNode_getChildrenImpl;
}

static void
Machine_Gui_BorderNode_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement
    (
      self,
      Ring3_Gui_Widget_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_Gui_BorderNode_implement_Ring3_Gui_Widget
    );
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_BorderNode,
                         Ring3_Gui_WidgetBase,
                         &Machine_Gui_BorderNode_visit,
                         &Machine_Gui_BorderNode_construct,
                         NULL,
                         &Machine_Gui_BorderNode_constructClass,
                         &Machine_Gui_BorderNode_implementInterfaces)

static void
boundsChangedCallback
  (
    Ring2_Context* context,
    Ring2_Value* result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_assert(numberOfArguments == 2, Ring1_Status_InvalidNumberOfArguments);
  Machine_Gui_BorderNode* self = (Machine_Gui_BorderNode*)Ring2_Value_getObject(&arguments[0]);
  self->childDirty = true;
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void
Machine_Gui_BorderNode_construct
  (
    Machine_Gui_BorderNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Gui_WidgetBase_construct((Ring3_Gui_WidgetBase*)self, numberOfArguments, arguments);
  self->borderModel = Machine_Gui_BorderModel_create();
  Machine_Gui_BorderModel_setWidth(self->borderModel, 1.f);
  self->borderRectangle = Ring3_Graphics2_Rectangle_create();
  self->childDirty = true;
  Ring3_Gui_Widget_subscribe(
    (Ring3_Gui_Widget*)self,
    ((Ring3_Gui_WidgetBase*)self)->context->signalsContext->PositionChanged, (Machine_Object*)self,
    &boundsChangedCallback);
  Ring3_Gui_Widget_subscribe((Ring3_Gui_Widget*)self,
    ((Ring3_Gui_WidgetBase*)self)->context->signalsContext->SizeChanged,
    (Machine_Object*)self, &boundsChangedCallback);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_Gui_BorderNode_getType());
}

static void
Machine_Gui_BorderNode_constructClass
  (
    Machine_Gui_BorderNode_Class* self
  )
{ }

static void
Machine_Gui_BorderNode_visit
  (
    Machine_Gui_BorderNode* self
  )
{
  if (self->child) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->child);
  }
  if (self->borderRectangle) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->borderRectangle);
  }
  if (self->borderModel) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->borderModel);
  }
}

static Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Machine_Gui_BorderNode_getCanvasRectangle
  (
    Machine_Gui_BorderNode const* self
  )
{
  Ring3_Math_Rectangle2* rectangle = Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget*)self);
  Ring3_Math_Rectangle2_inset(rectangle, Machine_Gui_BorderModel_getLeftWidth(self->borderModel),
                                         Machine_Gui_BorderModel_getTopWidth(self->borderModel),
                                         Machine_Gui_BorderModel_getRightWidth(self->borderModel),
                                         Machine_Gui_BorderModel_getBottomWidth(self->borderModel));
  return rectangle;
}

static Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gui_BorderNode_getChildrenImpl
  (
    Machine_Gui_BorderNode const* self
  )
{
  Ring2_Collections_List *list = (Ring2_Collections_List*)Ring2_Collections_ArrayList_create();
  Ring2_Value temporary;
  Ring2_Value_setObject(&temporary, (Machine_Object*)self->child);
  Ring2_Collections_List_append(list, temporary);
  return list;
}

static void
Machine_Gui_BorderNode_renderImpl
  (
    Machine_Gui_BorderNode* self,
    Ring3_Gui_RenderContext* renderContext
  )
{
  Ring3_Graphics2_Context* graphics2Context = ((Ring3_Gui_WidgetBase*)self)->context->graphics2Context;
  if (self->childDirty) {
    if (self->child) {
      Ring3_Math_Rectangle2* selfRectangle = Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget*)self);
      Ring3_Math_Rectangle2* childRectangle = Ring3_Math_Rectangle2_create();
      Ring3_Math_Rectangle2_setSize(childRectangle, Ring3_Math_Rectangle2_getSize(selfRectangle));
      Ring3_Math_Rectangle2_inset(childRectangle, Machine_Gui_BorderModel_getLeftWidth(self->borderModel),
                                                  Machine_Gui_BorderModel_getTopWidth(self->borderModel),
                                                  Machine_Gui_BorderModel_getRightWidth(self->borderModel),
                                                  Machine_Gui_BorderModel_getBottomWidth(self->borderModel));
      Ring3_Gui_Widget_setRectangle((Ring3_Gui_Widget*)self->child, childRectangle);
    }
    self->childDirty = false;
  }
  if (self->child) {
    Ring3_Gui_Widget_render((Ring3_Gui_Widget*)self->child, renderContext);
  }

  {
    Ring3_Math_Vector4f32* c = Machine_Gui_BorderModel_getColor(self->borderModel);
    Ring3_Graphics2_Rectangle_setColor(self->borderRectangle, c);
  }
  Ring2_Real32 lw = Machine_Gui_BorderModel_getLeftWidth(self->borderModel),
               tw = Machine_Gui_BorderModel_getTopWidth(self->borderModel),
               rw = Machine_Gui_BorderModel_getRightWidth(self->borderModel),
               bw = Machine_Gui_BorderModel_getBottomWidth(self->borderModel);
  if (lw > 0.f || tw > 0.f || rw > 0.f || bw > 0.f) {
    Ring3_Math_Rectangle2* R = Ring3_Gui_Widget_getAbsoluteRectangle((Ring3_Gui_Widget*)self);
    { // left/top
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMinX(R),
                                          Ring3_Math_Rectangle2_getMinY(R));

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, lw, tw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // right/top
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMaxX(R) - rw,
                                          Ring3_Math_Rectangle2_getMinY(R));

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, rw, tw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // left/bottom
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMinX(R),
                                          Ring3_Math_Rectangle2_getMaxY(R) - bw);

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, lw, bw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // right/bottom
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMaxX(R) - rw,
                                          Ring3_Math_Rectangle2_getMaxY(R) - bw);

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, rw, bw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // left side
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMinX(R),
                                          Ring3_Math_Rectangle2_getMinY(R) + tw);

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, lw, Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(R)) - tw - bw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // right side
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMaxX(R) - rw,
                                          Ring3_Math_Rectangle2_getMinY(R) + tw);

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, rw, Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(R)) - tw - bw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // top side
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMinX(R) + lw,
                                          Ring3_Math_Rectangle2_getMinY(R));

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getSize(R)) - lw - rw, tw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
    { // bottom side
      Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();

      //
      Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(position, Ring3_Math_Rectangle2_getMinX(R) + lw,
                                          Ring3_Math_Rectangle2_getMaxY(R) - bw);

      //
      Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(size, Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getSize(R)) - lw - rw, bw);

      Ring3_Math_Rectangle2_setPosition(r, position);
      Ring3_Math_Rectangle2_setSize(r, size);

      Ring3_Graphics2_Rectangle_setRectangle(self->borderRectangle, r);
      Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->borderRectangle, graphics2Context);
    }
  }
}

Ring1_NoDiscardReturn() Machine_Gui_BorderNode*
Machine_Gui_BorderNode_create
  (
    Machine_Gui_Context* context
  )
{
  Machine_Type* ty = Machine_Gui_BorderNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,context));
  Machine_Gui_BorderNode* self = Ring1_cast(Machine_Gui_BorderNode*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Gui_Widget*
Machine_Gui_BorderNode_getChild
  (
    Machine_Gui_BorderNode* self
  )
{ return self->child; }

void
Machine_Gui_BorderNode_setChild
  (
    Machine_Gui_BorderNode* self,
    Ring3_Gui_Widget* child
  )
{
  if (self->child == child) {
    return;
  }
  if (self->child != NULL) {
    ((Ring3_Gui_WidgetBase *)self->child)->parent = NULL;
  }
  self->child = child;
  if (self->child) {
    ((Ring3_Gui_WidgetBase*)self->child)->parent = (Ring3_Gui_Widget*)self;
  }
  self->childDirty = true;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_BorderNode_getBorderColor
  (
    Machine_Gui_BorderNode const* self
  )
{ return Machine_Gui_BorderModel_getColor(self->borderModel); }

void
Machine_Gui_BorderNode_setBorderColor
  (
    Machine_Gui_BorderNode* self,
    Ring3_Math_Vector4f32 const* color
  )
{ Machine_Gui_BorderModel_setColor(self->borderModel, color); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderNode_getBorderLeftWidth
  (
    Machine_Gui_BorderNode const* self
  )
{ return Machine_Gui_BorderModel_getLeftWidth(self->borderModel); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderNode_getBorderRightWidth
  (
    Machine_Gui_BorderNode const* self
  )
{ return Machine_Gui_BorderModel_getRightWidth(self->borderModel); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderNode_getBorderTopWidth
  (
    Machine_Gui_BorderNode const* self
  )
{ return Machine_Gui_BorderModel_getTopWidth(self->borderModel); }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderNode_getBorderBottomWidth
  (
    Machine_Gui_BorderNode const* self
  )
{ return Machine_Gui_BorderModel_getBottomWidth(self->borderModel); }

void
Machine_Gui_BorderNode_setBorderWidth
  (
    Machine_Gui_BorderNode* self,
    Ring2_Real32 width
  )
{ Machine_Gui_BorderModel_setWidth(self->borderModel, width); }

void
Machine_Gui_BorderNode_setLeftBorderWidth
  (
    Machine_Gui_BorderNode* self,
    Ring2_Real32 width
  )
{ Machine_Gui_BorderModel_setLeftWidth(self->borderModel, width); }

void
Machine_Gui_BorderNode_setRightBorderWidth
  (
    Machine_Gui_BorderNode* self,
    Ring2_Real32 width
  )
{ Machine_Gui_BorderModel_setRightWidth(self->borderModel, width); }

void
Machine_Gui_BorderNode_setTopBorderWidth
  (
    Machine_Gui_BorderNode* self,
    Ring2_Real32 width
  )
{ Machine_Gui_BorderModel_setTopWidth(self->borderModel, width); }

void
Machine_Gui_BorderNode_setBottomBorderWidth
  (
    Machine_Gui_BorderNode* self,
    Ring2_Real32 width
  )
{ Machine_Gui_BorderModel_setBottomWidth(self->borderModel, width); }

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Gui_BorderNode_getPreferredSizeImpl
  (
    Machine_Gui_BorderNode const* self
  )
{
  Ring3_Math_Vector2f32* preferredSize = self->child
                                       ? Ring3_Math_Vector2f32_clone(Ring3_Gui_Widget_getPreferredSize(self->child))
                                       : Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32* borderSize = Ring3_Math_Vector2f32_create();
  Ring2_Real32 w = Machine_Gui_BorderModel_getLeftWidth(self->borderModel)
                 + Machine_Gui_BorderModel_getRightWidth(self->borderModel);
  Ring2_Real32 h = Machine_Gui_BorderModel_getTopWidth(self->borderModel)
                 + Machine_Gui_BorderModel_getBottomWidth(self->borderModel);
  Ring3_Math_Vector2f32_set(borderSize, w, h);
  return Ring3_Math_Vector2f32_sum(preferredSize, borderSize);
}
