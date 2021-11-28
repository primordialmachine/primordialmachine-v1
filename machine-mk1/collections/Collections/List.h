/// @file Collections/List.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_LIST_H_INCLUDED)
#define MACHINE_COLLECTIONS_LIST_H_INCLUDED



#if !defined(MACHINE_COLLECTIONS_PRIVATE)
#error("Do not include this file directly, include `_Collections.h` instead.")
#endif

#include "Collections/Collection.h"



#define Machine_List_withReverse (0)
#define Machine_List_withSlice (0)

/// @brief A list.
MACHINE_DECLARE_CLASSTYPE(Machine_List)

struct Machine_List_Class {
  Machine_Collection_Class parent;
  Machine_Value(*getAt)(const Machine_List* self, size_t index);
  void(*insertAt)(Machine_List* self, size_t index, Machine_Value value);
  void(*prepend)(Machine_List* self, Machine_Value value);
  void(*append)(Machine_List* self, Machine_Value value);
  void(*removeAt)(Machine_List* self, size_t index);
  void(*removeAtFast)(Machine_List* self, size_t index);
#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1
  void(*reverse)(Machine_List* self);
#endif
#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1
  Machine_List* (*slice)(Machine_List* self, size_t start, size_t length);
#endif
};

struct Machine_List {
  Machine_Collection parent;
  size_t size;
  size_t capacity;
  Machine_Value* elements;
};

/// @brief Construct this list.
/// @param self A pointer to this list.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_List_construct(Machine_List* self, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Create an empty list.
/// @return The list.
Machine_List* Machine_List_create();

/// @brief Get the value at the specified index in this list.
/// @param self A pointer to this list.
/// @param index The index.
/// @return The value.
/// @error Machine_Status_IndexOutOfBounds @a index is smaller than @a 0 or greater than @a n where @a n is the size of this list.
/// @error Machine_Status_InvalidArgument @a self is null.
/// @abstract
Machine_Value Machine_List_getAt(Machine_List const* self, size_t index);

/// @brief Prepend a value to this list.
/// @param self This list.
/// @param value The value.
void Machine_List_prepend(Machine_List* self, Machine_Value value);

/// @brief Append a value to this list.
/// @param self This list.
/// @param value The value.
void Machine_List_append(Machine_List* self, Machine_Value value);

/// @brief Insert a value into this list at the specified index.
/// @param self A pointer to this list.
/// @param index The index.
/// @param value The value.
/// @abstract
void Machine_List_insertAt(Machine_List* self, size_t index, Machine_Value value);

/// @brief Remove the value at the specified index in this list.
/// This MAY NOT change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void Machine_List_removeAt(Machine_List* self, size_t index);

/// @brief Remove the value at the specified index in this list.
/// This MAY change the order of elements.
/// @param self A pointer to this list.
/// @param index The index.
void Machine_List_removeAtFast(Machine_List* self, size_t index);

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

/// @brief Reverse this list.
/// @param self This list.
/// @abstract
void Machine_List_reverse(Machine_List* self);

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

/// @brief Slice this list.
/// @param self This list.
/// @param start The start index of the slice.
/// @param length The length of the slice.
/// @return The slice.
Machine_List* Machine_List_slice(Machine_List* self, size_t start, size_t length);

#endif



#endif // MACHINE_COLLECTIONS_LIST_H_INCLUDED
