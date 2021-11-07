#if !defined(MACHINE_EAL_MEMORY_H_INCLUDED)
#define MACHINE_EAL_MEMORY_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Types.h"



/// @brief Allocate a memory block of the specified length.
/// @param n The length, in Bytes, of the memory block is given by <code>n</code>. Can be @a 0.
/// @return A pointer to an array of @a n Bytes on success, @a NULL on failure. 
/// @remark This function fails if not enough memory can be allocated.
void* c_alloc(size_t n);

/// @brief Allocate a memory block of the specified length.
/// @param n, m The length, in Bytes, of the memory block is given by <code>n*m</code>. The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
void* c_alloc_a(size_t n, size_t m);

/// @brief Reallocate a memory block to the specified length.
/// @param p A pointer to the memory block.
/// @param n The number of Bytes to reallocate the memory block to is given by <code>n</code>. Can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @success The old memory block was deallocated.
/// @failure The old memory block was not modified.
void* c_realloc(void* p, size_t n);

/// @brief Reallocate a memory block of the specified length.
/// @param p A pointer to the memory block.
/// @param n, m The number of Bytes to reallocate the memory block to is given by <code>n*m</code>. The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
/// @success The old memory block was deallocated.
/// @failure The old memory block was not modified.
void* c_realloc_a(void* p, size_t n, size_t m);

/// @brief Deallocate a memory block.
/// @param p A poitner to the memory block or a null pointer.
/// @remark If @a p is a null pointer, then this function is a no-operation.
void c_dealloc(void* p);



#endif // MACHINE_EAL_MEMORY_H_INCLUDED
