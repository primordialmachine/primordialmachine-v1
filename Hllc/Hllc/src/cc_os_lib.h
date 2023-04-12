/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
/**
 * @file cc_os_lib.h
 * @brief Runtime extensions.
 * @details Runtime extensions:
 * - cc_cstring_buffer
 *   Dynamically growing buffers for strings.
 * - cc_get_file_contents
 *   Getting the contents of a file.
 * - cc_set_file_contents
 *   Setting the contents of a file.
 * @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.
 */
#if !defined(CC_OS_LIB_H_INCLUDED)
#define CC_OS_LIB_H_INCLUDED

#include "cc_os.h"
#include "cc_os_arraylist.h"
#include "cc_os_bytebuffer.h"

/// @brief Macro which expands its arguments to the empty expression.
/// @param ... The arguments.
#define CC_IGNORE(...)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief C string buffer.
/// @extends cc_object
CC_DECLARE_CLASS(cc_cstring_buffer, cc_object)

struct cc_cstring_buffer
{
  cc_object parent;
  cc_bytebuffer* byte_buffer;
};

/// @brief Create a string buffer.
/// @param string A pointer to a string or a null pointer.
/// @return The string buffer.
cc_cstring_buffer* cc_cstring_buffer_create();

/// @brief Create a string buffer from a C string.
/// @param string A pointer to a C string.
/// @return A pointer to the string buffer.
cc_cstring_buffer* cc_cstring_buffer_create_p(const char* string);

/// @brief Create a string buffer from a string.
/// @param s The string.
/// @return A pointer to the string buffer.
cc_cstring_buffer* cc_cstring_buffer_create_s(cc_cstring* string);

/// @brief Convert a string buffer to a string.
/// @param self A pointer to the string buffer.
/// @return A pointer to the string.
cc_cstring* cc_cstring_buffer_to_string(cc_cstring_buffer* self);

void cc_cstring_buffer_to_lower(cc_cstring_buffer* self);

void cc_cstring_buffer_to_upper(cc_cstring_buffer* self);

void cc_cstring_buffer_replace(cc_cstring_buffer* self, char old, char new);

void cc_cstring_buffer_clear(cc_cstring_buffer* self);

size_t cc_cstring_buffer_get_size(cc_cstring_buffer* self);

/// @brief Prepend a string to this string buffer.
/// @param self A pointer to this string buffer.
/// @param string A ppinter to the C string.
void cc_cstring_buffer_prepend_p(cc_cstring_buffer* self, const char*);

/// @brief Append a string to this string buffer.
/// @param self A pointer to this string buffer.
/// @param string A pointer to the C string.
void cc_cstring_buffer_append_p(cc_cstring_buffer* self, const char* p);

/// @brief Prepend a string to this string buffer.
/// @param self A pointer to this string buffer.
/// @param string A pointer to the string.
void cc_cstring_buffer_prepend_s(cc_cstring_buffer* self, cc_cstring* s);

/// @brief Append a string to this string buffer.
/// @param self A pointer to this string buffer.
/// @param string A pointer to the string.
void cc_cstring_buffer_append_s(cc_cstring_buffer* self, cc_cstring* s);

void cc_cstring_buffer_print_v(cc_cstring_buffer* self, const char* format, va_list arguments);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Append the contents of a file to a Byte buffer.
/// @param file_path The path of the file.
/// @param buffer The Byte buffer to append the contents to.
/// @error CC_ARGUMENT_NULL_ERROR @a file_path is null.
/// @error CC_ARGUMENT_NULL_ERROR @a buffer is null.
void cc_get_file_contents_ex(cc_cstring* file_path, cc_bytebuffer* buffer);

/// @brief Set the contents of a file from a Byte buffer.
/// @param file_path The path of the file.
/// @param source The Byte buffer.
/// @param start_index The index of the first Byte to write.
/// @param end_index The index of the last Byte to write (exclusive).
void
cc_set_file_contents_from_byte_buffer
  (
    cc_cstring* file_path,
    cc_bytebuffer* source,
    size_t start_index,
    size_t end_index
  );

void
cc_set_file_contents_from_cstring_buffer
  (
    cc_cstring* pathname,
    cc_cstring_buffer* source
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * Flag denoting an "internal" message.
 * Mutually exclusive with CC_PRINT_FLAG_USER.
 */
#define CC_PRINT_FLAG_INTERNAL (1 << 8)

/**
 * Flag denoting a "user" message.
 * Mutually exclusive with CC_PRINT_FLAG_USER.
 */
#define CC_PRINT_FLAG_USER (1 << 9)

/**
 * Flag denoting an "informative" message.
 * Mutually exclusive with CC_PRINT_FLAG_WARNING and CC_PRINT_FLAG_ERROR.
 */
#define CC_PRINT_FLAG_INFO (1 << 1)

/**
 * Flag denoting a "warning" message.
 * Mutually exclusive with CC_PRINT_FLAG_INFO and CC_PRINT_FLAG_WARNING.
 */
#define CC_PRINT_FLAG_WARNING (1 << 2)

/**
 * Flag denoting an "error" message.
 * Mutually exclusive with CC_PRINT_FLAG_INFO and CC_PRINT_FLAG_WARNING.
 */
#define CC_PRINT_FLAG_ERROR (1 << 3)

typedef uint32_t cc_print_flags;

void cc_print_fv(cc_print_flags flags, const char* format, va_list arguments);

void cc_print_f(cc_print_flags flags, const char* format, ...);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A tool.
/// @extends cc_object
CC_DECLARE_CLASS(cc_tool, cc_object)

struct cc_tool
{
  cc_object parent;
  cc_cstring* name;
  void (*run)(cc_tool *self, cc_arraylist* args);
};

cc_tool *cc_tool_create(cc_cstring* name, void (*run)(cc_tool *self, cc_arraylist* args));

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // CC_OS_LIB_H_INCLUDED
