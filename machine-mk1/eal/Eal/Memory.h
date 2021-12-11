#if !defined(MACHINE_EAL_MEMORY_H_INCLUDED)
#define MACHINE_EAL_MEMORY_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Types.h"



/// @brief Allocate a memory block of the specified length.
/// @param n The length, in Bytes, of the memory block is given by <code>n</code>.
/// The length can be @a 0.
/// @return A pointer to an array of @a n Bytes on success, @a NULL on failure. 
/// @remark This function fails if not enough memory can be allocated.
void* Machine_Eal_Memory_allocate(size_t n);

/// @brief Allocate a memory block of the specified length.
/// @param n, m The length, in Bytes, of the memory block is given by <code>n*m</code>.
/// The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
void* Machine_Eal_Memory_allocateArray(size_t n, size_t m);

/// @brief Reallocate a memory block to the specified length.
/// @param p A pointer to the memory block.
/// @param n The number of Bytes to reallocate the memory block to is given by <code>n</code>. Can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @success The old memory block was deallocated.
/// @failure The old memory block was not modified.
void* Machine_Eal_Memory_reallocate(void* p, size_t n);

/// @brief Reallocate a memory block of the specified length.
/// @param p A pointer to the memory block.
/// @param n, m The number of Bytes to reallocate the memory block to is given by <code>n*m</code>. The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
/// @success The old memory block was deallocated.
/// @failure The old memory block was not modified.
void* Machine_Eal_Memory_reallocateArray(void* p, size_t n, size_t m);

/// @brief Deallocate a memory block.
/// @param p A poitner to the memory block or a null pointer.
/// @remark If @a p is a null pointer, then this function is a no-operation.
void Machine_Eal_Memory_deallocate(void* p);

/// @brief Copy Byte values from one memory block to another.
/// @param p A pointer to the target memory block.
/// @param q A pointer tot he source memory block.
/// @param n The number of Bytes to copy.
/// @remark
/// If @a overlap is true, the memory blocks may overlap.
/// Otherwise they may not overlap.
void Machine_Eal_Memory_copy(void* p, void const* q, size_t n, bool overlap);

/// @brief Compare Byte values of one memory block to the Byte values of another memory block.
/// @param p A pointer to the first memory block.
/// @param q A pointer to the second memory block.
/// @param n The number of Bytes to compare.
/// @return
/// @a 0 if all values at indices 0, 1, ..., n - 1 are equal.
/// Otherwise the values at some index i are different in the memory blocks:
/// If the value in the first memory block is lower (greater) than the value in the second memory blocked,
/// a negative (positive) value is returned.
int Machine_Eal_Memory_compare(void const* p, void const* q, size_t n);

void Machine_Eal_Memory_zero(void* p, size_t n);

/// @brief Clone a memory block of the specified length.
/// @param p A pointer to the memory block.
/// @param n The length, in Bytes, of the memory block is given by <code>n</code>.
/// The length can be @a 0.
/// @return A pointer to an array of @a n Bytes on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
void* Machine_Eal_Memory_clone(void* p, size_t n);

/// @brief Clone a memory block of the specified length.
/// @param p A pointer to the memory block.
/// @param n, m The length, in Bytes, of the memory block is given by <code>n*m</code>.
/// The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
void* Machine_Eal_Memory_cloneArray(void* p, size_t n, size_t m);

#endif // MACHINE_EAL_MEMORY_H_INCLUDED
