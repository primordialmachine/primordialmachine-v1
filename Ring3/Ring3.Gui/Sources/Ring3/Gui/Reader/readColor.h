/// @file Ring3/Gui/Reader/readColor.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_READER_READCOLOR_H_INCLUDED)
#define RING3_GUI_READER_READCOLOR_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Reader/readColor.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Math/_Include.h"
#include "Ring3/Gui/Context.h"

/// @brief Read a <code>Gdl.Color</code> value.
/// @param self A pointer to this GDL context.
/// @param name A pointer to the name of the source in the map.
/// @param source A pointer to the source map.
/// @return The <code>Gdl.Color</code> value.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Gui_Gdl_Reader_readColor
  (
    Machine_Gui_Context* self,
    Ring2_String* name,
    Ring2_Collections_Map const* source
  );

#endif // RING3_GUI_READER_READCOLOR_H_INCLUDED
