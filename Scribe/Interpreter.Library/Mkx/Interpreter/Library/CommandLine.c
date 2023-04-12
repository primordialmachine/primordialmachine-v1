// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/CommandLine.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Mkx/Interpreter/Library/CommandLine.h"
#undef RING2_LIBRARY_PRIVATE

#include "Ring2/Library/_Include.h"
#include "Mkx/CommandLine.h"
#include <stdio.h>

static Ring1_CheckReturn() Ring2_CommandLine_Argument*
Ring2_CommandLine_Argument_create
  (
    Mkx_CommandLine_Argument* pimpl
  );

static void
Ring2_CommandLine_Argument_destruct
  (
    Ring2_CommandLine_Argument* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring2_CommandLine_Argument,
                         Machine_Object,
                         NULL,
                         Ring2_CommandLine_Argument_construct,
                         Ring2_CommandLine_Argument_destruct,
                         NULL,
                         NULL)

/// @ffi
static void
Ring2_CommandLine_Argument_destruct
  (
    Ring2_CommandLine_Argument* self
  )
{
  if (self->pimpl) {
    Mkx_CommandLine_Argument_unref(self->pimpl);
    self->pimpl = NULL;
  }
}

void
Ring2_CommandLine_Argument_construct
  (
    Ring2_CommandLine_Argument *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_CommandLine_Argument_getType());
}

static Ring1_CheckReturn() Ring2_CommandLine_Argument *
Ring2_CommandLine_Argument_create
  (
    Mkx_CommandLine_Argument* pimpl
  )
{
  Machine_Type* ty = Ring2_CommandLine_Argument_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_CommandLine_Argument *self = Ring1_cast(Ring2_CommandLine_Argument*,
                                                Machine_allocateClassObject(ty,
                                                                            NUMBER_OF_ARGUMENTS,
                                                                            ARGUMENTS));
  self->pimpl = pimpl;
  return self;
}

Ring1_CheckReturn() Ring2_String *
Ring2_CommandLine_Argument_getName
  (
    Ring2_CommandLine_Argument* argument
  )
{
  if (!argument) {
    fprintf(stderr, "assertion `NULL != argument` failed\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  const char* p = Mkx_CommandLine_Argument_getName(argument->pimpl);
  if (!p) return NULL;
  return Ring2_String_fromC(false, p);
}

Ring1_CheckReturn() Ring2_String *
Ring2_CommandLine_Argument_getValue
  (
    Ring2_CommandLine_Argument* argument
  )
{
  if (!argument) {
    fprintf(stderr, "assertion `NULL != argument` failed\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  const char* p = Mkx_CommandLine_Argument_getValue(argument->pimpl);
  if (!p) return NULL;
  return Ring2_String_fromC(false, p);
}

static void
Ring2_CommandLine_ArgumentList_destruct
  (
    Ring2_CommandLine_ArgumentList* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring2_CommandLine_ArgumentList,
                         Machine_Object,
                         NULL,
                         Ring2_CommandLine_ArgumentList_construct,
                         Ring2_CommandLine_ArgumentList_destruct,
                         NULL,
                         NULL)

/// @ffi
static void
Ring2_CommandLine_ArgumentList_destruct
  (
    Ring2_CommandLine_ArgumentList* self
  )
{
  if (self->pimpl) {
    Mkx_CommandLine_ArgumentList_unref(self->pimpl);
    self->pimpl = NULL;
  }
}

void
Ring2_CommandLine_ArgumentList_construct
  (
    Ring2_CommandLine_ArgumentList *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_CommandLine_ArgumentList_getType());
}

Ring1_CheckReturn() Ring2_CommandLine_ArgumentList *
Ring2_CommandLine_ArgumentList_create
  (
    int argc,
    const char** argv
  )
{
  Machine_Type* ty = Ring2_CommandLine_ArgumentList_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_CommandLine_ArgumentList *self = Ring1_cast(Ring2_CommandLine_ArgumentList*,
                                                    Machine_allocateClassObject(ty,
                                                                                 NUMBER_OF_ARGUMENTS,
                                                                                 ARGUMENTS));

  Mkx_CommandLine_ArgumentList* pimpl = Mkx_CommandLine_ArgumentList_parse(argc, argv);
  if (!pimpl) {
    fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Mkx_CommandLine_ArgumentList_parse");
    Ring2_jump();
  }
  self->pimpl = pimpl;
  
  return self;
}

Ring1_CheckReturn() Ring2_CommandLine_Argument *
Ring2_CommandLine_ArgumentList_getAt
  (
    Ring2_CommandLine_ArgumentList* self,
    int64_t index
  )
{
  Mkx_CommandLine_Argument* pimpl;
  if (Mkx_CommandLine_ArgumentList_getAt(&pimpl, self->pimpl, index)) {
    fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Mkx_CommandLine_ArgumentList_getAt");
    Ring2_jump();
  }
  Ring2_JumpTarget jt;
  Ring2_pushJumpTarget(&jt);
  if (!setjmp(jt.environment)) {
    Ring2_CommandLine_Argument* argument = Ring2_CommandLine_Argument_create(pimpl);
    return argument;
  } else {
    Ring2_popJumpTarget();
    Mkx_CommandLine_Argument_unref(pimpl);
    pimpl = NULL;
    Ring2_jump();
  }
}

Ring1_CheckReturn() int64_t
Ring2_CommandLine_ArgumentList_getSize
  (
    Ring2_CommandLine_ArgumentList* self
  )
{
  if (!self) {
    fprintf(stderr, "%s:%d: assertion `%s` failed\n", __FILE__, __LINE__, "NULL != argumentList");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  int64_t size;
  if (Ring1_Unlikely(Mkx_CommandLine_ArgumentList_getSize(&size, self->pimpl))) {
    fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Mkx_CommandLine_ArgumentList_getSize");
    Ring2_jump();
  }
  return size;
}

void
Ring2_CommandLine_ArgumentList_removeAt
  (
    Ring2_CommandLine_ArgumentList* self,
    int64_t index
  )
{
  if (Mkx_CommandLine_ArgumentList_removeAt(self->pimpl, index)) {
    fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Mkx_CommandLine_ArgumentList_removeAt");
    Ring2_jump();
  }
}
