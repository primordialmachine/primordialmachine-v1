/// @file Ring3/Gdl/Lexical/DefaultScanner.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_DEFAULTSCANNER_H_INCLUDED)
#define RING3_GDL_LEXICAL_DEFAULTSCANNER_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/DefaultScanner.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Lexical/TokenKind.h"
#include "Ring3/Gdl/Configuration.h"
#include "Ring3/Gdl/Lexical/Token.h"

/// @brief Retain delimiters of strings as part of the token text.
#define Ring3_Gdl_Scanner_retainStringDelimiters (1)

/// @brief The default implementation of a GDL scanner.
/// @implements Ring3.Gdl.Scanner
MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_DefaultScanner)

struct Ring3_Gdl_DefaultScanner_Class {
  Machine_Object_Class __parent;
};

struct Ring3_Gdl_DefaultScanner {
  Machine_Object __parent;
  /// @brief Hash map to map a lexeme to a token type.
  Ring2_Collections_Map* keywords;
  struct {
    /// @brief The bytes of the input.
    Ring2_ByteBuffer* bytes;
    /// @brief The name of the input.
    Ring2_String* name;
    /// @brief The start position of the input.
    int64_t start;
    /// @brief The end position of the input.
    int64_t end;
  } input;
  /// @brief The current position in the input.
  int64_t current;
  /// @brief The literal buffer.
  Ring2_ByteBuffer* lexemeBuffer;
  /// @brief The current token.
  Ring3_Gdl_Token* token;
};

/// @brief Create a GDL scanner.
/// @param inputName The name of the input.
/// @param inputBytes The Bytes of the input.
/// @return A pointer to the GDL scanner.
/// @post The GDL scanner is in its initial state w.r.t. the specified input.
Ring1_NoDiscardReturn() Ring3_Gdl_DefaultScanner*
Ring3_Gdl_DefaultScanner_create
  (
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  );

#endif // RING3_GDL_LEXICAL_DEFAULTSCANNER_H_INCLUDED
