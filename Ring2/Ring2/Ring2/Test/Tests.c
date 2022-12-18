// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Tests.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Test/Tests.h"
#undef RING2_PRIVATE

#define RING2_PRIVATE (1)
#include "Ring2/Context.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Test/Test.h"
#undef RING2_PRIVATE
#include "Ring1/All/_Include.h"
#include <limits.h>
#include <stdio.h>

static void
printString
  (
    Ring2_String* s
  );

static void
Ring2_Tests_destruct
  (
    Ring2_Tests* self
  );

static void
Ring2_Tests_visit
  (
    Ring2_Tests* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring2_Tests,
                         Machine_Object,
                         &Ring2_Tests_visit,
                         &Ring2_Tests_construct,
                         &Ring2_Tests_destruct,
                         NULL,
                         NULL)

static void
printString
  (
    Ring2_String *s
  )
{
  Ring2_Integer n = Ring2_String_getNumberOfBytes(s);
  Ring2_Integer m = 0;
  const char* p = Ring2_String_getBytes(s);
  while (n > INT_MAX) {
    fprintf(stdout, "%.*s", (int)n, p + m);
    m += INT_MAX;
    n -= INT_MAX;
  }
  fprintf(stdout, "%.*s", (int)n, p + m);
}

static void
Ring2_Tests_destruct
  (
    Ring2_Tests* self
  )
{
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

static void
Ring2_Tests_visit
  (
    Ring2_Tests* self
  )
{
  for (size_t i = 0, n = self->size; i < n; ++i) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->elements[i]);
  }
}

void
Ring2_Tests_construct
  (
    Ring2_Tests *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = 0;
  if (Ring1_Memory_allocateArray((void **)&self->elements, 0, sizeof(Ring2_Test *))) {
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring2_Tests_getType());
}
  
Ring2_Tests *
Ring2_Tests_create
  (
  )
{
  Machine_ClassType* ty = Ring2_Tests_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Tests* self = (Ring2_Tests *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Ring2_Tests_addTest
  (
    Ring2_Tests *self,
    Ring2_String *name,
    Ring2_ForeignProcedure *procedure
  )
{
  if (self->size == self->capacity) {
    size_t oldCapacity = self->capacity;
    size_t newCapacity = oldCapacity;
    if (oldCapacity == 0) {
      newCapacity = 8;
    } else if (oldCapacity < SIZE_MAX / 2) {
      newCapacity = oldCapacity * 2;
    } else {
      newCapacity = SIZE_MAX;
    }
    if (Ring1_Memory_reallocateArray((void **)&self->elements, self->elements, newCapacity, sizeof(Ring2_Test *))) {
      Ring2_jump();
    }
    self->capacity = newCapacity;
  }
  Ring2_Test *test = Ring2_Test_create(name, procedure);
  self->elements[self->size] = test;
  self->size++;
}

void
Ring2_Tests_run
  (
    Ring2_Tests *self
  )
{
  int total = 0, succeeded = 0, failed = 0;
  for (size_t i = 0, n = self->size; i < n; ++i) {
    Ring2_Test* test = self->elements[i];
    test->flags = RING2_TEST_FLAG_ISEVALUATING;
    Ring2_JumpTarget jt;
    Ring2_pushJumpTarget(&jt);
    if (!setjmp(jt.environment)) {
      Ring2_Value result = Ring2_Value_StaticInitializerVoid();
      static const size_t NUMBER_OF_ARGUMENTS = 0;
      static const Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
      (*test->procedure)(Ring2_Context_get(), &result, NUMBER_OF_ARGUMENTS, ARGUMENTS);
      Ring2_popJumpTarget();
    } else {
      test->flags |= RING2_TEST_FLAG_HASERRORS;
      Ring2_popJumpTarget();
    }
    test->flags = (test->flags & ~RING2_TEST_FLAG_ISEVALUATING) | RING2_TEST_FLAG_ISEVALUATED;
    if (0 == (test->flags & RING2_TEST_FLAG_HASERRORS)) {
      printString(test->name);
      fprintf(stdout, " succeeded\n");
      total++;
      succeeded++;
    } else {
      printString(test->name);
      fprintf(stdout, " failed\n");
      total++;
      failed++;
    }
  }
  fprintf(stdout, "%d/%d succeeded\n", succeeded, total);
}
