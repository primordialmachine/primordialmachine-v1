/// @file Runtime/GC/GC.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_GC_H_INCLUDED)
#define MACHINE_RUNTIME_GC_GC_H_INCLUDED



#include "Runtime/C.h"



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
typedef void (Machine_VisitCallback)(void*);

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



#endif // MACHINE_RUNTIME_GC_GC_H_INCLUDED
