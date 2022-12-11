#if !defined(RING1_MODULES_DEPENDENCIES_H_INCLUDED)
#define RING1_MODULES_DEPENDENCIES_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module/Handle.h"
#include "Ring1/Result.h"

typedef struct Ring1_ModuleDependency {
  Ring1_ModuleHandle moduleHandle;
  Ring1_ModuleHandle(*acquire)();
  void (*relinquish)(Ring1_ModuleHandle moduleHandle);
} Ring1_ModuleDependency;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ModuleDependencies_initialize
  (
    size_t numberOfDependencies,
    Ring1_ModuleDependency* dependencies
  );

void
Ring1_ModuleDependencies_uninitialize
  (
    size_t numberOfDependencies,
    Ring1_ModuleDependency* dependencies
  );

#define Ring1_BeginDependencies() \
  static Ring1_ModuleDependency moduleDependencies[] = {
  
#define Ring1_Dependency(PARENT, SELF) \
  { Ring1_ModuleHandle_Invalid, &PARENT##_##SELF##_ModuleHandle_acquire, &PARENT##_##SELF##_ModuleHandle_relinquish },

#define Ring1_EndDependencies() \
  }; \
  \
  static Ring1_NoDiscardReturn() \
  startupDependencies() { \
    return Ring1_ModuleDependencies_initialize(sizeof(moduleDependencies) / sizeof(Ring1_ModuleDependency), moduleDependencies); \
  } \
  \
  static void \
  shutdownDependencies() { \
    Ring1_ModuleDependencies_uninitialize(sizeof(moduleDependencies) / sizeof(Ring1_ModuleDependency), moduleDependencies); \
  }

#endif // RING1_MODULES_DEPENDENCIES_H_INCLUDED
