/// @file Gdl/Lexical/TokenKind.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED)
#define RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/TokenKind.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

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

#endif // RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED
