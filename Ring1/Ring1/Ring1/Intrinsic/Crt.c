/// @file Ring1/Intrinsic/Crt.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define RING1_PRIVATE (1)
#include "Ring1/Intrinsic/Crt.h"

#include <string.h> // _strdup, strlen
#include <malloc.h> // malloc, realloc, free
#include <stdlib.h> // atexit

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *
crt_malloc
  (
    size_t x
  )
{ return malloc(x); }

void *
crt_realloc
  (
    void *x,
    size_t y
  )
{ return realloc(x, y); }

void
crt_free
  (
    void* x
  )
{
  free(x);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strdup
  (
    char const* a
  )
{ return _strdup(a); }

// Provide strndup for Visual C++.
#if defined(_MSC_VER)

char*
strndup
  (
    char const* a,
    size_t l
  );

char*
strndup
  (
    const char* a,
    size_t l
  )
{
  size_t m = strnlen_s(a, l);
  char *b = (char *)malloc(m + 1);
  if (NULL == b)
    return NULL;
  b[m] = '\0';
  return (char*)memcpy(b, a, m);
}

#endif

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strndup
  (
    char const *a,
    size_t l
  )
{ return strndup(a, l); }

#if defined(_MSC_VER)
_Check_return_
#endif
int
crt_strcmp
  (
    char const* a,
    char const* b
  )
{ return strcmp(a, b); }

#if defined(_MSC_VER)
_Check_return_
#endif
size_t
crt_strlen
  (
    char const* a
  )
{ return strlen(a); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void*
crt_memcpy
  (
    void* x,
    void const* y,
    size_t n
  )
{ return memcpy(x, y, n); }

void*
crt_memset
  (
    void* p,
    int v,
    size_t n
  )
{ return memset(p, v, n); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int
crt_atexit
  (
    void (__cdecl *function)(void)
  )
{ return atexit(function); }
