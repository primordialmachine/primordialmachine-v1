// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/Tag.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_GC_TAG_H_INCLUDED)
#define RING2_GC_TAG_H_INCLUDED

#include "Ring2/Gc/Type.h"
#include "Ring1/ReferenceCounter.h"
#include <stdbool.h>

/// @brief The caller of id := Ring2_Gc_Tag_addWeakRef(c,f) must ensure
/// that Ring2_Gc_Tag_removeWeakRef(id) is called when c goes out of scope.
typedef struct Ring2_Gc_WeakReference Ring2_Gc_WeakReference;

struct Ring2_Gc_WeakReference
{
  Ring2_Gc_WeakReference* nextWeakReference;
  void* context;
  void (*callback)(void* context);
};

typedef struct Ring2_Gc_Tag Ring2_Gc_Tag;

struct Ring2_Gc_Tag
{
  /// @brief The flags of this GC object
  uint8_t flags;

  /// @brief A pointer to a static const Mkx_Gc_Type C-level object or a null
  /// pointer.
  Ring2_Gc_Type const* type;

  /// @brief The number of locks on this GC object.
  Ring1_ReferenceCounter locks;

  /// @brief Pointer to the head of the list of weak references if list is not
  /// empty, the null pointer otherwise.
  Ring2_Gc_WeakReference* weakReferences;

  /// @brief Link of this object into the global list of objects.
  Ring2_Gc_Tag* objectNext;
  /// @brief Link of this object into the gray list (during mark phase), null otherwise.
  Ring2_Gc_Tag* grayNext;
};

/// @brief Initialize this tag.
/// @param tag A pointer to this tag.
/// @post
/// list of weak references is empty.
/// type is null.
/// locks is 0.
/// The color of this tag is "white".
/// objectNext and grayNext are null.
void
Ring2_Gc_Tag_initialize
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Uninitialize this tag.
/// @param tag A pointer to this tag.
void
Ring2_Gc_Tag_uninitialize
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Add a weak reference to the list of weak references of this tag.
/// @param tag A pointer to this tag.
/// @param pointer A pointer to a pointer variable.
/// @return The non-zero ID of the weak reference on success, 0 on failure.
/// @success The weak reference was added to the list of weak references of this tag.
uintptr_t
Ring2_Gc_Tag_addWeakReference
  (
    Ring2_Gc_Tag* tag,
    void* context,
    void (*callback)(void *context)
  );

/// @brief Remove a weak reference from the list of weak references of this tag.
/// @param tag A pointer to this tag.
/// @param id The non-zero ID of the weak reference or 0.
/// @success The weak reference was removed from the list of weak references of this tag if it was in that list.
void
Ring2_Gc_Tag_removeWeakReference
  (
    Ring2_Gc_Tag* tag, 
    uintptr_t id
  );

/// @brief Notify all weak references of this tag.
/// @param tag A pointer to this tag.
/// @post All weak references were notified.
/// @post The list of weak references is empty.
void
Ring2_Gc_Tag_notifyWeakReferences
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Set or clear the "class type" flag of this tag.
/// @param tag A pointer to this tag.
/// @param classType
/// @a true to set the "class type" flag of this tag,
/// @a false to clear the "class type" flag of this tag.
void
Ring2_Gc_Tag_setClassType
  (
    Ring2_Gc_Tag *tag,
    bool classType
  );

/// @brief Get if the "class type" flag of this tag is set or cleared.
/// @param tag A pointer to this tag.
/// @return
/// @a true if the "class type" flag of this tag is set,
/// @a false if the "class type" flag of this tag is cleared.
bool
Ring2_Gc_Tag_getClassType
  (
    Ring2_Gc_Tag const* tag
  );

/// @brief Color this tag "white".
/// @param tag A pointer to this tag.
/// @post This tag is colored "white".
void
Ring2_Gc_Tag_setWhite
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Get if this tag is colored "white".
/// @param tag A pointer to the tag.
/// @return @a true if this tag is colored "white", @a false otherwise.
bool
Ring2_Gc_Tag_isWhite
  (
    Ring2_Gc_Tag const* tag
  );

/// @brief Color this tag "gray".
/// @param tag A pointer to this tag.
/// @post This tag is colored "gray".
void
Ring2_Gc_Tag_setGray
  (
    Ring2_Gc_Tag* object
  );

/// @brief Get if this is colored "gray".
/// @param tag A pointer to this tag.
/// @return @a true if this tag is colored "gray", @a false otherwise.
bool
Ring2_Gc_Tag_isGray
  (
    Ring2_Gc_Tag const* object
  );

/// @brief Color this tag "black".
/// @param tag A pointer to this tag.
/// @post This tag is colored "black".
void
Ring2_Gc_Tag_setBlack
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Get if this tag is colored "black".
/// @param tag A pointer to this tag.
/// @return @a true if this tag is colored "black", @a false otherwise.
bool
Ring2_Gc_Tag_isBlack
  (
    Ring2_Gc_Tag const* tag
  );

/// @brief Increment the lock count of this tag by @a 1.
/// @param tag A pointer to this tag.
/// @remark The initial lock count is @a 0.
void
Ring2_Gc_Tag_lock
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Decrement the lock count of this tag by @a 1.
/// @param tag A pointer to this tag.
void
Ring2_Gc_Tag_unlock
  (
    Ring2_Gc_Tag* tag
  );

/// @brief Get the lock count of this tag.
/// @param tag A pointer to this tag.
/// @return The lock count of this tag.
int32_t
Ring2_Gc_Tag_getLockCount
  (
    Ring2_Gc_Tag const* tag
  );

#endif // RING2_GC_TAG_H_INCLUDED
