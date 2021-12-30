/// @file Runtime/Gc/Gc.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_TAG_H_INCLUDED)
#define MACHINE_RUNTIME_GC_TAG_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "_Eal.h"

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
  uint64_t lockCount;
  uint32_t flags;
  size_t size;
  Machine_Gc_VisitCallback* visit;
  Machine_Gc_FinalizeCallback* finalize;
};

/// @brief Initialize this tag.
/// @param tag A pointer to the tag.
/// @post
/// next, gray, visit, finalize are all null.
/// lockCount, size are all 0.
/// The color of the tag is "white".
void Machine_Gc_Tag_initialize(Machine_Gc_Tag* tag);

/// @brief Uninitialize this tag.
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_uninitialize(Machine_Gc_Tag* tag);

/// @brief Set the color of a tag to "white".
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_setWhite(Machine_Gc_Tag* tag);

/// @brief Get if the color of a tag is "white".
/// @param tag A pointer to the tag.
/// @return @a true if the tag is color "white", @a false otherwise.
bool Machine_Gc_Tag_isWhite(Machine_Gc_Tag const* tag);

/// @brief Set the color of a tag to "black".
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_setBlack(Machine_Gc_Tag* tag);

/// @brief Get if the color of tag is "black".
/// @param tag A pointer to the tag.
/// @return @a true if the color of the tag is "black", @a false otherwise.
bool Machine_Gc_Tag_isBlack(Machine_Gc_Tag const* tag);

/// @brief Set the color of a tag to "grey".
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_setGrey(Machine_Gc_Tag* tag);

/// @brief Get if the color of a tag is "grey".
/// @param tag A pointer to the tag.
/// @return @a true if the color the tag is "grey", @a false otherwise.
bool Machine_Gc_Tag_isGrey(Machine_Gc_Tag const* tag);

/// @brief Mark a tag as "root" or "non-root".
/// @param tag A pointer to the tag.
/// @param isRoot @a true marks the tag as "root", @a false marks the tag as "non-root".
/// @todo Remove this.
void Machine_Gc_Tag_setRoot(Machine_Gc_Tag* tag, bool isRoot);

/// @brief Get if a tag is marked as "root" or "non-root".
/// @param tag A pointer to the tag.
/// @return @a true if the tag is marked as "root", @a false if the tag is marked as "non-root".
/// @todo Remove this.
bool Machine_Gc_Tag_isRoot(Machine_Gc_Tag const* tag);

/// @brief Increment the lock count of a tag.
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_lock(Machine_Gc_Tag* tag);

/// @brief Decrement the lock count of a tag.
/// @param tag A pointer to the tag.
void Machine_Gc_Tag_unlock(Machine_Gc_Tag* tag);

#endif // MACHINE_RUNTIME_GC_TAG_H_INCLUDED
