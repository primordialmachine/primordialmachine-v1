/// @file Gdl/Lexical/Scanner.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gdl/Lexical/Scanner.h"


#include "Ring1/Intrinsic.h"
#include <string.h>


typedef struct KEYWORD {
  const char* bytes;
  size_t numberOfBytes;
  Machine_Gdl_TokenKind tokenKind;
} KEYWORD;

static const KEYWORD keywords[] = {
  {"true",  sizeof("true") - 1,  Machine_Gdl_TokenKind_Boolean  },
  {"void",  sizeof("void") - 1,  Machine_Gdl_TokenKind_Void  },
  {"false", sizeof("false") - 1, Machine_Gdl_TokenKind_Boolean },
};
static const size_t numberOfKeywords = sizeof(keywords) / sizeof(KEYWORD);

static void checkKeywords(Machine_Gdl_Scanner *self) {
  for (size_t i = 0, n = numberOfKeywords; i < n; ++i) {
    const KEYWORD* keyword = &(keywords[i]);
    if (keyword->numberOfBytes > Machine_ByteBuffer_getNumberOfBytes(self->tokenText)) {
      return;
    } else if (Machine_ByteBuffer_compareBytes(self->tokenText, keyword->bytes, keyword->numberOfBytes)) {
      self->tokenKind = keyword->tokenKind;
      return;
    }
  }
}

static void Machine_Gdl_Scanner_visit(Machine_Gdl_Scanner* self) {
  if (self->inputName) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->inputName);
  }
  if (self->inputBytes) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->inputBytes);
  }
  if (self->tokenText) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->tokenText);
  }
}

static void Machine_Gdl_Scanner_construct(Machine_Gdl_Scanner* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->inputName = Ring2_Value_getString(&arguments[0]);
  self->inputBytes = Machine_ByteBuffer_create();
  Machine_ByteBuffer* inputBytes = (Machine_ByteBuffer*)Ring2_Value_getObject(&arguments[1]);
  Machine_ByteBuffer_appendBytes(self->inputBytes, Machine_ByteBuffer_getBytes(inputBytes), Machine_ByteBuffer_getNumberOfBytes(inputBytes));
  self->currentPos = 0;
  self->endPos = Machine_ByteBuffer_getNumberOfBytes(self->inputBytes);
  self->tokenKind = Machine_Gdl_TokenKind_StartOfInput;
  self->tokenStart = 0;
  self->tokenText = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(self->tokenText, "<start of input>", strlen("<start of input>"));
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Scanner_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Scanner, Machine_Object, &Machine_Gdl_Scanner_visit,
                         &Machine_Gdl_Scanner_construct, NULL, NULL, NULL)

Machine_Gdl_Scanner* Machine_Gdl_Scanner_create(Ring2_String* inputName, Machine_ByteBuffer* inputBytes) {
  Machine_ClassType* ty = Machine_Gdl_Scanner_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[2];
  Ring2_Value_setString(&ARGUMENTS[0], inputName);
  Ring2_Value_setObject(&ARGUMENTS[1], (Machine_Object*)inputBytes);
  Machine_Gdl_Scanner* self = (Machine_Gdl_Scanner*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Gdl_Scanner_setInput(Machine_Gdl_Scanner* self, Ring2_String* inputName, Machine_ByteBuffer* inputBytes) {
  Machine_ByteBuffer *inputBytesNew = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(inputBytesNew, Machine_ByteBuffer_getBytes(inputBytes), Machine_ByteBuffer_getNumberOfBytes(inputBytes));
  Machine_ByteBuffer* tokenTextNew = Machine_ByteBuffer_create();
  Machine_ByteBuffer_appendBytes(tokenTextNew, "<start of input>", strlen("<start of input>"));
  size_t endPosNew = Machine_ByteBuffer_getNumberOfBytes(inputBytesNew);
  size_t currentPosNew = 0;

  self->inputBytes = inputBytes;
  self->inputName = inputName;
  
  self->endPos = endPosNew;
  self->currentPos = currentPosNew;

  self->tokenKind = Machine_Gdl_TokenKind_StartOfInput;
  self->tokenStart = 0;
  self->tokenText = tokenTextNew;
}

#include "Gdl/Lexical/Scanner-inlay.i"

static void scanSingleQuotedString(Machine_Gdl_Scanner* self)
{
  self->tokenStart = self->currentPos;
  Machine_ByteBuffer_clear(self->tokenText);
  next(self);
  while (true) {
    if (current(self) == '\\') {
      next(self);
      switch (current(self)) {
      case '\\':
        writeAndNext(self, '\\');
        break;
      case 'n':
        writeAndNext(self, '\n');
        break;
      case 'r':
        writeAndNext(self, '\r');
        break;
      case 't':
        writeAndNext(self, '\t');
        break;
      case '\'':
        writeAndNext(self, '\'');
        break;
      default:
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      };
    } else if (current(self) == '\'') {
      break;
    } else if (current(self) == Symbol_EndOfInput) {
      Ring1_Status_set(Ring1_Status_InvalidLexics);
      Ring2_jump();
    } else {
      saveAndNext(self);
    }
  }
  next(self);
  self->tokenKind = Machine_Gdl_TokenKind_String;
}

static void scanDoubleQuotedString(Machine_Gdl_Scanner* self)
{
  self->tokenStart = self->currentPos;
  Machine_ByteBuffer_clear(self->tokenText);
  next(self);
  while (true) {
    if (current(self) == '\\') {
      next(self);
      switch (current(self)) {
      case '\\':
        writeAndNext(self, '\\');
        break;
      case 'n':
        writeAndNext(self, '\n');
        break;
      case 'r':
        writeAndNext(self, '\r');
        break;
      case 't':
        writeAndNext(self, '\t');
        break;
      case '\'':
        writeAndNext(self, '"');
        break;
      default:
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      };
    }
    else if (current(self) == '"') {
      break;
    }
    else if (current(self) == Symbol_EndOfInput) {
      Ring1_Status_set(Ring1_Status_InvalidLexics);
      Ring2_jump();
    }
    else {
      saveAndNext(self);
    }
  }
  next(self);
  self->tokenKind = Machine_Gdl_TokenKind_String;
}

void Machine_Gdl_Scanner_step(Machine_Gdl_Scanner* self) {
  if (self->tokenKind == Machine_Gdl_TokenKind_EndOfInput) {
    self->tokenKind = Machine_Gdl_TokenKind_EndOfInput;
    Machine_ByteBuffer_clear(self->tokenText);
    save(self);
    return;
  }
  switch (current(self)) {
    case Symbol_EndOfInput: {
      self->tokenKind = Machine_Gdl_TokenKind_EndOfInput;
      Machine_ByteBuffer_clear(self->tokenText);
      save(self);
      return;
    } break;
    case ' ':
    case '\t':
    {
      do {
        next(self);
      } while (isWhitespace(self));
      Machine_Gdl_Scanner_step(self);
      return;
    } break;
    case '\n':
    case '\r': {
      do {
        int old = current(self);
        next(self);
        if (current(self) != old && isNewline(self)) {
          next(self);
        }
      } while (isNewline(self));
      Machine_Gdl_Scanner_step(self);
      return;
    } break;
    #define Machine_Gdl_Scanner_withPeriod (1)
    #if defined(Machine_Gdl_Scanner_withPeriod) && Machine_Gdl_Scanner_withPeriod == 1
    case '.':
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      if (isDigit(self)) {
        do {
          saveAndNext(self);
        } while (isDigit(self));
        if (is(self, 'e') || is(self, 'E')) {
          saveAndNext(self);
          scanExponent(self);
        }
        self->tokenKind = Machine_Gdl_TokenKind_Real;
      } else {
        self->tokenKind = Machine_Gdl_TokenKind_Period;
      }
      break;
    #endif
    case ',':
      self->tokenKind = Machine_Gdl_TokenKind_Comma;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    #define Machine_Gdl_Scanner_withSemicolon (1)
    #if defined(Machine_Gdl_Scanner_withSemicolon) && Machine_Gdl_Scanner_withSemicolon == 1
    case ';':
      self->tokenKind = Machine_Gdl_TokenKind_Semicolon;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    #endif
    case ':':
      self->tokenKind = Machine_Gdl_TokenKind_Colon;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    case '{':
      self->tokenKind = Machine_Gdl_TokenKind_LeftCurlyBracket;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    case '}':
      self->tokenKind = Machine_Gdl_TokenKind_RightCurlyBracket;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    case '[':
      self->tokenKind = Machine_Gdl_TokenKind_LeftSquareBracket;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    case ']':
      self->tokenKind = Machine_Gdl_TokenKind_RightSquareBracket;
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);
      saveAndNext(self);
      break;
    case '\'': {
      scanSingleQuotedString(self);
      return;
    } break;
    case '"': {
      scanDoubleQuotedString(self);
      return;
    } break;
    case '0': case '1': case '2':
    case '3': case '4': case '5':
    case '6': case '7': case '8':
    case '9': case '+': case '-':
    {
      self->tokenStart = self->currentPos;
      Machine_ByteBuffer_clear(self->tokenText);

      if (is(self, '+') || is(self, '-')) {
        saveAndNext(self);
      }
      // ('+'|'-') digit+ ('.' digit* exponent?)?
      if (isDigit(self)) {
        self->tokenKind = Machine_Gdl_TokenKind_Integer;
        do {
          saveAndNext(self);
        } while (isDigit(self));
        if (is(self, '.')) {
          saveAndNext(self);
          while (isDigit(self)) {
            saveAndNext(self);
          }
          if (is(self, 'e') || is(self, 'E')) {
            scanExponent(self);
          }
          self->tokenKind = Machine_Gdl_TokenKind_Real;
        }
      // ('+'|'-') '.' digit+ exponent?
      } else if (is(self, '.')) {
        self->tokenKind = Machine_Gdl_TokenKind_Real;
        saveAndNext(self);
        do {
          saveAndNext(self);
        } while (isDigit(self));
        if (is(self, '.')) {
          saveAndNext(self);
        }
        if (is(self, 'e') || is(self, 'E')) {
          scanExponent(self);
        }
      } else {
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      }
    } break;
    default:
    {
      if (is(self, '_') || isAlphabetic(self)) {
        Machine_ByteBuffer_clear(self->tokenText);
        saveAndNext(self);
        self->tokenStart = self->currentPos;
        do {
          saveAndNext(self);
        } while (is(self, '_') || isAlphabetic(self) || isDigit(self));
        self->tokenKind = Machine_Gdl_TokenKind_Name;
        checkKeywords(self);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      }
    } break;
  };
}

Machine_Gdl_TokenKind Machine_Gdl_Scanner_getTokenKind(Machine_Gdl_Scanner const* self) {
  return self->tokenKind;
}

Ring2_String* Machine_Gdl_Scanner_getTokenText(Machine_Gdl_Scanner const* self) {
  return Ring2_String_create(Ring2_Context_get(), Machine_ByteBuffer_getBytes(self->tokenText), Machine_ByteBuffer_getNumberOfBytes(self->tokenText));
}
