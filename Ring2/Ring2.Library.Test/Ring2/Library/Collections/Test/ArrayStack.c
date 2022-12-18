/// @file Ring2/Library/Collections/Test/ArrayStack.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring2/Library/Collections/Test/ArrayStack.h"


#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"


static void
test1
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

static void
test1
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Collections_Stack* stack = (Ring2_Collections_Stack*)Ring2_Collections_ArrayStack_create();
  Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)stack);
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)stack));
  Ring2_Collections_Collection_clear((Ring2_Collections_Collection*)stack);
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)stack));
}

void
Ring2_Test_registerArrayStackTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Library.Collections.Test.ArrayStackTest",
                                 crt_strlen("Ring2.Library.Collections.Test.ArrayStackTest"));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("1",
                                                                             crt_strlen("1"))),
                      &test1);

}
