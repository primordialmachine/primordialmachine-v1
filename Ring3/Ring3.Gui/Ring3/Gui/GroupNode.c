/// @file Ring3/Gui/GroupNode.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/GroupNode.h"

#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/RenderContext.h"
#include "Ring3/Gui/DefaultRenderContext.h"
#undef RING3_GUI_PRIVATE


#include "Ring3/Visuals/_Include.h"


static void
Machine_Gui_GroupNode_visit
  (
    Machine_Gui_GroupNode* self
  )
{
  if (self->layoutModel) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->layoutModel);
  }
  if (self->children) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->children);
  }
}

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Gui_GroupNode_getPreferredSize
  (
    Machine_Gui_GroupNode const* self
  )
{ return Ring3_Math_Rectangle2_getSize(Machine_Gui_Widget_getRectangle((Machine_Gui_Widget*)self)); }

static void
Machine_Gui_GroupNode_render
  (
    Machine_Gui_GroupNode* self,
    Ring3_Gui_RenderContext* renderContext
  )
{
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection *)self->children); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Machine_Gui_Widget_render(widget, (Ring3_Gui_RenderContext*)renderContext);
  }
}

static inline void
Machine_Gui_GroupNode_layout
  (
    Machine_Gui_GroupNode* self
  )
{
  // Set the size of all children to the same value: That value is the component-wise maxima vector
  // of the preferred sizes of all children.
  Ring3_Math_Vector2f32* preferredSize = Machine_Gui_Widget_getPreferredSize(Machine_Gui_ArrayWidgetList_getAt(self->children, 0));
  for (int64_t i = 1, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->children); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Vector2f32_maxima(preferredSize, preferredSize,
                                 Machine_Gui_Widget_getPreferredSize(widget));
  }
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->children); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self->children, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Machine_Gui_Widget_setSize(widget, preferredSize);
  }
  // Layout the children.
  Ring3_Math_Vector2f32* size = Machine_Gui_Widget_getSize((Machine_Gui_Widget*)self);
  Machine_Gui_ArrayWidgetList_layout(self->children,
                                     Ring3_Math_Vector2f32_getX(size),
                                     Ring3_Math_Vector2f32_getY(size),
                                     self->layoutModel);
}

static void
Machine_Gui_GroupNode_constructClass
  (
    Machine_Gui_GroupNode_Class* self
  )
{
  ((Machine_Gui_Widget_Class*)self)->render
    = (void (*)(Machine_Gui_Widget*, Ring3_Gui_RenderContext*))
    & Machine_Gui_GroupNode_render;
  ((Machine_Gui_Widget_Class*)self)->getPreferredSize
    = (Ring3_Math_Vector2f32* (*)(Machine_Gui_Widget const*))
    & Machine_Gui_GroupNode_getPreferredSize;
  ((Machine_Gui_Widget_Class*)self)->layout
    = (void (*)(Machine_Gui_Widget*))
    & Machine_Gui_GroupNode_layout;
}

void
Machine_Gui_GroupNode_construct
  (
    Machine_Gui_GroupNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Gui_Widget_construct((Machine_Gui_Widget*)self, numberOfArguments, arguments);
  self->layoutModel = Machine_Gui_LayoutModel_create();
  self->children = Machine_Gui_ArrayWidgetList_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_GroupNode_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_GroupNode,
                         Machine_Gui_Widget,
                         &Machine_Gui_GroupNode_visit,
                         &Machine_Gui_GroupNode_construct,
                         NULL,
                         &Machine_Gui_GroupNode_constructClass,
                         NULL)

Ring1_NoDiscardReturn() Machine_Gui_GroupNode*
Machine_Gui_GroupNode_create
  (
    Machine_Gui_Context* context
  )
{
  Machine_ClassType* ty = Machine_Gui_GroupNode_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context);
  Machine_Gui_GroupNode* self = (Machine_Gui_GroupNode*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_NoDiscardReturn() Machine_Gui_LayoutModel const*
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
