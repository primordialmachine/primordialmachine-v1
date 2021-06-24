/// @file Images.package.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Images.package.h"

#include <stdint.h>

static Machine_Integer referenceCount = 0;

void Machine_Images_startup() {
  if (referenceCount == Machine_Integer_Greatest) {
    Machine_setStatus(Machine_Status_InvalidOperation);
    Machine_jump();
  }
  else if (referenceCount == 0) {
    /* ~ */
    referenceCount++;
  } else {
    referenceCount++;
  }
}

void Machine_Images_shutdown() {
  if (0 == --referenceCount) {
    /* ~ */
  }
}
