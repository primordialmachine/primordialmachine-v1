
#define Symbol_StartOfInput (255+1)
#define Symbol_EndOfInput (255+2)

static int current(const Machine_GDL_Scanner* self);

static void write(const Machine_GDL_Scanner* self, int symbol) {
  if (symbol == Symbol_EndOfInput) {
    Machine_ByteBuffer_appendBytes(self->tokenText, "<end of input>", strlen("<end of input>"));
  } else {
    char temporary = (char)symbol;
    Machine_ByteBuffer_appendBytes(self->tokenText, &temporary, 1);
  }
}

static void save(const Machine_GDL_Scanner* self) {
  write(self, current(self));
}

static void next(Machine_GDL_Scanner* self) {
  if (self->currentPos < self->endPos) {
    self->currentPos++;
  }
}

static void saveAndNext(Machine_GDL_Scanner* self) {
    save(self);
    next(self);
}

static void writeAndNext(Machine_GDL_Scanner* self, int symbol) {
    write(self, symbol);
    next(self);
}

static int current(const Machine_GDL_Scanner* self) {
  if (self->currentPos == self->endPos) return Symbol_EndOfInput;
  return Machine_ByteBuffer_getBytes(self->inputBytes)[self->currentPos];
}

static bool is(const Machine_GDL_Scanner* self, int expectedSymbol) {
  int receivedSymbol = current(self);
  return expectedSymbol == receivedSymbol;
}

static bool isDigit(const Machine_GDL_Scanner* self) {
  int receivedSymbol = current(self);
  return '0' <= receivedSymbol && receivedSymbol <= '9';
}

static bool isWhitespace(const Machine_GDL_Scanner* self) {
  int receivedSymbol = current(self);
  return ' ' == receivedSymbol || '\t' == receivedSymbol;
}

static bool isNewline(const Machine_GDL_Scanner* self) {
  int receivedSymbol = current(self);
  return '\n' == receivedSymbol || '\r' == receivedSymbol;
}

static bool isAlphabetic(const Machine_GDL_Scanner* self) {
  int receivedSymbol = current(self);
  return ('a' <= receivedSymbol && receivedSymbol <= 'z')
      || ('A' <= receivedSymbol && receivedSymbol <= 'Z');
}

/// <code>plusMinus? digit+</code>
static void scanExponent(Machine_GDL_Scanner* self) {
  if (!is(self, 'e') && !is(self, 'E')) {
    Machine_setStatus(Machine_Status_LexicalError);
    Machine_jump();
  }
  saveAndNext(self);
  if (is(self, '+') || is(self, '-')) {
    saveAndNext(self);
  }
  if (!isDigit(self)) {
    Machine_setStatus(Machine_Status_LexicalError);
    Machine_jump();
  }
  do {
    saveAndNext(self);
  } while (isDigit(self));
}
