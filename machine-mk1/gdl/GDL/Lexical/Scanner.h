/// @file Gdl/Lexical/Scanner.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_LEXICAL_SCANNER_H_INCLUDED)
#define MACHINE_GDL_LEXICAL_SCANNER_H_INCLUDED


#include "Gdl/Lexical/Token.h"
#include "Gdl/Context.h"


MACHINE_DECLARE_CLASSTYPE(Machine_GDL_Scanner)

struct Machine_GDL_Scanner_Class {
  Machine_Object_Class __parent;
};

struct Machine_GDL_Scanner {
  Machine_Object __parent;

  Machine_String* inputName;
  Machine_ByteBuffer* inputBytes;
  /// @brief The end position.
  size_t endPos;
  /// @brief The current position.
  size_t currentPos;
  /// @brief The curren token.
  /// @default token type "start of input" with text "<start of input>" and offset 0.
  Machine_GDL_TokenKind tokenKind;
  size_t tokenStart;
  Machine_ByteBuffer* tokenText;
};

Machine_GDL_Scanner* Machine_GDL_Scanner_create(Machine_String *inputName, Machine_ByteBuffer* inputBytes);

void Machine_GDL_Scanner_setInput(Machine_GDL_Scanner* self, Machine_String* inputName, Machine_ByteBuffer* inputBytes);

/// @brief Compute the next token.
/// @param self This scanner.
void Machine_GDL_Scanner_step(Machine_GDL_Scanner* self);

/// @brief Get the token kind of the current token.
/// @param self This scanner.
/// @return The token kind of the current token.
Machine_GDL_TokenKind Machine_GDL_Scanner_getTokenKind(const Machine_GDL_Scanner* self);

/// @brief Get the token text of the current token.
/// @param self This scanner.
/// @return The token text of the current token.
Machine_String* Machine_GDL_Scanner_getTokenText(const Machine_GDL_Scanner * self);


#endif // MACHINE_GDL_LEXICAL_SCANNER_H_INCLUDED
