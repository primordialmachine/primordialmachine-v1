/// @file Ring3/Gui/Reader/Reader.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Reader/Reader.h"
#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/Reader/Reader.package.h"
#undef RING3_GUI_PRIVATE


Ring1_NoDiscardReturn() Machine_Gui_Widget*
Machine_Gui_Reader_readWidget
  (
    Machine_Gui_Context* self,
    Ring2_Collections_Map const* source
  )
{
  Ring2_String* s = NULL;
  Ring3_Gui_Gdl_Context* guiGdlContext = self->gdlContext;
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
