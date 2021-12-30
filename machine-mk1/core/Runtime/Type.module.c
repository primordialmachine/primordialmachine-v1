#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Type.module.h"

#include "Runtime/Gc/Gc.h"

void _Type_visit(Machine_Type* self) {
  for (size_t i = 0, n = self->children.size; i < n; ++i) {
    Machine_Type* element = self->children.elements[i];
    Machine_Gc_visit(element);
  }
}

void _Type_finalize(Machine_Type* self) {
  if (self->children.elements) {
    Machine_Eal_Memory_deallocate(self->children.elements);
    self->children.elements = NULL;
  }
  if (self->typeRemoved) {
    self->typeRemoved();
  }
}
