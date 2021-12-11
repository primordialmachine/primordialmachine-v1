/// @file Collections/List.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_ILIST_H_INCLUDED)
#define MACHINE_COLLECTIONS_ILIST_H_INCLUDED



#if !defined(MACHINE_COLLECTIONS_PRIVATE)
#error("Do not include this file directly, include `_Collections.h` instead.")
#endif

#include "Collections/ICollection.h"

/// @brief If this evaluates to @a 1, then the Machine.IList.slice is provided.
#define Machine_IList_withReverse (0)

/// @brief If this evaluates to @a 1, then Machine.IList.slice is provided.
#define Machine_IList_withSlice (0)

/// @extends Machine.ICollection.
MACHINE_DECLARE_INTERFACETYPE(Machine_IList)

struct Machine_IList_Dispatch {
  Machine_InterfaceDispatch parent;

  Machine_Value (*getAt)(Machine_IList const* self, size_t index);
  void (*insertAt)(Machine_IList* self, size_t index, Machine_Value value);
  void (*prepend)(Machine_IList* self, Machine_Value value);
  void (*append)(Machine_IList* self, Machine_Value value);
  void (*removeAt)(Machine_IList* self, size_t index);
  void (*removeAtFast)(Machine_IList* self, size_t index);
#if defined(Machine_IList_withReverse) && Machine_IList_withReverse == 1
  void (*reverse)(Machine_IList* self);
#endif
#if defined(Machine_IList_withSlice) && Machine_IList_withSlice == 1
  Machine_IList* (*slice)(Machine_IList* self, size_t start, size_t length);
#endif
};

/// @brief Get the value at the specified index in this list.
/// @param self A pointer to this list.
/// @param index The index.
/// @return The value.
/// @error Machine_Status_IndexOutOfBounds @a index is smaller than @a 0 or greater than @a n where
/// @a n is the size of this list.
/// @error Machine_Status_InvalidArgument @a self is null.
Machine_Value Machine_IList_getAt(Machine_IList const* self, size_t index);

/// @brief Prepend a value to this list.
/// @param self This list.
/// @param value The value.
void Machine_IList_prepend(Machine_IList* self, Machine_Value value);

/// @brief Append a value to this list.
/// @param self This list.
/// @param value The value.
void Machine_IList_append(Machine_IList* self, Machine_Value value);

/// @brief Insert a value into this list at the specified index.
/// @param self A pointer to this list.
/// @param index The index.
/// @param value The value.
/// @abstract
void Machine_IList_insertAt(Machine_IList* self, size_t index, Machine_Value value);

/// @brief Remove the value at the specified index in this list.
/// This MAY NOT change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void Machine_IList_removeAt(Machine_IList* self, size_t index);

/// @brief Remove the value at the specified index in this list.
/// This MAY change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void Machine_IList_removeAtFast(Machine_IList* self, size_t index);

#if defined(Machine_IList_withReverse) && Machine_IList_withReverse == 1

/// @brief Reverse this list.
/// @param self This list.
void Machine_IList_reverse(Machine_IList* self);

#endif

#if defined(Machine_IList_withSlice) && Machine_IList_withSlice == 1

/// @brief Slice this list.
/// @param self This list.
/// @param start The start index of the slice.
/// @param length The length of the slice.
/// @return The slice.
Machine_IList* Machine_IList_slice(Machine_IList* self, size_t start, size_t length);

#endif

#endif // MACHINE_COLLECTIONS_ILIST_H_INCLUDED
