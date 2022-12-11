#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApBool.h"
#undef RING1_AP_PRIVATE


#include "Ring1/Status.h"
#include <malloc.h>
#include <stdio.h>


Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_print
  (
    Ring1_ApBool *self
  )
{
  if (self->value) {
    fprintf(stdout, "true");
  } else {
    fprintf(stdout, "false");
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_initialize_bool
  (
    Ring1_ApBool *self,
    bool value
  )
{
  self->value = value;
  return Ring1_Result_Success;
}

Ring1_Result
Ring1_ApBool_uninitialize
  (
    Ring1_ApBool* self
  )
{
  if (!self) {
    return Ring1_Result_Success;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_assign
  (
    Ring1_ApBool* self,
    Ring1_ApBool* other
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  self->value = other->value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_toBool
  (
    bool *result,
    Ring1_ApBool* self
  )
{
  *result = self->value;
  return Ring1_Result_Success;
}
