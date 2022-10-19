#include "Ring1/TypeDescriptor.h"

#include "Ring1/Collections/PointerHashMap.h"
#include "Ring1/Memory.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define Ring1_TypeDescriptor_Flags_ScalarType (1)

struct Ring1_TypeDescriptor {
  char *name;
};

static Mkx_PointerHashMap *g_types = NULL;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

static Ring1_Result

Ring1_Module_Define(TypeDescriptor, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{
  g_types = NULL;
  if (Ring1_Memory_allocate(&g_types, sizeof(Ring1_TypeDescriptor))) {
    return Ring1_Result_Failure;
  }
  if (Mkx_PointerHashMap_initialize(&g_types, 0,
                                    NULL /*keyAdded*/,
                                    NULL /*keyRemoved*/,
                                    &hashhName /*hashKey*/,
                                    &areNamesEqual /*areKeysEqual*/,
                                    NULL,
                                    &valueRemoved/*valueRemoved*/)) {
    Ring1_Memory_deallocate(g_types);
    g_types = NULL;
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{ }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
