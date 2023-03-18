/// @file Ring3/Gdl/Test/ParseTest1.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring3/Gdl/Test/ParseTest1.h"
#include "Ring3/Gdl/_Include.h"

#define CHECK(EXPECTED_TOKEN_KIND) \
  if ((Machine_Gdl_Scanner_getTokenKind(scanner) != (EXPECTED_TOKEN_KIND))) \
  { \
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "expected token kind\n"); \
    Ring1_Status_set(Ring1_Status_InvalidLexics); \
    Ring2_jump(); \
  }

static void
test1
  (
    Ring2_Context * ctx,
    Ring2_Value * result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_ByteBuffer* inputText = Ring2_ByteBuffer_create();
  Ring2_ByteBuffer_appendBytes(inputText, "", crt_strlen(""));
  Machine_Gdl_Scanner* scanner = Machine_Gdl_Scanner_create(Ring2_String_fromC(false, ""), inputText);
  CHECK(Machine_Gdl_TokenKind_StartOfInput);
  Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_EndOfInput);
  Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_EndOfInput);
}

static void
test2
  (
    Ring2_Context* ctx,
    Ring2_Value* result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_ByteBuffer *inputText = Ring2_ByteBuffer_create();
  Ring2_ByteBuffer_appendBytes(inputText, "{:true,false.void;}", crt_strlen("{:true,false.void;}"));
  Machine_Gdl_Scanner* scanner = Machine_Gdl_Scanner_create(Ring2_String_fromC(false, ""), inputText);

  CHECK(Machine_Gdl_TokenKind_StartOfInput); Machine_Gdl_Scanner_step(scanner);

  CHECK(Machine_Gdl_TokenKind_LeftCurlyBracket); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Colon); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Boolean); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Comma); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Boolean); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Period); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Void); Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_Semicolon); Machine_Gdl_Scanner_step(scanner);

  CHECK(Machine_Gdl_TokenKind_RightCurlyBracket); Machine_Gdl_Scanner_step(scanner);

  CHECK(Machine_Gdl_TokenKind_EndOfInput);   Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_EndOfInput);
}

void
Ring3_Gdl_Test_registerParseTest1
  (
    Ring2_Tests* tests
  )
{
  Ring2_String* prefix = Ring2_String_fromC(false, "Ring3.Gdl.Test.ParseTest");
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, "1")),
                      &test1);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, "2")),
                      &test2);
}
