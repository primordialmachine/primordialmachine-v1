#define MACHINE_EAL_PRIVATE (1)
#include "Eal/Memory.h"



#include "Eal/multiplySafe.h"
#include <malloc.h> // malloc, realloc, free
#include <memory.h> // memmove, memcpy



void* Machine_Eal_Memory_allocate(size_t n) {
  return malloc(n > 0 ? n : 1);
}

void* Machine_Eal_Memory_allocateArray(size_t n, size_t m) {
  size_t l;
  if (!Machine_Eal_multiplySafe_sz(&l, n, m)) {
    return NULL;
  }
  return Machine_Eal_Memory_allocate(l);
}

void* Machine_Eal_Memory_reallocate(void* p, size_t n) {
  if (p == NULL) {
    return NULL;
  }
  void* q = realloc(p, n > 0 ? n : 1);
  if (!q) {
    return NULL;
  }
  return q;
}

void* Machine_Eal_Memory_reallocateArray(void* p, size_t n, size_t m) {
  size_t l;
  if (!Machine_Eal_multiplySafe_sz(&l, n, m)) {
    return NULL;
  }
  return Machine_Eal_Memory_reallocate(p, l);
}

void Machine_Eal_Memory_deallocate(void* p) {
  if (p) {
    free(p);
  }
}

void Machine_Eal_Memory_copy(void* p, void const* q, size_t n, bool overlap) {
  if (overlap) {
    memmove(p, q, n);
  } else {
    memcpy(p, q, n);
  }
}

int Machine_Eal_Memory_compare(void const* p, void const* q, size_t n) {
  return memcmp(p, q, n);
}

void Machine_Eal_Memory_zero(void* p, size_t n) {
  memset(p, 0, n);
}

void* Machine_Eal_Memory_clone(void* p, size_t n) {
  void *q = Machine_Eal_Memory_allocate(n);
  if (NULL == q) {
    return NULL;
  }
  Machine_Eal_Memory_copy(q, p, n, false);
  return q;
}

void* Machine_Eal_Memory_cloneArray(void* p, size_t n, size_t m) {
  size_t l;
  if (!Machine_Eal_multiplySafe_sz(&l, n, m)) {
    return NULL;
  }
  return Machine_Eal_Memory_clone(p, l);
}
