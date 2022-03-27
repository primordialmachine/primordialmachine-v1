// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include "Ring1/Intrinsic/Test/Intrinsic.h"


static int
runTests
  (
  );

static int
runTests
  (
  )
{
  return Mkx_Intrinsic_Test_runAll();
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (runTests())
  {
    return EXIT_FAILURE;
  }
  else
  {
    return EXIT_SUCCESS;
  }
}
