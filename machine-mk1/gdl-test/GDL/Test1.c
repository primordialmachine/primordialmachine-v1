#include "Gdl/Test1.h"
#include "_GDL.h"
#include <string.h>

#define CHECK(EXPECTED_TOKEN_KIND) \
  if ((Machine_Gdl_Scanner_getTokenKind(scanner) != (EXPECTED_TOKEN_KIND))) \
  { \
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "expected token kind\n"); \
    Ring1_Status_set(Ring1_Status_InvalidLexics); \
    Ring2_jump(); \
  }

static void test_1_1() {
  Machine_ByteBuffer* inputText = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(inputText, "", strlen(""));
  Machine_Gdl_Scanner* scanner = Machine_Gdl_Scanner_create(Ring2_String_create(Ring2_Context_get(), "", strlen("")), inputText);
  CHECK(Machine_Gdl_TokenKind_StartOfInput);
  Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_EndOfInput);
  Machine_Gdl_Scanner_step(scanner);
  CHECK(Machine_Gdl_TokenKind_EndOfInput);
}

static void test_1_2() {
  Machine_ByteBuffer *inputText = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(inputText, "{:true,false.void;}", strlen("{:true,false.void;}"));
  Machine_Gdl_Scanner* scanner = Machine_Gdl_Scanner_create(Ring2_String_create(Ring2_Context_get(), "", strlen("")), inputText);

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

void Machine_Gdl_test1() {
  test_1_1();
  test_1_2();
}
