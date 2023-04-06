/// @file Ring3/Gdl/Lexical/Token.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_TOKEN_H_INCLUDED)
#define RING3_GDL_LEXICAL_TOKEN_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/Token.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Lexical/TokenKind.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_Token)

struct Ring3_Gdl_Token_Class {
  Machine_Object_Class __parent;
};

struct Ring3_Gdl_Token {
  Machine_Object __parent;

  Ring3_Gdl_TokenKind kind;
  Ring2_String* text;
  Ring2_Integer start;
  Ring2_Integer end;
};

Ring1_NoDiscardReturn() Ring3_Gdl_Token*
Ring3_Gdl_Token_create
  (
    Ring3_Gdl_TokenKind,
    Ring2_String* text,
    Ring2_Integer start,
    Ring2_Integer end
  );

/// @brief Get the kind of this token.
/// @param self This token.
/// @return The kind of this token.
Ring1_NoDiscardReturn() Ring3_Gdl_TokenKind
Ring3_Gdl_Token_getKind
  (
    Ring3_Gdl_Token const* self
  );

/// @brief Get the text of this token.
/// @param self This token.
/// @return The text of this token.
Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_Token_getText
  (
    Ring3_Gdl_Token const* self
  );

/// @brief Get the start position of this token.
/// @param self This token.
/// @return The start position of this token.
Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_Token_getStart
  (
    Ring3_Gdl_Token const* self
  );

/// @brief Get the end position of this token.
/// @param self This token.
/// @return The end position of this token.
Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_Token_getEnd
  (
    Ring3_Gdl_Token const* self
  );

#endif // RING3_GDL_LEXICAL_TOKEN_H_INCLUDED
