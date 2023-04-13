#include "Ring1/FileSystem/Path/unparse.h"

#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"
#include <setjmp.h>

Ring1_Inline() void APPEND
  (
    jmp_buf *j,
    char** p,
    size_t* n,
    const char *q,
    size_t m
  )
{
  if (Ring1_Memory_reallocate((void **)p, *p, *n + m)) {
    longjmp(*j, -1);
  }
  Ring1_Memory_copyFast(*p + *n, q, m);
  *n += m;
}

Ring1_Inline() void
unparse1
  (
    jmp_buf *j,
    TokenList* tokenList,
    char** p,
    size_t* n
  )
{
  int64_t size;
  if (Ring1_PointerList_getSize(&size, &tokenList->elements)) {
    longjmp(*j, -1);
  }
  for (int64_t i = 0, m = size; i < m; ++i) {
    Token* token;
    if (Ring1_PointerList_getAt(&tokenList->elements, i, &token)) {
      longjmp(*j, -1);
    }
    switch (token->type) {
    case TokenType_BackSlash:
      APPEND(j, p, n, "\\", sizeof("\\") - 1);
      break;
    case TokenType_Dot:
      APPEND(j, p, n, ".", sizeof(".") - 1);
      break;
    case TokenType_DotDot:
      APPEND(j, p, n, "..", sizeof("..") - 1);
      break;
    case TokenType_DrivePrefix:
      APPEND(j, p, n, token->p, token->n);
      break;
    case TokenType_Empty:
      break;
    case TokenType_Slash:
      APPEND(j, p, n, "/", sizeof("/") - 1);
      break;
    case TokenType_Text:
      APPEND(j, p, n, token->p, token->n);
      break;
    case TokenType_Error:
    default:
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      break;
    };
  }
}

Ring1_NoDiscardReturn() Ring1_Result
unparse
  (
    TokenList* tokenList,
    bool zeroTerminated,
    char** p,
    size_t* n
  )
{
  char* p1 = NULL;
  size_t n1 = 0;
  if (Ring1_Memory_allocate(&p1, 0)) {
    return Ring1_Result_Failure;
  }
  jmp_buf env;
  if (!setjmp(env)) {
    unparse1(&env, tokenList, &p1, &n1);
    if (zeroTerminated) {
      APPEND(&env, &p1, &n1, "", 1);
    }
    *p = p1;
    *n = n1;
    return Ring1_Result_Success;
  } else {
    Ring1_Memory_deallocate(p1);
    p1 = NULL;
    n1 = 0;
    return Ring1_Result_Failure;
  }
}
