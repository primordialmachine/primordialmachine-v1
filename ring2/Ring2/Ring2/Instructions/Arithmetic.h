// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Instructions/Arithmetic.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_INSTRUCTIONS_ARITHMETIC_H_INCLUDED)
#define RING2_INSTRUCTIONS_ARITHMETIC_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Instructions/Affirmate.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


void
Mkx_Interpreter_Instructions_add
  (
    Ring2_Context* context
  );

void
Mkx_Interpreter_Instructions_subtract
  (
    Ring2_Context* context
  );

void
Mkx_Interpreter_Instructions_multiply
  (
    Ring2_Context* context
  );

void
Mkx_Interpreter_Instructions_divide
  (
    Ring2_Context* context
  );


#endif // RING2_INSTRUCTIONS_ARITHMETIC_H_INCLUDED
