/// @file Ring3/Gdl/Test/Main.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if defined(__cplusplus)
extern "C" {
#endif

#include "Ring3/Gdl/Test/ParseTest1.h"
#include <stdlib.h>

int main() {
  if (Ring2_Context_startup()) {
    return EXIT_FAILURE;
  }
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_Tests* tests = Ring2_Tests_create();
    Ring3_Gdl_Test_registerParseTest1(tests);
    Ring2_Tests_run(tests);
    Ring2_popJumpTarget();
  }
  Ring1_Status status = Ring1_Status_get();
  Ring2_Context_shutdown();
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
