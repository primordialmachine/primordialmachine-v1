/// @file Gui/Reader/Reader.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Reader/Reader.h"

#include "Gui/Context.h"
#include "Gui/Reader/Reader.package.h"

Machine_Gui_Widget* Machine_Gui_Reader_readWidget(Machine_Gui_Context* self,
                                                  Ring2_Collections_Map const* source) {
  Ring2_String* s = NULL;
  Machine_Gui_Gdl_Context* guiGdlContext = self->gdlContext;
  if (!Machine_Gui_Reader_hasString(self, source, guiGdlContext->KIND)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  s = Machine_Gui_Reader_getString(source, guiGdlContext->KIND);
  if (Ring2_String_isEqualTo(Ring2_Context_get(), s, guiGdlContext->GROUPNODEKIND)) {
    return (Machine_Gui_Widget*)Machine_Gui_Reader_readGroupNode(self, source);
  } else if (Ring2_String_isEqualTo(Ring2_Context_get(), s, guiGdlContext->TEXTNODEKIND)) {
    return (Machine_Gui_Widget*)Machine_Gui_Reader_readTextNode(self, source);
  } else if (Ring2_String_isEqualTo(Ring2_Context_get(), s, guiGdlContext->BORDERNODEKIND)) {
    return (Machine_Gui_Widget*)Machine_Gui_Reader_readBorderNode(self, source);
  } else {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
}
