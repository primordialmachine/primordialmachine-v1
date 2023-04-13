/// @file Ring2/Library/Collections/Test/PairTest.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring2/Library/Collections/Test/PairTest.h"


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
  Ring2_Value first = { Ring2_Value_Tag_Void, Ring2_Void_Void },
              second = { Ring2_Value_Tag_Void, Ring2_Void_Void };
  Ring2_Value_setVoid(&first, Ring2_Void_Void);
  Ring2_Value_setVoid(&first, Ring2_Void_Void);
  Ring2_Collections_Pair* pair = Ring2_Collections_Pair_create(first, second);
}

void
Ring2_Test_registerPairTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Library.Collections.Test.Pair",
                                  crt_strlen("Ring2.Library.Collections.Test.Pair"));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("1",
                                                                             crt_strlen("1"))),
                      &test1);
}
