/// @file Ring1/Crt/atexit.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CRT_ATEXIT_H_INCLUDED)
#define RING1_CRT_ATEXIT_H_INCLUDED

int
crt_atexit
  (
    void(__cdecl* x)(void)
  );

#endif // RING1_CRT_ATEXIT_H_INCLUDED
