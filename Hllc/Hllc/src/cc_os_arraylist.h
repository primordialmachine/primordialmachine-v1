/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// @file cc_os_arraylist.h
/// @brief Dynamically resizing array list for non-null cc_object pointers.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.

#if !defined(CC_OS_ARRAYLIST_H_INCLUDED)
#define CC_OS_ARRAYLIST_H_INCLUDED

#include "cc_os.h"

/// @brief Dynamically resizing array list for non-null cc_object pointers.
CC_DECLARE_CLASS(cc_arraylist, cc_object)

/// @brief Create a cc_arraylist object.
/// @param capacity The initial capacity of the cc_arraylist object. Can be @a 0.
/// @return A pointer to the cc_arraylist object.
cc_arraylist* cc_arraylist_create(size_t capacity);

/// @brief Get the size of this cc_arraylist object.
/// @param self A pointer to this cc_arraylist object.
/// @return The size.
size_t cc_arraylist_get_size(cc_arraylist* self);

/// @brief Get the value at the specified index in this cc_arraylist object.
/// @param self A pointer to this cc_arraylist object.
/// @param index The index.
/// Must be within the bounds of <ocde>[0,n)</code> where @a n is the size of this cc_arraylist object.
/// @return The pointer to the value.
cc_object* cc_arraylist_get_at(cc_arraylist* self, size_t index);

/// @brief Append a value to this cc_arraylist object.
/// @param self A pointer to this cc_arraylist object.
/// @param value The value to append.
void cc_arraylist_append(cc_arraylist* self, cc_object* value);

/// @brief Prepend a value to this cc_arraylist object.
/// @param self A pointer to this cc_arraylist object.
/// @param value The value to prepend.
void cc_arraylist_prepend(cc_arraylist* self, cc_object* value);

/// @brief Insert a value into this cc_arraylist object at the specified index.
/// @param self A pointer to this cc_arraylist object.
/// @param index The index.
/// Must be within the bounds of <code>[0, n]</code> where @a n is the size of this cc_arraylist object.
/// @param value The value.
/// @remark
/// Let @a n be the size of a cc_arraylist object @a l:
/// - A call <code>cc_arraylist_insert(l, 0, v)</code> is equivalent to a call <code>cc_arraylist_prepend(l, v)</code>.
/// - A call <code>cc_arraylist_insert(l, n, v)</code> is equivalent to a call <code>cc_arraylist_append(l, v)</code>.
void cc_arraylist_insert(cc_arraylist* self, size_t index, cc_object* value);

/// @brief Clear this cc_arraylist object i.e. set its number of elements to @a 0.
/// @param self A pointer to this cc_arraylist_object.
void cc_arraylist_clear(cc_arraylist* self);

#endif // CC_OS_ARRAYLIST_H_INCLUDED
