#if !defined(MACHINE_RUNTIME_POINTERARRAY_H_INCLUDED)
#define MACHINE_RUNTIME_POINTERARRAY_H_INCLUDED


#include "./../Machine.h"


/**
 * @brief An array of pointers to objects or null pointers.
 */
MACHINE_DECLARE_CLASSTYPE(Machine_PointerArray)

/**
 * @brief Create an object array.
 * @return The object array.
 * @error Machine_Status_AllocationFailed An allocation failed.
 */
Machine_PointerArray* Machine_PointerArray_create();

/**
 * @brief Clear this object array.
 * @param self A pointer to this object array.
 */
void Machine_PointerArray_clear(Machine_PointerArray* self);

/**
 * @brief Get the object at the specified index in this object array.
 * @param self A pointer to this object array.
 * @param index The index.
 * @return A pointer to the object or the null pointer.
 * @error Machine_Status_IndexOutOfBounds @a index is smaller than @a 0 or greater than @a n where @a n is the size of this object array.
 * @error Machine_Status_InvalidArgument @a self is null.
 */
void *Machine_PointerArray_getAt(Machine_PointerArray* self, size_t index);

/**
 * @brief Get the size of this object array.
 * @param self This object array.
 * @return The size of this object array.
 * @error Machine_Status_InvalidArgument @a self is null.
 */
size_t Machine_PointerArray_getSize(Machine_PointerArray* self);

/**
 * @brief Prepend a pointer to this pointer array.
 * @param self This pointer array.
 * @param pointer The pointer.
 */
void Machine_PointerArray_prepend(Machine_PointerArray* self, void* pointer);

/**
 * @brief Append a pointer to this pointer array.
 * @param self This pointer array.
 * @param pointer The pointer.
 */
void Machine_PointerArray_append(Machine_PointerArray* self, void* pointer);

/**
 * @brief Insert a pointer into this pointer array at the specified index.
 * @param self This pointer array.
 * @param index The index.
 * @param pointer The pointer.
 */
void Machine_PointerArray_insert(Machine_PointerArray* self, size_t index, void* pointer);


#endif // MACHINE_RUNTIME_POINTERARRAY_H_INCLUDED
