#if !defined(TYPE)
#error("macro `TYPE` must be defined")
#endif

#pragma push_macro("PARENT")
#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Scan <code>Numeral := Digit+</code>.
/// @param context The context.
/// @param self The scanner.
static void
scanNumeral
  (
    Ring2_Context* context,
    TYPE* self
  )
{
  Ring2_StringBuffer_clear(PARENT(self)->buffer);
  if (!isDigit(context, self))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "expected <digit>\n"));
    Ring1_Status_set(Ring1_Status_InvalidLexics);
    Ring2_jump();
  }
  do
  {
    saveAndNext(context, self);
  } while (isDigit(context, self));
  PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Integer;
  PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#pragma pop_macro("PARENT")
