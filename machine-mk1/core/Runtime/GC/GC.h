/// @file Runtime/GC/GC.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_GC_H_INCLUDED)
#define MACHINE_RUNTIME_GC_GC_H_INCLUDED



#include "_Eal.h"
#include "Runtime/Status.h"



/// @brief Initialize the GC module.
Machine_StatusValue Machine_initializeGcModule();

/// @brief Uninitialize the GC module.
void Machine_uninitializeGcModule();

/// @brief Tag flag indicating the color "white".
#define Machine_Flag_White (1)

/// @brief Tag flag indicating the color "black".
#define Machine_Flag_Black (2)

/// @brief Tag flag indicating the color "grey".
#define Machine_Flag_Grey (Machine_Flag_White | Machine_Flag_Black)

/// @brief Tag flag indicating a root object.
#define Machine_Flag_Root (4)

/// @brief Type of a finalize callback function.
/// @param object The object to finalize.
typedef void (Machine_FinalizeCallback)(void* object);

/// @brief Type of a visit callback function.
/// @param object The object to visit.
typedef void (Machine_VisitCallback)(void* object);

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

INLINE void Machine_Tag_setWhite(Machine_Tag* tag);

INLINE bool Machine_Tag_isWhite(Machine_Tag const* tag);

INLINE void Machine_Tag_setBlack(Machine_Tag* tag);

INLINE bool Machine_Tag_isBlack(Machine_Tag const* tag);

INLINE void Machine_Tag_setGrey(Machine_Tag* tag);

INLINE bool Machine_Tag_isGrey(Machine_Tag const* tag);

INLINE bool Machine_Tag_isRoot(Machine_Tag const* tag);

/// @brief Convert a pointer to an object into a pointer to the tag of the object.
/// @param src The pointer to the object.
/// @return A pointer to the tag of the object.
INLINE Machine_Tag* Machine_o2t(void* src);

/// @brief Convert a pointer to a tag into a pointer to the object of the tag.
/// @param src The pointer to the tag.
/// @return A pointer to the object of the tag.
INLINE void* Machine_t2o(Machine_Tag* src);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

INLINE void Machine_Tag_setWhite(Machine_Tag* tag) {
  tag->flags &= ~Machine_Flag_Black;
  tag->flags |= Machine_Flag_White;
}

INLINE bool Machine_Tag_isWhite(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Grey) == Machine_Flag_White;
}

INLINE void Machine_Tag_setBlack(Machine_Tag* tag) {
  tag->flags &= ~Machine_Flag_White;
  tag->flags |= Machine_Flag_Black;
}

INLINE bool Machine_Tag_isBlack(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Black) == Machine_Flag_Black;
}

INLINE void Machine_Tag_setGrey(Machine_Tag* tag) {
  tag->flags |= Machine_Flag_Grey;
}

INLINE bool Machine_Tag_isGrey(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Grey) == Machine_Flag_Grey;
}

INLINE bool Machine_Tag_isRoot(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Root) == Machine_Flag_Root;
}

INLINE Machine_Tag* Machine_o2t(void* src) {
  static const size_t N = sizeof(Machine_Tag);
  char* dst = ((char*)src) - N;
  return (Machine_Tag*)dst;
}

INLINE void* Machine_t2o(Machine_Tag* src) {
  static const size_t N = sizeof(Machine_Tag);
  char* dst = ((char*)src) + N;
  return (void*)dst;
}

/// @brief Increment the lock count of an object.
/// @param object A pointer to the object.
void Machine_lock(void* object);

/// @brief Decrement the lock count of an object.
/// @param object A pointer to the object.
void Machine_unlock(void* object);

/// @brief Set if an object is marked as a root object.
/// @undefined Invoked in visit callback or finalize callback.
void Machine_setRoot(void* object, bool isRoot);

/// @brief Get if an object is marked as a root object.
/// @param object the object.
/// @return @a true if the object is a root, @a false otherwise.
bool Machine_isRoot(void* object);

/// @brief Allocate a payload.
/// @param tagPrefixSize The size, in Bytes, of the tag prefix.
/// @param payloadSize The size, in Bytes, of the payload.
/// @param visit A pointer to the Machine_VisitCallback function for the object or a null pointer.
/// @param finalize A pointer to the Machine_FinalizeCallback function for the object or a null pointer.
/// @return A pointer to the object on success, a null pointer on failure.
void* Machine_allocateEx(size_t payloadSize, size_t tagPrefixSize, Machine_VisitCallback* visit, Machine_FinalizeCallback* finalize);



#endif // MACHINE_RUNTIME_GC_GC_H_INCLUDED
