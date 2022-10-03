/// @file Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif

#include "Gdl/Test1.h"
#include <stdlib.h>

int main() {
  if (Ring2_Context_startup()) {
    return EXIT_FAILURE;
  }
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_Gdl_test1();
    Ring2_popJumpTarget();
  }
  Ring1_Status status = Ring1_Status_get();
  Ring2_Context_shutdown();
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
