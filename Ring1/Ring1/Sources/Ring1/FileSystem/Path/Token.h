#if !defined(RING1_FILESYSTEM_PATH_TOKEN_H_INCLUDED)
#define RING1_FILESYSTEM_PATH_TOKEN_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include "Ring1/ReferenceCounter.h"
#include <stdint.h>

#define TokenType_Error (0)
#define TokenType_Slash (1)
#define TokenType_BackSlash (2)
#define TokenType_Dot (3)
#define TokenType_DotDot (4)
#define TokenType_DrivePrefix (5)
#define TokenType_Text (6)
#define TokenType_Empty (7)
// '"', '*', ':', '<', '>', and '|' are not allowed in paths.
#define TokenType_Forbidden (8)

typedef struct Token {
  Ring1_ReferenceCounter referenceCount;
  uint8_t type;
  size_t start;
  size_t length;
  char* p;
  size_t n;
} Token;

Ring1_CheckReturn() Ring1_Result
Token_create
  (
    Token** result,
    uint8_t type,
    size_t start,
    size_t length,
    const char* p,
    size_t n
  );

Ring1_CheckReturn() Ring1_Result
Token_clone
  (
    Token** result,
    Token* self
  );

void
Token_ref
  (
    Token* token
  );

void
Token_unref
  (
    Token* token
  );

#endif // RING1_FILESYSTEM_PATH_TOKEN_H_INCLUDED
