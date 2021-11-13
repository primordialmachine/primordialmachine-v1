/// @file Collections/Test/Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif

#include "_Runtime.h"
#include "Collections/Test/PairTest.h"
#include "Collections/Test/ListTest.h"
#include "Collections/Test/MapTest.h"
#include "Collections/Test/QueueTest.h"
#include <stdlib.h>

int main() {
  if (Machine_startup()) {
    return EXIT_FAILURE;
  }
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_Collections_Test_PairTest_test1();
    Machine_Collections_Test_ListTest_test1();
    Machine_Collections_Test_MapTest_test1();
    Machine_Collections_Test_QueueTest_test1();
    Machine_Collections_Test_QueueTest_test2();
    Machine_Collections_Test_QueueTest_test3();
    Machine_popJumpTarget();
  }
  Machine_StatusValue status = Machine_getStatus();
  Machine_shutdown();
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
