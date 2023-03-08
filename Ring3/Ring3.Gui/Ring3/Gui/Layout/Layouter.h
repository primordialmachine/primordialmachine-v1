#if !defined(RING3_GUI_LAYOUT_LAYOUTER_H_INCLUDED)
#define RING3_GUI_LAYOUT_LAYOUTER_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Layout/Layouter.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
typedef struct Ring3_Gui_WidgetList Ring3_Gui_WidgetList;
typedef struct Machine_Gui_LayoutModel Machine_Gui_LayoutModel;

/// @brief Layout the widgets in a column with a distance of paddingy between each two widgets.
/// The first widget start is located at the start of the axis if the axis is left to right.
/// The first widget end is located at the start of the axis if the axis is right to left.
/// The x-positions of the widgets are not modified.
/// @param self This widget list.
/// @param reverse The axis start and end points are reversed.
/// @param interChildSpacingY The spacing between to consecutive children.
/// @return The coordinate of the end of the last widget on the axis.
Ring2_Real32
Ring3_Gui_WidgetList_layoutColumn
  (
    Ring3_Gui_WidgetList* self,
    bool reverse,
    Ring2_Real32 interChildSpacingY,
    Ring2_Real32 columnSizeY
  );

/// @brief Layout the widgets in a column with a distance of paddingy between each two widgets.
/// The first widget start is located at the start of the axis if the axis is left to right.
/// The first widget end is located at the start of the axis if the axis is right to left.
/// The y-positions of the widgets are not modified.
/// @param self This widget list.
/// @param revese The axis start and end points are reversed.
/// @param interChildSpacingX The spacing between to consecutive children.
/// @return The coordinate of the end of the last widget on the axis.
Ring2_Real32
Ring3_Gui_WidgetList_layoutRow
  (
    Ring3_Gui_WidgetList* self,
    bool reverse,
    Ring2_Real32 interChildSpacingX,
    Ring2_Real32 columnSizeX
  );

/// @brief Layout the widgets according to the specified layout model.
/// @param self This widget list.
/// @param model The layout model.
void
Ring3_Gui_WidgetList_layout
  (
    Ring3_Gui_WidgetList* self,
    Ring2_Real32 parentWidth,
    Ring2_Real32 parentHeight,
    Machine_Gui_LayoutModel* model
  );

#endif // RING3_GUI_LAYOUT_LAYOUTER_H_INCLUDED
