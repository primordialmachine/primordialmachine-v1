#if !defined(MACHINE_EAL_INLINEARRAY_H_INCLUDED)
#define MACHINE_EAL_INLINEARRAY_H_INCLUDED

#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Types.h"

typedef int Machin_Eal_InlineArrayStatus;

/// @brief Result code returned by Machine_Eal_InlineArray_* functions.
/// Indicates success. Guaranteed to be the only Machine_Eal_InlineArray_* status code evaluating to @a 0.
#define Machine_Eal_InlineArray_Success (0)

/// @brief Result code returned by Machine_Eal_InlineArray_* functions.
/// Indicates an invalid argument.
#define Machine_Eal_InlineArray_InvalidArgument (1)

/// @brief Result code returned by Machine_Eal_InlineArray_* functions.
/// Indicates an allocation failed.
#define Machine_Eal_InlineArray_AllocationFailed (2)

typedef struct Machine_Eal_InlineArrayDispatch {
  size_t elementSize;
} Machine_Eal_InlineArrayDispatch;

typedef struct Machine_Eal_InlineArray {
  Machine_Eal_InlineArrayDispatch const *dispatch;
  void *elements;
  size_t size;
  size_t capacity;
} Machine_Eal_InlineArray;

/// @brief Initialize this array.
/// @param self A pointer to this array.
/// @param dispatch A pointer to the dispatch.
/// The struct must remain unchanged throughout the lifetime of this array.
/// @return @a 0 on success, a non-zero value on failure.
Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_initialize(
    Machine_Eal_InlineArray* self, Machine_Eal_InlineArrayDispatch const* dispatch);

/// @brief Uninitialize this array.
/// @param self A pointer to this array.
void Machine_Eal_InlineArray_uninitialize(Machine_Eal_InlineArray *self);

/// @brief Append to this array.
/// @param self A pointer to this array.
/// @param data A pointer to the data.
/// @return @a 0 on success, a non-zero value on failure.
Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_append(Machine_Eal_InlineArray* self,
                                                            void* data);

/// @brief Prepend to this array.
/// @param self A pointer to this array.
/// @param data A pointer to the data.
/// @return @a 0 on success, a non-zero value on failure.
Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_prepend(Machine_Eal_InlineArray* self,
                                                             void* data);

/// @brief Insert into to this array.
/// @param self A pointer to this array.
/// @param index the index at which to insert. Must be within @a 0 and @a n where @a n is the size of the array.
/// @param data A pointer to the data.
/// @return @a 0 on success, a non-zero value on failure.
Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_insert(Machine_Eal_InlineArray* self,
                                                            size_t index, void* data);

void* Machine_Eal_InlineArray_getAt(Machine_Eal_InlineArray* self, size_t index);

#endif // MACHINE_EAL_INLINEARRAY_H_INCLUDED
