/// @file Ring3/Gui/Widget.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Widget.h"
#undef RING3_GUI_PRIVATE

static void
addPrerequisites
  (
    Machine_InterfaceType* self
  )
{/*Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collections_List_getType());*/}

MACHINE_DEFINE_INTERFACETYPE(Ring3_Gui_Widget, &addPrerequisites)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Ring3_Gui_Widget_render
  (
    Ring3_Gui_Widget* self,
    Ring3_Gui_RenderContext* renderContext
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, render, , self, renderContext); }

void
Ring3_Gui_Widget_setPosition
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* position
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, setPosition, , self, position); }

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getPosition
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getPosition, return, self); }

void
Ring3_Gui_Widget_setSize
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* size
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, setSize, , self, size); }

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getSize
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getSize, return, self); }

void
Ring3_Gui_Widget_setRectangle
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Rectangle2 const* rectangle
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, setRectangle, , self, rectangle); }

Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_Widget_getRectangle
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getRectangle, return, self); }

void
Ring3_Gui_Widget_layout
  (
    Ring3_Gui_Widget* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, layout, , self); }

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getPreferredSize
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getPreferredSize, return , self); }

void
Ring3_Gui_Widget_translate
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* t
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, translate, , self, t); }

void
Ring3_Gui_Widget_emit
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, emit, , self, name, numberOfArguments, arguments); }

void
Ring3_Gui_Widget_subscribe
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, subscribe, , self, name, context, callback); }

void
Ring3_Gui_Widget_unsubscribe
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, unsubscribe, , self, name, context, callback); }

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getAbsolutePosition
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getAbsolutePosition, return , self); }

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getAbsoluteSize
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getAbsoluteSize, return, self); }

Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_Widget_getAbsoluteRectangle
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getAbsoluteRectangle, return, self); }

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_Widget_getName
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getName, return, self); }

void
Ring3_Gui_Widget_setName
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, setName, , self, name); }

Ring1_NoDiscardReturn() Ring2_Collections_List*
Ring3_Gui_Widget_getChildren
  (
    Ring3_Gui_Widget const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, getChildren, return, self); }

void
Ring3_Gui_Widget_select
  (
    Ring3_Gui_Widget const* self,
    Ring3_Gui_Selector const* selector,
    Ring3_Gui_WidgetList* results
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_Widget, select, , self, selector, results); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
