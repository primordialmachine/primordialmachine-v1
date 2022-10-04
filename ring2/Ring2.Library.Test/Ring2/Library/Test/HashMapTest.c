/// @file Ring2/Library/Test/HashMapTest.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring2/Library/Test/HashMapTest.h"


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
  Ring2_Map* map = (Ring2_Map*)Ring2_HashMap_create();
  Ring2_Collection_getSize((Ring2_Collection*)map);
  RING2_TEST_ASSERT(0 == Ring2_Collection_getSize((Ring2_Collection*)map));
  Ring2_Collection_clear((Ring2_Collection*)map);
  RING2_TEST_ASSERT(0 == Ring2_Collection_getSize((Ring2_Collection*)map));
}

void
Ring2_Test_registerHashMapTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_Tests_addTest(tests,
                      Ring2_String_create(Ring2_Context_get(), "Ring2.Test.HashMap1", strlen("Ring2.Test.HashMap1")),
                      &test1);

}
