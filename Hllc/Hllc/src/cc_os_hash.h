/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// @file cc_os_hash.h
/// @brief Hash functions.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.

#if !defined(CC_OS_HASH_H_INCLUDED)
#define CC_OS_HASH_H_INCLUDED


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


/// @ingroup hash
/// @brief Startup the hash module. Invoked by cc_startup().
/// @return @a true on success, @a false on failure.
bool cc_startup_hash();

/// @ingroup hash
/// @brief Shutdown the hash module. Invoked by cc_shutdown();
void cc_shutdown_hash();


/// @ingroup hash
/// @brief Compute the hash value of a pointer value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_p(void* v);

/// @ingroup hash
/// @brief Compute the hash value of an int8_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_i8(int8_t v);

/// @ingroup hash
/// @brief Compute the hash value of an int16_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_i16(int16_t v);

/// @ingroup hash
/// @brief Compute the hash value of an int32_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_i32(int32_t v);

/// @ingroup hash
/// @brief Compute the hash value of an int64_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_i64(int64_t v);

/// @ingroup hash
/// @brief Compute the hash value of an uint8_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_u8(uint8_t v);

/// @ingroup hash
/// @brief Compute the hash value of an uint16_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_u16(uint16_t v);

/// @ingroup hash
/// @brief Compute the hash value of an uint32_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_u32(uint32_t v);

/// @ingroup hash
/// @brief Compute the hash value of an uint64_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_u64(uint64_t v);

/// @ingroup hash
/// @brief Compute the hash value of a size_t value.
/// @param v The value.
/// @return The hash value.
size_t cc_hash_sz(size_t v);

/// @ingroup hash
/// @brief Compute the hash value of an array of Bytes.
/// @param p A pointer to the array.
/// @param n The length of the array.
/// @return The hash value.
/// @status CC_EINVAL @a p is 0.
size_t cc_hash_a(const char* p, size_t n);

#endif // CC_OS_HASH_H_INCLUDED
