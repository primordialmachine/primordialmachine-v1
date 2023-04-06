/// @file Ring3/Gdl/Lexical/Scanner.private.c.i
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Lexical/DefaultScanner.private.h.i"
#undef RING3_GDL_PRIVATE

/// @{

static void
write
  (
    Ring3_Gdl_DefaultScanner const* self,
    int symbol
  )
{
  if (symbol == Symbol_EndOfInput) {
    Ring2_ByteBuffer_appendBytes(self->lexemeBuffer, "<end of input>", crt_strlen("<end of input>"));
  } else {
    char temporary = (char)symbol;
    Ring2_ByteBuffer_appendBytes(self->lexemeBuffer, &temporary, 1);
  }
}

static void
save
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{ write(self, current(self)); }

static void
next
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  if (self->current < self->input.end) {
    self->current++;
  }
}

static void
saveAndNext
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  save(self);
  next(self);
}

static void
writeAndNext
  (
    Ring3_Gdl_DefaultScanner* self,
    int symbol
  )
{
  write(self, symbol);
  next(self);
}

static int
current
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{
  if (self->current == self->input.end) return Symbol_EndOfInput;
  return Ring2_ByteBuffer_getBytes(self->input.bytes)[self->current];
}

static bool
is
  (
    Ring3_Gdl_DefaultScanner const* self,
    int expectedSymbol
  )
{
  int receivedSymbol = current(self);
  return expectedSymbol == receivedSymbol;
}

static bool
isDigit
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{
  int receivedSymbol = current(self);
  return '0' <= receivedSymbol && receivedSymbol <= '9';
}

static bool
isWhitespace
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{
  int receivedSymbol = current(self);
  return ' ' == receivedSymbol || '\t' == receivedSymbol;
}

static bool
isNewline
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{
  int receivedSymbol = current(self);
  return '\n' == receivedSymbol || '\r' == receivedSymbol;
}

static bool
isAlphabetic
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{
  int receivedSymbol = current(self);
  return ('a' <= receivedSymbol && receivedSymbol <= 'z')
      || ('A' <= receivedSymbol && receivedSymbol <= 'Z');
}

/// @}

/// @{

/// <code>plusMinus? digit+</code>
static void
scanExponent
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  if (!is(self, 'e') && !is(self, 'E')) {
    Ring1_Status_set(Ring1_Status_InvalidLexics);
    Ring2_jump();
  }
  saveAndNext(self);
  if (is(self, '+') || is(self, '-')) {
    saveAndNext(self);
  }
  if (!isDigit(self)) {
    Ring1_Status_set(Ring1_Status_InvalidLexics);
    Ring2_jump();
  }
  do {
    saveAndNext(self);
  } while (isDigit(self));
}


static void
scanSingleQuotedString
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  int64_t start = self->current;
  Ring2_ByteBuffer_clear(self->lexemeBuffer);
#if Ring3_Gdl_Scanner_retainStringDelimiters == 1
  saveAndNext(self);
#else
  next(self);
#endif
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
#if Ring3_Gdl_Scanner_retainStringDelimiters == 1
  saveAndNext(self);
#else
  next(self);
#endif
  self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_String,
                                       makeText(self),
                                       start,
                                       self->current);
}

static void
scanDoubleQuotedString
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  int64_t start = self->current;
  Ring2_ByteBuffer_clear(self->lexemeBuffer);
#if Ring3_Gdl_Scanner_retainStringDelimiters == 1
  saveAndNext(self);
#else
  next(self);
#endif
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
#if Ring3_Gdl_Scanner_retainStringDelimiters == 1
  saveAndNext(self);
#else
  next(self);
#endif
  self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_String,
                                       makeText(self),
                                       start,
                                       self->current);
}

/// @}

/// @{

static void
stepImpl
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  if (Ring3_Gdl_Token_getKind(self->token) == Ring3_Gdl_TokenKind_EndOfInput) {
    return;
  }
  switch (current(self)) {
    case Symbol_EndOfInput: {
      self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_EndOfInput,
                                           Ring2_String_fromC(false, "<end of input>"),
                                           self->current,
                                           self->current);
    } break;
    case ' ':
    case '\t':
    {
      do {
        next(self);
      } while (isWhitespace(self));
      Ring3_Gdl_Scanner_step(Ring1_cast(Ring3_Gdl_Scanner*,self));
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
      Ring3_Gdl_Scanner_step(Ring1_cast(Ring3_Gdl_Scanner*,self));
    } break;
    #if defined(Machine_Gdl_DefaultScanner_withPeriod) && Machine_Gdl_DefaultScanner_withPeriod == 1
    case '.': {
      int64_t start = self->current;
      Ring2_ByteBuffer_clear(self->lexemeBuffer);
      saveAndNext(self);
      if (isDigit(self)) {
        do {
          saveAndNext(self);
        } while (isDigit(self));
        if (is(self, 'e') || is(self, 'E')) {
          saveAndNext(self);
          scanExponent(self);
        }
        self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_Real,
          makeText(self),
          start,
          self->current);
      }
      else {
        self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_Period,
          makeText(self),
          start,
          self->current);
      }
    } break;
    #endif
    case ',':
    #if defined(Machine_Gdl_DefaultScanner_withSemicolon) && Machine_Gdl_DefaultScanner_withSemicolon == 1
    case ';':
    #endif
    case ':':
    case '{':
    case '}':
    case '[':
    case ']': {
      int64_t start = self->current;
      Ring2_ByteBuffer_clear(self->lexemeBuffer);
      saveAndNext(self);
      Ring2_String* text = makeText(self);
      Ring3_Gdl_TokenKind kind;
      {
        Ring2_Value k;
        Ring2_Value_setString(&k, text);
        Ring2_Value v = Ring2_Collections_Map_get(self->keywords, k);
        if (!Ring2_Value_isInteger(&v)) {
          Ring1_Status_set(Ring1_Status_InternalError);
          Ring2_jump();
        }
        kind = (Ring3_Gdl_TokenKind)Ring2_Value_getInteger(&v);
      }
      self->token = Ring3_Gdl_Token_create(kind,
                                           text,
                                           start,
                                           self->current);
    } break;
    case '\'': {
      scanSingleQuotedString(self);
    } break;
    case '"': {
      scanDoubleQuotedString(self);
    } break;
    case '0': case '1': case '2':
    case '3': case '4': case '5':
    case '6': case '7': case '8':
    case '9': case '+': case '-':
    {
      int64_t start = self->current;
      Ring2_ByteBuffer_clear(self->lexemeBuffer);
      if (is(self, '+') || is(self, '-')) {
        saveAndNext(self);
      }
      // ('+'|'-') digit+ ('.' digit* exponent?)?
      if (isDigit(self)) {
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
          self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_Real,
                                                 makeText(self),
                                                 start,
                                                 self->current);

        } else {
          self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_Integer,
                                               makeText(self),
                                               start,
                                               self->current);
        }
      // ('+'|'-') '.' digit+ exponent?
      } else if (is(self, '.')) {
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
        self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_Real,
                                             makeText(self),
                                             start,
                                             self->current);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      }
    } break;
    default: {
      if (is(self, '_') || isAlphabetic(self)) {
        int64_t start = self->current;
        Ring2_ByteBuffer_clear(self->lexemeBuffer);
        saveAndNext(self);
        do {
          saveAndNext(self);
        } while (is(self, '_') || isAlphabetic(self) || isDigit(self));
        Ring2_String* text = makeText(self);
        Ring3_Gdl_TokenKind kind = Ring3_Gdl_TokenKind_Name;
        {
          Ring2_Value k;
          Ring2_Value_setString(&k, text);
          Ring2_Value v = Ring2_Collections_Map_get(self->keywords, k);
          if (Ring2_Value_isInteger(&v)) {
             kind = (Ring3_Gdl_TokenKind)Ring2_Value_getInteger(&v);
          }
        }
        self->token = Ring3_Gdl_Token_create(kind,
                                             text,
                                             start,
                                             self->current);
      } else {
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      }
    } break;
  };
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring3_Gdl_Token*
getTokenImpl
  (
    Ring3_Gdl_DefaultScanner const* self
  )
{ return self->token; }

static void
setInputImpl
  (
    Ring3_Gdl_DefaultScanner* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  )
{
  Ring2_ByteBuffer* inputBytesNew = Ring2_ByteBuffer_create();
  Ring2_ByteBuffer_appendBytes(inputBytesNew, Ring2_ByteBuffer_getBytes(inputBytes), Ring2_ByteBuffer_getNumberOfBytes(inputBytes));
  Ring2_ByteBuffer* lexemeBufferNew = Ring2_ByteBuffer_create();
  int64_t endPosNew = Ring2_ByteBuffer_getNumberOfBytes(inputBytesNew);

  self->input.bytes = inputBytesNew;
  self->input.name = inputName;
  self->input.start = 0;
  self->input.end = Ring2_ByteBuffer_getNumberOfBytes(inputBytesNew);

  self->current = 0;

  self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_StartOfInput,
    Ring2_String_fromC(false, "<start of input>"),
    0,
    0);
  self->lexemeBuffer = lexemeBufferNew;
}

/// @}

static Ring1_NoDiscardReturn() Ring2_Collections_Map*
makeKeywords
  (
  )
{
  Ring2_Collections_Map* map = Ring1_cast(Ring2_Collections_Map*,Ring2_Collections_HashMap_create());
#define Define(KEY,VALUE) \
  { \
    Ring2_Value k, v; \
    Ring2_Value_setString(&k, Ring2_String_fromC(false, KEY)); \
    Ring2_Value_setInteger(&v, (Ring2_Integer)VALUE); \
    Ring2_Collections_Map_set(map, k, v); \
  }
  Define("false", Ring3_Gdl_TokenKind_Boolean);
  Define("true", Ring3_Gdl_TokenKind_Boolean);
  Define("void", Ring3_Gdl_TokenKind_Void)
  Define(",", Ring3_Gdl_TokenKind_Comma);
#if defined(Machine_Gdl_DefaultScanner_withSemicolon) && Machine_Gdl_DefaultScanner_withSemicolon == 1
  Define(";", Ring3_Gdl_TokenKind_Semicolon);
#endif
  Define(":", Ring3_Gdl_TokenKind_Colon);
  Define("{", Ring3_Gdl_TokenKind_LeftCurlyBracket);
  Define("}", Ring3_Gdl_TokenKind_RightCurlyBracket);
  Define("[", Ring3_Gdl_TokenKind_LeftSquareBracket);
  Define("]", Ring3_Gdl_TokenKind_RightSquareBracket);
#undef Define
    return map;
}

static Ring1_NoDiscardReturn() Ring2_String*
makeText
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  return Ring2_String_create(Ring2_ByteBuffer_getBytes(self->lexemeBuffer),
                             Ring2_ByteBuffer_getNumberOfBytes(self->lexemeBuffer));
}