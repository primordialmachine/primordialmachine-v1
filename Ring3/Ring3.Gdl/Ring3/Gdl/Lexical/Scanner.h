/// @file Gdl/Lexical/Scanner.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_SCANNER_H_INCLUDED)
#define RING3_GDL_LEXICAL_SCANNER_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/Scanner.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Lexical/TokenKind.h"
#include "Ring3/Gdl/Configuration.h"

/// @brief Retain delimiters of strings as part of the token text.
#define Ring3_Gdl_Scanner_retainStringDelimiters (1)

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Scanner)

struct Machine_Gdl_Scanner_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Scanner {
  Machine_Object __parent;

  Ring2_String* inputName;
  Ring2_ByteBuffer* inputBytes;
  /// @brief The end position.
  size_t endPos;
  /// @brief The current position.
  size_t currentPos;
  /// @brief The curren token.
  /// @default token type "start of input" with text "<start of input>" and offset 0.
  Machine_Gdl_TokenKind tokenKind;
  size_t tokenStart;
  Ring2_ByteBuffer* tokenText;
};

/// @brief Create a GDL scanner.
/// @param inputName The name of the input.
/// @param inputBytes The Bytes of the input.
/// @return A pointer to the GDL scanner.
/// @post The GDL scanner is in its initial state w.r.t. the specified input.
Ring1_NoDiscardReturn() Machine_Gdl_Scanner*
Machine_Gdl_Scanner_create
  (
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  );

/// @brief Set the input for this GDL scanner.
/// @param self This GDL scanner.
/// @param inputName The name of the input.
/// @param inputBytes The Bytes of the input.
/// @post The GDL scanner is in its initial state w.r.t. the specified input.
void
Machine_Gdl_Scanner_setInput
  (
    Machine_Gdl_Scanner* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  );

/// @brief Compute the next token.
/// @param self This scanner.
void
Machine_Gdl_Scanner_step
  (
    Machine_Gdl_Scanner* self
  );

/// @brief Get the token kind of the current token.
/// @param self This scanner.
/// @return The token kind of the current token.
Ring1_NoDiscardReturn() Machine_Gdl_TokenKind
Machine_Gdl_Scanner_getTokenKind
  (
    Machine_Gdl_Scanner const* self
  );

/// @brief Get the token text of the current token.
/// @param self This scanner.
/// @return The token text of the current token.
Ring1_NoDiscardReturn() Ring2_String*
Machine_Gdl_Scanner_getTokenText
  (
    Machine_Gdl_Scanner const* self
  );

#endif // RING3_GDL_LEXICAL_SCANNER_H_INCLUDED
