#include "Ring1/FileSystem/Path.h"


#include "Ring1/Memory/_Include.h"
#include "Ring1/Crt/_Include.h"

#include "Ring1/FileSystem/Path/unparse.h"
#include "Ring1/FileSystem/Path/parse.h"
#include "Ring1/FileSystem/Path/normalize.h"


struct Ring1_FileSystem_Path {
  Ring1_ReferenceCounter referenceCount;
  TokenList* tokens;
};

static Ring1_NoDiscardReturn() Ring1_Result
isEmpty
  (
    bool* result,
    Ring1_FileSystem_Path* self
  )
{
  int64_t size;
  if (TokenList_getSize(&size, self->tokens)) {
    return Ring1_Result_Failure;
  }
  *result = 0 == size;
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
isAbsolute
  (
    bool* result,
    Ring1_FileSystem_Path* self
  )
{
  int64_t size;
  if (TokenList_getSize(&size, self->tokens)) {
    return Ring1_Result_Failure;
  }
  if (0 == size) {
    *result = false;
    return Ring1_Result_Success;
  }
  Token* firstToken;
  if (TokenList_getAt(&firstToken, self->tokens, 0)) {
    return Ring1_Result_Failure;
  }
  *result = firstToken->type == TokenType_DrivePrefix;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Path_create
  (
    Ring1_FileSystem_Path** result,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!bytes) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Path))) {
    return Ring1_Result_Failure;
  }
  if (Ring1_FileSystem_Path_parse(&self->tokens, bytes, numberOfBytes)) {
    Ring1_Memory_deallocate(self);
    self = NULL;
    return Ring1_Result_Failure;
  }
  if (normalize(self->tokens)) {
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
    self = NULL;
    return Ring1_Result_Failure;
  }
  self->referenceCount = 1;
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Path_concatenate
  (
    Ring1_FileSystem_Path** result,
    Ring1_FileSystem_Path* prefix,
    Ring1_FileSystem_Path* suffix
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!prefix || !suffix) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Path))) {
    return Ring1_Result_Failure;
  }
  if (TokenList_create(&self->tokens)) {
    Ring1_Memory_deallocate(self);
    self = NULL;
    Ring1_Result_Failure;
  }
  // error if the prefix is not the empty path and the suffix is an absolute path.
  bool prefixEmpty, suffixAbsolute;
  if (isEmpty(&prefixEmpty, prefix) || isAbsolute(&suffixAbsolute, suffix)) {
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
    self = NULL;
    Ring1_Result_Failure;
  }
  if (!prefixEmpty && suffixAbsolute) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
    self = NULL;
    Ring1_Result_Failure;
  }
  if (TokenList_pushAll(self->tokens, prefix->tokens)) {
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
    self = NULL;
    Ring1_Result_Failure;
  }
  if (TokenList_pushAll(self->tokens, suffix->tokens)) {
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
    self = NULL;
    Ring1_Result_Failure;
  }
  if (normalize(self->tokens)) {
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
    self = NULL;
    return Ring1_Result_Failure;
  }
  self->referenceCount = 1;
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Path_toString
  (
    Ring1_FileSystem_Path* self,
    bool zeroTerminated,
    char** bytes,
    size_t* numberOfBytes
  )
{
  return unparse(self->tokens, zeroTerminated, bytes, numberOfBytes);
}

void
Ring1_FileSystem_Path_ref
  (
    Ring1_FileSystem_Path *self
  )
{
  Ring1_ReferenceCounter_increment(&self->referenceCount);
}
  
void
Ring1_FileSystem_Path_unref
  (
    Ring1_FileSystem_Path *self
  )
{
  if (!Ring1_ReferenceCounter_decrement(&self->referenceCount)) {
    TokenList_destroy(self->tokens);
    self->tokens = NULL;
    Ring1_Memory_deallocate(self);
  }
}
