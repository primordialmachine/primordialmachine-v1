#include "Runtime/Gc/Tag.h"

/// @brief Tag flag indicating the color "white".
#define Machine_Flag_White (1)

/// @brief Tag flag indicating the color "black".
#define Machine_Flag_Black (2)

/// @brief Tag flag indicating the color "grey".
#define Machine_Flag_Grey (Machine_Flag_White | Machine_Flag_Black)

/// @brief Tag flag indicating a root object.
/// @todo Remove this.
#define Machine_Flag_Root (4)

void Machine_Tag_initialize(Machine_Tag* tag) {
  tag->lockCount = 0;
  tag->flags = Machine_Flag_White;
  tag->size = 0;
  tag->visit = NULL;
  tag->finalize = NULL;
  tag->next = NULL;
  tag->gray = NULL;
}

void Machine_Tag_uninitialize(Machine_Tag* tag) {
}

void Machine_Tag_setWhite(Machine_Tag* tag) {
  tag->flags &= ~Machine_Flag_Black;
  tag->flags |= Machine_Flag_White;
}

bool Machine_Tag_isWhite(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Grey) == Machine_Flag_White;
}

void Machine_Tag_setBlack(Machine_Tag* tag) {
  tag->flags &= ~Machine_Flag_White;
  tag->flags |= Machine_Flag_Black;
}

bool Machine_Tag_isBlack(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Black) == Machine_Flag_Black;
}

void Machine_Tag_setGrey(Machine_Tag* tag) {
  tag->flags |= Machine_Flag_Grey;
}

bool Machine_Tag_isGrey(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Grey) == Machine_Flag_Grey;
}

void Machine_Tag_setRoot(Machine_Tag* tag, bool isRoot) {
  if (isRoot) {
    tag->flags |= Machine_Flag_Root;
  } else {
    tag->flags &= ~Machine_Flag_Root;
  }
}

bool Machine_Tag_isRoot(Machine_Tag const* tag) {
  return (tag->flags & Machine_Flag_Root) == Machine_Flag_Root;
}

void Machine_Tag_lock(Machine_Tag* tag) {
  tag->lockCount++;
}

void Machine_Tag_unlock(Machine_Tag* tag) {
  tag->lockCount--;
}
