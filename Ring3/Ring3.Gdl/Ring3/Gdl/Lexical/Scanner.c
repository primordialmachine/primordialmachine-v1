/// @file Ring3/Gdl/Lexical/Scanner.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Lexical/Scanner.h"
#undef RING3_GDL_PRIVATE

MACHINE_DEFINE_INTERFACETYPE(Ring3_Gdl_Scanner, NULL)

void
Ring3_Gdl_Scanner_setInput
  (
    Ring3_Gdl_Scanner* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gdl_Scanner, setInput, , self, inputName, inputBytes); }

void
Ring3_Gdl_Scanner_step
  (
    Ring3_Gdl_Scanner* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gdl_Scanner, step, , self); }

Ring1_NoDiscardReturn() Ring3_Gdl_Token*
Ring3_Gdl_Scanner_getToken
  (
    Ring3_Gdl_Scanner const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gdl_Scanner, getToken, return, self); }
