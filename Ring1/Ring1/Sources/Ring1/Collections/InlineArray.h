#if !defined(RING1_COLLECTIONS_INLINEARRAY_H_INCLUDED)
#define RING1_COLLECTIONS_INLINEARRAY_H_INCLUDED

#include <stddef.h>
#include "Ring1/Result.h"
#include "Ring1/Annotations/_Include.h"

typedef struct Ring1_InlineArrayDispatch {
  size_t elementSize;
} Ring1_InlineArrayDispatch;

typedef struct Ring1_InlineArray {
  Ring1_InlineArrayDispatch const *dispatch;
  void *elements;
  size_t size;
  size_t capacity;
} Ring1_InlineArray;

/// @brief Initialize this array.
/// @param self A pointer to this array.
/// @param dispatch A pointer to the dispatch.
/// The struct must remain unchanged throughout the lifetime of this array.
/// @return @a 0 on success, a non-zero value on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_initialize
  (
    Ring1_InlineArray* self,
    Ring1_InlineArrayDispatch const* dispatch
  );

/// @brief Uninitialize this array.
/// @param self A pointer to this array.
void
Ring1_InlineArray_uninitialize
  (
    Ring1_InlineArray *self
  );

/// @brief Append to this array.
/// @param self A pointer to this array.
/// @param data A pointer to the data.
/// @return @a 0 on success, a non-zero value on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_append
  (
    Ring1_InlineArray* self,
    void* data
  );

/// @brief Prepend to this array.
/// @param self A pointer to this array.
/// @param data A pointer to the data.
/// @return @a 0 on success, a non-zero value on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_prepend
  (
    Ring1_InlineArray* self,
    void* data
  );

/// @brief Insert into to this array.
/// @param self A pointer to this array.
/// @param index the index at which to insert. Must be within @a 0 and @a n where @a n is the size of the array.
/// @param data A pointer to the data.
/// @return @a 0 on success, a non-zero value on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_insert
  (
    Ring1_InlineArray* self,
    size_t index,
    void* data
  );

void*
Ring1_InlineArray_getAt
  (
    Ring1_InlineArray* self,
    size_t index
  );

#endif // RING1_COLLECTIONS_INLINEARRAY_H_INCLUDED
