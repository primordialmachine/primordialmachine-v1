#if !defined(MACHINE_RUNTIME_LIST_H_INCLUDED)
#define MACHINE_RUNTIME_LIST_H_INCLUDED

#include "./Runtime/Collection.h"

#define Machine_List_withReverse (0)

MACHINE_DECLARE_CLASSTYPE(Machine_List)

struct Machine_List {
  Machine_Collection parent;
  Machine_Value(*getAt)(Machine_List* self, size_t index);
  void(*insert)(Machine_List* self, size_t index, Machine_Value value);
  void(*prepend)(Machine_List* self, Machine_Value value);
  void(*append)(Machine_List* self, Machine_Value value);
#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1
  void(*reverse)(Machine_List* self);
#endif
};

/// @brief Construct this list.
/// @param self A pointer to this list.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_List_construct(Machine_List* self, size_t numberOfArguments, const Machine_Value* arguments);

/// @brief Get the value at the specified index in this list.
/// @param self A pointer to this list.
/// @param index The index.
/// @return The value.
/// @error Machine_Status_IndexOutOfBounds @a index is smaller than @a 0 or greater than @a n where @a n is the size of this list.
/// @error Machine_Status_InvalidArgument @a self is null.
/// @abstract
Machine_Value Machine_List_getAt(Machine_List* self, size_t index);

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
void Machine_List_insert(Machine_List* self, size_t index, Machine_Value value);

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

/// @brief Reverse this list.
/// @param self This list.
/// @abstract
void Machine_List_reverse(Machine_List* self);

#endif

#endif // MACHINE_RUNTIME_LIST_H_INCLUDED
