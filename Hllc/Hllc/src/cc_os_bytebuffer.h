/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// @file cc_os_bytebuffer.h
/// @brief Dynamically resizing buffer for Bytes.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.

#if !defined(CC_OS_BYTEBUFFER_H_INCLUDED)
#define CC_OS_BYTEBUFFER_H_INCLUDED

#include "cc_os.h"

/// @brief A dynamically resizing buffer for Bytes.
/// @extends cc_object
CC_DECLARE_CLASS(cc_bytebuffer, cc_object)

struct cc_bytebuffer
{
  cc_object parent;
  char* p;
  size_t sz, cp;
};

/// @brief Create a Byte buffer.
/// @return The Byte buffer.
cc_bytebuffer* cc_bytebuffer_create();

/// @brief Increase the capacity of a Byte buffer.
/// @param self A pointer to the Byte buffer.
/// @param additional The amount to increase the capacity by.
/// @error CC_EINVAL buffer is a null pointer.
/// @error CC_EOVERFLOW sum of current capacity an additional capacity would overflow.
/// @error CC_ENOMEM allocation failed.
void cc_bytebuffer_increase_capacity(cc_bytebuffer* self, size_t additional);

/// @brief Prepend one Byte to a Byte buffer.
/// @param self A pointer to the Byte buffer.
/// @param byte The Byte.
void cc_bytebuffer_prepend_byte(cc_bytebuffer* self, char byte);

/// @brief Append one Byte to a Byte buffer.
/// @param self A pointer to the Byte buffer.
/// @param byte The Byte.
void cc_bytebuffer_append_byte(cc_bytebuffer* self, char byte);

/// @brief Prepend Bytes to a Byte buffer.
/// @param buffer A pointer to the Byte buffer.
/// @param bytes A pointer to the Bytes.
/// @param number_of_bytes The number of Bytes.
void cc_bytebuffer_prepend_bytes(cc_bytebuffer* self, const char* bytes, size_t number_of_bytes);

/// @brief Append Bytes to a Byte buffer.
/// @param buffer A pointer to the Byte buffer.
/// @param bytes A pointer to the Bytes.
/// @param number_of_bytes The number of Bytes.
void cc_bytebuffer_append_bytes(cc_bytebuffer* self, const char* bytes, size_t number_of_bytes);

/// @brief Map 'a' -> 'A' .. 'z' -> 'Z'.
/// @param self A pointer to the Byte buffer.
void cc_bytebuffer_to_upper(cc_bytebuffer* self);

/// @brief Map 'A' -> 'a' .. 'Z' -> 'z'.
/// @param self A pointer to the Byte buffer.
void cc_bytebuffer_to_lower(cc_bytebuffer* self);

/// @brief Replace @a old by @a new.
/// @param self A pointer to the Byte buffer.
/// @param old The old value.
/// @param new The new value.
void cc_bytebuffer_replace(cc_bytebuffer* self, char old, char new);

/// @brief Set the number of elements to @a 0.
/// @param self A pointer to the Byte buffer.
void cc_bytebuffer_clear(cc_bytebuffer* self);

/// @brief Get the size of the Byte buffer.
/// @param self A pointer to the Byte buffer.
/// @return The size.
size_t cc_bytebuffer_get_size(cc_bytebuffer* self);

/// @brief Get the available free capacity.
/// @param self A pointer to the Byte buffer.
/// @return The available free capacity.
size_t cc_bytebuffer_get_free_capacity(cc_bytebuffer* self);

/// @brief Ensure the available free capacity is greater than or equal to a required free capacity.
/// @param self A pointer to the Byte buffer.
/// @param required The required free capacity.
void cc_bytebuffer_require_free_capacity(cc_bytebuffer* self, size_t required);

#endif // CC_OS_BYTEBUFFER_H_INCLUDED
