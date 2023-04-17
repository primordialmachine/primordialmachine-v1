#if !defined(RING1_FILESYSTEM_PATH_TOKENLIST_H_INCLUDED)
#define RING1_FILESYSTEM_PATH_TOKENLIST_H_INCLUDED

#include "Ring1/FileSystem/Path/Token.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include "Ring1/Collections/_Include.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct TokenList {
  Ring1_PointerList elements;
} TokenList;

Ring1_NoDiscardReturn() Ring1_Result
TokenList_getSize
  (
    int64_t* result,
    TokenList* self
  );

/// @error #Ring1_Status_InvalidArgument @a tokenList is null
/// @error #Ring1_Status_InvalidArgument @a tokenList is null
/// @error #Ring1_Status_CollectionFull @a tokenList is full
Ring1_NoDiscardReturn() Ring1_Result
TokenList_push
  (
    TokenList* tokenList,
    bool ownership,
    Token* token
  );

Ring1_NoDiscardReturn() Ring1_Result
TokenList_removeAt
  (
    Token** result,
    TokenList* self,
    bool ownership,
    size_t index
  );

Ring1_NoDiscardReturn() Ring1_Result
TokenList_getAt
  (
    Token** result,
    TokenList* self,
    int64_t index
  );

Ring1_NoDiscardReturn() Ring1_Result
TokenList_clear
  (
    TokenList* self
  );

Ring1_NoDiscardReturn() Ring1_Result
TokenList_pushAll
  (
    TokenList* self,
    TokenList* source
  );

Ring1_NoDiscardReturn() Ring1_Result
TokenList_create
  (
    TokenList** result
  );

void
TokenList_destroy
  (
    TokenList* tokenList
  );

#endif  // RING1_FILESYSTEM_PATH_TOKENLIST_H_INCLUDED
