#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Layout/Layouter.h"

#include "Ring3/Gui/Widget.h"
#include "Ring3/Gui/WidgetList.h"
#include "Ring3/Gui/LayoutModel.h"
#undef RING3_GUI_PRIVATE

Ring2_Real32
Ring3_Gui_WidgetList_layoutColumn
  (
    Ring3_Gui_WidgetList* self,
    bool reverse,
    Ring2_Real32 interChildSpacingY,
    Ring2_Real32 columnSizeY
  )
{
  Ring2_Value temporary = Ring2_Value_StaticInitializerVoid();
  Ring3_Gui_Widget* widget = NULL;
  int64_t n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self);
  // Basically just lay them out consecutively.
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  if (reverse) {
    Ring2_Real32 nextStartY = columnSizeY, currentStartY = 0.f, currentEndY = 0.f;
    for (int64_t i = 0; i < n; ++i) {
      temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
      widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
      Ring2_Real32 h = Ring3_Math_Vector2f32_getY(Ring3_Gui_Widget_getSize((Ring3_Gui_Widget*)widget));
      currentStartY = nextStartY;
      Ring3_Math_Vector2f32 const* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget*)widget);
      Ring3_Math_Vector2f32_set(newPosition, Ring3_Math_Vector2f32_getX(oldPosition), currentStartY - h);
      Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)widget, newPosition);
      currentEndY = currentStartY - h;
      nextStartY = currentEndY - interChildSpacingY;
    }
    return currentEndY;
  } else {
    Ring2_Real32 nextStartY = 0.f, currentStartY = 0.f, currentEndY = 0.f;
    for (int64_t i = 0; i < n; ++i) {
      currentStartY = nextStartY;
      temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
      widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
      Ring3_Math_Vector2f32 const* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget*)widget);
      Ring3_Math_Vector2f32_set(newPosition, Ring3_Math_Vector2f32_getX(oldPosition), currentStartY);
      Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)widget, newPosition);
      currentEndY = currentStartY + Ring3_Math_Vector2f32_getY(Ring3_Gui_Widget_getSize((Ring3_Gui_Widget*)widget));
      nextStartY = currentEndY + interChildSpacingY;
    }
    return currentEndY;
  }
}

Ring2_Real32
Ring3_Gui_WidgetList_layoutRow
  (
    Ring3_Gui_WidgetList* self,
    bool reverse,
    Ring2_Real32 interChildSpacingX,
    Ring2_Real32 columnSizeX
  )
{
  Ring2_Value temporary = Ring2_Value_StaticInitializerVoid();
  Ring3_Gui_Widget* widget = NULL;
  int64_t n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self);
  // Basically just lay them out consecutively.
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  if (reverse) {
    Ring2_Real32 nextStartX = columnSizeX, currentStartX = 0.f, currentEndX = 0.f;
    for (int64_t i = 0; i < n; ++i) {
      temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
      widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
      Ring2_Real32 w = Ring3_Math_Vector2f32_getX(Ring3_Gui_Widget_getSize((Ring3_Gui_Widget*)widget));
      currentStartX = nextStartX;
      Ring3_Math_Vector2f32 const* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget*)widget);
      Ring3_Math_Vector2f32_set(newPosition, currentStartX - w, Ring3_Math_Vector2f32_getY(oldPosition));
      Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)widget, newPosition);
      currentEndX = currentStartX - w;
      nextStartX = currentEndX - interChildSpacingX;
    }
    return currentEndX;
  } else {
    Ring2_Real32 nextStartX = 0.f, currentStartX = 0.f, currentEndX = 0.f;
    for (int64_t i = 0; i < n; ++i) {
      currentStartX = nextStartX;
      temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
      widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
      Ring3_Math_Vector2f32 const* oldPosition = Ring3_Gui_Widget_getPosition((Ring3_Gui_Widget*)widget);
      Ring3_Math_Vector2f32_set(newPosition, currentStartX, Ring3_Math_Vector2f32_getY(oldPosition));
      Ring3_Gui_Widget_setPosition((Ring3_Gui_Widget*)widget, newPosition);
      currentEndX = currentStartX + Ring3_Math_Vector2f32_getX(Ring3_Gui_Widget_getSize((Ring3_Gui_Widget*)widget));
      nextStartX = currentEndX + interChildSpacingX;
    }
    return currentEndX;
  }
}

void
Ring3_Gui_WidgetList_layout
  (
    Ring3_Gui_WidgetList* self,
    Ring2_Real32 parentWidth,
    Ring2_Real32 parentHeight,
    Machine_Gui_LayoutModel* model
  )
{
  // Set the size of all elements to the same value: That value is the component-wise maxima vector
  // of the preferred sizes of all elements.
  Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, 0);
  Ring3_Gui_Widget* widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
  Ring3_Math_Vector2f32* preferredSize = Ring3_Gui_Widget_getPreferredSize(widget);
  for (int64_t i = 1, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Vector2f32_maxima(preferredSize, preferredSize, Ring3_Gui_Widget_getPreferredSize(widget));
  }
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    widget = (Ring3_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Gui_Widget_setSize((Ring3_Gui_Widget*)widget, preferredSize);
  }
  switch (Machine_Gui_LayoutModel_getPrimaryDirection(model)) {
  case Ring3_Gui_Layout_Direction_Column: {
    Ring2_Real32 y =
      Ring3_Gui_WidgetList_layoutColumn
      (
        (Ring3_Gui_WidgetList*)self,
        false,
        Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model),
        parentHeight
      );
    Ring2_Real32 t = y;
    switch (Machine_Gui_LayoutModel_getPrimaryJustification(model)) {
    case Ring3_Gui_Layout_Justification_Start: {
      // Intentionally empty.
    } break;
    case Ring3_Gui_Layout_Justification_Center: {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, 0.f, (parentHeight - t) * 0.5f);
      Ring3_Gui_WidgetList_translate(self, v);
    } break;
    case Ring3_Gui_Layout_Justification_End: {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, 0.f, (parentHeight - t));
      Ring3_Gui_WidgetList_translate(self, v);
    } break;
    default: {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    } break;
    };
    // Center around the column.
    Ring3_Gui_WidgetList_centerHorizontally(self, parentWidth * 0.5f);
  } break;
  case Ring3_Gui_Layout_Direction_ColumnReverse: {
    Ring2_Real32 y =
      Ring3_Gui_WidgetList_layoutColumn
      (
        (Ring3_Gui_WidgetList*)self,
        true,
        Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model),
        parentHeight
      );
    Ring2_Real32 t = y;
    switch (Machine_Gui_LayoutModel_getPrimaryJustification(model)) {
    case Ring3_Gui_Layout_Justification_Start: {
      // Nothing to do.
    } break;
    case Ring3_Gui_Layout_Justification_Center: {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, 0.f, -t * 0.5f);
      Ring3_Gui_WidgetList_translate(self, v);
    } break;
    case Ring3_Gui_Layout_Justification_End: {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, 0.f, -t);
      Ring3_Gui_WidgetList_translate(self, v);
    } break;
    default: {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    } break;
    };
    // Center around the column.
    Ring3_Gui_WidgetList_centerHorizontally(self, parentWidth * 0.5f);
  } break;
  case Ring3_Gui_Layout_Direction_Row: {
    Ring2_Real32 x =
      Ring3_Gui_WidgetList_layoutRow
      (
        (Ring3_Gui_WidgetList*)self,
        false,
        Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model),
        parentWidth
      );

    Ring2_Real32 t = x;
    if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
      == Ring3_Gui_Layout_Justification_Start) {
    }
    else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
      == Ring3_Gui_Layout_Justification_Center) {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, (parentWidth - t) * 0.5f, 0.f);
      Ring3_Gui_WidgetList_translate(self, v);
    }
    else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
      == Ring3_Gui_Layout_Justification_End) {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, (parentWidth - t), 0.f);
      Ring3_Gui_WidgetList_translate(self, v);
    }
    else {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    // Center around the row.
    Ring3_Gui_WidgetList_centerVertically(self, parentHeight * 0.5f);
  } break;
  case Ring3_Gui_Layout_Direction_RowReverse: {
    Ring2_Real32 x =
      Ring3_Gui_WidgetList_layoutRow
      (
        self,
        true,
        Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model),
        parentWidth
      );
    Ring2_Real32 t = x;
    if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
      == Ring3_Gui_Layout_Justification_Start) { /**/
    }
    else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
      == Ring3_Gui_Layout_Justification_Center) {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, -t * 0.5f, 0.f);
      Ring3_Gui_WidgetList_translate(self, v);
    }
    else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
      == Ring3_Gui_Layout_Justification_End) {
      Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(v, -t, 0.f);
      Ring3_Gui_WidgetList_translate(self, v);
    }
    else {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    // Center around the row.
    Ring3_Gui_WidgetList_centerVertically(self, parentHeight * 0.5f);
  } break;
  default: {
    Ring2_unreachable();
  } break;
  };
}
