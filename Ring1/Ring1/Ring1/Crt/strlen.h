/// @file Ring1/Crt/strlen.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CRT_STRLEN_H_INCLUDED)
#define RING1_CRT_STRLEN_H_INCLUDED

#include <stddef.h>

#if defined(_MSC_VER)
_Check_return_
#endif
size_t
crt_strlen
  (
    char const *a
  );

#endif // RING1_CRT_STRLEN_H_INCLUDED