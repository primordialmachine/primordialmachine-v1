#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Layout/Justification.h"
#undef RING3_GUI_PRIVATE

#include "Ring2/Library/_Include.h"

MACHINE_DEFINE_ENUMERATIONTYPE(Ring3_Gui_Layout_Justification)

#define Define(STRINGLITERAL, VARIABLENAME, NUMBER) \
  static Ring2_String* g_string##VARIABLENAME = NULL;
#include "Ring3/Gui/Layout/Justification.i"
#undef Define
static Ring2_Collections_Map* g_map = NULL;

static void
initialize
  (
  )
{
  if (!g_map) {
    g_map = (Ring2_Collections_Map*)Ring2_Collections_HashMap_create();
    Ring2_Gc_lock(g_map);
  }

#define Define(STRINGLITERAL, VARIABLENAME, ENUMERATIONELEMENTNAME) \
  { \
    if (!g_string##VARIABLENAME) { \
      g_string##VARIABLENAME = Ring2_String_fromC(false, STRINGLITERAL); \
      Ring2_Gc_lock(g_string##VARIABLENAME); \
    } \
    Ring2_JumpTarget jumpTarget; \
    Ring2_pushJumpTarget(&jumpTarget); \
    if (!setjmp(jumpTarget.environment)) { \
      Ring2_Value key, value; \
\
      Ring2_Value_setString(&key, g_string##VARIABLENAME); \
      Ring2_Value_setInteger(&value, ENUMERATIONELEMENTNAME); \
      Ring2_Collections_Map_set(g_map, key, value); \
\
      Ring2_Value_setInteger(&key, ENUMERATIONELEMENTNAME); \
      Ring2_Value_setString(&value, g_string##VARIABLENAME); \
      Ring2_Collections_Map_set(g_map, key, value); \
\
      Ring2_popJumpTarget(); \
    } else { \
      Ring2_popJumpTarget(); \
      Ring2_Gc_unlock(g_string##VARIABLENAME); \
      g_string##VARIABLENAME = NULL; \
      Ring2_jump(); \
    } \
  }
#include "Ring3/Gui/Layout/Justification.i"
#undef Define
}

static bool g_registered = false;

static void
uninitialize
  (
  )
{
  if (g_map) {
    Ring2_Gc_unlock(g_map);
    g_map = NULL;
  }
#define Define(STRINGLITERAL, VARIABLENAME, ENUMERATIONELEMENT) \
    if (g_string##VARIABLENAME) { \
      Ring2_Gc_unlock(g_string##VARIABLENAME); \
      g_string##VARIABLENAME = NULL; \
    }
#include "Ring3/Gui/Layout/Justification.i"
#undef Define
  g_registered = false;
}

static void
ensureInitialized
  (
  )
{
  if (!g_registered) {
    Ring2_JumpTarget jumpTarget;
    Ring2_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      initialize();
      Ring2_popJumpTarget();
    } else {
      uninitialize();
      Ring2_popJumpTarget();
      Ring2_jump();
    }
    if (Ring2_registerStaticVariables(&uninitialize)) {
      uninitialize();
      Ring2_jump();
    }
    g_registered = true;
  }
}

Ring1_NoDiscardReturn() Ring3_Gui_Layout_Justification
Ring3_Gui_Layout_Justification_parse
  (
    Ring2_String* source
  )
{
  ensureInitialized();
  Ring2_Value key;
  Ring2_Value_setString(&key, source);
  Ring2_Value value = Ring2_Collections_Map_get(g_map, key);
  if (!Ring2_Value_isInteger(&value)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  return Ring2_Value_getInteger(&value);
}

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_Layout_Justification_unparse
  (
    Ring3_Gui_Layout_Justification source
  )
{
  ensureInitialized();
  Ring2_Value key;
  Ring2_Value_setInteger(&key, source);
  Ring2_Value value = Ring2_Collections_Map_get(g_map, key);
  if (!Ring2_Value_isString(&value)) {
    Ring1_Status_set(Ring1_Status_InvalidSemantics);
    Ring2_jump();
  }
  return Ring2_Value_getString(&value);
}
