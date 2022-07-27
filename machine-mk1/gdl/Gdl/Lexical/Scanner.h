/// @file Gdl/Lexical/Scanner.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_LEXICAL_SCANNER_H_INCLUDED)
#define MACHINE_GDL_LEXICAL_SCANNER_H_INCLUDED

#include "Gdl/Context.h"
#include "Gdl/Lexical/Token.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Scanner)

struct Machine_Gdl_Scanner_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Scanner {
  Machine_Object __parent;

  Ring2_String* inputName;
  Machine_ByteBuffer* inputBytes;
  /// @brief The end position.
  size_t endPos;
  /// @brief The current position.
  size_t currentPos;
  /// @brief The curren token.
  /// @default token type "start of input" with text "<start of input>" and offset 0.
  Machine_Gdl_TokenKind tokenKind;
  size_t tokenStart;
  Machine_ByteBuffer* tokenText;
};

Machine_Gdl_Scanner* Machine_Gdl_Scanner_create(Ring2_String* inputName,
                                                Machine_ByteBuffer* inputBytes);

void Machine_Gdl_Scanner_setInput(Machine_Gdl_Scanner* self, Ring2_String* inputName,
                                  Machine_ByteBuffer* inputBytes);

/// @brief Compute the next token.
/// @param self This scanner.
void Machine_Gdl_Scanner_step(Machine_Gdl_Scanner* self);

/// @brief Get the token kind of the current token.
/// @param self This scanner.
/// @return The token kind of the current token.
Machine_Gdl_TokenKind Machine_Gdl_Scanner_getTokenKind(Machine_Gdl_Scanner const* self);

/// @brief Get the token text of the current token.
/// @param self This scanner.
/// @return The token text of the current token.
Ring2_String* Machine_Gdl_Scanner_getTokenText(Machine_Gdl_Scanner const* self);

#endif // MACHINE_GDL_LEXICAL_SCANNER_H_INCLUDED
