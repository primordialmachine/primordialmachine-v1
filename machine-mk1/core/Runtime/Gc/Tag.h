/// @file Runtime/Gc/Gc.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_TAG_H_INCLUDED)
#define MACHINE_RUNTIME_GC_TAG_H_INCLUDED



#include "_Eal.h"





/// @brief Type of a finalize callback function.
/// @param object The object to finalize.
typedef void(Machine_FinalizeCallback)(void* object);

/// @brief Type of a visit callback function.
/// @param object The object to visit.
typedef void(Machine_VisitCallback)(void* object);

typedef struct Machine_Tag Machine_Tag;

struct Machine_Tag {
  Machine_Tag* next;
  Machine_Tag* gray;
  uint64_t lockCount;
  uint32_t flags;
  size_t size;
  Machine_VisitCallback* visit;
  Machine_FinalizeCallback* finalize;
};

/// @brief Initialize this tag.
/// @param tag A pointer to the tag.
/// @post
/// next, gray, visit, finalize are all null.
/// lockCount, size are all 0.
/// The color of the tag is "white". 
void Machine_Tag_initialize(Machine_Tag* tag);

/// @brief Uninitialize this tag.
/// @param tag A pointer to the tag.
void Machine_Tag_uninitialize(Machine_Tag* tag);

/// @brief Set the color of a tag to "white".
/// @param tag A pointer to the tag.
void Machine_Tag_setWhite(Machine_Tag* tag);

/// @brief Get if the color of a tag is "white".
/// @param tag A pointer to the tag.
/// @return @a true if the tag is color "white", @a false otherwise.
bool Machine_Tag_isWhite(Machine_Tag const* tag);

/// @brief Set the color of a tag to "black".
/// @param tag A pointer to the tag.
void Machine_Tag_setBlack(Machine_Tag* tag);

/// @brief Get if the color of tag is "black".
/// @param tag A pointer to the tag.
/// @return @a true if the color of the tag is "black", @a false otherwise.
bool Machine_Tag_isBlack(Machine_Tag const* tag);

/// @brief Set the color of a tag to "grey".
/// @param tag A pointer to the tag.
void Machine_Tag_setGrey(Machine_Tag* tag);

/// @brief Get if the color of a tag is "grey".
/// @param tag A pointer to the tag.
/// @return @a true if the color the tag is "grey", @a false otherwise.
bool Machine_Tag_isGrey(Machine_Tag const* tag);

/// @brief Mark a tag as "root" or "non-root".
/// @param tag A pointer to the tag.
/// @param isRoot @a true marks the tag as "root", @a false marks the tag as "non-root".
/// @todo Remove this.
void Machine_Tag_setRoot(Machine_Tag* tag, bool isRoot);

/// @brief Get if a tag is marked as "root" or "non-root".
/// @param tag A pointer to the tag.
/// @return @a true if the tag is marked as "root", @a false if the tag is marked as "non-root".
/// @todo Remove this.
bool Machine_Tag_isRoot(Machine_Tag const* tag);

/// @brief Increment the lock count of a tag.
/// @param tag A pointer to the tag.
void Machine_Tag_lock(Machine_Tag* tag);

/// @brief Decrement the lock count of a tag.
/// @param tag A pointer to the tag.
void Machine_Tag_unlock(Machine_Tag* tag);


#endif // MACHINE_RUNTIME_GC_TAG_H_INCLUDED