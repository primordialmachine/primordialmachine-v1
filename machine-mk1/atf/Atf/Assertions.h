/// @file Atf/Assertions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_ATF_ASSERTIONS_H_INCLUDED)
#define MACHINE_ATF_ASSERTIONS_H_INCLUDED



#include "_Runtime.h"



#define MACHINE_ATF_ASSERT(e) \
  if (!(e)) { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "test assertion `%s` failed\n", #e); \
    Machine_setStatus(Machine_Status_TestFailed); \
    Machine_jump(); \
  }



#endif // MACHINE_ATF_ASSERTIONS_H_INCLUDED
