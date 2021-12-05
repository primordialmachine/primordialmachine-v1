/// @file Gdl/Lexical/Token.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_LEXICAL_TOKEN_H_INCLUDED)
#define MACHINE_GDL_LEXICAL_TOKEN_H_INCLUDED


#include "Gdl/Lexical/TokenKind.h"


MACHINE_DECLARE_CLASSTYPE(Machine_GDL_Token)

struct Machine_GDL_Token_Class {
  Machine_Object_Class __parent;
};

struct Machine_GDL_Token {
  Machine_Object __parent;

  Machine_GDL_TokenKind kind;
  Machine_String* text;
  Machine_Integer offset;
};

Machine_GDL_Token* Machine_GDL_Token_create(Machine_GDL_TokenKind, Machine_String* text, Machine_Integer offset);

Machine_GDL_TokenKind Machine_GDL_Token_getKind(const Machine_GDL_Token* self);

Machine_String* Machine_GDL_Token_getText(const Machine_GDL_Token* self);


#endif // MACHINE_GDL_LEXICAL_TOKEN_H_INCLUDED
