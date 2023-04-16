// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/Scanner.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Hll/Scanner.h"

static void
visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Hll_Scanner* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Hll_Scanner, Machine_Object, &visit, &Mkx_Scribe_Hll_Scanner_construct, NULL, NULL, NULL);

void
Mkx_Scribe_Hll_Scanner_construct
  (
    Mkx_Scribe_Hll_Scanner* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  
  self->symbolScanner = (Mkx_SymbolScanner *)Ring2_Value_getObject(&arguments[0]);
  self->token.text = Ring2_String_fromC(false, "<start of input>");
  self->token.type = Mkx_Scribe_Hll_TokenType_StartOfInput;
  self->buffer = Ring2_StringBuffer_create(Ring2_Context_get());

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Mkx_Scribe_Hll_Scanner_getType());
}

static void
visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Hll_Scanner* self
  )
{
  if (NULL != self->buffer)
  {
    Ring2_Gc_visit(gc, self->buffer);
  }
  if (NULL != self->token.text)
  {
    Ring2_Gc_visit(gc, self->token.text);
  }
  if (NULL != self->symbolScanner)
  {
    Ring2_Gc_visit(gc, self->symbolScanner);
  }
}

Ring2_String*
Mkx_Scribe_Hll_Scanner_getInputPathname
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ return Mkx_SymbolScanner_getInputPathname(self->symbolScanner); }

int64_t
Mkx_Scribe_Hll_Scanner_getInputLineNumber
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ return Mkx_SymbolScanner_getInputLineNumber(self->symbolScanner); }

void
Mkx_Scribe_Hll_Scanner_incrementInputLineNumber
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ Mkx_SymbolScanner_incrementInputLineNumber(self->symbolScanner); }

int64_t
Mkx_Scribe_Hll_Scanner_beginOffset
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ return Mkx_SymbolScanner_beginOffset(self->symbolScanner); }

int64_t
Mkx_Scribe_Hll_Scanner_currentOffset
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ return Mkx_SymbolScanner_currentOffset(self->symbolScanner); }

Mkx_Scribe_Hll_TokenType
Mkx_Scribe_Hll_Scanner_getTokenType
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ return self->token.type; }

Ring2_String*
Mkx_Scribe_Hll_Scanner_getTokenText
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ return self->token.text; }

void
Mkx_Scribe_Hll_Scanner_step
  (
    Mkx_Scribe_Hll_Scanner* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Hll_Scanner, step, , self); }
