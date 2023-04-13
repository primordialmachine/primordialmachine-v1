/// @file Ring1/Crt/setjmp.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CRT_SETJMP_H_INCLUDED)
#define RING1_CRT_SETJMP_H_INCLUDED

#include <setjmp.h> // jmp_buf

typedef jmp_buf crt_jmp_buf;

int
crt_setjmp
  (
    jmp_buf x
  );

#if defined(_MSC_VER)
__declspec(noreturn)
#endif
void
crt_longjmp
  (
    crt_jmp_buf x,
    int y
  );

#endif // RING1_CRT_SETJMP_H_INCLUDED
