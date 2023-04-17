#include "Ring1/FileSystem/Path/TokenList.h"

#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"

static void added(Token** token) {
  Token_ref(*token);
}

static void removed(Token** token) {
  Token_unref(*token);
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_getSize
  (
    int64_t* result,
    TokenList* self
  )
{
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return Ring1_PointerList_getSize(result, &self->elements);
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_push
  (
    TokenList* tokenList,
    bool transferOwnership,
    Token* token
  )
{
  if (!tokenList || !token) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_PointerList_insertBack(&tokenList->elements, token)) {
    return Ring1_Result_Failure;
  }
  if (transferOwnership) {
    // Revert the increment.
    Token_unref(token);
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_removeAt
  (
    Token** result,
    TokenList* self,
    bool ownership,
    size_t index
  )
{
  if (index > INT64_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (ownership) {
    if (Ring1_PointerList_removeAt(&self->elements, index, result)) {
      return Ring1_Result_Failure;
    }
  } else {
    if (Ring1_PointerList_stealAt(&self->elements, index, result)) {
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_getAt
  (
    Token** result,
    TokenList* self,
    int64_t index
  )
{
  Token* temporary;
  if (Ring1_PointerList_getAt(&self->elements, index, &temporary)) {
    return Ring1_Result_Failure;
  }
  *result = temporary;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_clear
  (
    TokenList* self
  ) 
{
  return Ring1_PointerList_clear(&self->elements);
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_pushAll
  (
    TokenList* self,
    TokenList* source
  )
{
  int64_t sourceSize;
  if (Ring1_PointerList_getSize(&sourceSize, &source->elements)) {
    return Ring1_Result_Failure;
  }
  for (int64_t i = 0, n = sourceSize; i < n; ++i) {
    Token* token;
    if (Ring1_PointerList_getAt(&source->elements, i, &token)) {
      return Ring1_Result_Failure;
    }
    if (Ring1_PointerList_insertBack(&self->elements, token)) {
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
TokenList_create
  (
    TokenList** result
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  TokenList* tokenList;
  if (Ring1_Memory_allocate(&tokenList, sizeof(TokenList))) {
    return Ring1_Result_Failure;
  }
  if (Ring1_PointerList_initialize(&tokenList->elements, &added, &removed)) {
    Ring1_Memory_deallocate(tokenList);
    tokenList = NULL;
    return Ring1_Result_Failure;
  }
  *result = tokenList;
  return Ring1_Result_Success;
}

void
TokenList_destroy
  (
    TokenList* tokenList
  )
{
  Ring1_PointerList_uninitialize(&tokenList->elements);
  Ring1_Memory_deallocate(tokenList);
}
