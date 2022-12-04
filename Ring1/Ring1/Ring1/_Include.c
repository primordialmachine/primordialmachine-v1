// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/_Include.h"

static Ring1_Memory_ModuleHandle g_memory = Ring1_Memory_ModuleHandle_Invalid;

static Ring1_Collections_ModuleHandle g_collections = Ring1_Collections_ModuleHandle_Invalid;

static Ring1_Atom_ModuleHandle g_atom = Ring1_Atom_ModuleHandle_Invalid;

static Ring1_FileSystem_ModuleHandle g_fileSystem = Ring1_FileSystem_ModuleHandle_Invalid;

Ring1_CheckReturn() Ring1_Result
Ring1_startup
  (
  )
{
  g_memory = Ring1_Memory_ModuleHandle_acquire();
  if (!g_memory) {
    return Ring1_Result_Failure;
  }
  g_collections = Ring1_Collections_ModuleHandle_acquire();
  if (!g_collections) {
    Ring1_Memory_ModuleHandle_relinquish(g_memory);
    g_memory = Ring1_Memory_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  g_atom = Ring1_Atom_ModuleHandle_acquire();
  if (!g_atom) {
    Ring1_Memory_ModuleHandle_relinquish(g_collections);
    g_collections = Ring1_Collections_ModuleHandle_Invalid;

    Ring1_Memory_ModuleHandle_relinquish(g_memory);
    g_memory = Ring1_Memory_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  g_fileSystem = Ring1_FileSystem_ModuleHandle_acquire();
  if (!g_fileSystem) {
    Ring1_Memory_ModuleHandle_relinquish(g_atom);
    g_atom = Ring1_Atom_ModuleHandle_Invalid;

    Ring1_Memory_ModuleHandle_relinquish(g_collections);
    g_collections = Ring1_Collections_ModuleHandle_Invalid;

    Ring1_Memory_ModuleHandle_relinquish(g_memory);
    g_memory = Ring1_Memory_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void
Ring1_shutdown
  (
  )
{
  Ring1_FileSystem_ModuleHandle_relinquish(g_fileSystem);
  g_fileSystem = Ring1_FileSystem_ModuleHandle_Invalid;

  Ring1_Atom_ModuleHandle_relinquish(g_atom);
  g_atom = Ring1_Atom_ModuleHandle_Invalid;

  Ring1_Collections_ModuleHandle_relinquish(g_collections);
  g_collections = Ring1_Collections_ModuleHandle_Invalid;

  Ring1_Memory_ModuleHandle_relinquish(g_memory);
  g_memory = Ring1_Memory_ModuleHandle_Invalid;
}
