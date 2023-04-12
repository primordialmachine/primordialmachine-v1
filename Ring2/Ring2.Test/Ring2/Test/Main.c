// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Main.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if defined(__cplusplus)
extern "C" {
#endif


#include "Ring1/Test.h"
#include "Ring1/Status.h"
#include "Ring2/_Include.h"
#include "Ring2/Test/Value.h"
#include "Ring2/Test/Stack.h"
#include "Ring2/Test/String.h"
#include "Ring2/Test/Instructions.h"
#include <stdlib.h>


int
main
  (
    int argc,
    char** argv
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
  Ring2_Tests* tests = NULL;

  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    tests = Ring2_Tests_create();
    Ring2_Gc_lock(tests);
    Ring2_JumpTarget jumpTarget2;
    Ring2_pushJumpTarget(&jumpTarget2);
    if (!setjmp(jumpTarget.environment)) {
      Ring2_Test_registerValueTests(tests);
      Ring2_Test_registerStackTests(tests);
      Ring2_Test_registerStringTests(tests);
      Ring2_Test_registerInstructionTests(tests);
      Ring2_Tests_run(tests);
      Ring2_popJumpTarget();
      Ring2_Gc_unlock(tests);
    } else {
      Ring2_popJumpTarget();
      Ring2_Gc_unlock(tests);
      Ring2_jump();
    }
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    Ring2_Gc_unlock(tests);
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
