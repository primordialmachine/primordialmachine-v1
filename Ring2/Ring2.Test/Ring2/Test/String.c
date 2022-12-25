// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/String.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/String.h"

#include "Ring1/All/_Include.h"
#include "Ring2/Test/String/concatenate.h"
#include "Ring2/Test/String/firstOccurrenceOf.h"

void
Ring2_Test_registerStringTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Test.StringTest.",
                                  crt_strlen("Ring2.Test.StringTest."));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("concatenate",
                                                                             crt_strlen("concatenate"))),
                      &Mkx_Interpreter_Test_String_concatenate);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("firstOccurenceOf",
                                                                             crt_strlen("firstOccurenceOf"))),
                      &Mkx_Interpreter_Test_String_firstOccurrenceOf);
}
