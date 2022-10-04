/// @file Ring2/Library/Test/ArrayListTest.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring2/Library/Test/ArrayListTest.h"


#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"
#include <string.h>


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
  Ring2_List* list = (Ring2_List *)Ring2_ArrayList_create();
  RING2_TEST_ASSERT(0 == Ring2_Collection_getSize((Ring2_Collection*)list));
  Ring2_Collection_clear((Ring2_Collection*)list);
  RING2_TEST_ASSERT(0 == Ring2_Collection_getSize((Ring2_Collection*)list));
}

void
Ring2_Test_registerArrayListTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_Tests_addTest(tests,
                      Ring2_String_create(Ring2_Context_get(), "Ring2.Test.ArrayList1", strlen("Ring2.Test.ArrayList1")),
                      &test1);
}
