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


/// @brief If this evaluates to @a 1, then the Machine.List.slice is provided.
#define Machine_List_withReverse (0)

/// @brief If this evaluates to @a 1, then Machine.List.slice is provided.
#define Machine_List_withSlice (0)

/// @extends Machine.ICollection.
MACHINE_DECLARE_INTERFACETYPE(Machine_List)

struct Machine_List_Dispatch {
  Machine_InterfaceDispatch parent;

  Ring2_Value (*getAt)(Machine_List const* self, int64_t index);
  void (*insertAt)(Machine_List* self, int64_t index, Ring2_Value value);
  void (*prepend)(Machine_List* self, Ring2_Value value);
  void (*append)(Machine_List* self, Ring2_Value value);
  void (*removeAt)(Machine_List* self, int64_t index);
  void (*removeAtFast)(Machine_List* self, int64_t index);
#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1
  void (*reverse)(Machine_List* self);
#endif
#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1
  Machine_List* (*slice)(Machine_List* self, int64_t start, int64_t length);
#endif
};

/// @brief Get the value at the specified index in this list.
/// @param self A pointer to this list.
/// @param index The index.
/// @return The value.
/// @error Machine_Status_IndexOutOfBounds @a index is smaller than @a 0 or greater than @a n where
/// @a n is the size of this list.
/// @error Machine_Status_InvalidArgument @a self is null.
Ring2_Value Machine_List_getAt(Machine_List const* self, int64_t index);

/// @brief Prepend a value to this list.
/// @param self This list.
/// @param value The value.
void Machine_List_prepend(Machine_List* self, Ring2_Value value);

/// @brief Append a value to this list.
/// @param self This list.
/// @param value The value.
void Machine_List_append(Machine_List* self, Ring2_Value value);

/// @brief Insert a value into this list at the specified index.
/// @param self A pointer to this list.
/// @param index The index.
/// @param value The value.
void Machine_List_insertAt(Machine_List* self, int64_t index, Ring2_Value value);

/// @brief Remove the value at the specified index in this list.
/// This MAY NOT change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void Machine_List_removeAt(Machine_List* self, int64_t index);

/// @brief Remove the value at the specified index in this list.
/// This MAY change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void Machine_List_removeAtFast(Machine_List* self, int64_t index);

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

/// @brief Reverse this list.
/// @param self This list.
void Machine_List_reverse(Machine_List* self);

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

/// @brief Slice this list.
/// @param self This list.
/// @param start The start index of the slice.
/// @param length The length of the slice.
/// @return The slice.
Machine_List* Machine_List_slice(Machine_List* self, int64_t start, int64_t length);

#endif


#endif // RING2_LIBRARY_LIST_H_INCLUDED