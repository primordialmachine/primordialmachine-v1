/// @file Gdl/Lexical/Token.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_TOKEN_H_INCLUDED)
#define RING3_GDL_LEXICAL_TOKEN_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/Token.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Lexical/TokenKind.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Token)

struct Machine_Gdl_Token_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Token {
  Machine_Object __parent;

  Machine_Gdl_TokenKind kind;
  Ring2_String* text;
  Ring2_Integer offset;
};

Machine_Gdl_Token*
Machine_Gdl_Token_create
  (
    Machine_Gdl_TokenKind,
    Ring2_String* text,
    Ring2_Integer offset
  );

Machine_Gdl_TokenKind
Machine_Gdl_Token_getKind
  (
    Machine_Gdl_Token const* self
  );

Ring2_String*
Machine_Gdl_Token_getText
  (
    Machine_Gdl_Token const* self
  );

#endif // RING3_GDL_LEXICAL_TOKEN_H_INCLUDED
