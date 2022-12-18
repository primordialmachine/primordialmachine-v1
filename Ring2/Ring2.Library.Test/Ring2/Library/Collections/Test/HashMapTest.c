/// @file Ring2/Library/Collections/Test/HashMapTest.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring2/Library/Collections/Test/HashMapTest.h"


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
  Ring2_Collections_Map* map = (Ring2_Collections_Map*)Ring2_Collections_HashMap_create();
  Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)map);
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)map));
  Ring2_Collections_Collection_clear((Ring2_Collections_Collection*)map);
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)map));
}

void
Ring2_Test_registerHashMapTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Library.Collections.Test.HashMapTest",
                                  crt_strlen("Ring2.Library.Collections.Test.HashMapTest"));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("1",
                                                                             crt_strlen("1"))),
                      &test1);

}
