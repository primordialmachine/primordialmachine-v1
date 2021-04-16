#include "VertexDescriptor.h"



#include <malloc.h>
#include <memory.h>



#define TRACE_VISIT (0)



struct Machine_VertexDescriptor {
  size_t n;
  Machine_VertexElementSemantics* p;
};

#if defined(TRACE_VISIT) && (1) == TRACE_VISIT
static void visit(Machine_VertexDescriptor* self) {
  Machine_log(Machine_LogFlags_ToTrace, __FILE__, __LINE__, "Machine.VertexDescriptor.visit()\n");
}
#endif

static void finalize(Machine_VertexDescriptor* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
}

Machine_VertexDescriptor* Machine_VertexDescriptor_create() {
#if defined(TRACE_VISIT) && (1) == TRACE_VISIT
  Machine_VertexDescriptor* self = Machine_allocate(sizeof(Machine_VertexDescriptor), (void (*)(void*)) & visit, (void (*)(void*)) & finalize);
#else
  Machine_VertexDescriptor* self = Machine_allocate(sizeof(Machine_VertexDescriptor), NULL, (void (*)(void*)) & finalize);
#endif
  if (!self) return NULL;
  self->n = 0;
  self->p = NULL;
  return self;
}

size_t Machine_VertexDescriptor_getVertexSize(Machine_VertexDescriptor* self) {
  if (self->n == 0) {
    return 0;
  }
  size_t size = 0;
  for (size_t i = 0, n = self->n; i < n; ++i) {
    switch (self->p[i]) {
    case Machine_VertexElementSemantics_XfYf:
      size += sizeof(float) * 2;
      break;
    case Machine_VertexElementSemantics_RfGfBf:
      size += sizeof(float) * 3;
      break;
    case Machine_VertexElementSemantics_UfVf:
      size += sizeof(float) * 2;
      break;
    };
  }
  return size;
}

size_t Machine_VertexDescriptor_getNumberOfElements(Machine_VertexDescriptor* self) {
  return self->n;
}

Machine_VertexElementSemantics Machine_VertexDescriptor_getElementSemantics(Machine_VertexDescriptor* self, size_t index) {
  return self->p[index];
}

size_t Machine_VertexDescriptor_getElementOffset(Machine_VertexDescriptor* self, size_t index) {
  size_t offset = 0;
  for (size_t i = 0, n = index; i < n; ++i) {
    switch (self->p[i]) {
    case Machine_VertexElementSemantics_XfYf:
      offset += sizeof(float) * 2;
      break;
    case Machine_VertexElementSemantics_RfGfBf:
      offset += sizeof(float) * 3;
      break;
    case Machine_VertexElementSemantics_UfVf:
      offset += sizeof(float) * 2;
      break;
    };
  }
  return offset;
}

void Machine_VertexDescriptor_insert(Machine_VertexDescriptor* self, size_t index, Machine_VertexElementSemantics semantics) {
  size_t n = self->n + 1;
  Machine_VertexElementSemantics* p = realloc(self->p, n * sizeof(Machine_VertexElementSemantics));
  if (!p) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  if (index < self->n) {
    // [a, b, c] insert x at index 1 => 1 smaller than size = 3 =>
    // move 3 - 1 = 2 elements from index = 1 to index + 1 = 2.
    // => [a, , b, c] => [a, x, b, c]
    //
    // [a, b, c] insert x at index 2 => 2 smaller than size = 3 =>
    // move 3 - 2 = 1 elements from index = 2 to index + 1 = 3.
    // => [a, b, ,c] => [a, b, x, c]
    // ...
    memmove(p + index + 1, p + index, sizeof(Machine_VertexElementSemantics) * (self->n - index));
  }
  p[index] = semantics;
  self->p = p;
  self->n = n;
}

void Machine_VertexDescriptor_append(Machine_VertexDescriptor* self, Machine_VertexElementSemantics semantics) {
  Machine_VertexDescriptor_insert(self, self->n, semantics);
}

void Machine_VertexDescriptor_prepend(Machine_VertexDescriptor* self, Machine_VertexElementSemantics semantics) {
  Machine_VertexDescriptor_insert(self, 0, semantics);
}
