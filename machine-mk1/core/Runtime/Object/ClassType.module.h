#if !defined(MACHINE_RUNTIME_OBJECT_CLASSTYPE_MODULE_H_INCLUDED)
#define MACHINE_RUNTIME_OBJECT_CLASSTYPE_MODULE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Object/ClassType.module.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring1/InlineArray.h"
#include "Runtime/Object/ClassType.h"

typedef struct Machine_InterfaceImplementation {
  Machine_InterfaceType* interfaceType;
  Machine_InterfaceConstructCallback* constructInterface;
} Machine_InterfaceImplementation;

typedef struct Machine_InterfaceDispatchNode {
  Machine_InterfaceDispatch* dispatch;
} Machine_InterfaceDispatchNode;

struct Machine_ClassType {
  Machine_Type __parent__;
  Machine_ClassType* parent;

  struct {
    size_t size;
    Machine_ClassObjectVisitCallback* visit;
    Machine_ClassObjectConstructCallback* construct;
    Machine_ClassObjectDestructCallback* destruct;
  } object;

  struct {
    size_t size;
    Machine_ClassConstructCallback* construct;
    void* data;
  } class;

  struct {
    /// @brief Pointer to a Machine_ImplementInterfacesCallback or a null pointer.
    Machine_ImplementInterfacesCallback* implementInterfaces;
    Ring1_InlineArray implementations2;
    bool implementationsInitialized;
    Ring1_InlineArray dispatches2;
    bool dispatchesInitialized;
  } interfaces;
};

#endif // MACHINE_RUNTIME_OBJECT_CLASSTYPE_MODULE_H_INCLUDED
