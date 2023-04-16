#if !defined(TYPE)
#error("macro `TYPE` must be defined")
#endif

#if !defined(PARENT)
#error("macro `PARENT` must be defined")
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static Ring2_String *
getInputPathname
  (
    Ring2_Context* context,
    TYPE* self
  )
{ return Mkx_SymbolScanner_getInputPathname(PARENT(self)->symbolScanner); }

/// @shortcut
static int64_t
getInputLineNumber
  (
    Ring2_Context* context,
    TYPE* self
  )
{ return Mkx_SymbolScanner_getInputLineNumber(PARENT(self)->symbolScanner); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static bool
is
  (
    Ring2_Context* context,
    TYPE* self,
    int x
  )
{ return Mkx_SymbolScanner_is(PARENT(self)->symbolScanner, x); }

/// @shortcut
static bool
isInRange
  (
    Ring2_Context* context,
    TYPE* self,
    int x,
    int y
  )
{ return Mkx_SymbolScanner_isInRange(PARENT(self)->symbolScanner, x, y); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static int
current
  (
    Ring2_Context* context,
    TYPE* self
  )
{ return Mkx_SymbolScanner_current(PARENT(self)->symbolScanner); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static void
next
  (
    Ring2_Context* context,
    TYPE* self
  )
{ Mkx_SymbolScanner_increment(PARENT(self)->symbolScanner); }

static void
write
  (
    Ring2_Context* context,
    TYPE* self,
    int symbol
  )
{
  if (symbol == Mkx_Symbol_StartOfInput || symbol == Mkx_Symbol_EndOfInput)
  {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  Ring2_StringBuffer_appendByte(PARENT(self)->buffer, symbol);
}

static void
writeAndNext
  (
    Ring2_Context* context,
    TYPE* self,
    int symbol
  )
{
  write(context, self, symbol);
  next(context, self);
}

static void
save
  (
    Ring2_Context* context,
    TYPE* self
  )
{
  write(context, self, current(context, self));
}

static void
saveAndNext
  (
    Ring2_Context* context,
    TYPE* self
  )
{
  save(context, self);
  next(context, self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static bool
isAlphabetic
  (
    Ring2_Context *context,
    TYPE *self
  )
{
  return isInRange(context, self, 'a', 'z')
      || isInRange(context, self, 'A', 'Z');
}

/// @shortcut
static bool
isDigit
  (
    Ring2_Context* context,
    TYPE *self
  )
{ return isInRange(context, self, '0', '9'); }
