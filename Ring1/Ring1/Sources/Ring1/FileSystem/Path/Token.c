#include "Ring1/FileSystem/Path/Token.h"

#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Token_create
  (
    Token** result,
    uint8_t type,
    size_t start,
    size_t length,
    const char* p,
    size_t n
  )
{
  Token* self;
  if (Ring1_Memory_allocate(&self, sizeof(Token))) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Memory_allocate(&self->p, n)) {
    Ring1_Memory_deallocate(self);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_copyFast(self->p, p, n);
  self->n = n;
  self->type = type;
  self->start = start;
  self->length = length;
  self->referenceCount = 1;
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Token_clone
  (
    Token** result,
    Token* self
  )
{
  Token* clone;
  if (Ring1_Memory_allocate(&clone, sizeof(Token))) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Memory_allocate(&clone->p, self->n)) {
    Ring1_Memory_deallocate(clone);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_copyFast(clone->p, self->p, self->n);
  clone->n = self->n;
  clone->type = self->type;
  clone->start = self->start;
  clone->length = self->length;
  clone->referenceCount = 1;
  *result = clone;
  return Ring1_Result_Success;
}

void
Token_ref
  (
   Token* token
  )
{
  Ring1_ReferenceCounter_increment(&token->referenceCount);
}

void
Token_unref
  (
    Token* token
  )
{
  if (0 == Ring1_ReferenceCounter_decrement(&token->referenceCount)) {
    Ring1_Memory_deallocate(token->p);
    Ring1_Memory_deallocate(token);
  }
}
