/// @file Gui/Reader/Reader.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_READER_H_INCLUDE)
#define MACHINE_GUI_READER_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include `Gui/Reader/Reader.h` directly, include `_Gui.h` instead.")
#endif
#include "Gui/Widget.h"

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
Machine_Gui_Widget* Machine_Gui_Reader_readWidget(Machine_Gui_Context* self,
                                                  Ring2_Collections_Map const* source);

#endif // MACHINE_GUI_READER_H_INCLUDED
