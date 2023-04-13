/// @file Ring1/Crt/strdup.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CRT_STRDUP_H_INCLUDED)
#define RING1_CRT_STRDUP_H_INCLUDED

#if defined(_MSC_VER)
#include <sal.h>
#endif

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strdup
  (
    char const *a
  );

#endif // RING1_CRT_STRDUP_H_INCLUDED