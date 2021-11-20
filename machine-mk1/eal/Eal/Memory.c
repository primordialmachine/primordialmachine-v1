#define MACHINE_EAL_PRIVATE (1)
#include "Eal/Memory.h"



#include "Eal/multiplySafe.h"
#include <malloc.h>



void* Machine_Eal_alloc(size_t n) {
  return malloc(n > 0 ? n : 1);
}

void* Machine_Eal_alloc_a(size_t n, size_t m) {
  size_t l;
  if (!Machine_Eal_multiplySafe_sz(&l, n, m)) {
    return NULL;
  }
  return Machine_Eal_alloc(l);
}

void* Machine_Eal_realloc(void* p, size_t n) {
  if (p == NULL) {
    return NULL;
  }
  void* q = realloc(p, n > 0 ? n : 1);
  if (!q) {
    return NULL;
  }
  return q;
}

void* Machine_Eal_realloc_a(void* p, size_t n, size_t m) {
  size_t l;
  if (!Machine_Eal_multiplySafe_sz(&l, n, m)) {
    return NULL;
  }
  return Machine_Eal_realloc(p, l);
}

void Machine_Eal_dealloc(void* p) {
  if (p) {
    free(p);
  }
}
