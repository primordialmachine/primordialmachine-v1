/// @file Ring3/Gdl/Lexical/Scanner-inlay.i
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define Symbol_StartOfInput (255+1)
#define Symbol_EndOfInput (255+2)

static int current(Machine_Gdl_Scanner const* self);

static void write(Machine_Gdl_Scanner const* self, int symbol) {
  if (symbol == Symbol_EndOfInput) {
    Ring2_ByteBuffer_appendBytes(self->tokenText, "<end of input>", crt_strlen("<end of input>"));
  } else {
    char temporary = (char)symbol;
    Ring2_ByteBuffer_appendBytes(self->tokenText, &temporary, 1);
  }
}

static void save(Machine_Gdl_Scanner const* self) {
  write(self, current(self));
}

static void next(Machine_Gdl_Scanner* self) {
  if (self->currentPos < self->endPos) {
    self->currentPos++;
  }
}

static void saveAndNext(Machine_Gdl_Scanner* self) {
    save(self);
    next(self);
}

static void writeAndNext(Machine_Gdl_Scanner* self, int symbol) {
    write(self, symbol);
    next(self);
}

static int current(Machine_Gdl_Scanner const* self) {
  if (self->currentPos == self->endPos) return Symbol_EndOfInput;
  return Ring2_ByteBuffer_getBytes(self->inputBytes)[self->currentPos];
}

static bool is(Machine_Gdl_Scanner const* self, int expectedSymbol) {
  int receivedSymbol = current(self);
  return expectedSymbol == receivedSymbol;
}

static bool isDigit(Machine_Gdl_Scanner const* self) {
  int receivedSymbol = current(self);
  return '0' <= receivedSymbol && receivedSymbol <= '9';
}

static bool isWhitespace(Machine_Gdl_Scanner const* self) {
  int receivedSymbol = current(self);
  return ' ' == receivedSymbol || '\t' == receivedSymbol;
}

static bool isNewline(Machine_Gdl_Scanner const* self) {
  int receivedSymbol = current(self);
  return '\n' == receivedSymbol || '\r' == receivedSymbol;
}

static bool isAlphabetic(Machine_Gdl_Scanner const* self) {
  int receivedSymbol = current(self);
  return ('a' <= receivedSymbol && receivedSymbol <= 'z')
      || ('A' <= receivedSymbol && receivedSymbol <= 'Z');
}

/// <code>plusMinus? digit+</code>
static void scanExponent(Machine_Gdl_Scanner* self) {
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
