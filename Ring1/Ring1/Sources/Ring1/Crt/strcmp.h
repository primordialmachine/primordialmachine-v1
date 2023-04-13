/// @file Ring1/Crt/strcmp.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined (RING1_CRT_STRCMP_H_INCLUDED)
#define RING1_CRT_STRCMP_H_INCLUDED

#include <stddef.h>

#if defined(_MSC_VER)
_Check_return_
#endif
int
crt_strcmp
  (
    char const* p,
    char const* q
  );

#endif // RING1_CRT_STRCMP_H_INCLUDED
