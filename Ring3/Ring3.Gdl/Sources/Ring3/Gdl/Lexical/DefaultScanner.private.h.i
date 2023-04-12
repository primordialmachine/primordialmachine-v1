/// @file Ring3/Gdl/Lexical/Scanner.private.h.i
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_DEFAULTSCANNER_PRIVATE_H_INCLUDED)
#define RING3_GDL_LEXICAL_DEFAULTSCANNER_PRIVATE_H_INCLUDED

#include "Ring3/Gdl/Lexical/DefaultScanner.h"

#define Machine_Gdl_DefaultScanner_withPeriod (1)

#define Machine_Gdl_DefaultScanner_withSemicolon (1)

#define Symbol_StartOfInput (255+1)

#define Symbol_EndOfInput (255+2)

/// @{

static void
write
  (
    Ring3_Gdl_DefaultScanner const* self,
    int symbol
  );

static void
save
  (
    Ring3_Gdl_DefaultScanner const* self
  );

static void
next
  (
    Ring3_Gdl_DefaultScanner* self
  );

static void
saveAndNext
  (
    Ring3_Gdl_DefaultScanner* self
  );

static void
writeAndNext
  (
    Ring3_Gdl_DefaultScanner* self,
    int symbol
  );

static int
current
  (
    Ring3_Gdl_DefaultScanner const* self
  );

static bool
is
  (
    Ring3_Gdl_DefaultScanner const* self,
    int expectedSymbol
  );

static bool
isDigit
  (
    Ring3_Gdl_DefaultScanner const* self
  );

static bool
isWhitespace
  (
    Ring3_Gdl_DefaultScanner const* self
  );

static bool
isNewline
  (
    Ring3_Gdl_DefaultScanner const* self
  );

static bool
isAlphabetic
  (
    Ring3_Gdl_DefaultScanner const* self
  );

/// @}

/// @{

/// <code>plusMinus? digit+</code>
static void
scanExponent
  (
    Ring3_Gdl_DefaultScanner* self
  );

static void
scanSingleQuotedString
  (
    Ring3_Gdl_DefaultScanner* self
  );

static void
scanDoubleQuotedString
  (
    Ring3_Gdl_DefaultScanner* self
  );

/// @}

/// @{

static void
stepImpl
  (
    Ring3_Gdl_DefaultScanner* self
  );

static Ring1_NoDiscardReturn() Ring3_Gdl_Token*
getTokenImpl
  (
    Ring3_Gdl_DefaultScanner const* self
  );

static void
setInputImpl
  (
    Ring3_Gdl_DefaultScanner* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  );

/// @}

static Ring1_NoDiscardReturn() Ring2_Collections_Map*
makeKeywords
  (
  );

static Ring1_NoDiscardReturn() Ring2_String*
makeText
  (
    Ring3_Gdl_DefaultScanner* self
  );

#endif // RING3_GDL_LEXICAL_DEFAULTSCANNER_PRIVATE_H_INCLUDED
