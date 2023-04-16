// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/CommandLine/ArgumentList.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/CommandLine/ArgumentList.h"

#include "Ring1/CommandLine/Argument.h"
#include "Ring1/ReferenceCounter.h"
#include "Ring1/Collections/PointerList.h"
#include <malloc.h>

struct Ring1_CommandLine_ArgumentList {
  Ring1_ReferenceCounter referenceCount;
  Ring1_PointerList arguments;
};

static void
Ring1_CommandLine_ArgumentList_destroy
  (
    Ring1_CommandLine_ArgumentList* argumentList
  )
{
  Ring1_PointerList_uninitialize(&argumentList->arguments);
}

static void
ref
  (
    void** p
  )
{ Ring1_CommandLine_Argument_ref(*p); }

static void
unref
  (
    void** p
  )
{ Ring1_CommandLine_Argument_unref(*p); }

Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_ArgumentList_create
  (
    Ring1_CommandLine_ArgumentList **result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_CommandLine_ArgumentList* self = malloc(sizeof(Ring1_CommandLine_ArgumentList));
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
Ring1_CommandLine_ArgumentList_ref
  (
    Ring1_CommandLine_ArgumentList* self
  )
{ Ring1_ReferenceCounter_increment(&self->referenceCount); }

void
Ring1_CommandLine_ArgumentList_unref
  (
    Ring1_CommandLine_ArgumentList* self
  )
{
  if (0 == Ring1_ReferenceCounter_decrement(&self->referenceCount))
  { Ring1_CommandLine_ArgumentList_destroy(self); }
}

Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_ArgumentList_append
  (
    Ring1_CommandLine_ArgumentList* self,
    Ring1_CommandLine_Argument* argument
  )
{
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!argument) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return Ring1_PointerList_insertBack(&self->arguments, argument);
}

Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_ArgumentList_getSize
  (
    int64_t *result,
    Ring1_CommandLine_ArgumentList* self
  )
{ return Ring1_PointerList_getSize(result, &self->arguments); }

Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_ArgumentList_getAt
  (
    Ring1_CommandLine_Argument **result,
    Ring1_CommandLine_ArgumentList* self,
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
  Ring1_CommandLine_Argument* temporary;
  if (Ring1_PointerList_getAt(&self->arguments, index, &temporary)) {
    return Ring1_Result_Failure;
  }
  Ring1_CommandLine_Argument_ref(temporary);
  *result = temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_ArgumentList_removeAt
  (
    Ring1_CommandLine_ArgumentList* self,
    int64_t index
  )
{
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return Ring1_PointerList_removeAt(&self->arguments, index, NULL);
}
