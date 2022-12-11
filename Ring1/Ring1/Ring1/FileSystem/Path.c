#include "Ring1/FileSystem/Path.h"

#include "Ring1/Memory.h"
#include "Ring1/ReferenceCounter.h"
#include "Ring1/Status.h"
#include "Ring1/Intrinsic/Crt.h"

#include <stdbool.h>

typedef struct State {
  const char* start;
  const char* end;
  const char* current;
} State;

/// @brief Get the drive prefix if any
/// <code>
/// ('a'-'z'|'A - 'Z') colon
/// </code>
/// @param span
/// assigned the index and the length of the drive prefix if it exists.
/// assigned (size_t)-1 both to index and length otherwise.
static Ring1_Result
parseRootName
  (
    bool *result,
    State *state
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!state) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  const char *old = state->current;
  // Fast fail.
  if (!(state->current - state->end) < 2) {
    *result = false;
    return Ring1_Result_Success;
  }
  if (('a' <= *state->current && *state->current <= 'z') || ('A' <= *state->current && *state->current <= 'Z')) {
    state->current++;
  } else {
    state->current = old;
    *result = false;
    return Ring1_Result_Success;
  }
  if (*state->current == ':') {
    state->current++;
  } else {
    state->current = old;
    *result = false;
    return Ring1_Result_Success;
  }
  *result = true;
  return Ring1_Result_Success;
}

/// @details
/// - replace any forward slash with a backward slash.
/// - replace any sequence of two or more backward slashes with a single backward slash.
static Ring1_Result
normalizeDirectorySeparators
  (
    char** result,
    const char* source
  )
{
  size_t source_l = crt_strlen(source);
  char* target;
  if (Ring1_Memory_allocate(&target, source_l + 1)) {
    return Ring1_Result_Failure;
  }
  size_t target_l = 0;
  bool lastWasDirectorySeparator = false;
  const char* source_cur = source;
  const char* source_end = source + source_l;
  char* target_cur = target;
  while (source_cur != source_end) {
    if (*source_cur == '/' || *source_cur == '\\') {
      if (!lastWasDirectorySeparator) {
        *target_cur = '\\';
        target_cur++;
        source_cur++;
        target_l++;
      }
      else {
        source_cur++;
      }
    }
    else {
      lastWasDirectorySeparator = false;
      *target_cur = *source_cur;
      target_cur++;
      source_cur++;
      target_l++;
    }
  }
  if (target_l < source_l) {
    char* target1;
    if (Ring1_Memory_allocate(&target1, target_l + 1)) {
      Ring1_Memory_deallocate(target);
      return Ring1_Result_Failure;
    }
    Ring1_Memory_copyFast(target1, target, target_l);
    Ring1_Memory_deallocate(target);
    target = target1;
  }
  target[target_l] = '\0';
  *result = target;
  return Ring1_Result_Success;
}


struct Ring1_FileSystem_Path {
  Ring1_ReferenceCounter referenceCount;
  char *string;
};

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Path_create
  (
    Ring1_FileSystem_Path** result,
    const char* string
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!string) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Path))) {
    return Ring1_Result_Failure;
  }
  char* temporary;
  if (normalizeDirectorySeparators(&temporary, string)) {
    Ring1_Memory_deallocate(self);
    return Ring1_Result_Failure;
  }
  self->referenceCount = 1;
  self->string = temporary;
  *result = self;
  return Ring1_Result_Success;
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
    Ring1_Memory_deallocate(self->string);
    Ring1_Memory_deallocate(self);
  }
}
