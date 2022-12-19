/// @file Ring1/Crt.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(RING1_CRT_H_INCLUDED)
#define RING1_CRT_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h> // jmp_buf

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *
crt_malloc
  (
    size_t x
  );

void*
crt_realloc
  (
    void* x,
    size_t y
  );

void
crt_free
  (
    void* x
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strdup
  (
    char const *a
  );
  
#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strndup
  (
    char const *a,
    size_t l
  );

#if defined(_MSC_VER)
_Check_return_
#endif
int
crt_strcmp
  (
    char const* a,
    char const* b
  );

#if defined(_MSC_VER)
_Check_return_
#endif
size_t
crt_strlen
  (
    char const *a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void*
crt_memcpy
  (
    void* x,
    void const* y,
    size_t n
  );

void*
crt_memset
  (
    void* p,
    int v,
    size_t n
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int
crt_atexit
  (
    void(__cdecl *x)(void)
  );

/// @brief printf/scanf-style format specifier for size_t.
/// @remark This is necessary because of Redmon Retards' (aka Microsoft's) Visual C++.
#if defined(_MSC_VER)
  #define PRIuZ "Iu"
#else
  #define PRIuZ "zu"
#endif

#endif // RING1_CRT_H_INCLUDED
