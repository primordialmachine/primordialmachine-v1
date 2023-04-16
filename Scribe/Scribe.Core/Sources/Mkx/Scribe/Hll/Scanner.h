// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/Scanner.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_HLL_SCANNER_H_INCLUDED)
#define MKX_SCRIBE_HLL_SCANNER_H_INCLUDED


#include "Mkx/Scribe/Hll.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Hll_Scanner)

struct Mkx_Scribe_Hll_Scanner_Class {
  Machine_Object_Class _parent;
  void (*step)(Mkx_Scribe_Hll_Scanner*);
};

struct Mkx_Scribe_Hll_Scanner {
  Machine_Object _parent;
  Mkx_SymbolScanner* symbolScanner;
  Ring2_StringBuffer* buffer;
  struct
  {
    int type;
    Ring2_String* text;
  } token;
};

void
Mkx_Scribe_Hll_Scanner_construct
  (
    Mkx_Scribe_Hll_Scanner* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Ring2_String*
Mkx_Scribe_Hll_Scanner_getInputPathname
  (
    Mkx_Scribe_Hll_Scanner* self
  );

int64_t
Mkx_Scribe_Hll_Scanner_getInputLineNumber
  (
    Mkx_Scribe_Hll_Scanner* self
  );

void
Mkx_Scribe_Hll_Scanner_incrementInputLineNumber
  (
    Mkx_Scribe_Hll_Scanner* self
  );

int64_t
Mkx_Scribe_Hll_Scanner_beginOffset
  (
    Mkx_Scribe_Hll_Scanner* self
  );

int64_t
Mkx_Scribe_Hll_Scanner_currentOffset
  (
    Mkx_Scribe_Hll_Scanner* self
  );

Mkx_Scribe_Hll_TokenType
Mkx_Scribe_Hll_Scanner_getTokenType
  (
    Mkx_Scribe_Hll_Scanner* self
  );

Ring2_String*
Mkx_Scribe_Hll_Scanner_getTokenText
  (
    Mkx_Scribe_Hll_Scanner* self
  );

void
Mkx_Scribe_Hll_Scanner_step
  (
    Mkx_Scribe_Hll_Scanner* self
  );

#endif // MKX_SCRIBE_HLL_SCANNER_H_INCLUDED
