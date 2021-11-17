/// @file Gui/Reader/Reader.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_READER_H_INCLUDE)
#define MACHINE_GUI_READER_H_INCLUDED



#include "Gui/Widget.h"



/// @brief 
/// <code>
/// widget :
///   border
///   group
///   textButton
///   textLabel
/// </code>
/// @param self A pointer to this GUI context.
/// @param source A pointer to the source map.
/// @return A pointer to the widget.
/// @todo Restruct visibility to "package".
Machine_GUI_Widget* Machine_GUI_Reader_readWidget(Machine_Gui_Context* self, Machine_Map const* source);



#endif // MACHINE_GUI_READER_H_INCLUDED
