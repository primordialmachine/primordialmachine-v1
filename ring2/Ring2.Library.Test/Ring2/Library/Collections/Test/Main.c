/// @file Ring2/Library/Collections/Test/Main.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if defined(__cplusplus)
extern "C" {
#endif


#include "Ring1/Test.h"
#include "Ring2/Library/Collections/Test/ArrayDequeTest.h"
#include "Ring2/Library/Collections/Test/ArrayListTest.h"
#include "Ring2/Library/Collections/Test/ArrayStack.h"
#include "Ring2/Library/Collections/Test/HashMapTest.h"
#include "Ring2/Library/Collections/Test/HashSetTest.h"
#include "Ring2/Library/Collections/Test/PairTest.h"
#include <stdlib.h>


int
main
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return EXIT_FAILURE;
  }
  if (Ring2_Context_startup()) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return EXIT_FAILURE;
  }
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_Tests* tests = Ring2_Tests_create();

    Ring2_Test_registerArrayDequeTests(tests);
    Ring2_Test_registerArrayListTests(tests);
    Ring2_Test_registerArrayStackTests(tests);
    Ring2_Test_registerHashMapTests(tests);
    Ring2_Test_registerHashSetTests(tests);
    Ring2_Test_registerPairTests(tests);

    Ring2_Tests_run(tests);

    Ring2_popJumpTarget();
  }
  Ring1_Status status = Ring1_Status_get();
  Ring2_Context_shutdown();
  Ring1_Test_Context_destroy(ctx);
  ctx = NULL;
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
