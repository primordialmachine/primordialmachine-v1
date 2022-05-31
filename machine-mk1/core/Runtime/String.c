/// @file Runtime/String.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/String.h"

#include "Runtime/Assertions.h"
#include "Runtime/Gc/Gc.h"
#include "Ring2/JumpTarget.h"
#include "Runtime/Status.h"

struct Machine_String {
  size_t hashValue;
  size_t n;
  char p[];
};

static size_t hashBytesToSz(char const *p, size_t n) {
  size_t hashValue = n;
  for (size_t i = 0; i < n; ++i) {
    hashValue = p[i] + hashValue * 37;
  }
  return hashValue;
}

// Maximal length, in Bytes, of a memory block.
#define MACHINE_MEMORYBLOCK_MAXIMALLENGTH \
  (SIZE_MAX < INT64_MAX ? SIZE_MAX : INT64_MAX)

/// Maximal length, in Bytes, of a string.
#define MACHINE_STRING_MAXIMALLENGTH \
  (MACHINE_MEMORYBLOCK_MAXIMALLENGTH - sizeof(Machine_String))

static Ring2_Gc_Type const g_gcType = {
  .finalize = (Ring2_Gc_FinalizeCallback*)NULL,
  .visit = (Ring2_Gc_VisitCallback*)NULL,
};

Machine_String* Machine_String_create(char const* p, size_t n) {
  if (n > MACHINE_STRING_MAXIMALLENGTH) {
    Machine_setStatus(Machine_Status_TooLong);
    Ring2_jump();
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .suffixSize = sizeof(Machine_String) + n,
    .type = &g_gcType,
  };
  Machine_String* self = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Ring2_jump();
  }
  Ring1_Memory_copyFast(self->p, p, n);
  self->n = n;
  self->hashValue = hashBytesToSz(self->p, self->n);
  return self;
}

Machine_String* Machine_String_concatenate(Machine_String const* self,
                                           Machine_String const* other) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(other);
  if (MACHINE_STRING_MAXIMALLENGTH - self->n < other->n) {
    Machine_setStatus(Machine_Status_TooLong);
    Ring2_jump();
  }
  size_t m = self->n + other->n;
  if (m > MACHINE_STRING_MAXIMALLENGTH) {
    Machine_setStatus(Machine_Status_TooLong);
    Ring2_jump();
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .suffixSize = sizeof(Machine_String) + m,
    .type = &g_gcType,
  };
  Machine_String* c = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Ring2_jump();
  }
  Ring1_Memory_copyFast(c->p, self->p, self->n);
  Ring1_Memory_copyFast(c->p + self->n, other->p, other->n);
  c->n = m;
  c->hashValue = hashBytesToSz(c->p, c->n);
  return c;
}

bool Machine_String_isEqualTo(Machine_String const* self, Machine_String const* other) {
  if (self == other)
    return true;
  if (self->n == other->n && self->hashValue == other->hashValue) {
    int temporary;
    Ring1_Memory_compare(&temporary, self->p, self->n, other->p, other->n, Ring1_Memory_Compare_Lexicographic);
    return !temporary;
  }
  return false;
}

Machine_Integer Machine_String_getHashValue(Machine_String const* self) {
  uint64_t v = (uint64_t)self->hashValue;
  return (Machine_Integer)(v >> 1);
}

const char* Machine_String_getBytes(Machine_String const* self) {
  return self->p;
}

size_t Machine_String_getNumberOfBytes(Machine_String const* self) {
  return self->n;
}
