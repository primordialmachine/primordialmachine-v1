/// @file Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif

#include "Gdl/Test1.h"
#include <stdlib.h>

int main() {
  if (Machine_startup()) {
    return EXIT_FAILURE;
  }
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_GDL_test1();
    Machine_popJumpTarget();
  }
  Machine_StatusValue status = Machine_getStatus();
  Machine_shutdown();
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
