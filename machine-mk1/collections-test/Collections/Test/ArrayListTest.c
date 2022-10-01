/// @file Ring2/Test/ArrayListTest.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Collections/Test/ArrayListTest.h"


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
  Machine_List* list = (Machine_List *)Machine_ArrayList_create();
  RING2_TEST_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)list));
  Machine_Collection_clear((Machine_Collection*)list);
  RING2_TEST_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)list));
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
