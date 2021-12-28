/// @file Runtime/String.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/String.h"




struct Machine_String {
  size_t hashValue;
  size_t n;
  char p[];
};

/// @todo Machine_allocate has its own limit which is smaller than this value.
static size_t const MACHINE_STRING_MAXIMAL_LENGTH = SIZE_MAX - sizeof(Machine_String);

Machine_String* Machine_String_create_noraise(char const* p, size_t n) {
  if (n > MACHINE_STRING_MAXIMAL_LENGTH) {
    Machine_setStatus(Machine_Status_TooLong);
    return NULL;
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = 0,
    .suffixSize = sizeof(Machine_String) + n,
    .visit = (Machine_Gc_VisitCallback*)NULL,
    .finalize = (Machine_Gc_FinalizeCallback*)NULL,
  };
  Machine_String* self = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    return NULL;
  }
  Machine_Eal_Memory_copy(self->p, p, n, false);
  self->n = n;
  self->hashValue = n;
  for (size_t i = 0; i < n; ++i) {
    self->hashValue = p[i] + self->hashValue * 37;
  }
  return self;
}

Machine_String* Machine_String_create(char const* p, size_t n) {
  if (n > MACHINE_STRING_MAXIMAL_LENGTH) {
    Machine_setStatus(Machine_Status_TooLong);
    Machine_jump();
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = 0,
    .suffixSize = sizeof(Machine_String) + n,
    .visit = (Machine_Gc_VisitCallback*)NULL,
    .finalize = (Machine_Gc_FinalizeCallback*)NULL,
  };
  Machine_String* self = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Eal_Memory_copy(self->p, p, n, false);
  self->n = n;
  self->hashValue = n;
  for (size_t i = 0; i < n; ++i) {
    self->hashValue = p[i] + self->hashValue * 37;
  }
  return self;
}

Machine_String* Machine_String_concatenate(Machine_String const* self, Machine_String const* other) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(other);
  if (SIZE_MAX - self->n < other->n) {
    Machine_setStatus(Machine_Status_TooLong);
    Machine_jump();
  }
  size_t m = self->n + other->n;
  if (m > MACHINE_STRING_MAXIMAL_LENGTH) {
    Machine_setStatus(Machine_Status_TooLong);
    Machine_jump();
  }
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = 0,
    .suffixSize = sizeof(Machine_String) + m,
    .visit = (Machine_Gc_VisitCallback*)NULL,
    .finalize = (Machine_Gc_FinalizeCallback*)NULL,
  };
  Machine_String* c = Machine_Gc_allocate(&allocationArguments);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();    
  }
  Machine_Eal_Memory_copy(c->p, self->p, self->n, false);
  Machine_Eal_Memory_copy(c->p + self->n, other->p, other->n, false);
  c->n = m;
  c->hashValue = m;
  for (size_t i = 0; i < m; ++i) {
    c->hashValue = c->p[i] + self->hashValue * 37;
  }
  return c;
}

bool Machine_String_isEqualTo(Machine_String const* self, Machine_String const* other) {
  if (self == other) return true;
  if (self->n == other->n && self->hashValue == other->hashValue) {
    return !Machine_Eal_Memory_compare(self->p, other->p, self->n);
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
