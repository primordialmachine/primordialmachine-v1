/// @file Gdl/Lexical/Token.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_LEXICAL_TOKEN_H_INCLUDED)
#define MACHINE_GDL_LEXICAL_TOKEN_H_INCLUDED

#include "Gdl/Lexical/TokenKind.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Token)

struct Machine_Gdl_Token_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Token {
  Machine_Object __parent;

  Machine_Gdl_TokenKind kind;
  Machine_String* text;
  Machine_Integer offset;
};

Machine_Gdl_Token* Machine_Gdl_Token_create(Machine_Gdl_TokenKind, Machine_String* text,
                                            Machine_Integer offset);

Machine_Gdl_TokenKind Machine_Gdl_Token_getKind(Machine_Gdl_Token const* self);

Machine_String* Machine_Gdl_Token_getText(Machine_Gdl_Token const* self);

#endif // MACHINE_GDL_LEXICAL_TOKEN_H_INCLUDED
