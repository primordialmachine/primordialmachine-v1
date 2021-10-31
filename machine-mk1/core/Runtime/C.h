/// @file Runtime/C.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_C_H_INCLUDED)
#define MACHINE_RUNTIME_C_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>



#if defined(INLINE)
#error('INLINE already defined')
#endif
/// @brief Function annotation. Annotate a function as an inline function.
/// Use as
/// @code
/// INLINE void f() { ... }
/// @endcode
#define INLINE static inline

#if defined(NORETURN)
#error('NORETURN already defined')
#endif
/// @brief Function annotation. Annotate a function as not returning function.
/// Use as
/// @code
/// NORETURN void f() { ... }
/// @endcode
#define NORETURN __declspec(noreturn)

#if defined(DEPRECATED)
#error('DEPRECATED already defined')
#endif
/// @brief Function, structure, field, and variable annotation. Annotate a function, structure, field, or variable as deprecated.
/// Use as
/// @code
/// DEPRECATED
/// static int v = 0;
/// @endcode
#define DEPRECATED



/// @brief Safe multiplcation.
/// @param n The multiplicant.
/// @param m The multiplier.
/// @param k A pointer to a variable or a null pointer.
/// @return @a true if the product <code>n*m</code> does not overflow, @a false otherwise.
/// If @a k is not null, the variable pointed to is assigned the product if it does not overflow and is assigned <code>(size_t)-1</code> otherwise.
bool c_safe_mul_sz(size_t n, size_t m, size_t* k);



/// @brief Allocate a memory block of the specified length.
/// @param n The length, in Bytes, of the memory block is given by <code>n</code>. Can be @a 0.
/// @return A pointer to an array of @a n Bytes on success, @a NULL on failure. 
/// @remark This function fails if not enough memory can be allocated.
void *c_alloc(size_t n);

/// @brief Allocate a memory block of the specified length.
/// @param n, m The length, in Bytes, of the memory block is given by <code>n*m</code>. The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
void *c_alloc_a(size_t n, size_t m);

/// @brief Reallocate a memory block to the specified length.
/// @param p A pointer to the memory block.
/// @param n The number of Bytes to reallocate the memory block to is given by <code>n</code>. Can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @success The old memory block was deallocated.
/// @failure The old memory block was not modified.
void *c_realloc(void* p, size_t n);

/// @brief Reallocate a memory block of the specified length.
/// @param p A pointer to the memory block.
/// @param n, m The number of Bytes to reallocate the memory block to is given by <code>n*m</code>. The length can be @a 0.
/// @return A pointer to a memory block of the specified length on success, @a NULL on failure.
/// @remark This function fails if not enough memory can be allocated.
/// @remark This function fails if the product <code>n*m</code> would overflow.
/// @success The old memory block was deallocated.
/// @failure The old memory block was not modified.
void* c_realloc_a(void *p, size_t n, size_t m);

/// @brief Deallocate a memory block.
/// @param p A poitner to the memory block or a null pointer.
/// @remark If @a p is a null pointer, then this function is a no-operation.
void c_dealloc(void* p);



/// @brief Get the minimum of two values.
/// @param x The first value.
/// @param y The second value.
/// @return The minimum of the first and the second value.
INLINE size_t c_min_sz(size_t x, size_t y) {
  return x < y ? x : y;
}

/// @brief Get the maximum of two values.
/// @param x The first value.
/// @param y The second value.
/// @return The maximum of the first and the second value.
INLINE size_t c_max_sz(size_t x, size_t y) {
  return x > y ? x : y;
}



#endif // MACHINE_RUNTIME_C_H_INCLUDED
