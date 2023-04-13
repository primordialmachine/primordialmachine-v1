#include "Ring1/FileSystem/Path/parse.h"

typedef struct {
  const char* start;
  const char* end;
} Input;

typedef struct {
  const char* start;
  const char* end;
} Parse;

typedef struct  {
  Input input;
  Parse parse;
} State;

#include <setjmp.h>

Ring1_Inline() void
PUSH1
  (
    jmp_buf* j,
    TokenList* tokens,
    uint8_t type,
    State *state
  )
{
  Token* token;
  if (Token_create(&token,
                   type,
                   state->parse.start - state->input.start,
                   state->parse.end - state->parse.start,
                   state->parse.start,
                   state->parse.end - state->parse.start)) {
    longjmp(*j, -1);
  }
  if (TokenList_push(tokens, true, token)) {
    Token_unref(token);
    longjmp(*j, -1);
  }
}

Ring1_Inline() bool
ISSLASH
  (
    State* state
  )
{
  return state->parse.end != state->input.end
      && *state->parse.end == '/';
}

Ring1_Inline() bool
ISBACKSLASH
  (
    State* state
  )
{
  return state->parse.end != state->input.end
      && *state->parse.end == '\\';
}

Ring1_Inline() bool
ISPERIOD
  (
    State* state
  )
{
  return state->parse.end != state->input.end
      && *state->parse.end == '.';
}

Ring1_Inline() bool
ISCOLON
  (
    State* state
  )
{
  return state->parse.end != state->input.end
      && *state->parse.end == ':';
}

Ring1_Inline() bool
ISALPHA
  (
    State* state
  )
{
  if (state->parse.end == state->input.end) {
    return false;
  } else {
    return ('a' <= *state->parse.end && *state->parse.end <= 'z')
        || ('A' <= *state->parse.end && *state->parse.end <= 'Z');
  }
}

Ring1_Inline() bool
ISEND
  (
    State* state
  )
{
  return state->parse.end == state->input.end;
}

Ring1_Inline() bool
ISSPECIAL
  (
    State* state
  )
{
  return ISBACKSLASH(state)
      || ISCOLON(state)
      || ISPERIOD(state)
      || ISSLASH(state);
}


/// @code
/// DRIVEPREFIX := ALPHA COLON
/// @endcode
Ring1_Inline() bool
parseRootName
  (
    jmp_buf *j,
    TokenList *tokens,
    State *state
  )
{
  if (!ISALPHA(state)) {
    return false;
  }
  state->parse.end++;
  if (!ISCOLON(state)) {
    state->parse.end--;
    return false;
  }
  state->parse.end++;

  PUSH1(j, tokens, TokenType_DrivePrefix, state);
  state->parse.start = state->parse.end;

  return true;
}

// @code
// DOT := '.'
// DOTDOT := '..'
// DOT_OR_DOTDOT := DOT | DOTDOT
// @code
Ring1_Inline() bool
parseDotOrDotDot 
  (
    jmp_buf *j,
    TokenList* tokens,
    State* state
  )
{
  if (!ISPERIOD(state)) {
    return false;
  }
  state->parse.end++;

  uint8_t type = TokenType_Dot;
  if (ISPERIOD(state)) {
    state->parse.end++;
    type = TokenType_DotDot;
  }

  PUSH1(j, tokens, type, state);
  state->parse.start = state->parse.end;

  return true;
}

Ring1_Inline() void
parse1
  (
    jmp_buf *j,
    TokenList* tokens,
    State* state
  )
{
  if (ISEND(state)) {
    PUSH1(j, tokens, TokenType_Empty, state);
    state->parse.start = state->parse.end;
  } else {
    parseRootName(j, tokens, state);
    while (!ISEND(state)) {
      if (ISPERIOD(state)) {
        parseDotOrDotDot(j, tokens, state);
      } else if (ISSLASH(state)) {
        state->parse.end++;
        PUSH1(j, tokens, TokenType_Slash, state);
        state->parse.start = state->parse.end;
      } else if (ISBACKSLASH(state)) {
        state->parse.end++;
        PUSH1(j, tokens, TokenType_BackSlash, state);
        state->parse.start = state->parse.end;
      } else if (!ISSPECIAL(state) && !ISEND(state)) {
        do {
          state->parse.end++;
        } while (!ISSPECIAL(state) && !ISEND(state));
        PUSH1(j, tokens, TokenType_Text, state);
        state->parse.start = state->parse.end;
      }
    }
  }
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Path_parse
  (
    TokenList **result,
    const char* s,
    size_t sn
  )
{
  TokenList* tokens;
  if (TokenList_create(&tokens)) {
    Ring1_Result_Failure;
  }

  State state;

  state.input.start = s;
  state.input.end = s + sn;
  state.parse.start = s;
  state.parse.end = s;

  jmp_buf env;
  if (!setjmp(env)) {
    parse1(&env, tokens, &state);
    *result = tokens;
    return Ring1_Result_Success;
  } else {
    TokenList_destroy(tokens);
    tokens = NULL;
    return Ring1_Result_Failure;
  }
}
