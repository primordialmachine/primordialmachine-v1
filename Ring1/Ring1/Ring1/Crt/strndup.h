/// @file Ring1/Crt/strndup.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CRT_STRNDUP_H_INCLUDED)
#define RING1_CRT_STRNDUP_H_INCLUDED

#include <stddef.h>

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strndup
  (
    char const *a,
    size_t l
  );

#endif // RING1_CRT_STRNDUP_H_INCLUDED
