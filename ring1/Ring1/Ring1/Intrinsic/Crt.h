/// @file Ring1/Crt.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(RING1_CRT_H_INCLUDED)
#define RING1_CRT_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h> // jmp_buf

typedef jmp_buf crt_jmp_buf;

int crt_setjmp(jmp_buf x);

void crt_longjmp(jmp_buf x, int y);

void *crt_malloc(size_t x);

void* crt_realloc(void* x, size_t y);

void crt_free(void* x);

int crt_atexit(void(__cdecl *x)(void));

char* crt_strdup(char const *x);

size_t crt_strlen(char const *x);

#endif // RING1_CRT_H_INCLUDED
