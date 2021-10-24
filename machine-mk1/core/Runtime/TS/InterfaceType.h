/// @file Runtime/TS/ClassType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_TS_INTERFACETYPE_H_INCLUDED)
#define MACHINE_RUNTIME_TS_INTERFACETYPE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "Runtime/TS/Type.h"
typedef struct Machine_Value Machine_Value;

typedef struct Machine_InterfaceType Machine_InterfaceType;

struct Machine_InterfaceType {
  Machine_Type __parent__;
  Machine_InterfaceType**extendedInterfaces;
  size_t numberOfExtendedInterface;
};

#endif // MACHINE_RUNTIME_TS_INTERFACETYPE_H_INCLUDED

