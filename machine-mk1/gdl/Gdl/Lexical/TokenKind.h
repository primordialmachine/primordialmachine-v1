/// @file Gdl/Lexical/TokenKind.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_LEXICAL_TOKENKIND_H_INCLUDED)
#define MACHINE_GDL_LEXICAL_TOKENKIND_H_INCLUDED

#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_Gdl_TokenKind)

enum Machine_Gdl_TokenKind {

  /// @brief "start of input".
  Machine_Gdl_TokenKind_StartOfInput,

  /// @brief "end of input".
  Machine_Gdl_TokenKind_EndOfInput,

  /// @brief "left parenthesis".
  Machine_Gdl_TokenKind_LeftParenthesis,

  /// @brief "right parenthesis".
  Machine_Gdl_TokenKind_RightParenthesis,

  /// @brief "period".
  Machine_Gdl_TokenKind_Period,

  /// @brief "name".
  Machine_Gdl_TokenKind_Name,

  /// @brief "semicolon".
  Machine_Gdl_TokenKind_Semicolon,

  /// @brief "colon".
  Machine_Gdl_TokenKind_Colon,

  /// @brief "comma".
  Machine_Gdl_TokenKind_Comma,

  /// @brief "left curly bracket".
  Machine_Gdl_TokenKind_LeftCurlyBracket,

  /// @brief "right curly bracket".
  Machine_Gdl_TokenKind_RightCurlyBracket,

  /// @brief "left square bracket".
  Machine_Gdl_TokenKind_LeftSquareBracket,

  /// @brief "right sqaure bracket".
  Machine_Gdl_TokenKind_RightSquareBracket,

  /// @brief "string".
  Machine_Gdl_TokenKind_String,

  /// @brief "integer".
  Machine_Gdl_TokenKind_Integer,

  /// @brief "real".
  Machine_Gdl_TokenKind_Real,

  Machine_Gdl_TokenKind_Boolean,

  Machine_Gdl_TokenKind_Void,

};

#endif // MACHINE_GDL_LEXICAL_TOKENKIND_H_INCLUDED
