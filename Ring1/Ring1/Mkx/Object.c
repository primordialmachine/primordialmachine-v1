// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#include "Mkx/Object.h"

#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Type.internal.h"
#include "Mkx/Object/Types.internal.h"
#include "Mkx/Object/WeakReference.Module.h"
#undef MKX_OBJECT_INTERNAL

#include "Ring1/Atom/_Include.h"
#include "Ring1/Collections/_Include.h"
#include "Ring1/Memory/_Include.h"


static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, ObjectModule, initializeModule, uninitializeModule)

typedef struct Handles
{
  Ring1_Atom_ModuleHandle atom;
  Ring1_Memory_ModuleHandle memory;
  Ring1_PointerList_ModuleHandle pointerList;
  Ring1_PointerDeque_ModuleHandle pointerDeque;
} Handles;

static Handles g_handles = { .memory = Ring1_Memory_ModuleHandle_Invalid,
                             .pointerList = Ring1_PointerList_ModuleHandle_Invalid,
                             .pointerDeque = Ring1_PointerDeque_ModuleHandle_Invalid,
                             .atom = Ring1_Atom_ModuleHandle_Invalid, };

static void
uninitializeExternalModules
  (
  )
{
  if (g_handles.atom) {
    Ring1_PointerList_ModuleHandle_relinquish(g_handles.pointerList);
    g_handles.pointerList = Ring1_PointerList_ModuleHandle_Invalid;
  }
  
  if (g_handles.pointerDeque) {
    Ring1_PointerDeque_ModuleHandle_relinquish(g_handles.pointerDeque);
    g_handles.pointerDeque = Ring1_PointerDeque_ModuleHandle_Invalid;
  }
  
  if (g_handles.pointerList) {
    Ring1_PointerList_ModuleHandle_relinquish(g_handles.pointerList);
    g_handles.pointerList = Ring1_PointerList_ModuleHandle_Invalid;
  }

  if (g_handles.memory) {
    Ring1_Memory_ModuleHandle_relinquish(g_handles.memory);
    g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
  }
}

Ring1_CheckReturn() static int
initializeExternalModules
  (
  )
{
  int result = 0;
  
  g_handles.memory = Ring1_Memory_ModuleHandle_acquire();
  if (!g_handles.memory) {
    result = 1;
    goto End;
  }
  
  g_handles.pointerList = Ring1_PointerList_ModuleHandle_acquire();
  if (!g_handles.pointerList) {
    result = 1;
    goto End;
  }
  
  g_handles.pointerDeque = Ring1_PointerDeque_ModuleHandle_acquire();
  if (!g_handles.pointerDeque) {
    result = 1;
    goto End;
  }

  g_handles.atom = Ring1_Atom_ModuleHandle_acquire();
  if (!g_handles.atom) {
    result = 1;
    goto End;
  }
  
  return result;

End:
  uninitializeExternalModules();
  return result;
}

static Ring1_Result
initializeModule
  (
  )
{
  if (initializeExternalModules()) {
    return Ring1_Result_Failure;
  }
  //
  if (Mkx_Object_Types_initialize()) {
    uninitializeExternalModules();
    return Ring1_Result_Failure;
  }
  if (Mkx_WeakReferences_initialize()) {
    Mkx_Object_Types_uninitialize();
    uninitializeExternalModules();
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  //
  Mkx_WeakReferences_uninitialize();
  //
  Mkx_Object_Types_uninitialize();
  //
  Ring1_PointerDeque_ModuleHandle_relinquish(g_handles.pointerDeque);
  g_handles.pointerDeque = Ring1_PointerDeque_ModuleHandle_Invalid;
  //
  Ring1_PointerList_ModuleHandle_relinquish(g_handles.pointerList);
  g_handles.pointerList = Ring1_PointerList_ModuleHandle_Invalid;
  //
  Ring1_Memory_ModuleHandle_relinquish(g_handles.memory);
  g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
  //
  Ring1_Atom_ModuleHandle_relinquish(g_handles.atom);
  g_handles.atom = Ring1_Atom_ModuleHandle_Invalid;
}
