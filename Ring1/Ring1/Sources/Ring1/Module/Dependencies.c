#include "Ring1/Module/Dependencies.h"

#include "Ring1/Status.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ModuleDependencies_initialize
  (
    size_t numberOfDependencies,
    Ring1_ModuleDependency *dependencies
  )
{
  for (size_t i = 0, n = numberOfDependencies; i < n ; ++i) {
    Ring1_ModuleDependency* dependency = &dependencies[i];
    if (!dependency->moduleHandle) {
      dependency->moduleHandle = dependency->acquire();
      if (!dependency->moduleHandle) {
        while (i > 0) {
          dependency = &dependencies[--i];
          dependency->relinquish(dependency->moduleHandle);
          dependency->moduleHandle = Ring1_ModuleHandle_Invalid;
        }
        Ring1_Status_set(Ring1_Status_EnvironmentFailed);
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

void
Ring1_ModuleDependencies_uninitialize
  (
    size_t numberOfDependencies,
    Ring1_ModuleDependency *dependencies
  )
{
  size_t i = numberOfDependencies;
  while (i > 0) {
    Ring1_ModuleDependency *dependency = &dependencies[--i];
    dependency->relinquish(dependency->moduleHandle);
    dependency->moduleHandle = Ring1_ModuleHandle_Invalid;
  }
}
