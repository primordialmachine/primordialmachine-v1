#include "Ring1/TypeDescriptor.h"

#include "Ring1/Collections/PointerHashMap.h"
#include "Ring1/Memory.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define Ring1_TypeDescriptor_Flags_ScalarType (1)

struct Ring1_TypeDescriptor {
  char *name;
};

Ring1_Result areNamesEqual(bool *result, const char *x, const char *y) {
  *result = !crt_strcmp(x, y);
  return Ring1_Result_Success;
}

Ring1_Result hashName_u64(uint64_t *result, const char *name) {
  static_assert(SIZE_MAX <= UINT64_MAX, "unsupported environment");
  uint64_t hv = (uint64_t)crt_strlen(name);
  for (uint64_t i = 0, n = (uint64_t)crt_strlen(name); i < n; ++i) {
    hv = ((hv << 5) ^ (hv >> 3)) | (uint64_t)name[i];
  }
  *result = hv;
  return Ring1_Result_Success;
}

Ring1_Result hashName(int64_t *result, const char *name) {
  uint64_t hv;
  if (hashName_u64(&hv, name)) {
    return Ring1_Result_Failure;
  }
  *result = (int64_t)(hv & 0x7fffffffffffffff);
  return Ring1_Result_Success;
}

void valueRemoved(Ring1_TypeDescriptor *typeDescriptor) {
  Ring1_Memory_deallocate(typeDescriptor->name);
  Ring1_Memory_deallocate(typeDescriptor);
}

static Ring1_PointerHashMap *g_types = NULL;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, TypeDescriptor, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{
  g_types = NULL;
  if (Ring1_Memory_allocate(&g_types, sizeof(Ring1_TypeDescriptor))) {
    return Ring1_Result_Failure;
  }
  if (Mkx_PointerHashMap_initialize(g_types, 0,
                                    NULL /*keyAdded*/,
                                    NULL /*keyRemoved*/,
                                    &hashName /*hashKey*/,
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
{ 
  Mkx_PointerHashMap_uninitialize(g_types);
  Ring1_Memory_deallocate(g_types);
  g_types = NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
