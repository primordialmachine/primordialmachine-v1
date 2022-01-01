/// @file Runtime/Enumeration/EnumerationType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_ENUMERATION_ENUMERATIONTYPE_H_INCLUDED)
#define MACHINE_RUNTIME_ENUMERATION_ENUMERATIONTYPE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Type.h"
typedef struct Machine_Value Machine_Value;

/// C-level representation of an enumeration type.
typedef struct Machine_EnumerationType Machine_EnumerationType;

typedef struct Machine_CreateEnumerationTypeArgs {
  Machine_CreateTypeArgs createTypeArgs;
} Machine_CreateEnumerationTypeArgs;

/// @brief Create an enumeration type.
/// @param args A pointer to a stack-allocated Machine_CreateEnumerationTypeArgs object.
/// @return A pointer to the enumeration type.
Machine_EnumerationType* Machine_createEnumerationType(Machine_CreateEnumerationTypeArgs* args);

void Machine_EnumerationType_ensureInitialized(Machine_EnumerationType* self);

#define MACHINE_DECLARE_ENUMERATIONTYPE(THIS_TYPE)                                                 \
  typedef enum THIS_TYPE THIS_TYPE;                                                                \
  Machine_EnumerationType* THIS_TYPE##_getType();

#define MACHINE_DEFINE_ENUMERATIONTYPE(THIS_TYPE)                                                  \
                                                                                                   \
  static Machine_EnumerationType* g_##THIS_TYPE##_EnumerationType = NULL;                          \
                                                                                                   \
  static void THIS_TYPE##_onTypeDestroyed() {                                                      \
    g_##THIS_TYPE##_EnumerationType = NULL;                                                        \
  }                                                                                                \
                                                                                                   \
  Machine_EnumerationType* THIS_TYPE##_getType() {                                                 \
    if (!g_##THIS_TYPE##_EnumerationType) {                                                        \
      Machine_CreateEnumerationTypeArgs args = { \
        .createTypeArgs = { \
          .typeRemoved = (Machine_TypeRemovedCallback*)&THIS_TYPE##_onTypeDestroyed, \
        }, \
      };                                                \
      g_##THIS_TYPE##_EnumerationType = Machine_createEnumerationType(&args);                      \
    }                                                                                              \
    return g_##THIS_TYPE##_EnumerationType;                                                        \
  }

#endif // MACHINE_RUNTIME_ENUMERATION_ENUMERATIONTYPE_H_INCLUDED
