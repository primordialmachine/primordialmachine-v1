// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Stack.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Stack.h"

#include "Ring2/Test/Stack/pushArray.h"
#include "Ring2/Test/Stack/pushBoolean.h"
#include "Ring2/Test/Stack/pushInteger.h"
#include "Ring2/Test/Stack/pushReal.h"
#include "Ring2/Test/Stack/pushString.h"
#include "Ring2/Test/Stack/pushVoid.h"

void
Ring2_Test_registerStackTests
  (
    Ring2_Tests* tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Test.StackTest.",
                                  crt_strlen("Ring2.Test.StackTest."));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("pushArray",
                                                                             crt_strlen("pushArray"))),
                      &Mkx_Interpreter_Test_Stack_pushArray);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("pushBoolean",
                                                                             crt_strlen("pushBoolean"))),
                      &Mkx_Interpreter_Test_Stack_pushBoolean);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("pushInteger",
                                                                             crt_strlen("pushInteger"))),
                      &Mkx_Interpreter_Test_Stack_pushInteger);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("pushReal",
                                                                             crt_strlen("pushReal"))),
                      &Mkx_Interpreter_Test_Stack_pushReal);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("pushString",
                                                                             crt_strlen("pushString"))),
                      &Mkx_Interpreter_Test_Stack_pushString);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("pushVoid",
                                                                             crt_strlen("pushVoid"))),
                      &Mkx_Interpreter_Test_Stack_pushVoid);
}
