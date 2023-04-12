/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os_memory.h"

#include "Ring1/Memory.h"
#include "cc_os.h"
#include <malloc.h> // For malloc() and free().
#include <memory.h> // For memset().
#include <stdio.h>  // For printf() and stderr.

/// @brief If defined and @a true:
/// - Tag each memory block with its size.
/// - Track allocated Bytes.
/// - Allow for dumping the allocated Bytes at any point.
#define WITH_TAG (1)

#if defined(WITH_TAG) && 1 == WITH_TAG
typedef struct cc_tag
{
  size_t size;
} cc_tag;

static size_t allocated = 0;

static cc_tag* T(void* p)
{
  return ((cc_tag *)p) - 1;
}

static void* P(cc_tag* t)
{
  return t + 1;
}

#endif

static Ring1_Memory_ModuleHandle g_memory_module_handle = Ring1_Memory_ModuleHandle_Invalid;

bool cc_startup_memory()
{
  g_memory_module_handle = Ring1_Memory_ModuleHandle_acquire();
  if (!g_memory_module_handle) {
    return false;
  }
  return true;
}

void cc_shutdown_memory()
{
  Ring1_Memory_ModuleHandle_relinquish(g_memory_module_handle);
  g_memory_module_handle = Ring1_Memory_ModuleHandle_Invalid;
}

void cc_log_memory()
{
#if defined(WITH_TAG) && 1 == WITH_TAG
  size_t mb = 0, kb = 0, b = 0;
  b = allocated;
  while (b > 1000)
  {
    b -= 1000;
    kb += 1;
  }
  while (kb > 1000)
  {
    kb -= 1000;
    mb += 1;
  }
  fprintf(stdout, "[memory manager] allocated %zu MB, %zu KB, %zu B\n", mb, kb, b);
#endif
}

#define CHECK_OVERFLOW(a, b) ((a) > 0 && (SIZE_MAX / (a)) < (b))

void* cc_zalloc(size_t n)
{
  void* p = cc_alloc(n);
  if (!p) return NULL;
  memset(p, 0, n);
  return p;
}

void* cc_zalloc_a(size_t n, size_t m)
{
  if (CHECK_OVERFLOW(n, m))
  {
    cc_set_status(CC_EOVERFLOW);
    return NULL;
  }
  return cc_zalloc(n * m);
}


void* cc_alloc(size_t n)
{
#if defined(WITH_TAG) && 1 == WITH_TAG
  cc_tag* t = malloc(sizeof(cc_tag) + n);
  if (!t)
  {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, n);
    cc_set_status(CC_ENOMEM);
    return NULL;
  }
  t->size = n;
  allocated += n;
  return P(t);
#else
  void* p = malloc(n > 0 ? n : 1);
  if (!p)
  {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, n);
    cc_set_status(CC_ENOMEM);
    return NULL;
  }
  return p;
#endif
}

void *cc_alloc_a(size_t n, size_t m)
{
  if (CHECK_OVERFLOW(n, m))
  {
    cc_set_status(CC_EOVERFLOW);
    return NULL;
  }
  return cc_alloc(n * m);
}

void *cc_realloc(void* p, size_t n)
{
  if (!p)
  {
    cc_set_status(CC_EINVAL);
    return NULL;
  }
#if defined(WITH_TAG) && 1 == WITH_TAG
  cc_tag* t = T(p);
  size_t old_size = t->size, new_size = n;
  cc_tag* s = realloc(t, sizeof(cc_tag) + n);
  if (!s)
  {
    cc_set_status(CC_ENOMEM);
    return NULL;
  }
  s->size = n;
  allocated -= old_size;
  allocated += new_size;
  return P(s);
#else
  void *q = realloc(p, n > 0 ? n : 1);
  if (!q)
  {
    cc_set_status(CC_ENOMEM);
    return NULL;
  }
  return q;
#endif
}

void* cc_realloc_a(void* p, size_t n, size_t m)
{
  if (CHECK_OVERFLOW(n, m))
  {
    cc_set_status(CC_EOVERFLOW);
    return NULL;
  }
  return cc_realloc(p, n * m);
}

void cc_dealloc(void* p)
{
  if (!p) return;
#if defined(WITH_TAG) && 1 == WITH_TAG
  cc_tag* t = T(p);
  allocated -= t->size;
  free(t);
#else
  free(p);
#endif
}


#undef CHECK_OVERFLOW
