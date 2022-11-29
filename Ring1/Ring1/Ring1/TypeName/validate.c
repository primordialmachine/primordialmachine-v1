#include "Ring1/TypeName/validate.h"

#include "Ring1/Atom/_Include.h"
#include "Ring1/Intrinsic.h"
#include "Ring1/Memory.h"
#include "Ring1/ByteBuffer.h"
#include "Ring1/Collections/_Include.h"

#define START (255+1)
#define END (255+2)

typedef struct State {
  const char* start;
  const char* end;
  const char* current;
  short symbol;
} State;

Ring1_Inline() Ring1_CheckReturn() void
next
  (
    State *state
  )
{
  if (state->current == state->end) {
    return;
  }
  state->current++;
  if (state->current == state->end) {
    state->symbol = END;
  } else {
    state->symbol = *state->current;
  }
}

Ring1_Inline() Ring1_CheckReturn() bool
isEnd
  (
    State *state
  )
{
  return END  == state->symbol;
}

Ring1_Inline() Ring1_CheckReturn() bool
isPeriod
  (
    State *state
  )
{
  return '.'  == state->symbol;
}

Ring1_Inline() Ring1_CheckReturn() bool
isUnderscore
  (
    State *state
  )
{
  return '_'  == state->symbol;
}

Ring1_Inline() Ring1_CheckReturn() bool
isAlphabetic
  (
    State *state
  )
{
  return ('a' <= state->symbol && state->symbol <= 'z')
      || ('A' <= state->symbol && state->symbol <= 'Z');
}

Ring1_Inline() Ring1_CheckReturn() bool
isNumeric
  (
    State *state
  )
{
  return ('0' <= state->symbol && state->symbol <= '9');
}

static Ring1_CheckReturn() Ring1_Result
onNameComponent
  (
    State *state
  )
{
  if (!isAlphabetic(state) && !isUnderscore(state)) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    return Ring1_Result_Failure;
  }
  do {
    next(state);
  } while (isAlphabetic(state) || isUnderscore(state) || isNumeric(state));
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
isScalarTypeName
  (
    const char *p
  )
{
  State state;
  state.start = p;
  state.end = p + crt_strlen(p);
  state.current = p;
  state.symbol = START;

  next(&state);
  if (onNameComponent(&state)) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    return Ring1_Result_Failure;
  }
  while (isPeriod(&state)) {
    next(&state);
    if (onNameComponent(&state)) {
      Ring1_Status_set(Ring1_Status_InvalidSyntactics);
      return Ring1_Result_Failure;
    }
  }
  if (!isEnd(&state)) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
