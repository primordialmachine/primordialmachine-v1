/// @file Ring3/Gui/Reader/Reader.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_READER_H_INCLUDE)
#define MACHINE_GUI_READER_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Gui/Reader/Reader.h` directly, include `_Gui.h` instead.")
#endif
#include "Ring3/Gui/WidgetBase.h"

/// @brief
/// <code>
/// widget :
///   border
///   group
///   text
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
/// @todo Restruct visibility to "package".
Ring1_NoDiscardReturn() Ring3_Gui_Widget*
Machine_Gui_Reader_readWidget
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source
  );

#endif // MACHINE_GUI_READER_H_INCLUDED
