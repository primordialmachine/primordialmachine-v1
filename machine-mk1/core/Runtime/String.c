/// @file Runtime/String.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/String.h"

#include "Runtime/Assertions.h"
#include "Runtime/Gc/Gc.h"
#include "Ring2/_Include.h"
#include "Ring1/Status.h"

struct Ring2_String {
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
  (MACHINE_MEMORYBLOCK_MAXIMALLENGTH - sizeof(Ring2_String))

static Ring2_Gc_Type const g_gcType = {
  .finalize = (Ring2_Gc_FinalizeCallback*)NULL,
  .visit = (Ring2_Gc_VisitCallback*)NULL,
};

Ring2_String* Machine_String_create(char const* p, size_t n) {
  if (n > MACHINE_STRING_MAXIMALLENGTH) {
    Ring1_Status_set(Ring1_Status_TooLong);
    Ring2_jump();
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .suffixSize = sizeof(Ring2_String) + n,
    .type = &g_gcType,
  };
  Ring2_String* self = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Ring2_jump();
  }
  Ring1_Memory_copyFast(self->p, p, n);
  self->n = n;
  self->hashValue = hashBytesToSz(self->p, self->n);
  return self;
}

Ring2_String* Machine_String_concatenate(Ring2_String const* self,
                                         Ring2_String const* other) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(other);
  if (MACHINE_STRING_MAXIMALLENGTH - self->n < other->n) {
    Ring1_Status_set(Ring1_Status_TooLong);
    Ring2_jump();
  }
  size_t m = self->n + other->n;
  if (m > MACHINE_STRING_MAXIMALLENGTH) {
    Ring1_Status_set(Ring1_Status_TooLong);
    Ring2_jump();
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .suffixSize = sizeof(Ring2_String) + m,
    .type = &g_gcType,
  };
  Ring2_String* c = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Ring2_jump();
  }
  Ring1_Memory_copyFast(c->p, self->p, self->n);
  Ring1_Memory_copyFast(c->p + self->n, other->p, other->n);
  c->n = m;
  c->hashValue = hashBytesToSz(c->p, c->n);
  return c;
}

bool Machine_String_isEqualTo(Ring2_String const* self, Ring2_String const* other) {
  if (self == other)
    return true;
  if (self->n == other->n && self->hashValue == other->hashValue) {
    int temporary;
    Ring1_Memory_compare(&temporary, self->p, self->n, other->p, other->n, Ring1_Memory_Compare_Lexicographic);
    return !temporary;
  }
  return false;
}

Ring2_Integer Machine_String_getHashValue(Ring2_String const* self) {
  uint64_t v = (uint64_t)self->hashValue;
  return (Ring2_Integer)(v >> 1);
}

const char* Machine_String_getBytes(Ring2_String const* self) {
  return self->p;
}

size_t Machine_String_getNumberOfBytes(Ring2_String const* self) {
  return self->n;
}
