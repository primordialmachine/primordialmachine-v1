#if !defined(TYPE)
#error("macro `TYPE` must be defined")
#endif

#pragma push_macro("PARENT")
#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/// @shortcut
static bool
isUnderscore
  (
    Ring2_Context *context,
    TYPE *self
  )
{ return is(context, self, '_'); }

/// @brief Scan <code>Name := (Alphabetic|Underscore)(Alphabetic|Underscore|Digit)*</code>.
/// @param context The context.
/// @param self The scanner.
static void
scanName
  (
    Ring2_Context* context,
    TYPE* self
  )
{
  Ring2_StringBuffer_clear(PARENT(self)->buffer);
  if (!isAlphabetic(context, self) && !isUnderscore(context, self))
  {
    Ring2_emitf(context, Ring2_String_fromC(false, "expected <name>\n"));
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
  do
  {
    saveAndNext(context, self);
  } while (isAlphabetic(context, self) || isDigit(context, self) || isUnderscore(context, self));
  PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Name;
  PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#pragma pop_macro("PARENT")
