/// @file Ring3/Gui/WidgetBase.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_WIDGETBASE_H_INCLUDED)
#define RING3_GUI_WIDGETBASE_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/WidgetBase.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Signals/_Include.h"
#include "Ring3/Gui/Widget.h"
typedef struct Ring3_Gui_RenderContext Ring3_Gui_RenderContext;
typedef struct Machine_Gui_Context Machine_Gui_Context;

/// @brief Base of all widgets.
MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_WidgetBase)

struct Ring3_Gui_WidgetBase_Class {
  Machine_Object_Class __parent;
};

struct Ring3_Gui_WidgetBase {
  Machine_Object __parent;

  /// @brief Pointer to the name of the widget or the null pointer.
  Ring2_String* name;
  /// @brief The context this widget belongs to.
  Machine_Gui_Context* context;
  /// @brief Rectangle in canvas coordinate sof the parent.
  Ring3_Math_Rectangle2* rectangle;
  Ring3_Gui_Widget* parent;

  Machine_Signals_Signal* signal;
};

/// @brief Construct this widget.
/// @param self This widget.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void
Ring3_Gui_WidgetBase_construct
  (
    Ring3_Gui_WidgetBase* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Emit a <code>"position changed", this</code> signal.
void
Ring3_Gui_WidgetBase_emitPositionChangedSignal
  (
    Ring3_Gui_WidgetBase* self
  );

/// @brief Emit a <code>"size changed", this</code> signal.
void
Ring3_Gui_WidgetBase_emitSizeChangedSignal
  (
    Ring3_Gui_WidgetBase* self
  );

/// @brief Emit a <code>&lt;propertyName changed&gt; this</code> signal.
void
Ring3_Gui_WidgetBase_emitPropertyChanged
  (
    Ring3_Gui_WidgetBase* self,
    Ring2_String* propertyName
  );

#endif // RING3_GUI_WIDGETBASE_H_INCLUDED
