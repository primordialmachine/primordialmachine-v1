#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Gc/Tag.h"

/// @brief Tag flag indicating the color "white".
#define Machine_Flag_White (1)

/// @brief Tag flag indicating the color "black".
#define Machine_Flag_Black (2)

/// @brief Tag flag indicating the color "grey".
#define Machine_Flag_Grey (Machine_Flag_White | Machine_Flag_Black)

void Machine_Gc_Tag_initialize(Machine_Gc_Tag* tag) {
  tag->lockCount = 0;
  tag->flags = Machine_Flag_White;
  tag->visit = NULL;
  tag->finalize = NULL;
  tag->next = NULL;
  tag->gray = NULL;
}

void Machine_Gc_Tag_uninitialize(Machine_Gc_Tag* tag) {
}

void Machine_Gc_Tag_setWhite(Machine_Gc_Tag* tag) {
  tag->flags &= ~Machine_Flag_Black;
  tag->flags |= Machine_Flag_White;
}

bool Machine_Gc_Tag_isWhite(Machine_Gc_Tag const* tag) {
  return (tag->flags & Machine_Flag_Grey) == Machine_Flag_White;
}

void Machine_Gc_Tag_setBlack(Machine_Gc_Tag* tag) {
  tag->flags &= ~Machine_Flag_White;
  tag->flags |= Machine_Flag_Black;
}

bool Machine_Gc_Tag_isBlack(Machine_Gc_Tag const* tag) {
  return (tag->flags & Machine_Flag_Black) == Machine_Flag_Black;
}

void Machine_Gc_Tag_setGrey(Machine_Gc_Tag* tag) {
  tag->flags |= Machine_Flag_Grey;
}

bool Machine_Gc_Tag_isGrey(Machine_Gc_Tag const* tag) {
  return (tag->flags & Machine_Flag_Grey) == Machine_Flag_Grey;
}

void Machine_Gc_Tag_lock(Machine_Gc_Tag* tag) {
  tag->lockCount++;
}

void Machine_Gc_Tag_unlock(Machine_Gc_Tag* tag) {
  tag->lockCount--;
}
