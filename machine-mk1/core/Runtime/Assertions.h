/// @file Runtime/Assertions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_ASSERTIONS_H_INCLUDED)
#define MACHINE_RUNTIME_ASSERTIONS_H_INCLUDED

#include "Ring2/JumpTarget.h"
#include "Runtime/LogModule.h"
#include "Runtime/Status.h"

#define MACHINE_ASSERT(e, s)                                                                       \
  if (!(e)) {                                                                                      \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "assertion `%s` failed\n", #e);     \
    Machine_setStatus(s);                                                                          \
    Ring2_jump();                                                                                \
  }

#define MACHINE_ASSERT_NOTNULL(e)                                                                  \
  if (!(e)) {                                                                                      \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "assertion `%s != NULL' failed\n",  \
                #e);                                                                               \
    Machine_setStatus(Machine_Status_ArgumentNull);                                                \
    Ring2_jump();                                                                                \
  }

#define MACHINE_ASSERT_UNREACHABLE()                                                               \
  Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,                                       \
              "unreachable program point reached\n");                                              \
  Machine_setStatus(Machine_Status_UnreachableProgramPointReached);                                \
  Ring2_jump();

#endif // MACHINE_RUNTIME_ASSERTIONS_H_INCLUDED
