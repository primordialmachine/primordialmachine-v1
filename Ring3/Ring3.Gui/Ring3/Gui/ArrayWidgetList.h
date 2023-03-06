/// @file Ring3/Gui/ArrayWidgetList.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_ARRAYWIDGETLIST_H_INCLUDED)
#define MACHINE_GUI_ARRAYWIDGETLIST_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/WidgetList.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/header.h.i"
#include "Ring3/Gui/LayoutModel.h"
#include "Ring3/Gui/Widget.h"
#include "Ring3/Gui/WidgetList.h"

/// @brief A label to display a text.
/// @remarks The preferred size of a panel is computed by combining the rectangles of its child
/// nodes.
/// @extends Machine.Object
/// @implements Ring3.Gui.WidgetList
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_ArrayWidgetList)

/// @brief Create an empty panel.
/// @return The panel.
Ring1_NoDiscardReturn() Machine_Gui_ArrayWidgetList*
Machine_Gui_ArrayWidgetList_create
  (
  );

/// @brief Get the widget at an index in this widget list.
/// @param self This widget list.
/// @param index The index.
/// @return The widget.
/// @error @a index is out of bounds.
Ring1_NoDiscardReturn() Machine_Gui_Widget*
Machine_Gui_ArrayWidgetList_getAt
  (
    Machine_Gui_ArrayWidgetList const* self,
    int64_t index
  );

/// @brief Append a widget to this widget list.
/// @param self This widget list.
/// @param widget The widget.
void
Machine_Gui_ArrayWidgetList_append
  (
    Machine_Gui_ArrayWidgetList* self,
    Machine_Gui_Widget* widget
  );

/// @brief Center the widgets horizontally around the given x-coordinate.
/// The y-positions of the widgets are not modified.
/// @param self This widget list.
/// @param x The x-coordinate.
static inline void
Machine_Gui_ArrayWidgetList_centerColumn
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Real32 x
  )
{
  Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Rectangle2 const* bounds = Machine_Gui_Widget_getRectangle(widget);
    Ring2_Real32 cx = Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getCenter(bounds));
    Ring2_Real32 dx = x - cx;
    Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Ring3_Math_Vector2f32_set(delta, dx, 0.f);
    Ring3_Math_Vector2f32_add(oldPosition, delta, newPosition);
    Machine_Gui_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Center the widgets vertically around the given y-coordinate.
/// The x-positions of the widgets are not modified.
/// @param self This widget list.
/// @param y The y-coordinate.
static inline void
Machine_Gui_ArrayWidgetList_centerRow
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Real32 y
  )
{
  Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Machine_Gui_ArrayWidgetList_getAt(self, i);
    Ring3_Math_Rectangle2 const* bounds = Machine_Gui_Widget_getRectangle(widget);
    Ring2_Real32 cy = Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getCenter(bounds));
    Ring2_Real32 dy = y - cy;
    Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Ring3_Math_Vector2f32_set(delta, 0.f, dy);
    Ring3_Math_Vector2f32_add(oldPosition, delta, newPosition);
    Machine_Gui_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Layout the widgets in a column with a distance of paddingy between each two widgets.
/// The first widget is located at y = 0. The x-positions of the widgets are not modified.
/// @param self Theis widget list.
/// @param paddingy The padding between two widgets.
static inline void
Machine_Gui_ArrayWidgetList_layoutColumn
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Real32 paddingy
  )
{
  Ring2_Real32 y = 0.f;
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Ring3_Math_Vector2f32_set(newPosition, Ring3_Math_Vector2f32_getX(oldPosition), y);
    Machine_Gui_Widget_setPosition(widget, newPosition);
    y += Ring3_Math_Vector2f32_getY(Machine_Gui_Widget_getSize(widget)) + paddingy;
  }
}

/// @brief Layout the widgets according to the specified layout model.
/// @param self This widget list.
/// @param model The layout model.
static inline void
Machine_Gui_ArrayWidgetList_layout
  (
    Machine_Gui_ArrayWidgetList* self,
    Ring2_Real32 parentWidth,
    Ring2_Real32 parentHeight,
    Machine_Gui_LayoutModel* model
  )
{
  // Set the size of all elements to the same value: That value is the component-wise maxima vector
  // of the preferred sizes of all elements.
  Ring3_Math_Vector2f32* preferredSize = Ring3_Math_Vector2f32_clone(
      Machine_Gui_Widget_getPreferredSize(Machine_Gui_ArrayWidgetList_getAt(self, 0)));
  for (int64_t i = 1, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Ring3_Math_Vector2f32_maxima(preferredSize, preferredSize, Machine_Gui_Widget_getPreferredSize(widget));
  }
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
    Machine_Gui_Widget_setSize(widget, preferredSize);
  }

  switch (Machine_Gui_LayoutModel_getPrimaryDirection(model)) {
    case Machine_Gui_Layout_Direction_Column: {
      Ring2_Real32 y = 0.f;
      // Basically just lay them out consecutively.
      Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
      for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
        Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
        Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
        Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Ring3_Math_Vector2f32_set(newPosition, Ring3_Math_Vector2f32_getX(oldPosition), y);
        Machine_Gui_Widget_setPosition(widget, newPosition);
        y += Ring3_Math_Vector2f32_getY(Machine_Gui_Widget_getSize(widget))
             + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }
      Ring2_Real32 t = y - Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) {
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, 0.f, (parentHeight - t) * 0.5f);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, 0.f, (parentHeight - t));
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the column.
      Machine_Gui_ArrayWidgetList_centerColumn(self, parentWidth * 0.5f);

    } break;
    case Machine_Gui_Layout_Direction_ColumnReverse: {
      Ring2_Real32 y = parentHeight;
      Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
      for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
        Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
        Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
        y -= Ring3_Math_Vector2f32_getY(Machine_Gui_Widget_getSize(widget));
        Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Ring3_Math_Vector2f32_set(newPosition, Ring3_Math_Vector2f32_getX(oldPosition), y);
        Machine_Gui_Widget_setPosition(widget, newPosition);
        y -= Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }

      Ring2_Real32 t = y + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) { /**/
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, 0.f, -t * 0.5f);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, 0.f, -t);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the column.
      Machine_Gui_ArrayWidgetList_centerColumn(self, parentWidth * 0.5f);

    } break;
    case Machine_Gui_Layout_Direction_Row: {
      Ring2_Real32 x = 0.f;
      Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
      for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
        Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
        Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
        Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Ring3_Math_Vector2f32_set(newPosition, x, Ring3_Math_Vector2f32_getY(oldPosition));
        Machine_Gui_Widget_setPosition(widget, newPosition);
        x += Ring3_Math_Vector2f32_getX(Machine_Gui_Widget_getSize(widget))
           + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }

      Ring2_Real32 t = x - Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) {
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, (parentWidth - t) * 0.5f, 0.f);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, (parentWidth - t), 0.f);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the row.
      Machine_Gui_ArrayWidgetList_centerRow(self, parentHeight * 0.5f);

    } break;
    case Machine_Gui_Layout_Direction_RowReverse: {
      Ring2_Real32 x = parentWidth;
      Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_create();
      for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self); i < n; ++i) {
        Ring2_Value temporary = Ring2_Collections_List_getAt((Ring2_Collections_List*)self, i);
        Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Ring2_Value_getObject(&temporary);
        x -= Ring3_Math_Vector2f32_getX(Machine_Gui_Widget_getSize(widget));
        Ring3_Math_Vector2f32 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Ring3_Math_Vector2f32_set(newPosition, x, Ring3_Math_Vector2f32_getY(oldPosition));
        Machine_Gui_Widget_setPosition(widget, newPosition);
        x -= Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }

      Ring2_Real32 t = x + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) { /**/
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, -t * 0.5f, 0.f);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
        Ring3_Math_Vector2f32_set(v, -t, 0.f);
        Ring3_Gui_WidgetList_translate((Ring3_Gui_WidgetList*)self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the row.
      Machine_Gui_ArrayWidgetList_centerRow(self, parentHeight * 0.5f);

    } break;
    default: {
      Ring2_unreachable();
    } break;
  };
}

#endif // MACHINE_GUI_ARRAYWIDGETLIST_H_INCLUDED
