/// @file Ring3/Gui/DefaultRenderContext.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_DEFAULTRENDERCONTEXT_H_INCLUDED)
#define RING3_GUI_DEFAULTRENDERCONTEXT_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/DefaultRenderContext.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/header.h.i"

/// @brief The default render context.
/// @extends Machine.Object
/// @implements Ring3.Gui.RenderContext
MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_DefaultRenderContext)

struct Ring3_Gui_DefaultRenderContext_Class {
  Machine_Object_Class __parent;
};

struct Ring3_Gui_DefaultRenderContext {
  Machine_Object __parent;
  /// @brief The underlaying 2D context.
  Ring3_Context2* context2;
};

/// @brief Create a default render context.
/// @param context2 The underlaying 2D context.
/// @return The GUI context.
Ring1_NoDiscardReturn() Ring3_Gui_DefaultRenderContext*
Ring3_Gui_DefaultRenderContext_create
  (
    Ring3_Context2* context2
  );

#endif // RING3_GUI_DEFAULTRENDERCONTEXT_H_INCLUDED
