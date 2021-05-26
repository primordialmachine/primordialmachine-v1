/// @file Runtime/IO.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/IO.h"


#include "Runtime/String.h"
#include <string.h>


FILE* Machine_openFileRead(Machine_String* path) {
  MACHINE_ASSERT_NOTNULL(path);
  // Unconditionally append a zero terminator.
  path = Machine_String_concatenate(path, Machine_String_create("", strlen("") + 1));
  FILE* fd = fopen(Machine_String_getBytes(path), "rb");
  if (!fd) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  return fd;
}

void Machine_closeFile(FILE* fd) {
  if (fd && fd != stdin && fd != stdout && fd != stderr) {
    fclose(fd);
  }
}
