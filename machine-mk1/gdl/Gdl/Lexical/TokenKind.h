/// @file Gdl/Lexical/TokenKind.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_LEXICAL_TOKENKIND_H_INCLUDED)
#define MACHINE_GDL_LEXICAL_TOKENKIND_H_INCLUDED


#include "_Runtime.h"


typedef enum Machine_GDL_TokenKind Machine_GDL_TokenKind;

enum Machine_GDL_TokenKind {
  
  /// @brief "start of input".
  Machine_GDL_TokenKind_StartOfInput,
  
  /// @brief "end of input".
  Machine_GDL_TokenKind_EndOfInput,
  
  /// @brief "left parenthesis".
  Machine_GDL_TokenKind_LeftParenthesis,
  
  /// @brief "right parenthesis".
  Machine_GDL_TokenKind_RightParenthesis,
  
  /// @brief "period".
  Machine_GDL_TokenKind_Period,
  
  /// @brief "name".
  Machine_GDL_TokenKind_Name,
  
  /// @brief "semicolon".
  Machine_GDL_TokenKind_Semicolon,
  
  /// @brief "colon".
  Machine_GDL_TokenKind_Colon,

  /// @brief "comma".
  Machine_GDL_TokenKind_Comma,

  /// @brief "left curly bracket".
  Machine_GDL_TokenKind_LeftCurlyBracket,

  /// @brief "right curly bracket".
  Machine_GDL_TokenKind_RightCurlyBracket,

  /// @brief "left square bracket".
  Machine_GDL_TokenKind_LeftSquareBracket,

  /// @brief "right sqaure bracket".
  Machine_GDL_TokenKind_RightSquareBracket,

  /// @brief "string".
  Machine_GDL_TokenKind_String,

  /// @brief "integer".
  Machine_GDL_TokenKind_Integer,

  /// @brief "real".
  Machine_GDL_TokenKind_Real,

  Machine_GDL_TokenKind_Boolean,

  Machine_GDL_TokenKind_Void,

};


#endif // MACHINE_GDL_LEXICAL_TOKENKIND_H_INCLUDED
