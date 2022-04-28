/// @file Runtime/Gc/Gc.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_TAG_H_INCLUDED)
#define MACHINE_RUNTIME_GC_TAG_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "_Eal.h"
// Forward declaration.
typedef struct Machine_WeakReference Machine_WeakReference;

/// @brief Type of a finalize callback function.
/// @param object The object to finalize.
typedef void(Machine_Gc_FinalizeCallback)(void* object);

/// @brief Type of a visit callback function.
/// @param object The object to visit.
typedef void(Machine_Gc_VisitCallback)(void* object);

typedef struct Machine_Gc_Tag Machine_Gc_Tag;

struct Machine_Gc_Tag {
  Machine_Gc_Tag* next;
  Machine_Gc_Tag* gray;
  /// @brief The number of locks on this tag.
  uint64_t lockCount;
  /// @brief The flags of this tag.
  uint8_t flags;
  /// @brief Head of the singly-linked list of weak references to this object.
  Machine_WeakReference* weakReferences;
  /// @brief A pointer to a Machine_Gc_VisitCallback function or a null pointer.
  Machine_Gc_VisitCallback* visit;
  /// @brief A pointer to a Machine_Gc_FinalizeCallback function or a null pointer.
  Machine_Gc_FinalizeCallback* finalize;
};

/// @brief Initialize a tag.
/// @param tag A pointer to the tag.
/// @post
/// next, gray, visit, and finalize are all null.
/// lockCount and size are all 0.
/// The color of the tag is "white".
void Machine_Gc_Tag_initialize(Machine_Gc_Tag* tag);

/// @brief Uninitialize a tag.
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_uninitialize(Machine_Gc_Tag* tag);

/// @brief Set the color of a tag to "white".
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_setWhite(Machine_Gc_Tag* tag);

/// @brief Get if the color of a tag is "white".
/// @param tag A pointer to the tag.
/// @return @a true if the color of the tag is "white", @a false otherwise.
bool Machine_Gc_Tag_isWhite(Machine_Gc_Tag const* tag);

/// @brief Set the color of a tag to "black".
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_setBlack(Machine_Gc_Tag* tag);

/// @brief Get if the color of tag is "black".
/// @param tag A pointer to the tag.
/// @return @a true if the color of the tag is "black", @a false otherwise.
bool Machine_Gc_Tag_isBlack(Machine_Gc_Tag const* tag);

/// @brief Set the color of a tag to "gray".
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_setGrey(Machine_Gc_Tag* tag);

/// @brief Get if the color of a tag is "gray".
/// @param tag A pointer to the tag.
/// @return @a true if the color of the tag is "gray", @a false otherwise.
bool Machine_Gc_Tag_isGrey(Machine_Gc_Tag const* tag);

/// @brief Increment the lock count of a tag.
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_lock(Machine_Gc_Tag* tag);

/// @brief Decrement the lock count of a tag.
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_unlock(Machine_Gc_Tag* tag);

#endif // MACHINE_RUNTIME_GC_TAG_H_INCLUDED
