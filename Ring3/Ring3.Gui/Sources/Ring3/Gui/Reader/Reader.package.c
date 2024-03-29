/// @file Ring3/Gui/Reader/Reader.package.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Reader/Reader.package.h"
#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/Gdl/ListToVector.h"
#include "Ring3/Gui/Reader/Reader.h"
#include "Ring3/Gui/Reader/readColor.h"
#undef RING3_GUI_PRIVATE

static void
checkKind
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source,
    Ring2_String* expected
  )
{
  Ring3_Gui_Gdl_Context* context = self->gdlContext;
  if (!Machine_Gui_Reader_hasString(self, source, context->KIND)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  Ring2_String* received = Machine_Gui_Reader_getString(source, context->KIND);
  if (!Ring2_String_isEqualTo(Ring2_Context_get(), received, expected)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
}

Ring1_NoDiscardReturn() Machine_Gui_LayoutModel*
Machine_Gui_Reader_readLayout
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source
  )
{
  Ring3_Gui_Gdl_Context* subContext = self->gdlContext;
  Machine_Gui_LayoutModel* model = Machine_Gui_LayoutModel_create();
  if (Machine_Gui_Reader_hasString(self, source, subContext->DIRECTION)) {
    Ring2_String* temporary = Machine_Gui_Reader_getString(source, subContext->DIRECTION);
    Machine_Gui_LayoutModel_setPrimaryDirection(model, Ring3_Gui_Layout_Direction_parse(temporary));
  }
  if (Machine_Gui_Reader_hasString(self, source, subContext->JUSTIFICATION)) {
    Ring2_String* temporary = Machine_Gui_Reader_getString(source, subContext->JUSTIFICATION);
    Machine_Gui_LayoutModel_setPrimaryJustification(model, Ring3_Gui_Layout_Justification_parse(temporary));
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->INTERSPACING)) {
    Ring2_Real32 temporary = Machine_Gui_Reader_getReal(source, subContext->INTERSPACING);
    Machine_Gui_LayoutModel_setPrimaryInterChildspacing(model, temporary);
  }
  return model;
}

Ring1_NoDiscardReturn() Machine_Gui_GroupNode*
Machine_Gui_Reader_readGroupNode
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source
  )
{
  Ring3_Gui_Gdl_Context* subContext = self->gdlContext;
  checkKind(self, source, subContext->GROUPNODEKIND);
  Machine_Gui_GroupNode* widget = Machine_Gui_GroupNode_create(self);
  if (Machine_Gui_Reader_hasString(self, source, subContext->NAME)) {
    Ring2_String* temporary = Machine_Gui_Reader_getString(source, subContext->NAME);
    Ring3_Gui_Widget_setName((Ring3_Gui_Widget*)widget, temporary);
  }
  if (Machine_Gui_Reader_hasList(self, source, subContext->CHILDREN)) {
    Ring2_Collections_List* temporary1 = Machine_Gui_Reader_getList(self, source, subContext->CHILDREN);
    for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)temporary1); i < n; ++i) {
      Ring2_Value temporary2 = Ring2_Collections_List_getAt(temporary1, i);
      Ring2_Collections_Map* temporary3 = (Ring2_Collections_Map*)Ring2_Value_getObject(&temporary2);
      Ring3_Gui_Widget* childWidget = Machine_Gui_Reader_readWidget(self, temporary3);
      Ring2_Value_setObject(&temporary2, (Machine_Object*)childWidget);
      Ring2_Collections_List_append((Ring2_Collections_List*)widget->children, temporary2);
      ((Ring3_Gui_WidgetBase*)childWidget)->parent = (Ring3_Gui_Widget*)widget;
    }
  }
  if (Machine_Gui_Reader_hasList(self, source, subContext->BACKGROUNDCOLOR)) {
    Ring3_Math_Vector4f32* color = Ring3_Gui_Gdl_Reader_readColor(self, subContext->BACKGROUNDCOLOR, source);
    Machine_Gui_GroupNode_setBackgroundColor(widget, color);
  }
  if (Machine_Gui_Reader_hasMap(self, source, subContext->LAYOUT)) {
    Ring2_Collections_Map* temporary1 = Machine_Gui_Reader_getMap(self, source, subContext->LAYOUT);
    Machine_Gui_LayoutModel* layout = Machine_Gui_Reader_readLayout(self, temporary1);
    Machine_Gui_GroupNode_setLayoutModel(widget, layout);
  }
  return widget;
}

Ring1_NoDiscardReturn() Machine_Gui_BorderNode*
Machine_Gui_Reader_readBorderNode
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source
  )
{
  Ring3_Gui_Gdl_Context* subContext = self->gdlContext;
  checkKind(self, source, subContext->BORDERNODEKIND);
  Machine_Gui_BorderNode* widget = Machine_Gui_BorderNode_create(self);
  if (Machine_Gui_Reader_hasString(self, source, subContext->NAME)) {
    Ring2_String* temporary = Machine_Gui_Reader_getString(source, subContext->NAME);
    Ring3_Gui_Widget_setName((Ring3_Gui_Widget*)widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->BORDERWIDTH)) {
    Ring2_Real32 temporary = Machine_Gui_Reader_getReal(source, subContext->BORDERWIDTH);
    Machine_Gui_BorderNode_setBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->LEFTBORDERWIDTH)) {
    Ring2_Real32 temporary = Machine_Gui_Reader_getReal(source, subContext->LEFTBORDERWIDTH);
    Machine_Gui_BorderNode_setLeftBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->RIGHTBORDERWIDTH)) {
    Ring2_Real32 temporary = Machine_Gui_Reader_getReal(source, subContext->RIGHTBORDERWIDTH);
    Machine_Gui_BorderNode_setRightBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->TOPBORDERWIDTH)) {
    Ring2_Real32 temporary = Machine_Gui_Reader_getReal(source, subContext->TOPBORDERWIDTH);
    Machine_Gui_BorderNode_setTopBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->BOTTOMBORDERWIDTH)) {
    Ring2_Real32 temporary = Machine_Gui_Reader_getReal(source, subContext->BOTTOMBORDERWIDTH);
    Machine_Gui_BorderNode_setBottomBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasList(self, source, subContext->BORDERCOLOR)) {
    Ring3_Math_Vector4f32* color = Ring3_Gui_Gdl_Reader_readColor(self, subContext->BORDERCOLOR, source);
    Machine_Gui_BorderNode_setBorderColor(widget, color);
  }
  if (Machine_Gui_Reader_hasMap(self, source, subContext->CHILD)) {
    Ring2_Collections_Map* temporary = Machine_Gui_Reader_getMap(self, source, subContext->CHILD);
    Ring3_Gui_Widget* childWidget = Machine_Gui_Reader_readWidget(self, temporary);
    Machine_Gui_BorderNode_setChild(widget, childWidget);
  }
  return widget;
}

Ring1_NoDiscardReturn() Machine_Gui_TextNode*
Machine_Gui_Reader_readTextNode
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source
  )
{
  Ring3_Gui_Gdl_Context* subContext = self->gdlContext;
  checkKind(self, source, subContext->TEXTNODEKIND);
  Machine_Gui_TextNode* widget = Machine_Gui_TextNode_create(self);
  if (Machine_Gui_Reader_hasString(self, source, subContext->NAME)) {
    Ring2_String* temporary = Machine_Gui_Reader_getString(source, subContext->NAME);
  }
  if (Machine_Gui_Reader_hasString(self, source, subContext->TEXT)) {
    Ring2_String* temporary = Machine_Gui_Reader_getString(source, subContext->TEXT);
    Machine_Gui_TextNode_setText(widget, temporary);
  }
  return widget;
}
