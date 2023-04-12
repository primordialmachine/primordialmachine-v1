#if !defined(TYPE)
#error("macro `TYPE` must be defined")
#endif

#if !defined(PARENT)
#error("macro `PARENT` must be defined")
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring2_String*
getTokenPathname
  (
    TYPE* self
  )
{ return Mkx_Scribe_Hll_Scanner_getInputPathname(Ring1_cast(Mkx_Scribe_Hll_Scanner*, self->scanner)); }

static int64_t
getTokenLineNumber
  (
    TYPE* self
  )
{ return Mkx_Scribe_Hll_Scanner_getInputLineNumber(Ring1_cast(Mkx_Scribe_Hll_Scanner*, self->scanner)); }

static Mkx_Scribe_Position*
getTokenPosition
  (
    TYPE *self
  )
{ return Mkx_Scribe_Position_create(getTokenPathname(self), getTokenLineNumber(self)); }

static int
getTokenType
  (
    TYPE* self
  )
{ return Mkx_Scribe_Hll_Scanner_getTokenType(Ring1_cast(Mkx_Scribe_Hll_Scanner *, self->scanner)); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static bool
is
  (
    TYPE* self,
    Mkx_Scribe_Hll_TokenType type
  )
{ return type == getTokenType(self); }

static void
next
  (
    TYPE *self
  )
{ Mkx_Scribe_Hll_Scanner_step(Ring1_cast(Mkx_Scribe_Hll_Scanner *, self->scanner)); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring2_String*
getTokenText
  (
    TYPE *self
  )
{ return Mkx_Scribe_Hll_Scanner_getTokenText(Ring1_cast(Mkx_Scribe_Hll_Scanner *, self->scanner)); }
