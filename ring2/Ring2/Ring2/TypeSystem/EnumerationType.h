// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/EnumerationType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPESYSTEM_ENUMERATIONTYPE_H_INCLUDED)
#define RING2_TYPESYSTEM_ENUMERATIONTYPE_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/TypeSystem/EnumerationType.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/TypeSystem/Type.h"

/// @brief The description of an enumeration type.
typedef struct Machine_EnumerationType Machine_EnumerationType;

/// @internal
struct Machine_EnumerationType {
  Machine_Type parent_;
};

/// @brief Arguments to the Machine_createEnumerationType function.
typedef struct Machine_CreateEnumerationTypeArgs {
  Machine_CreateTypeArgs createTypeArgs;
} Machine_CreateEnumerationTypeArgs;

/// @brief Create an enumeration type.
/// @param args A pointer to a stack-allocated Machine_CreateEnumerationTypeArgs object.
/// @return A pointer to the enumeration type.
Machine_EnumerationType* Machine_createEnumerationType(Machine_CreateEnumerationTypeArgs* args);

/// @internal
/// @brief Ensure this enumeration type is initialized.
/// @param self A pointer to this enumeration type.
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
      Machine_CreateEnumerationTypeArgs args = {                                                   \
        .createTypeArgs = {                                                                        \
          .typeRemoved = (Machine_TypeRemovedCallback*)&THIS_TYPE##_onTypeDestroyed,               \
        },                                                                                         \
      };                                                                                           \
      g_##THIS_TYPE##_EnumerationType = Machine_createEnumerationType(&args);                      \
    }                                                                                              \
    return g_##THIS_TYPE##_EnumerationType;                                                        \
  }

#endif // RING2_TYPESYSTEM_ENUMERATIONTYPE_H_INCLUDED
