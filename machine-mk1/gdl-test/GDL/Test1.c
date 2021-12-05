#include "Gdl/Test1.h"
#include "_GDL.h"
#include <string.h>

#define CHECK(EXPECTED_TOKEN_KIND) \
  if ((Machine_GDL_Scanner_getTokenKind(scanner) != (EXPECTED_TOKEN_KIND))) \
  { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "expected token kind\n"); \
    Machine_setStatus(Machine_Status_LexicalError); \
    Machine_jump(); \
  }

static void test_1_1() {
  Machine_ByteBuffer* inputText = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(inputText, "", strlen(""));
  Machine_GDL_Scanner* scanner = Machine_GDL_Scanner_create(Machine_String_create("", strlen("")), inputText);
  CHECK(Machine_GDL_TokenKind_StartOfInput);
  Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_EndOfInput);
  Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_EndOfInput);
}

static void test_1_2() {
  Machine_ByteBuffer *inputText = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(inputText, "{:true,false.void;}", strlen("{:true,false.void;}"));
  Machine_GDL_Scanner* scanner = Machine_GDL_Scanner_create(Machine_String_create("", strlen("")), inputText);

  CHECK(Machine_GDL_TokenKind_StartOfInput); Machine_GDL_Scanner_step(scanner);

  CHECK(Machine_GDL_TokenKind_LeftCurlyBracket); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Colon); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Boolean); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Comma); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Boolean); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Period); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Void); Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_Semicolon); Machine_GDL_Scanner_step(scanner);

  CHECK(Machine_GDL_TokenKind_RightCurlyBracket); Machine_GDL_Scanner_step(scanner);

  CHECK(Machine_GDL_TokenKind_EndOfInput);   Machine_GDL_Scanner_step(scanner);
  CHECK(Machine_GDL_TokenKind_EndOfInput);
}

void Machine_GDL_test1() {
  test_1_1();
  test_1_2();
}
