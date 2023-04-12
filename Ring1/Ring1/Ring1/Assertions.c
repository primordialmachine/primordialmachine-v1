// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Assertions.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Assertions.h"

#include <stdlib.h>
#include <stdio.h>

void _Ring1_onAssertionFailed(char const *file, int line, char const *expression) {
  fprintf(stderr, "%s:%d: internal error: assertion `%s` failed", file, line, expression);
  exit(EXIT_FAILURE);
}
