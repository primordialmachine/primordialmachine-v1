#define RING2_PRIVATE (1)
#include "Ring2/Operations/_Buffer.h"
#undef RING2_PRIVATE


#include "Ring1/All/_Include.h"
#include <stdlib.h>


struct buffer_t {
  char* p;
  size_t l;
};

static struct buffer_t* g_buffer = NULL;

Ring1_Result
Ring2_Operations__Buffer_shutdown
  (
  )
{
  free(g_buffer->p);
  g_buffer->p;
  free(g_buffer);
  g_buffer = NULL;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring2_Operations__Buffer_startup
  (
  )
{
  g_buffer = malloc(sizeof(struct buffer_t));
  if (!g_buffer) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  g_buffer->l = 0;
  g_buffer->p = malloc(1);
  if (!g_buffer->p) {
    free(g_buffer);
    g_buffer = NULL;
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring2_Operations__Buffer_get
  (
    char** result,
    size_t requiredSize
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (g_buffer->l < requiredSize) {
    char* p = realloc(g_buffer->p, requiredSize);
    if (!p) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    g_buffer->p = p;
    g_buffer->l = requiredSize;
  }
  *result = g_buffer->p;
  return Ring1_Result_Success;
}
