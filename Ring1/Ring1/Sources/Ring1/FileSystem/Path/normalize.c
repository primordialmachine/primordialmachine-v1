#include "Ring1/FileSystem/Path/normalize.h"


typedef struct State {
  TokenList* sources;
  TokenList* targets;
  int modified;
} State;

typedef Ring1_Result(NormalizationFunction)(State*);

static Ring1_NoDiscardReturn() Ring1_Result
copy
  (
    TokenList* targets,
    Token** p,
    size_t n
  )
{
  for (size_t i = 0; i < n; ++i) {
    Token* target;
    if (Token_clone(&target, p[i])) {
      return Ring1_Result_Failure;
    }
    if (TokenList_push(targets, true, target)) {
      Token_unref(target);
      target = NULL;
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

/// @details
/// - if <code>w = u Filename BackSlash DotDot BackSlash v</code> then <code>w := u BackSlash v</code>
static Ring1_NoDiscardReturn() Ring1_Result
normalizeDotDots
  (
    State* state
  )
{
  int64_t size;
  if (TokenList_getSize(&size, state->sources)) {
    return Ring1_Result_Failure;
  }
  // 1 = FileName
  // 2 = FileName BackSlash
  // 3 = FileName BackSlash DotDot
  // 4 = FileName BackSlash DotDot BackSlash
  int j = 0;
  Token* buffer[4];
  for (int64_t i = 0, n = size; i < n;) {
    Token* token1;
    if (TokenList_getAt(&token1, state->sources, i)) {
      return Ring1_Result_Failure;
    }
    if (token1->type == TokenType_Text) {
      if (j == 0) {
        buffer[j] = token1;
        j++;
      } else {
        if (j > 0) {
          if (copy(state->targets, buffer, j)) {
            return Ring1_Result_Failure;
          }
          j = 0;
        }
        Token* newToken;
        if (Token_clone(&newToken, token1)) {
          return Ring1_Result_Failure;
        }
        if (TokenList_push(state->targets, true, newToken)) {
          Token_unref(newToken);
          newToken = NULL;
          return Ring1_Result_Failure;
        }
      }
      i++;
    } else if (token1->type == TokenType_BackSlash) {
      if (j == 1) {
        buffer[j] = token1;
        j++;
      } else if (j == 3) {
        state->modified++;
        j = 0;
      } else {
        if (j > 0) {
          if (copy(state->targets, buffer, j)) {
            return Ring1_Result_Failure;
          }
          j = 0;
        }
        Token* newToken;
        if (Token_clone(&newToken, token1)) {
          return Ring1_Result_Failure;
        }
        if (TokenList_push(state->targets, true, newToken)) {
          Token_unref(newToken);
          newToken = NULL;
          return Ring1_Result_Failure;
        }
      }
      i++;
    } else if (token1->type == TokenType_DotDot) {
      if (j == 2) {
        buffer[j] = token1;
        j++;
      } else {
        if (j > 0) {
          if (copy(state->targets, buffer, j)) {
            return Ring1_Result_Failure;
          }
          j = 0;
        }
        Token* newToken;
        if (Token_clone(&newToken, token1)) {
          return Ring1_Result_Failure;
        }
        if (TokenList_push(state->targets, true, newToken)) {
          Token_unref(newToken);
          newToken = NULL;
          return Ring1_Result_Failure;
        }
      }
      i++;
    } else {
      if (j > 0) {
        if (copy(state->targets, buffer, j)) {
          return Ring1_Result_Failure;
        }
        j = 0;
      }
      Token* newToken;
      if (Token_clone(&newToken, token1)) {
        return Ring1_Result_Failure;
      }
      if (TokenList_push(state->targets, true, newToken)) {
        Token_unref(newToken);
        newToken = NULL;
        return Ring1_Result_Failure;
      }
      i++;
    }
  }
  if (copy(state->targets, buffer, j)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

/// @details
/// - if <code>w = u Dot Backslash v</code> then <code>w = u v</code>.
static Ring1_NoDiscardReturn() Ring1_Result
normalizeDots
  (
    State* state
  )
{
  bool lastWasSlash = false;
  int64_t size;
  if (TokenList_getSize(&size, state->sources)) {
    return Ring1_Result_Failure;
  }
  for (int64_t i = 0, n = size; i < n;) {
    Token* token1;
    if (TokenList_getAt(&token1, state->sources, i)) {
      return Ring1_Result_Failure;
    }
    // (I)
    if (token1->type == TokenType_Dot) {
      // If followed by slash, drop both.
      if (i < size - 1) {
        i++;
        Token* token2;
        if (TokenList_getAt(&token2, state->sources, i)) {
          return Ring1_Result_Failure;
        }
        if (token2->type == TokenType_BackSlash) {
          i++;
          state->modified++;
          continue;
        } else {
          Token* newToken;
          //
          if (Token_clone(&newToken, token1)) {
            return Ring1_Result_Failure;
          }
          if (TokenList_push(state->targets, false, newToken)) {
            Token_unref(newToken);
            newToken = NULL;
            return Ring1_Result_Failure;
          }
          //
          if (Token_clone(&newToken, token2)) {
            return Ring1_Result_Failure;
          }
          if (TokenList_push(state->targets, false, newToken)) {
            Token_unref(newToken);
            newToken = NULL;
            return Ring1_Result_Failure;
          }
          i++;
        }
      } else {
        Token* newToken;
        if (Token_clone(&newToken, token1)) {
          return Ring1_Result_Failure;
        }
        if (TokenList_push(state->targets, false, newToken)) {
          Token_unref(newToken);
          newToken = NULL;
          return Ring1_Result_Failure;
        }
        i++;
      }
    } else {
      Token* newToken;
      if (Token_clone(&newToken, token1)) {
        return Ring1_Result_Failure;
      }
      if (TokenList_push(state->targets, true, newToken)) {
        Token_unref(newToken);
        newToken = NULL;
        return Ring1_Result_Failure;
      }
      i++;
    }
  }
  return Ring1_Result_Success;
}

/// @details
/// - if <code>w = u Slash v</code> then <code>w = u BackwardSlash v</code>
/// - if <code>w = u BackwardSlash+ v</code> then <code>w = u BackwardSlash v</code>
static Ring1_NoDiscardReturn() Ring1_Result
normalizeDirectorySeparators
  (
    State* state
  )
{
  int64_t size;
  if (TokenList_getSize(&size, state->sources)) {
    return Ring1_Result_Failure;
  }
  bool lastWasSlash = false;
  for (int64_t i = 0, n = size; i < n;) {
    Token* token;
    if (TokenList_getAt(&token, state->sources, i)) {
      return Ring1_Result_Failure;
    }
    if (token->type == TokenType_BackSlash || token->type == TokenType_Slash) {
      if (lastWasSlash) {
        state->modified++;
        // Skip.
      }
      else {
        if (token->type == TokenType_Slash) {
          state->modified++;
        }
        // Emit backslash.
        Token* newToken;
        if (Token_create(&newToken, TokenType_BackSlash, token->start, token->length, "\\", sizeof("\\") - 1)) {
          return Ring1_Result_Failure;
        }
        if (TokenList_push(state->targets, true, newToken)) {
          Token_unref(newToken);
          newToken = NULL;
          return Ring1_Result_Failure;
        }
        lastWasSlash = true;
      }
    }
    else {
      lastWasSlash = false;
      Token* newToken;
      if (Token_create(&newToken, token->type, token->start, token->length, token->p, token->n)) {
        return Ring1_Result_Failure;
      }
      if (TokenList_push(state->targets, true, newToken)) {
        Token_unref(newToken);
        newToken = NULL;
        return Ring1_Result_Failure;
      }
    }
    ++i;
  }
  return Ring1_Result_Success;
}

/// @details
/// - if <code>w = e</code> then <code>w = .</code>
static Ring1_NoDiscardReturn() Ring1_Result
normalizeEmpty
  (
    State* state
  )
{
  int64_t size;
  if (TokenList_getSize(&size, state->sources)) {
    return Ring1_Result_Failure;
  }
  if (size == 0) {
    Token* token;
    if (Token_create(&token, TokenType_Dot, 0, 1, ".", sizeof(".") - 1)) {
      return Ring1_Result_Failure;
    }
    if (TokenList_push(state->targets, false, token)) {
      Token_unref(token);
      token = NULL;
      return Ring1_Result_Failure;
    }
    return Ring1_Result_Success;
  }
  else {
    return TokenList_pushAll(state->targets, state->sources);
  }
}

/// @details
/// - if <code>w = v BACKSLASH</code> then <code>w = v</code>
static Ring1_NoDiscardReturn() Ring1_Result
removeTrailingSlash
  (
    State* state
  )
{
  int64_t size;
  if (TokenList_getSize(&size, state->sources)) {
    return Ring1_Result_Failure;
  }
  if (size > 0) {
    Token* token;
    if (TokenList_getAt(&token, state->sources, size - 1)) {
      return Ring1_Result_Failure;
    }
    if (token->type == TokenType_BackSlash) {
      if (TokenList_pushAll(state->targets, state->sources)) {
        return Ring1_Result_Failure;
      }
      if (TokenList_removeAt(NULL, state->targets, true, size - 1)) {
        return Ring1_Result_Failure;
      }
    } else {
      return TokenList_pushAll(state->targets, state->sources);
    }
  } else {
    return TokenList_pushAll(state->targets, state->sources);
  }
}

Ring1_NoDiscardReturn() Ring1_Result
normalize
  (
    TokenList* tokens
  )
{
  // Do nothing if the path is the empty path.
  int64_t size;
  if (TokenList_getSize(&size, tokens)) {
    return Ring1_Result_Failure;
  }
  if (0 == size) {
    return Ring1_Result_Success;
  }
  static NormalizationFunction* functions[] = {
    &normalizeDirectorySeparators,
    &normalizeDots,
    &normalizeDotDots,
    &normalizeEmpty
  };
  static size_t const numberOfFunctions = sizeof(functions) / sizeof(NormalizationFunction*);
  State state = { .sources = NULL, .targets = NULL, .modified = 1 };
  if (TokenList_create(&state.targets)) {
    return Ring1_Result_Failure;
  }
  state.sources = tokens;
  while (state.modified) {
    state.modified = 0;
    for (size_t i = 0, n = numberOfFunctions; i < n; ++i) {
      if (functions[i](&state)) {
        TokenList_destroy(state.targets);
        state.targets = NULL;
        return Ring1_Result_Failure;
      }
      if (TokenList_clear(state.sources)) {
        TokenList_destroy(state.targets);
        state.targets = NULL;
        return Ring1_Result_Failure;
      }
      if (TokenList_pushAll(state.sources, state.targets)) {
        TokenList_destroy(state.targets);
        state.targets = NULL;
        return Ring1_Result_Failure;
      }
      if (TokenList_clear(state.targets)) {
        TokenList_destroy(state.targets);
        state.targets = NULL;
        return Ring1_Result_Failure;
      }
    }
  }
  TokenList_destroy(state.targets);
  state.targets = NULL;
#if 1
  // If there is a trailing slash, remove it.
  {
    size_t size;
    if (TokenList_getSize(&size, state.sources)) {
      return Ring1_Result_Failure;
    }
    if (size > 0) {
      Token* token;
      if (TokenList_getAt(&token, state.sources, size - 1)) {
        return Ring1_Result_Failure;
      }
      if (token->type == TokenType_BackSlash) {
        if (TokenList_removeAt(NULL, state.sources, true, size - 1)) {
          return Ring1_Result_Failure;
        }
      }
    }
  }
#endif
  return Ring1_Result_Success;
}
