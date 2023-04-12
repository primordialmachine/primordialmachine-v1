#if !defined(TYPE)
#error("macro `TYPE` must be defined")
#endif

#pragma push_macro("PARENT")
#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static bool
isDoubleQuote
  (
    Ring2_Context* context,
    TYPE* self
  )
{ return is(context, self, '"'); }

/// @brief Scan <code>String</code>.
/// @param context The context.
/// @param self The environment scanner.
static void
scanString
  (
    Ring2_Context *context,
    TYPE *self
  )
{
  Ring2_StringBuffer_clear(PARENT(self)->buffer);
  if (!isDoubleQuote(context, self))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "expected '\"'\n"));
    Ring1_Status_set(Ring1_Status_InvalidLexics);
    Ring2_jump();
  }
  next(context, self);
  bool lastWasBackslash = false;
  while (true)
  {
    if (is(context, self, Mkx_Symbol_EndOfInput))
    {
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "unclosed string literal\n"));
      Ring1_Status_set(Ring1_Status_InvalidLexics);
      Ring2_jump();
    }
    if (lastWasBackslash)
    {
      if (is(context, self, 'n'))
      {
        writeAndNext(context, self, '\n');
        lastWasBackslash = false;
      }
      else if (is(context, self, '\\'))
      {
        writeAndNext(context, self, '\\');
        lastWasBackslash = false;
      }
      else if (is(context, self, '"'))
      {
        writeAndNext(context, self, '"');
        lastWasBackslash = false;
      }
      else
      {
        Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "unknown escape character\n"));
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      }
    }
    else
    {
      if (is(context, self, '\\'))
      {
        next(context, self);
        lastWasBackslash = true;
      }
      else if (is(context, self, '"'))
      {
        next(context, self);
        break;
      }
      else
      {
        saveAndNext(context, self);
      }
    }
  }
  PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_String;
  PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#pragma pop_macro("PARENT")
