#if !defined(TYPE)
#error("macro `TYPE` must be defined")
#endif

#pragma push_macro("PARENT")
#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static bool
isNewline
  (
    Ring2_Context* context,
    TYPE* self
  )
{
  static const int ELEMENTS[] = { '\n', '\r' };
  return Mkx_SymbolScanner_isAnyOf(PARENT(self)->symbolScanner, 2, ELEMENTS);
}

/// @shortcut
static bool
isWhitespace
  (
    Ring2_Context* context,
    TYPE* self
  )
{
  static const int ELEMENTS[] = { ' ', '\t' };
  return Mkx_SymbolScanner_isAnyOf(PARENT(self)->symbolScanner, 2, ELEMENTS);
}

/// @brief Scan <code>(Whitespace|Newline)*</code>.
/// @param context The context.
/// @param scanner The scanner.
/// @param lineCounter A pointer to a <code>int64_t</code> variable or a null pointer.
static void
scanNewlinesWhitespaces
  (
    Ring2_Context* context,
    TYPE* self,
    int64_t *lineCounter
  )
{
  bool found;
  do
  {
    found = false;
    if (isWhitespace(context, self))
    {
      found = true;
      do
      {
        next(context, self);
      } while (isWhitespace(context, self));
    }
    else if (isNewline(context, self))
    {
      found = true;
      do
      {
        int old = current(context, self);
        next(context, self);
        if (isNewline(context, self) && !is(context, self, old))
        {
          next(context, self);
        }
        if (lineCounter) (*lineCounter)++;
      } while (isNewline(context, self));
    }
  } while (found);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#pragma pop_macro("PARENT")
