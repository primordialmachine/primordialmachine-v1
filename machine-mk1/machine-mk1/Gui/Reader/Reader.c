/// @file Gui/Reader/Reader.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/Reader/Reader.h"



#include "Gui/Context.h"
#include "Gui/Reader/Reader.package.h"



Machine_GUI_Widget* Machine_GUI_Reader_readWidget(Machine_Gui_Context* self,  Machine_Map const* source) {
  Machine_String* s = NULL;
  Machine_Gui_Gdl_Context* guiGdlContext = self->gdlContext;
  if (!Machine_GUI_Reader_hasString(self, source, guiGdlContext->KIND)) {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
  s = Machine_GUI_Reader_getString(source, guiGdlContext->KIND);
  if (Machine_String_isEqualTo(s, guiGdlContext->GROUP)) {
    return (Machine_GUI_Widget*)Machine_GUI_Reader_readGroup(self, source);
  }
  else if (Machine_String_isEqualTo(s, guiGdlContext->TEXTBUTTON)) {
    return (Machine_GUI_Widget*)Machine_GUI_Reader_readTextButton(self, source);
  }
  else if (Machine_String_isEqualTo(s, guiGdlContext->TEXTLABEL)) {
    return (Machine_GUI_Widget*)Machine_GUI_Reader_readTextLabel(self, source);
  }
  else if (Machine_String_isEqualTo(s, guiGdlContext->BORDER)) {
    return (Machine_GUI_Widget*)Machine_GUI_Reader_readBorder(self, source);
  }
  else {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
}
