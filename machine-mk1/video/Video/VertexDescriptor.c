/// @file Video/VertexDescriptor.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/VertexDescriptor.h"

#include "Ring1/Status.h"

#define TRACE_VISIT (0)

struct Machine_VertexDescriptor_Class {
  Machine_Object_Class __parent;
};

struct Machine_VertexDescriptor {
  Machine_Object __parent;

  size_t n;
  Machine_VertexElementSemantics* p;
};

#if defined(TRACE_VISIT) && (1) == TRACE_VISIT
static void Machine_VertexDescriptor_visit(Machine_VertexDescriptor* self);
#endif

static void Machine_VertexDescriptor_construct(Machine_VertexDescriptor* self,
                                               size_t numberOfArguments,
                                               Machine_Value const* arguments);

static void Machine_VertexDescriptor_destruct(Machine_VertexDescriptor* self);

#if defined(TRACE_VISIT) && (1) == TRACE_VISIT
MACHINE_DEFINE_CLASSTYPE(Machine_VertexDescriptor, Machine_Object, &Machine_VertexDescriptor_visit,
                         &Machine_VertexDescriptor_construct, &Machine_VertexDescriptor_destruct,
                         NULL, NULL)
#else
MACHINE_DEFINE_CLASSTYPE(Machine_VertexDescriptor, Machine_Object, NULL,
                         &Machine_VertexDescriptor_construct, &Machine_VertexDescriptor_destruct,
                         NULL, NULL)
#endif

#if defined(TRACE_VISIT) && (1) == TRACE_VISIT
static void Machine_VertexDescriptor_visit(Machine_VertexDescriptor* self) {
  Machine_log(Machine_LogFlags_ToTrace, __FILE__, __LINE__, "Machine.VertexDescriptor.visit()\n");
}
#endif

static void Machine_VertexDescriptor_construct(Machine_VertexDescriptor* self,
                                               size_t numberOfArguments,
                                               Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->n = 0;
  self->p = NULL;
  if (Ring1_Memory_allocate(&self->p, 0)) {
    Ring2_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_VertexDescriptor_getType());
}

static void Machine_VertexDescriptor_destruct(Machine_VertexDescriptor* self) {
  if (self->p) {
    Ring1_Memory_deallocate(self->p);
    self->p = NULL;
  }
}

Machine_VertexDescriptor* Machine_VertexDescriptor_create() {
  Machine_ClassType* ty = Machine_VertexDescriptor_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Ring2_Void_Void } };
#if defined(TRACE_VISIT) && (1) == TRACE_VISIT
  Machine_VertexDescriptor* self
      = (Machine_VertexDescriptor*)Machine_allocateClassObjec(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
#else
  Machine_VertexDescriptor* self
      = (Machine_VertexDescriptor*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
#endif
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

Machine_VertexElementSemantics Machine_VertexDescriptor_getElementSemantics(
    Machine_VertexDescriptor* self, size_t index) {
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

void Machine_VertexDescriptor_insert(Machine_VertexDescriptor* self, size_t index,
                                     Machine_VertexElementSemantics semantics) {
  size_t n = self->n + 1;
  Machine_VertexElementSemantics* p = NULL;
  if (Ring1_Memory_reallocateArray(&p, self->p, n, sizeof(Machine_VertexElementSemantics))) {
    Ring2_jump();
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
    Ring1_Memory_copySlow(p + index + 1, p + index,
                          sizeof(Machine_VertexElementSemantics) * (self->n - index));
  }
  p[index] = semantics;
  self->p = p;
  self->n = n;
}

void Machine_VertexDescriptor_append(Machine_VertexDescriptor* self,
                                     Machine_VertexElementSemantics semantics) {
  Machine_VertexDescriptor_insert(self, self->n, semantics);
}

void Machine_VertexDescriptor_prepend(Machine_VertexDescriptor* self,
                                      Machine_VertexElementSemantics semantics) {
  Machine_VertexDescriptor_insert(self, 0, semantics);
}
