// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/CommandLine/ArgumentList.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/CommandLine/ArgumentList.h"

#include "Mkx/CommandLine/Argument.h"
#include "Ring1/ReferenceCounter.h"
#include "Ring1/Collections/PointerList.h"
#include <malloc.h>

struct Mkx_CommandLine_ArgumentList
{
  Ring1_ReferenceCounter referenceCount;
  Ring1_PointerList arguments;
};

static void
Mkx_CommandLine_ArgumentList_destroy
  (
    Mkx_CommandLine_ArgumentList* argumentList
  )
{
  Ring1_PointerList_uninitialize(&argumentList->arguments);
}

static void ref(void** p) {
  Mkx_CommandLine_Argument_ref(*p);
}

static void unref(void** p) {
  Mkx_CommandLine_Argument_unref(*p);
}

Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_create
  (
    Mkx_CommandLine_ArgumentList **result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Mkx_CommandLine_ArgumentList* self = malloc(sizeof(Mkx_CommandLine_ArgumentList));
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  if (Ring1_PointerList_initialize(&self->arguments, &ref, &unref)) {
    free(self);
    return Ring1_Result_Failure;
  }
  self->referenceCount = 1;
  *result = self;
  return Ring1_Result_Success;
}

void
Mkx_CommandLine_ArgumentList_ref
  (
    Mkx_CommandLine_ArgumentList* self
  )
{ Ring1_ReferenceCounter_increment(&self->referenceCount); }

void
Mkx_CommandLine_ArgumentList_unref
  (
    Mkx_CommandLine_ArgumentList* self
  )
{
  if (0 == Ring1_ReferenceCounter_decrement(&self->referenceCount))
  { Mkx_CommandLine_ArgumentList_destroy(self); }
}

Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_append
  (
    Mkx_CommandLine_ArgumentList* self,
    Mkx_CommandLine_Argument* argument
  )
{
  if (!self || !argument) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return Ring1_PointerList_insertBack(&self->arguments, argument);
}

Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_getSize
  (
    int64_t *result,
    Mkx_CommandLine_ArgumentList* self
  )
{ return Ring1_PointerList_getSize(result, &self->arguments); }

Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_getAt
  (
    Mkx_CommandLine_Argument **result,
    Mkx_CommandLine_ArgumentList* self,
    int64_t index
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Mkx_CommandLine_Argument* temporary;
  if (Ring1_PointerList_getAt(&self->arguments, index, &temporary)) {
    return Ring1_Result_Failure;
  }
  Mkx_CommandLine_Argument_ref(temporary);
  *result = temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_removeAt
  (
    Mkx_CommandLine_ArgumentList* self,
    int64_t index
  )
{
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return Ring1_PointerList_removeAt(&self->arguments, index, NULL);
}

