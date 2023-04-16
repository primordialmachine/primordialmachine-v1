// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Common/SymbolScanner.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_COMMON_SYMBOLSCANNER_H_INCLUDED)
#define MKX_SCRIBE_COMMON_SYMBOLSCANNER_H_INCLUDED

#if !defined(MKX_SCRIBE_COMMON_PRIVATE)
#error Do not include `Mkx/Scribe/Common/SymbolScanner.h` directly. Include `Mkx/Scribe/Common.h` instead
#endif

#include "Mkx/Scribe/Common/Includes.h"


/// @brief The "start of input" symbol.
/// @remark Macro evaluating to an integer literal.
#define Mkx_Symbol_StartOfInput (255 + 1)

/// @brief The "end of input" symbol.
/// @remark Macro evaluating to an integer literal.
#define Mkx_Symbol_EndOfInput (255 + 2)


/// @brief The maximal offset.
/// @remark Macro evaluating to an integer literal.
#define Mkx_SymbolScanner_MaximumOffset (INT64_MAX)


MACHINE_DECLARE_CLASSTYPE(Mkx_SymbolScanner)

struct Mkx_SymbolScanner_Class {
  Machine_Object_Class parent;
};

struct Mkx_SymbolScanner {
  Machine_Object parent;
  Ring2_String* inputString;
  Ring2_String* inputPathname;
  const char *inputBytes;
  int64_t inputLineNumber;
  struct
  {
    uint64_t current;
    uint64_t begin;
    uint64_t end;
  } offsets;
};

void
Mkx_SymbolScanner_construct
  (
    Mkx_SymbolScanner* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Mkx_SymbolScanner*
Mkx_SymbolScanner_create
  (
    Ring2_String* inputString,
    Ring2_String* inputPathname
  );

int
Mkx_SymbolScanner_current
  (
    Mkx_SymbolScanner* self
  );

int64_t
Mkx_SymbolScanner_beginOffset
  (
    Mkx_SymbolScanner* self
  );

int64_t
Mkx_SymbolScanner_endOffset
  (
    Mkx_SymbolScanner* self
  );

int64_t
Mkx_SymbolScanner_currentOffset
  (
    Mkx_SymbolScanner* self
  );

void
Mkx_SymbolScanner_setInputBytes
  (
    Mkx_SymbolScanner *self,
    Ring2_String* inputString,
    Ring2_String* inputPathname,
    int64_t lineNumber,
    uint64_t offsetBegin,
    uint64_t offsetEnd,
    uint64_t offsetCurrent
  );

void
Mkx_SymbolScanner_setInput
  (
    Mkx_SymbolScanner* self,
    Ring2_String* input,
    Ring2_String* inputPathname
  );

/// @brief Increment the current position.
/// @error The current position is the end position.
void
Mkx_SymbolScanner_increment
  (
    Mkx_SymbolScanner *self
  );

void
Mkx_SymbolScanner_increment_n
  (
    Mkx_SymbolScanner* self,
    int64_t n
  );

Ring2_String*
Mkx_SymbolScanner_getInputPathname
  (
    Mkx_SymbolScanner *self
  );

int64_t
Mkx_SymbolScanner_getInputLineNumber
  (
    Mkx_SymbolScanner* self
  );

void
Mkx_SymbolScanner_incrementInputLineNumber
  (
    Mkx_SymbolScanner* self
  );

bool
Mkx_SymbolScanner_is
  (
    Mkx_SymbolScanner* self,
    int c
  );

bool
Mkx_SymbolScanner_isAnyOf
  (
    Mkx_SymbolScanner* self,
    size_t numberOfElements,
    const int* elements
  );

bool
Mkx_SymbolScanner_isInRange
  (
    Mkx_SymbolScanner* self,
    int x,
    int y
  );

#endif // MKX_SCRIBE_COMMON_SYMBOLSCANNER_H_INCLUDED
