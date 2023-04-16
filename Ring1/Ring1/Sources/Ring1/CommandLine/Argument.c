#include "Ring1/CommandLine/Argument.h"

#include "Ring1/Crt/_Include.h"
#include "Ring1/Status.h"


struct Ring1_CommandLine_Argument {
  Ring1_ReferenceCounter referenceCount;
  char* name;
  char* value;
};

static void
destroy
  (
    Ring1_CommandLine_Argument* argument
  );

static void
destroy
  (
    Ring1_CommandLine_Argument* argument
  )
{
  if (argument->value) {
    crt_free(argument->value);
    argument->value = NULL;
  }
  if (argument->name) {
    crt_free(argument->name);
    argument->name = NULL;
  }
  crt_free(argument);
}

Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_Argument_create
  (
    Ring1_CommandLine_Argument **result,
    char const* name,
    char const* value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_CommandLine_Argument* argument1 = crt_malloc(sizeof(Ring1_CommandLine_Argument));
  if (!argument1) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  argument1->referenceCount = 1;
  argument1->name = NULL;
  argument1->value = NULL;
  if (name) {
    argument1->name = crt_strdup(name);
    if (!argument1->name) {
      crt_free(argument1);
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
  }
  if (value) {
    argument1->value = crt_strdup(value);
    if (!argument1->value) {
      if (argument1->name) {
        crt_free(argument1->name);
        argument1->name = NULL;
      }
      crt_free(argument1);
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
  }
  *result = argument1;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_CommandLine_Argument_getName
  (
    char const** result,
    Ring1_CommandLine_Argument const* argument
  )
{
  *result = argument->name;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_CommandLine_Argument_getValue
  (
    char const** result,
    Ring1_CommandLine_Argument const* argument
  )
{ 
  *result = argument->value;
  return Ring1_Result_Success;
}

void
Ring1_CommandLine_Argument_ref
  (
    Ring1_CommandLine_Argument* argument
  )
{ Ring1_ReferenceCounter_increment(&argument->referenceCount); }

void
Ring1_CommandLine_Argument_unref
  (
    Ring1_CommandLine_Argument* argument
  )
{
  if (0 == Ring1_ReferenceCounter_decrement(&argument->referenceCount))
  { destroy(argument); }
}
