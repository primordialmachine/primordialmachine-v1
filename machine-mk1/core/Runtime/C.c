/// @file Runtime/C.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/C.h"



#include <intsafe.h>
#include <malloc.h>



bool c_safe_mul_sz(size_t n, size_t m, size_t* k) {
  size_t k0;
  HRESULT r = SizeTMult(n, m, &k0);
  if (r != S_OK) {
    k0 = (size_t)-1;
  }
  if (k) *k = k0;
  return r == S_OK;
}

void *c_alloc(size_t n) {
  return malloc(n > 0 ? n : 1);
}

void *c_alloc_a(size_t n, size_t m) {
  size_t k;
  if (!c_safe_mul_sz(n, m, &k)) {
    return NULL;
  }
  return c_alloc(k);
}

void* c_realloc(void *p, size_t n) {
  if (p == NULL) {
    return NULL;
  }
  void *q = realloc(p, n > 0 ? n : 1);
  if (!q) {
    return NULL;
  }
  return q;
}

void* c_realloc_a(void* p, size_t n, size_t m) {
  size_t k;
  if (!c_safe_mul_sz(n, m, &k)) {
    return NULL;
  }
  return c_realloc(p, k);
}


void c_dealloc(void* p) {
  if (p) {
    free(p);
  }
}
