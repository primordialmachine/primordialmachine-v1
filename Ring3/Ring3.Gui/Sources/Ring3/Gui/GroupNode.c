/// @file Ring3/Gui/GroupNode.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/GroupNode.h"

#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/RenderContext.h"
#include "Ring3/Gui/DefaultRenderContext.h"
#include "Ring3/Gui/Layout/Layouter.h"
#include "Ring3/Gui/ArrayWidgetList.h"
#undef RING3_GUI_PRIVATE


#include "Ring3/Visuals/_Include.h"


static void
Machine_Gui_GroupNode_visit
  (
    Machine_Gui_GroupNode* self
  )
{
  if (self->background) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->background);
  }
  if (self->layoutModel) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->layoutModel);
  }
  if (self->children) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->children);
  }
}

static Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gui_GroupNode_getChildrenImpl
  (
    Machine_Gui_GroupNode const* self
  )
{
  Ring2_Collections_List* list = (Ring2_Collections_List*)Ring2_Collections_ArrayList_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection const*)self->children); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List const*)self->children, i);
    Ring2_Collections_List_append(list, temporary);
  }
  return list;
}

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Gui_GroupNode_getPreferredSizeImpl
  (
    Machine_Gui_GroupNode const* self
  )
{ return Ring3_Math_Rectangle2_getSize(Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget*)self)); }

static void
Machine_Gui_GroupNode_renderImpl
  (
    Machine_Gui_GroupNode* self,
    Ring3_Gui_RenderContext* renderContext
  )
{
  Ring3_Graphics2_Context* ctx2 = ((Ring3_Gui_WidgetBase*)self)->context->graphics2Context;
  Ring3_Graphics2_Context_setTargetSize(ctx2, Ring3_Gui_RenderContext_getCanvasWidth(renderContext),
    Ring3_Gui_RenderContext_getCanvasHeight(renderContext));
  Ring3_Math_Rectangle2* R = Ring3_Gui_Widget_getAbsoluteRectangle((Ring3_Gui_Widget*)self);
  Ring3_Graphics2_Rectangle_setRectangle(self->background, R);
  Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->background, ctx2);
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->children); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, i);
    Ring3_Gui_Widget* widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Gui_Widget_render((Ring3_Gui_Widget*)widget, renderContext);
  }
}

static inline void
Machine_Gui_GroupNode_layoutImpl
  (
    Machine_Gui_GroupNode* self
  )
{
  // Set the size of all children to the same value: That value is the component-wise maxima vector
  // of the preferred sizes of all children.
  Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, 0);
  Ring3_Gui_Widget* widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
  Ring3_Math_Vector2f32* preferredSize = Ring3_Gui_Widget_getPreferredSize(widget);
  for (int64_t i = 1, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->children); i < n; ++i) {
    temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, i);
    widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Vector2f32_maxima(preferredSize, preferredSize,
                                 Ring3_Gui_Widget_getPreferredSize(widget));
  }
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->children); i < n; ++i) {
    temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, i);
    widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Gui_Widget_setSize((Ring3_Gui_Widget*)widget, preferredSize);
  }
  // Layout the children.
  Ring3_Math_Vector2f32* size = Ring3_Gui_Widget_getSize((Ring3_Gui_Widget*)self);
  Ring3_Gui_WidgetList_layout(self->children,
                              Ring3_Math_Vector2f32_getX(size),
                              Ring3_Math_Vector2f32_getY(size),
                              self->layoutModel);
}

static void
Machine_Gui_GroupNode_constructClass
  (
    Machine_Gui_GroupNode_Class* self
  )
{ }

void
Machine_Gui_GroupNode_construct
  (
    Machine_Gui_GroupNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Gui_WidgetBase_construct((Ring3_Gui_WidgetBase*)self, numberOfArguments, arguments);
  self->background = Ring3_Graphics2_Rectangle_create();
  Ring3_Graphics2_Rectangle_setColor(self->background, Ring3_Math_Vector4f32_create(0.f, 0.f, 0.f, 0.f));
  self->layoutModel = Machine_Gui_LayoutModel_create();
  self->children = (Ring3_Gui_WidgetList*)Machine_Gui_ArrayWidgetList_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_GroupNode_getType());
}

static void
Machine_Gui_GroupNode_implement_Ring3_Gui_Widget
  (
    Ring3_Gui_Widget_Dispatch* self
  )
{
  self->getChildren = (Ring2_Collections_List * (*)(Ring3_Gui_Widget const*)) & Machine_Gui_GroupNode_getChildrenImpl;
  self->getPreferredSize = (Ring3_Math_Vector2f32 * (*)(Ring3_Gui_Widget const*)) & Machine_Gui_GroupNode_getPreferredSizeImpl;
  self->layout = (void (*)(Ring3_Gui_Widget*)) & Machine_Gui_GroupNode_layoutImpl;
  self->render = (void (*)(Ring3_Gui_Widget*, Ring3_Gui_RenderContext*)) & Machine_Gui_GroupNode_renderImpl;
}

static void
Machine_Gui_GroupNode_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement
    (
      self,
      Ring3_Gui_Widget_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_Gui_GroupNode_implement_Ring3_Gui_Widget
    );
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_GroupNode,
                         Ring3_Gui_WidgetBase,
                         &Machine_Gui_GroupNode_visit,
                         &Machine_Gui_GroupNode_construct,
                         NULL,
                         &Machine_Gui_GroupNode_constructClass,
                         &Machine_Gui_GroupNode_implementInterfaces)

Ring1_NoDiscardReturn() Machine_Gui_GroupNode*
Machine_Gui_GroupNode_create
  (
    Machine_Gui_Context* context
  )
{
  Machine_Type* ty = Machine_Gui_GroupNode_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_Gui_GroupNode* self = Ring1_cast(Machine_Gui_GroupNode*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring1_NoDiscardReturn() Machine_Gui_LayoutModel*
Machine_Gui_GroupNode_getLayoutModel
  (
    Machine_Gui_GroupNode const* self
  )
{ return self->layoutModel; }

void
Machine_Gui_GroupNode_setLayoutModel
  (
    Machine_Gui_GroupNode* self,
    Machine_Gui_LayoutModel* layoutModel
  )
{ self->layoutModel = layoutModel; }

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_GroupNode_getBackgroundColor
  (
    Machine_Gui_GroupNode const* self
  )
{ return Ring3_Graphics2_Rectangle_getColor(self->background); }

void
Machine_Gui_GroupNode_setBackgroundColor
  (
    Machine_Gui_GroupNode* self,
    Ring3_Math_Vector4f32 const* backgroundColor
  )
{ Ring3_Graphics2_Rectangle_setColor(self->background, backgroundColor); }
