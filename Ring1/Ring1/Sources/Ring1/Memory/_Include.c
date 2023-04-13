// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_MEMORY_PRIVATE (1)
#include "Ring1/Memory/_Include.h"
#undef RING1_MEMORY_PRIVATE

#include "Ring1/Intrinsic/Multiply/multiply.h"

#include <stdlib.h> // For EXIT_FAILURE.
#include <string.h> // For memcpy().
#include <stdarg.h> // For va_list, va_start, va_end.
#include <malloc.h>
#include <stdio.h>

#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
#include "Ring1/Memory/Statistics.h"
#endif

#include "Ring1/Status.h"
#include "Ring1/Memory/Windows/getPageSize.h"

static void error(const char* file, int line, char const* format, ...) {
  fprintf(stderr, "%s:%d", __FILE__, __LINE__);
  fprintf(stderr, ": ");
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

#pragma push_macro("ERROR")
#if defined(ERROR)
  #undef ERROR
#endif
#define ERROR(FORMAT, ...) error(__FILE__, __LINE__, FORMAT, __VA_ARGS__)

#define CHECK_NOTNULL(EXPRRESSION) \
  if (Ring1_Unlikely(NULL == (EXPRRESSION))) { \
    ERROR("invalid argument `%s`\n", #EXPRRESSION); \
    Ring1_Status_set(Ring1_Status_InvalidArgument); \
    return Ring1_Result_Failure; \
  }

static_assert(SIZE_MAX <= UINT64_MAX, "SIZE_MAX must be smalle than or equal to UINT64_MAX");


static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, Memory, initializeModule, uninitializeModule)

#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
static Ring1_Memory_Statistics g_statistics = { 0 };
#endif

static size_t g_pageSize = 0;

static Ring1_Result
initializeModule
  (
  )
{
#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
  Ring1_Memory_Statistics_initialize(&g_statistics);
#endif
  if (Ring1_Memory_Windows_getPageSize(&g_pageSize)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
  Ring1_Memory_Statistics_uninitialize(&g_statistics);
#endif
}

static Ring1_NoDiscardReturn() Ring1_Result
allocate
  (
    void** result,
    size_t n
  )
{
  CHECK_NOTNULL(result);
#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
  if (SIZE_MAX - sizeof(Ring1_Memory_Statistics_Tag) < n) {
    ERROR("unable to allocate %zu Bytes\n", n);
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Statistics_Tag* tag = malloc(sizeof(Ring1_Memory_Statistics_Tag) + n);
  if (!tag) {
    ERROR("unable to allocate % zu Bytes\n ", n);
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  tag->n = n;
  Ring1_Memory_Statistics_allocated(&g_statistics, n, sizeof(Ring1_Memory_Statistics_Tag));
  *result = tag + 1;
#else
#if !defined(_MSC_VER)
  // Visual C++ allows for zero-sized allocations using malloc as stated here:
  // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc?view=vs-2019.
  // For other compiles, take the safe-path for now.
  n = n > 0 ? n : 1;
#endif
  void* p = malloc(n);
  if (!p) {
    ERROR("unable to allocate %zu Bytes\n", n);
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  *result = p;
#endif
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_allocate
  (
    void **result,
    size_t n
  )
{
  CHECK_NOTNULL(result)
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  if (allocate(result, n)) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_allocateArray
  (
    void **result,
    size_t numberOfElements,
    size_t elementSize
  )
{
  CHECK_NOTNULL(result);
  size_t blockSize;
  if (Ring1_Intrinsic_multiply_sz(&blockSize, numberOfElements, elementSize)) {
    ERROR("unable to allocate %zu*%zu Bytes\n", numberOfElements, elementSize);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  if (allocate(result, blockSize)) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
reallocate
  (
    void** result,
    void* block,
    size_t blockSize
  )
{
  CHECK_NOTNULL(result);
  CHECK_NOTNULL(block);
#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
  Ring1_Memory_Statistics_Tag* oldTag = ((Ring1_Memory_Statistics_Tag*)(block)) - 1;
  size_t oldSize = oldTag->n, newSize = blockSize;
  Ring1_Memory_Statistics_Tag* newTag = realloc(oldTag, sizeof(Ring1_Memory_Statistics_Tag) + newSize);
  if (Ring1_Unlikely(!newTag)) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Statistics_reallocated(&g_statistics,
                                      oldSize,
                                      newSize,
                                      sizeof(Ring1_Memory_Statistics_Tag),
                                      sizeof(Ring1_Memory_Statistics_Tag));
  *result = newTag + 1;
#else
  blockSize = blockSize > 0 ? blockSize : 1;
  void* q = realloc(block, blockSize);
  if (!q) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  *result = q;
#endif
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_reallocate
  (
    void **result,
    void* p,
    size_t blockSize
  )
{
  CHECK_NOTNULL(result);
  CHECK_NOTNULL(p);
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  if (reallocate(result, p, blockSize)) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_reallocateArray
  (
    void **result,
    void* p,
    size_t numberOfElements,
    size_t elementSize
  )
{
  CHECK_NOTNULL(result);
  CHECK_NOTNULL(p);
  size_t blockSize;
  if (Ring1_Intrinsic_multiply_sz(&blockSize, numberOfElements, elementSize)) {
    ERROR("unable to allocate %zu * %zu Bytes\n",
          numberOfElements,
          elementSize);
    return Ring1_Result_Failure;
  }
  return Ring1_Memory_reallocate(result, p, blockSize);
}

Ring1_Result
Ring1_Memory_deallocate
  (
    void *p
  )
{
  if (!p) {
    return Ring1_Result_Success;
  }
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Success;
  }
#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
  Ring1_Memory_Statistics_Tag* tag = ((Ring1_Memory_Statistics_Tag*)p) - 1;
  Ring1_Memory_Statistics_deallocated(&g_statistics, tag->n, sizeof(Ring1_Memory_Statistics_Tag));
  free(tag);
#else
  free(p);
#endif
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_zeroFill
  (
    void *p,
    size_t n
  )
{
  CHECK_NOTNULL(p);
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  memset(p, 0, n);
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_zeroFillArray
  (
    void* p,
    size_t numberOfElements,
    size_t elementSize
  )
{
  CHECK_NOTNULL(p);
  size_t blockSize;
  if (Ring1_Intrinsic_multiply_sz(&blockSize, numberOfElements, elementSize)) {
    ERROR("unable to allocate %zu*%zu Bytes\n", numberOfElements, elementSize);
    return Ring1_Result_Failure;
  }
  return Ring1_Memory_zeroFill(p, blockSize);
}

static Ring1_Result
Ring1_compareMemoryLexicographic1
  (
    int *result,
    const unsigned char *p,
    size_t n,
    const unsigned char *q,
    size_t m
  )
{
  if (p == q && n == m) {
    *result = 0;
    return Ring1_Result_Success;
  }
  for (size_t i = 0; i < n && i < m; ++i)
  {
    unsigned char a = p[i],
                  b = q[i];
    if (a != b)
    {
      *result = a < b ? -1 : +1;
      return Ring1_Result_Success;
    }
  }
  *result = n < m ? -1 : (n > m ? +1 : 0);
  return Ring1_Result_Success;
}

static Ring1_Result
Ring1_compareMemoryLexicographic2
  (
    int *result,
    const unsigned char *p,
    size_t n,
    const unsigned char *q,
    size_t m
  )
{
  if (p == q && n == m) {
    *result = 0;
    return Ring1_Result_Success;
  }
  size_t i = 0;
  size_t k = n < m ? n : m;
  const unsigned char *x = p, *y = q;
  // Skip until
  // - the end of at least one string was reached or
  // - the strings differ in the character at index i.
  while (i < k && p[i] == q[i])
  {
    i++;
  }
  // Both strings are equal length.
  if (n == m)
  {
    // The end of both strings was reached.
    if (i == k)
    {
      // Both strings are equal.
      *result = 0;
      return Ring1_Result_Success;
    }
    // The strings differ in the character at index i.
    *result = p[i] < q[i] ? -1 : +1;
    return Ring1_Result_Success;
  }
  // Both strings are different length.
  else
  {
    // The strings differ in the character at index i.
    if (i < k)
    {
      *result = p[i] < q[i] ? -1 : +1;
      return Ring1_Result_Success;
    }
    // The end of the shorter string was reached.
    else
    {
      *result = n < m ? -1 : (n > m ? +1 : 0);
      return Ring1_Result_Success;
    }
  }
}

static Ring1_Result
Ring1_compareMemoryColexicographic1
  (
    int *result,
    const unsigned char *p,
    size_t n,
    const unsigned char *q,
    size_t m
  )
{
  if (p == q && n == m) {
    *result = 0;
    return Ring1_Result_Success;
  }
  for (size_t i = n, j = m; i > 0 && j > 0; --i, --j)
  {
    unsigned char a = p[i],
                  b = q[j];
    if (a != b)
    {
      *result = a < b ? -1 : +1;
      return Ring1_Result_Success;
    }
  }
  *result = n < m ? -1 : (n > m ? +1 : 0);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_compare
  (
    int *result,
    const void* p,
    size_t n,
    const void* q,
    size_t m,
    int flags
  )
{
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    Ring1_Status_set(Ring1_Status_NotInitialized);
    return Ring1_Result_Failure;
  }
  switch (flags) {
    case Ring1_Memory_Compare_Colexicographic: {
      int temporary;
      Ring1_Result r = Ring1_compareMemoryColexicographic1(&temporary, (const unsigned char*)p, n, (const unsigned char*)q, m);
      *result = temporary;
      Ring1_Memory_Module_unlock();
      return r;
    } break;
    case Ring1_Memory_Compare_Lexicographic: {
      int temporary;
      Ring1_Result r = Ring1_compareMemoryLexicographic1(&temporary, (const unsigned char*)p, n, (const unsigned char*)q, m);
      *result = temporary;
      Ring1_Memory_Module_unlock();
      return r;
    } break;
    default: {
      Ring1_Memory_Module_unlock();
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      return Ring1_Result_Failure;
    } break;
  };
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copyFast
  (
    void *p,
    const void *q,
    size_t n
  )
{
  CHECK_NOTNULL(p);
  CHECK_NOTNULL(q);
  if (Ring1_Unlikely(!n)) {
    return Ring1_Result_Success;
  }
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized())
  {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  memcpy(p, q, n);
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copyArrayFast
  (
    void* p,
    const void* q,
    size_t numberOfElements,
    size_t elementSize
  )
{
  CHECK_NOTNULL(p);
  CHECK_NOTNULL(q);
  size_t blockSize;
  if (Ring1_Intrinsic_multiply_sz(&blockSize, numberOfElements, elementSize)) {
    ERROR("unable to copy %zu*%zu Bytes\n", numberOfElements, elementSize);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!blockSize)) {
    return Ring1_Result_Success;
  }
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized())
  {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  memcpy(p, q, blockSize);
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copySlow
  (
    void *p,
    const void *q,
    size_t n
  )
{
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized())
  {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  memmove(p, q, n);
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copyArraySlow
  (
    void* target,
    const void* source,
    size_t numberOfElements,
    size_t elementSize
  )
{
  CHECK_NOTNULL(target);
  CHECK_NOTNULL(source);
  size_t blockSize;
  if (Ring1_Intrinsic_multiply_sz(&blockSize, numberOfElements, elementSize)) {
    ERROR("unable to copy %zu*%zu Bytes\n", numberOfElements, elementSize);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  memmove(target, source, blockSize);
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_getPageSze
  (
    size_t *result
  )
{
  CHECK_NOTNULL(result);
  Ring1_Memory_Module_lock();
  if (!Ring1_Memory_Module_isInitialized()) {
    Ring1_Memory_Module_unlock();
    return Ring1_Result_Failure;
  }
  *result = g_pageSize;
  Ring1_Memory_Module_unlock();
  return Ring1_Result_Success;
}

#pragma pop_macro("ERROR")
