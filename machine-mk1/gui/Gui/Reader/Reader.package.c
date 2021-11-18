/// @file Gui/Reader/Reader.package.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Reader/Reader.package.h"

#include "Gui/Context.h"
#include "Gui/Gdl/ListToVector.h"
#include "Gui/Reader/Reader.h"

static void checkKind(Machine_Gui_Context* self, Machine_Map const* source,
                      Machine_String* expected) {
  Machine_Gui_Gdl_Context* context = self->gdlContext;
  if (!Machine_Gui_Reader_hasString(self, source, context->KIND)) {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
  Machine_String* received = Machine_Gui_Reader_getString(source, context->KIND);
  if (!Machine_String_isEqualTo(received, expected)) {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
}

Machine_Gui_LayoutModel* Machine_Gui_Reader_readLayout(Machine_Gui_Context* self,
                                                       Machine_Map const* source) {
  Machine_Gui_Gdl_Context* subContext = self->gdlContext;
  Machine_Gui_LayoutModel* model = Machine_Gui_LayoutModel_create();
  if (Machine_Gui_Reader_hasString(self, source, subContext->DIRECTION)) {
    Machine_String* temporary = Machine_Gui_Reader_getString(source, subContext->DIRECTION);
    if (Machine_String_isEqualTo(temporary, subContext->COLUMN)) {
      Machine_Gui_LayoutModel_setPrimaryDirection(model, Machine_Gui_Layout_Direction_Column);
    } else if (Machine_String_isEqualTo(temporary, subContext->COLUMNREVERSE)) {
      Machine_Gui_LayoutModel_setPrimaryDirection(model,
                                                  Machine_Gui_Layout_Direction_ColumnReverse);
    } else if (Machine_String_isEqualTo(temporary, subContext->ROW)) {
      Machine_Gui_LayoutModel_setPrimaryDirection(model, Machine_Gui_Layout_Direction_Row);
    } else if (Machine_String_isEqualTo(temporary, subContext->ROWREVERSE)) {
      Machine_Gui_LayoutModel_setPrimaryDirection(model, Machine_Gui_Layout_Direction_RowReverse);
    } else {
      Machine_setStatus(Machine_Status_SemanticalError);
      Machine_jump();
    }
  }
  if (Machine_Gui_Reader_hasString(self, source, subContext->JUSTIFICATION)) {
    Machine_String* temporary = Machine_Gui_Reader_getString(source, subContext->JUSTIFICATION);
    if (Machine_String_isEqualTo(temporary, subContext->START)) {
      Machine_Gui_LayoutModel_setPrimaryJustification(model,
                                                      Machine_Gui_Layout_Justification_Start);
    } else if (Machine_String_isEqualTo(temporary, subContext->CENTER)) {
      Machine_Gui_LayoutModel_setPrimaryJustification(model,
                                                      Machine_Gui_Layout_Justification_Center);
    } else if (Machine_String_isEqualTo(temporary, subContext->END)) {
      Machine_Gui_LayoutModel_setPrimaryJustification(model, Machine_Gui_Layout_Justification_End);
    } else {
      Machine_setStatus(Machine_Status_LexicalError);
      Machine_jump();
    }
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->INTERSPACING)) {
    Machine_Real temporary = Machine_Gui_Reader_getReal(source, subContext->INTERSPACING);
    Machine_Gui_LayoutModel_setPrimaryInterChildspacing(model, temporary);
  }
  return model;
}

Machine_Gui_GroupNode* Machine_Gui_Reader_readGroupNode(Machine_Gui_Context* self,
                                                        Machine_Map const* source) {
  Machine_Gui_Gdl_Context* subContext = self->gdlContext;
  checkKind(self, source, subContext->GROUPNODEKIND);
  Machine_Gui_GroupNode* widget = Machine_Gui_GroupNode_create(self);
  if (Machine_Gui_Reader_hasList(self, source, subContext->CHILDREN)) {
    Machine_List* temporary1 = Machine_Gui_Reader_getList(self, source, subContext->CHILDREN);
    for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)temporary1); i < n;
         ++i) {
      Machine_Value temporary2 = Machine_List_getAt(temporary1, i);
      Machine_Map* temporary3 = (Machine_Map*)Machine_Value_getObject(&temporary2);
      Machine_Gui_Widget* childWidget
          = Machine_Gui_Reader_readWidget(self, (Machine_Map*)temporary3);

      // TODO: Should be Machine_Gui_Widget_appendChild.
      Machine_Gui_WidgetList_append(widget->children, childWidget);
      childWidget->parent = (Machine_Gui_Widget*)widget;
    }
  }
  if (Machine_Gui_Reader_hasMap(self, source, subContext->LAYOUT)) {
    Machine_Map* temporary1 = Machine_Gui_Reader_getMap(self, source, subContext->LAYOUT);
    Machine_Gui_LayoutModel* layout = Machine_Gui_Reader_readLayout(self, temporary1);
    Machine_Gui_GroupNode_setLayoutModel(widget, layout);
  }
  return widget;
}

Machine_Gui_BorderNode* Machine_Gui_Reader_readBorderNode(Machine_Gui_Context* self,
                                                          Machine_Map const* source) {
  Machine_Gui_Gdl_Context* subContext = self->gdlContext;
  checkKind(self, source, subContext->BORDERNODEKIND);
  Machine_Gui_BorderNode* widget = Machine_Gui_BorderNode_create(self);
  if (Machine_Gui_Reader_hasReal(self, source, subContext->BORDERWIDTH)) {
    Machine_Real temporary = Machine_Gui_Reader_getReal(source, subContext->BORDERWIDTH);
    Machine_Gui_BorderNode_setBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->LEFTBORDERWIDTH)) {
    Machine_Real temporary = Machine_Gui_Reader_getReal(source, subContext->LEFTBORDERWIDTH);
    Machine_Gui_BorderNode_setLeftBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->RIGHTBORDERWIDTH)) {
    Machine_Real temporary = Machine_Gui_Reader_getReal(source, subContext->RIGHTBORDERWIDTH);
    Machine_Gui_BorderNode_setRightBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->TOPBORDERWIDTH)) {
    Machine_Real temporary = Machine_Gui_Reader_getReal(source, subContext->TOPBORDERWIDTH);
    Machine_Gui_BorderNode_setTopBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasReal(self, source, subContext->BOTTOMBORDERWIDTH)) {
    Machine_Real temporary = Machine_Gui_Reader_getReal(source, subContext->BOTTOMBORDERWIDTH);
    Machine_Gui_BorderNode_setBottomBorderWidth(widget, temporary);
  }
  if (Machine_Gui_Reader_hasList(self, source, subContext->BORDERCOLOR)) {
    Machine_Math_Vector3* temporary = Machine_Gui_Gdl_listToVector3(
        Machine_Gui_Reader_getList(self, source, subContext->BORDERCOLOR));
    Machine_Math_Vector4* temporary2 = Machine_Math_Vector4_create();
    Machine_Math_Vector4_set(temporary2, Machine_Math_Vector3_getX(temporary),
                             Machine_Math_Vector3_getY(temporary),
                             Machine_Math_Vector3_getZ(temporary), 1.f);
    Machine_Gui_BorderNode_setBorderColor(widget, temporary2);
  }
  if (Machine_Gui_Reader_hasMap(self, source, subContext->CHILD)) {
    Machine_Map* temporary = Machine_Gui_Reader_getMap(self, source, subContext->CHILD);
    Machine_Gui_Widget* childWidget = Machine_Gui_Reader_readWidget(self, (Machine_Map*)temporary);
    Machine_Gui_BorderNode_setChild(widget, childWidget);
  }
  return widget;
}

Machine_Gui_TextNode* Machine_Gui_Reader_readTextNode(Machine_Gui_Context* self,
                                                      Machine_Map const* source) {
  Machine_Gui_Gdl_Context* subContext = self->gdlContext;
  checkKind(self, source, subContext->TEXTNODEKIND);
  Machine_Gui_TextNode* widget = Machine_Gui_TextNode_create(self);
  if (Machine_Gui_Reader_hasString(self, source, subContext->TEXT)) {
    Machine_String* temporary = Machine_Gui_Reader_getString(source, subContext->TEXT);
    Machine_Gui_TextNode_setText(widget, temporary);
  }
  return widget;
}