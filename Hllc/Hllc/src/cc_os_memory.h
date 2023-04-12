/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// @file cc_os_memory.h
/// @brief Operating system level memory allocation/deallocation/reallocation functionality.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.

#if !defined(CC_OS_MEMORY_H_INCLUDED)
#define CC_OS_MEMORY_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>


/// @brief Startup the memory module. Invoked by cc_startup().
/// @return @a true on success, @a false on failure.
bool cc_startup_memory();

/// @brief Shutdown the memory module. Invoked by cc_shutdown();
void cc_shutdown_memory();

/// @brief Log memory module statistics.
void cc_log_memory();


/// @brief Allocate a memory block.
/// @param n The size of the memory. Can be @a 0.
/// @return A pointer to a memory block of at least <code>element_size * number_of_elements</code> Bytes on success, a null pointer on failure.
/// @error CC_ENOMEM The allocation failed.
/// @remark If this function fails, it sets the by-thread status variable.
/// Use cc_get_status to obtain detailed error information.
void* cc_zalloc(size_t n);

/// @brief Allocate a new memory block.
/// @param n, m The size of the memory block is the product <code>n * m</code>. Both @a n and @a m can be @a 0.
/// @return A pointer to a memory block of at least <code>n * m</code> Bytes on success, a null pointer on failure.
/// @error CC_EOVERFLOW <code>n * m</code> overflows.
/// @error CC_ENOMEM The allocation failed.
/// @remark If this function fails, it sets the by-thread status variable.
/// Use cc_get_status to obtain detailed error information.
void* cc_zalloc_a(size_t n, size_t m);

/// @brief Allocate a memory block.
/// @param n The number of Bytes to allocate. Can be @a 0.
/// @return A pointer to a memory block of at least <code>element_size * number_of_elements</code> Bytes on success, a null pointer on failure.
/// @error CC_ENOMEM The allocation failed.
/// @remark If this function fails, it sets the by-thread status variable.
/// Use cc_get_status to obtain detailed error information.
void* cc_alloc(size_t n);

/// @brief Allocate a new memory block.
/// @param n, m The size of the memory block is the product <code>n * m</code>. Both @a n and @a m can be @a 0.
/// @return A pointer to a memory block of at least <code>n * m</code> Bytes on success, a null pointer on failure.
/// @error CC_EOVERFLOW <code>n * m</code> overflows.
/// @error CC_ENOMEM The allocation failed.
/// @remark If this function fails, it sets the by-thread status variable.
/// Use cc_get_status to obtain detailed error information.
void* cc_alloc_a(size_t n, size_t m);

/// @brief Allocate a new memory block, deallocating an existing memory block.
/// @param p A pointer to an existing memory block.
/// @param n The size of the new memory block. Can be @a 0.
/// @return A pointer to a memory block of at least <code>n</code> Bytes on success, a null pointer on failure.
/// @remark The contents of the old and the new memory block remain unchanged up to the lesser of the old and new sizes.
/// If the new size is greater than the old size, the contents beyond the old size are undefined.
/// @error CC_ENOMEM The allocation failed.
/// @remark If this function fails, it sets the by-thread status variable.
/// Use cc_get_status to obtain detailed error information.
void* cc_realloc(void* p, size_t size);

/// @brief Allocate a new memory block, deallocating an existing memory block,
/// @param p A pointer to an existing memory block.
/// @param n, m The size of the new memory block. Can be @a 0.
/// @return A pointer to a memory block of at least <code>n * m</code> Bytes on success, a null pointer on failure.
/// @remark The contents of the old and the new memory block remain unchanged up to the lesser of the old and new sizes.
/// If the new size is greater than the old size, the contents beyond the old size are undefined.
/// @remark The old memory block is was
/// @error CC_EOVERFLOW <code>n * m</code> overflows.
/// @error CC_ENOMEM The allocation failed.
/// @remark If this function fails, it sets the by-thread status variable.
/// Use cc_get_status to obtain detailed error information.
void* cc_realloc_a(void* p, size_t n, size_t m);

/// @brief Deallocate a memory block.
/// @param p A pointer to a memory block or a null pointer.
void cc_dealloc(void* p);


#endif // CC_OS_MEMORY_H_INCLUDED
