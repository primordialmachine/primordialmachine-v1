#if !defined(MACHINE_GUI_WIDGETLIST_H_INCLUDED)
#define MACHINE_GUI_WIDGETLIST_H_INCLUDED

#include "./../GUI/Widget.h"

/// @brief A label to display a text.
/// @remarks The preferred size of a panel is computed by combining the rectangles of its child nodes.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_WidgetList)

/// @brief Create an empty panel.
/// @return The panel.
Machine_GUI_WidgetList* Machine_GUI_WidgetList_create();

/// @brief Get the size of this widget list.
/// @param self This widget list.
/// @return The size.
size_t Machine_GUI_WidgetList_getSize(Machine_GUI_WidgetList* self);

/// @brief Get the widget at an index in this widget list.
/// @param self This widget list.
/// @param index The index.
/// @return The widget.
/// @error @a index is out of bounds.
Machine_GUI_Widget* Machine_GUI_WidgetList_getAt(Machine_GUI_WidgetList* self, size_t index);

/// @brief Append a widget to this widget list.
/// @param self This widget list.
/// @param widget The widget.
void Machine_GUI_WidgetList_append(Machine_GUI_WidgetList* self, Machine_GUI_Widget* widget);

/// @brief Translate the widgets.
/// @param self This list widgets.
/// @param t The translation vector.
static inline void Machine_GUI_WidgetList_translate(Machine_GUI_WidgetList* self, const Machine_Math_Vector2* t) {
  for (size_t i = 0, n = Machine_GUI_WidgetList_getSize(self); i < n; ++i) {
    Machine_GUI_Widget* widget = (Machine_GUI_Widget*)Machine_GUI_WidgetList_getAt(self, i);
    // @todo Add and utilize Machine_GUI_Widget_translate(Machine_GUI_Widget*, const Machine_Math_Vector2 *).
    const Machine_Math_Vector2* oldPosition = Machine_GUI_Widget_getPosition(widget);
    Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, t);
    Machine_GUI_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Center the widgets vertically around the given x-coordinate.
/// The y-positions of the widgets are not modified.
/// @param self This widget list.
/// @param paddingy The x-coordinate.
static inline void Machine_GUI_WidgetList_centerVertically(Machine_GUI_WidgetList *self, float x) {
  Machine_Math_Vector2* delta = Machine_Math_Vector2_create();
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
  for (size_t i = 0, n = Machine_GUI_WidgetList_getSize(self); i < n; ++i) {
    Machine_GUI_Widget* widget = (Machine_GUI_Widget*)Machine_GUI_WidgetList_getAt(self, i);
    const Machine_Math_Rectangle2* bounds = Machine_GUI_Widget_getRectangle(widget);
    float cx = Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getCenter(bounds));
    float dx = x - cx;
    const Machine_Math_Vector2* oldPosition = Machine_GUI_Widget_getPosition(widget);
    Machine_Math_Vector2_set(delta, dx, 0.f);
    Machine_Math_Vector2_add(newPosition, oldPosition, delta);
    Machine_GUI_Widget_setPosition(widget, newPosition);
  }
}

/// @brief Layout the widgets in a column with a distance of paddingy between each two widgets.
/// The first widget is located at y = 0. The x-positions of the widgets are not modified.
/// @param self Theis widget list.
/// @param paddingy The padding between two widgets.
static inline void Machine_GUI_WidgetList_layoutColumn(Machine_GUI_WidgetList* self, float paddingy) {
  float y = 0.f;
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_create();
  for (size_t i = 0, n = Machine_GUI_WidgetList_getSize(self); i < n; ++i) {
    Machine_GUI_Widget* widget = Machine_GUI_WidgetList_getAt(self, i);
    const Machine_Math_Vector2* oldPosition = Machine_GUI_Widget_getPosition(widget);
    Machine_Math_Vector2_set(newPosition, Machine_Math_Vector2_getX(oldPosition), y);
    Machine_GUI_Widget_setPosition(widget, newPosition);
    y += Machine_Math_Vector2_getY(Machine_GUI_Widget_getSize(widget)) + paddingy;
  }
}

#endif // MACHINE_GUI_WIDGETLIST_H_INCLUDED
