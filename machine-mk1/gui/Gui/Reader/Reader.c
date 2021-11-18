/// @file Gui/Reader/Reader.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/Reader/Reader.h"



#include "Gui/Context.h"
#include "Gui/Reader/Reader.package.h"



Machine_Gui_Widget* Machine_Gui_Reader_readWidget(Machine_Gui_Context* self,  Machine_Map const* source) {
  Machine_String* s = NULL;
  Machine_Gui_Gdl_Context* guiGdlContext = self->gdlContext;
  if (!Machine_Gui_Reader_hasString(self, source, guiGdlContext->KIND)) {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
  s = Machine_Gui_Reader_getString(source, guiGdlContext->KIND);
  if (Machine_String_isEqualTo(s, guiGdlContext->GROUPNODEKIND)) {
    return (Machine_Gui_Widget*)Machine_Gui_Reader_readGroupNode(self, source);
  }
  else if (Machine_String_isEqualTo(s, guiGdlContext->TEXTNODEKIND)) {
    return (Machine_Gui_Widget*)Machine_Gui_Reader_readTextNode(self, source);
  }
  else if (Machine_String_isEqualTo(s, guiGdlContext->BORDERNODEKIND)) {
    return (Machine_Gui_Widget*)Machine_Gui_Reader_readBorderNode(self, source);
  }
  else {
    Machine_setStatus(Machine_Status_SemanticalError);
    Machine_jump();
  }
}
