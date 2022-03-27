#define MACHINE_EAL_PRIVATE (1)
#include "Eal/Memory.h"



#include "Ring1/Intrinsic/Multiply/multiply.h"
#include <malloc.h> // malloc, realloc, free
#include <memory.h> // memmove, memcpy



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

void* Machine_Eal_Memory_clone(void* p, size_t n) {
  void* q = NULL;
  if (Ring1_Memory_allocate(&q, n)) {
    return NULL;
  }
  Machine_Eal_Memory_copy(q, p, n, false);
  return q;
}

void* Machine_Eal_Memory_cloneArray(void* p, size_t n, size_t m) {
  size_t l;
  if (Ring1_Intrinsic_multiply_sz(&l, n, m)) {
    return NULL;
  }
  return Machine_Eal_Memory_clone(p, l);
}
