/// @file Ring3/Gui/ArrayWidgetList.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/ArrayWidgetList.h"

#include "Ring3/Gui/Layout/Layouter.h"
#include "Ring3/Gui/LayoutModel.h"
#include "Ring3/Gui/Widget.h"
#undef RING3_GUI_PRIVATE


struct Machine_Gui_ArrayWidgetList_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gui_ArrayWidgetList {
  Machine_Object __parent;

  Ring2_Collections_ArrayList* backing;
};

static void
Machine_Gui_ArrayWidgetList_visit
  (
    Machine_Gui_ArrayWidgetList* self
  )
{
  if (self->backing) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->backing);
  }
}

static void
Machine_Gui_ArrayWidgetList_constructClass
  (
    Machine_Gui_ArrayWidgetList_Class* self
  )
{/*Intentionally empty.*/}

static Ring1_NoDiscardReturn() int64_t
Machine_Gui_ArrayWidgetList_getSizeImpl
  (
    Machine_Gui_ArrayWidgetList const* self
  )
{ return Ring2_Collections_Collection_getSize((Ring2_Collections_Collection const *)self->backing); }

static void
Machine_Gui_ArrayWidgetList_clearImpl
  (
    Machine_Gui_ArrayWidgetList* self
  )
{ Ring2_Collections_Collection_clear((Ring2_Collections_Collection*)self->backing); }

static bool
Machine_Gui_ArrayWidgetList_isEmptyImpl
  (
    Machine_Gui_ArrayWidgetList const* self
  )
{ return Ring2_Collections_Collection_isEmpty((Ring2_Collections_Collection const*)self->backing); }

static void
Machine_Gui_ArrayWidgetList_implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  )
{
  self->clear = (void (*)(Ring2_Collections_Collection*)) & Machine_Gui_ArrayWidgetList_clearImpl;
  self->getSize = (int64_t(*)(Ring2_Collections_Collection const*)) & Machine_Gui_ArrayWidgetList_getSizeImpl;
  self->isEmpty = (bool (*)(Ring2_Collections_Collection const*)) & Machine_Gui_ArrayWidgetList_isEmptyImpl;
}

static void
Machine_Gui_ArrayWidgetList_appendImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Value value
  )
{ Ring2_Collections_List_append((Ring2_Collections_List*)self->backing, value); }

static Ring2_Value
Machine_Gui_ArrayWidgetList_getAtImpl
  (
    Machine_Gui_ArrayWidgetList const* self,
    int64_t index
  )
{ return Ring2_Collections_List_getAt((Ring2_Collections_List const*)self->backing, index); }

static void
Machine_Gui_ArrayWidgetList_insertAtImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    int64_t index,
    Ring2_Value value
  )
{ Ring2_Collections_List_insertAt((Ring2_Collections_List*)self->backing, index, value); }

static void
Machine_Gui_ArrayWidgetList_prependImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Value value
  )
{ Ring2_Collections_List_prepend((Ring2_Collections_List*)self->backing, value); }

static void
Machine_Gui_ArrayWidgetList_removeAtImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    int64_t index
  )
{ Ring2_Collections_List_removeAt((Ring2_Collections_List*)self->backing, index); }

static void
Machine_Gui_ArrayWidgetList_removeAtFastImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    int64_t index
  )
{ Ring2_Collections_List_removeAtFast((Ring2_Collections_List*)self->backing, index); }

static void
Machine_Gui_ArrayWidgetList_implement_Ring2_Collections_List
  (
    Ring2_Collections_List_Dispatch* self
  )
{
  self->append = (void (*)(Ring2_Collections_List*, Ring2_Value)) & Machine_Gui_ArrayWidgetList_appendImpl;
  self->getAt = (Ring2_Value(*)(Ring2_Collections_List const*, int64_t index)) & Machine_Gui_ArrayWidgetList_getAtImpl;
  self->insertAt = (void (*)(Ring2_Collections_List*, int64_t, Ring2_Value)) & Machine_Gui_ArrayWidgetList_insertAtImpl;
  self->prepend = (void (*)(Ring2_Collections_List*, Ring2_Value)) & Machine_Gui_ArrayWidgetList_prependImpl;
  self->removeAt = (void (*)(Ring2_Collections_List*, int64_t)) & Machine_Gui_ArrayWidgetList_removeAtImpl;
  self->removeAtFast = (void (*)(Ring2_Collections_List*, int64_t)) & Machine_Gui_ArrayWidgetList_removeAtFastImpl;
}

static void
Machine_Gui_ArrayWidgetList_translateImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring3_Math_Vector2f32 const* t
  )
{
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection *)self); i < n; ++i) {
    Ring2_Value widgetValue = Ring2_Collections_List_getAt((Ring2_Collections_List *)self, i);
    Ring3_Gui_Widget* widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&widgetValue);
    Ring3_Gui_Widget_translate((Ring3_Gui_Widget*)widget, t);
  }
}

static void
Machine_Gui_ArrayWidgetList_centerHorizontallyImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Real32 x
  )
{
  Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    Ring3_Gui_Widget* widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Rectangle2 const* bounds = Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget const*)widget);
    Ring2_Real32 cx = Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getCenter(bounds));
    Ring2_Real32 dx = x - cx;
    Ring3_Math_Vector2f32 const* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget const*)widget);
    Ring3_Math_Vector2f32_set(delta, dx, 0.f);
    Ring3_Math_Vector2f32_add(oldPosition, delta, newPosition);
    Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)widget, newPosition);
  }
}

static void
Machine_Gui_ArrayWidgetList_centerVerticallyImpl
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Real32 y
  )
{
  Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    Ring3_Gui_Widget* widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Rectangle2 const* bounds = Ring3_Gui_Widget_getRectangle((Ring3_Gui_Widget const*)widget);
    Ring2_Real32 cy = Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getCenter(bounds));
    Ring2_Real32 dy = y - cy;
    Ring3_Math_Vector2f32 const* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget const*)widget);
    Ring3_Math_Vector2f32_set(delta, 0.f, dy);
    Ring3_Math_Vector2f32_add(oldPosition, delta, newPosition);
    Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)widget, newPosition);
  }
}

static void
Machine_Gui_ArrayWidgetList_implement_Ring3_Gui_WidgetList
  (
    Ring3_Gui_WidgetList_Dispatch* self
  )
{
  self->translate = (void (*)(Ring3_Gui_WidgetList*, Ring3_Math_Vector2f32 const*)) & Machine_Gui_ArrayWidgetList_translateImpl;
  self->centerHorizontally = (void (*)(Ring3_Gui_WidgetList*, Ring2_Real32)) &Machine_Gui_ArrayWidgetList_centerHorizontallyImpl;
  self->centerVertically = (void (*)(Ring3_Gui_WidgetList*, Ring2_Real32)) &Machine_Gui_ArrayWidgetList_centerVerticallyImpl;
}

static void
Machine_Gui_ArrayWidgetList_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement
    (
      self,
      Ring2_Collections_Collection_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_Gui_ArrayWidgetList_implement_Ring2_Collections_Collection
    );
  Machine_ClassType_implement
    (
      self,
      Ring2_Collections_List_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_Gui_ArrayWidgetList_implement_Ring2_Collections_List
    );
  Machine_ClassType_implement
    (
      self,
      Ring3_Gui_WidgetList_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_Gui_ArrayWidgetList_implement_Ring3_Gui_WidgetList
    );
}

void
Machine_Gui_ArrayWidgetList_construct
  (
    Machine_Gui_ArrayWidgetList* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->backing = Ring2_Collections_ArrayList_create();
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_Gui_ArrayWidgetList_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_ArrayWidgetList,
                         Machine_Object,
                         &Machine_Gui_ArrayWidgetList_visit,
                         &Machine_Gui_ArrayWidgetList_construct,
                         NULL,
                         &Machine_Gui_ArrayWidgetList_constructClass,
                         &Machine_Gui_ArrayWidgetList_implementInterfaces)

Ring1_NoDiscardReturn() Machine_Gui_ArrayWidgetList*
Machine_Gui_ArrayWidgetList_create
  (
  )
{
  Machine_Type* ty = Machine_Gui_ArrayWidgetList_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gui_ArrayWidgetList* self = Ring1_cast(Machine_Gui_ArrayWidgetList*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
