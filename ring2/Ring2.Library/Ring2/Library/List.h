// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/List.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_LIST_H_INCLUDED)
#define RING2_LIBRARY_LIST_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/List.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @brief If defined and evaluateing to @a 1,
/// then the Ring2.List.slice is provided.
#define Ring2_List_withReverse (0)

/// @brief If defined and evaluating to @a 1,
/// then Ring2.List.slice is provided.
#define Ring2_List_withSlice (0)

/// @extends Machine.ICollection.
MACHINE_DECLARE_INTERFACETYPE(Ring2_List)

struct Ring2_List_Dispatch {
  Machine_InterfaceDispatch parent;

  Ring2_Value (*getAt)(Ring2_List const* self, int64_t index);
  void (*insertAt)(Ring2_List* self, int64_t index, Ring2_Value value);
  void (*prepend)(Ring2_List* self, Ring2_Value value);
  void (*append)(Ring2_List* self, Ring2_Value value);
  void (*removeAt)(Ring2_List* self, int64_t index);
  void (*removeAtFast)(Ring2_List* self, int64_t index);
#if defined(Ring2_List_withReverse) && Ring2_List_withReverse == 1
  void (*reverse)(Ring2_List* self);
#endif
#if defined(Ring2_List_withSlice) && Ring2_List_withSlice == 1
  Ring2_List* (*slice)(Ring2_List* self, int64_t start, int64_t length);
#endif
};

/// @brief Get the value at the specified index in this list.
///
/// @param self A pointer to this list.
/// @param index The index.
///
/// @return The value.
/// 
/// @error Ring1_Status_IndexOutOfBounds
/// @a index is smaller than @a 0 or greater than @a n where @a n is the size of this list.
/// 
/// @error Ring1_Status_InvalidArgument
/// @a self is null.
Ring2_Value
Ring2_List_getAt
  (
    Ring2_List const* self,
    int64_t index
  );

/// @brief Prepend a value to this list.
/// @param self This list.
/// @param value The value.
void
Ring2_List_prepend
  (
    Ring2_List* self,
    Ring2_Value value
  );

/// @brief Append a value to this list.
/// @param self This list.
/// @param value The value.
void
Ring2_List_append
  (
    Ring2_List* self,
    Ring2_Value value
  );

/// @brief Insert a value into this list at the specified index.
/// @param self A pointer to this list.
/// @param index The index.
/// @param value The value.
void
Ring2_List_insertAt
  (
    Ring2_List* self,
    int64_t index,
    Ring2_Value value
  );

/// @brief Remove the value at the specified index in this list.
/// This MAY NOT change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void
Ring2_List_removeAt
  (
    Ring2_List* self,
    int64_t index
  );

/// @brief Remove the value at the specified index in this list.
/// This MAY change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void
Ring2_List_removeAtFast
  (
    Ring2_List* self,
    int64_t index
  );

#if defined(Ring2_List_withReverse) && Ring2_List_withReverse == 1

/// @brief Reverse this list.
/// @param self This list.
void
Ring2_List_reverse
  (
    Ring2_List* self
  );

#endif

#if defined(Ring2_List_withSlice) && Ring2_List_withSlice == 1

/// @brief Slice this list.
/// @param self This list.
/// @param start The start index of the slice.
/// @param length The length of the slice.
/// @return The slice.
Ring2_List*
Ring2_List_slice
  (
    Ring2_List* self,
    int64_t start,
    int64_t length
  );

#endif


#endif // RING2_LIBRARY_LIST_H_INCLUDED
