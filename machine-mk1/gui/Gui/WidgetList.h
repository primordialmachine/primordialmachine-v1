/// @file Gui/WidgetList.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_WIDGETLIST_H_INCLUDED)
#define MACHINE_GUI_WIDGETLIST_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "Gui/LayoutModel.h"
#include "Gui/Widget.h"

/// @brief A label to display a text.
/// @remarks The preferred size of a panel is computed by combining the rectangles of its child
/// nodes.
/// @extends Machine.Gui.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_WidgetList)

/// @brief Create an empty panel.
/// @return The panel.
Machine_Gui_WidgetList* Machine_Gui_WidgetList_create();

/// @brief Get the size of this widget list.
/// @param self This widget list.
/// @return The size.
size_t Machine_Gui_WidgetList_getSize(Machine_Gui_WidgetList* self);

/// @brief Get the widget at an index in this widget list.
/// @param self This widget list.
/// @param index The index.
/// @return The widget.
/// @error @a index is out of bounds.
Machine_Gui_Widget* Machine_Gui_WidgetList_getAt(Machine_Gui_WidgetList* self, size_t index);

/// @brief Append a widget to this widget list.
/// @param self This widget list.
/// @param widget The widget.
void Machine_Gui_WidgetList_append(Machine_Gui_WidgetList* self, Machine_Gui_Widget* widget);

/// @brief Translate the widgets.
/// @param self This list widgets.
/// @param t The translation vector.
static inline void Machine_Gui_WidgetList_translate(Machine_Gui_WidgetList* self,
                                                    Machine_Math_Vector2 const* t) {
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Machine_Gui_WidgetList_getAt(self, i);
    // @todo Add and utilize Machine_Gui_Widget_translate(Machine_Gui_Widget*, Machine_Math_Vector2
    // const*).
    Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, t);
    Machine_Gui_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Center the widgets horizontally around the given x-coordinate.
/// The y-positions of the widgets are not modified.
/// @param self This widget list.
/// @param x The x-coordinate.
static inline void Machine_Gui_WidgetList_centerColumn(Machine_Gui_WidgetList* self,
                                                       Ring2_Real32 x) {
  Machine_Math_Vector2* delta = Machine_Math_Vector2_create();
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Machine_Gui_WidgetList_getAt(self, i);
    Machine_Math_Rectangle2 const* bounds = Machine_Gui_Widget_getRectangle(widget);
    Ring2_Real32 cx = Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getCenter(bounds));
    Ring2_Real32 dx = x - cx;
    Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Machine_Math_Vector2_set(delta, dx, 0.f);
    Machine_Math_Vector2_add(newPosition, oldPosition, delta);
    Machine_Gui_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Center the widgets vertically around the given y-coordinate.
/// The x-positions of the widgets are not modified.
/// @param self This widget list.
/// @param y The y-coordinate.
static inline void Machine_Gui_WidgetList_centerRow(Machine_Gui_WidgetList* self, Ring2_Real32 y) {
  Machine_Math_Vector2* delta = Machine_Math_Vector2_create();
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
    Machine_Gui_Widget* widget = (Machine_Gui_Widget*)Machine_Gui_WidgetList_getAt(self, i);
    Machine_Math_Rectangle2 const* bounds = Machine_Gui_Widget_getRectangle(widget);
    Ring2_Real32 cy = Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getCenter(bounds));
    Ring2_Real32 dy = y - cy;
    Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Machine_Math_Vector2_set(delta, 0.f, dy);
    Machine_Math_Vector2_add(newPosition, oldPosition, delta);
    Machine_Gui_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Layout the widgets in a column with a distance of paddingy between each two widgets.
/// The first widget is located at y = 0. The x-positions of the widgets are not modified.
/// @param self Theis widget list.
/// @param paddingy The padding between two widgets.
static inline void Machine_Gui_WidgetList_layoutColumn(Machine_Gui_WidgetList* self,
                                                       Ring2_Real32 paddingy) {
  Ring2_Real32 y = 0.f;
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
    Machine_Gui_Widget* widget = Machine_Gui_WidgetList_getAt(self, i);
    Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
    Machine_Math_Vector2_set(newPosition, Machine_Math_Vector2_getX(oldPosition), y);
    Machine_Gui_Widget_setPosition(widget, newPosition);
    y += Machine_Math_Vector2_getY(Machine_Gui_Widget_getSize(widget)) + paddingy;
  }
}

/// @brief Layout the widgets according to the specified layout model.
/// @param self This widget list.
/// @param model The layout model.
static inline void Machine_Gui_WidgetList_layout(
    Machine_Gui_WidgetList* self, Ring2_Real32 parentWidth, Ring2_Real32 parentHeight,
    Ring2_Real32 canvasWidth, Ring2_Real32 canvasHeight, Machine_Gui_LayoutModel* model) {
  // Set the size of all elements to the same value: That value is the component-wise maxima vector
  // of the preferred sizes of all elements.
  Machine_Math_Vector2* preferredSize = Machine_Math_Vector2_clone(
      Machine_Gui_Widget_getPreferredSize(Machine_Gui_WidgetList_getAt(self, 0)));
  for (size_t i = 1, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
    // Machine_Gui_Widget_getHorizontalGrowth();
    // Machine_Gui_Widget_getVerticalGrowth();
    Machine_Math_Vector2_maxima(
        preferredSize, preferredSize,
        Machine_Gui_Widget_getPreferredSize(Machine_Gui_WidgetList_getAt(self, i)));
  }
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
    Machine_Gui_Widget_setSize(Machine_Gui_WidgetList_getAt(self, i), preferredSize);
  }

  switch (Machine_Gui_LayoutModel_getPrimaryDirection(model)) {
    case Machine_Gui_Layout_Direction_Column: {
      Ring2_Real32 y = 0.f;
      // Basically just lay them out consecutively.
      Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
      for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
        Machine_Gui_Widget* widget = Machine_Gui_WidgetList_getAt(self, i);
        Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Machine_Math_Vector2_set(newPosition, Machine_Math_Vector2_getX(oldPosition), y);
        Machine_Gui_Widget_setPosition(widget, newPosition);
        y += Machine_Math_Vector2_getY(Machine_Gui_Widget_getSize(widget))
             + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }
      Ring2_Real32 t = y - Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) {
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, 0.f, (parentHeight - t) * 0.5f);
        Machine_Gui_WidgetList_translate(self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, 0.f, (parentHeight - t));
        Machine_Gui_WidgetList_translate(self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the column.
      Machine_Gui_WidgetList_centerColumn(self, parentWidth * 0.5f);

    } break;
    case Machine_Gui_Layout_Direction_ColumnReverse: {
      Ring2_Real32 y = parentHeight;
      Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
      for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
        Machine_Gui_Widget* widget = Machine_Gui_WidgetList_getAt(self, i);
        y -= Machine_Math_Vector2_getY(Machine_Gui_Widget_getSize(widget));
        Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Machine_Math_Vector2_set(newPosition, Machine_Math_Vector2_getX(oldPosition), y);
        Machine_Gui_Widget_setPosition(widget, newPosition);
        y -= Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }

      Ring2_Real32 t = y + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) { /**/
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, 0.f, -t * 0.5f);
        Machine_Gui_WidgetList_translate(self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, 0.f, -t);
        Machine_Gui_WidgetList_translate(self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the column.
      Machine_Gui_WidgetList_centerColumn(self, parentWidth * 0.5f);

    } break;
    case Machine_Gui_Layout_Direction_Row: {
      Ring2_Real32 x = 0.f;
      Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
      for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
        Machine_Gui_Widget* widget = Machine_Gui_WidgetList_getAt(self, i);
        Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Machine_Math_Vector2_set(newPosition, x, Machine_Math_Vector2_getY(oldPosition));
        Machine_Gui_Widget_setPosition(widget, newPosition);
        x += Machine_Math_Vector2_getX(Machine_Gui_Widget_getSize(widget))
             + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }

      Ring2_Real32 t = x - Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) {
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, (parentWidth - t) * 0.5f, 0.f);
        Machine_Gui_WidgetList_translate(self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, (parentWidth - t), 0.f);
        Machine_Gui_WidgetList_translate(self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the row.
      Machine_Gui_WidgetList_centerRow(self, parentHeight * 0.5f);

    } break;
    case Machine_Gui_Layout_Direction_RowReverse: {
      Ring2_Real32 x = parentWidth;
      Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
      for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self); i < n; ++i) {
        Machine_Gui_Widget* widget = Machine_Gui_WidgetList_getAt(self, i);
        x -= Machine_Math_Vector2_getX(Machine_Gui_Widget_getSize(widget));
        Machine_Math_Vector2 const* oldPosition = Machine_Gui_Widget_getPosition(widget);
        Machine_Math_Vector2_set(newPosition, x, Machine_Math_Vector2_getY(oldPosition));
        Machine_Gui_Widget_setPosition(widget, newPosition);
        x -= Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      }

      Ring2_Real32 t = x + Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(model);
      if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
          == Machine_Gui_Layout_Justification_Start) { /**/
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_Center) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, -t * 0.5f, 0.f);
        Machine_Gui_WidgetList_translate(self, v);
      } else if (Machine_Gui_LayoutModel_getPrimaryJustification(model)
                 == Machine_Gui_Layout_Justification_End) {
        Machine_Math_Vector2* v = Machine_Math_Vector2_create();
        Machine_Math_Vector2_set(v, -t, 0.f);
        Machine_Gui_WidgetList_translate(self, v);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }

      // Center around the row.
      Machine_Gui_WidgetList_centerRow(self, parentHeight * 0.5f);

    } break;
    default: {
      MACHINE_ASSERT_UNREACHABLE();
    } break;
  };
}

#endif // MACHINE_GUI_WIDGETLIST_H_INCLUDED
