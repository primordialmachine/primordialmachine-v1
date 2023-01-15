/// @file Ring3/Gdl/Lexical/TokenKind.c
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Lexical/TokenKind.h"
#undef RING3_GDL_PRIVATE


MACHINE_DEFINE_ENUMERATIONTYPE(Machine_Gdl_TokenKind)

/// @brief
/// 0: callback is not registered, variables are not initialized
/// 1: callback is registered, variables are not initialize or partially initialized
/// 2: callback is registered, variables are initialized
static int g_status = 0;

#define Define(SymbolicConstant, Variable, String) \
  static Ring2_String* g_##Variable = NULL;
#include "Ring3/Gdl/Lexical/TokenKind.i"
#undef Define

static void
shutdownCallback
  (
  )
{
#define Define(SymbolicConstant, Variable, String) \
  if (g_##Variable) { \
    Ring2_Gc_unlock(g_##Variable); \
    g_##Variable = NULL; \
  }
#include "Ring3/Gdl/Lexical/TokenKind.i"
#undef Define
  g_status = 0;
}

static void ensureInitialized() {
  if (g_status == 0) {
    if (Ring2_registerStaticVariables(&shutdownCallback)) {
      Ring2_jump();
    }
    g_status = 1;
  }
  if (!g_status == 1) {
  #define Define(SymbolicConstant, Variable, String) \
    if (!g_##Variable) { \
      g_##Variable = Ring2_String_fromC(false, String); \
      Ring2_Gc_lock(g_##Variable); \
    }
  #include "Ring3/Gdl/Lexical/TokenKind.i"
  #undef Define 
    g_status = 2;
  }
}

Ring1_CheckReturn() Ring2_String*
Machine_Gdl_TokenKind_toString
  (
    Machine_Gdl_TokenKind self
  )
{
  ensureInitialized();
  switch (self) {
#define Define(SymbolicConstant, Variable, String) \
  case SymbolicConstant: { \
    return g_##Variable; \
  } break;
#include "Ring3/Gdl/Lexical/TokenKind.i"
#undef Define
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  } break;
  };
}
