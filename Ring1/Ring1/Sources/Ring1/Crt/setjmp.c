/// @file Ring1/Crt/setjmp.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/setjmp.h"

int 
crt_setjmp
  (
    jmp_buf x
  )
{ return setjmp(x); }

#if defined(_MSC_VER)
__declspec(noreturn)
#endif
void
crt_longjmp
  (
    crt_jmp_buf x,
    int y
  )
{ longjmp(x, y); }
