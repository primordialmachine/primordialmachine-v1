// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/Type.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_TYPE_H_INCLUDED)
#define MKX_TYPE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/Type.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Ring1/Atom/_Include.h"


/// @todo Should be part of the public API.
#define MKX_TYPE(pointer) ((Mkx_Type *)(pointer))


/// @brief The data of  type.
typedef struct Mkx_Type Mkx_Type;


// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_type_isarraytype
Ring1_CheckReturn() int
Mkx_Type_isArrayType
  (
    bool* result,
    const Mkx_Type* type
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_type_isclasstype
Ring1_CheckReturn() int
Mkx_Type_isClassType
  (
    bool* result,
    const Mkx_Type *type
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_type_isenumerationtype
Ring1_CheckReturn() int
Mkx_Type_isEnumerationType
  (
    bool* result,
    const Mkx_Type* type
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_type_isinterfacetype
Ring1_CheckReturn() int
Mkx_Type_isInterfaceType
  (
    bool *result,
    const Mkx_Type* type
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_type_isscalartype
Ring1_CheckReturn() int
Mkx_Type_isScalarType
  (
    bool *result,
    const Mkx_Type* type
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_type_isinstantiable
Ring1_CheckReturn() int
Mkx_Type_isInstantiableType
  (
    bool *result,
    const Mkx_Type* type
  );

// https://primordialmachine.com/utility-libraries/object-library#mkx_type_getname
Ring1_CheckReturn() int
Mkx_Type_getName
  (
    Ring1_Atom **result,
    const Mkx_Type* type
  );

/// @brief Get if a type is a subtype of another type.
/// @param a The type.
/// @param b The other type.
/// @return @a true if the type @a a is a subtype of the other type @a b, @a false otherwise.
Ring1_CheckReturn() bool
Mkx_Type_isSubTypeOf
  (
    const Mkx_Type* a,
    const Mkx_Type* b
  );

/// @brief Get if a type is a true subtype of another type.
/// @param a The type.
/// @param b The other type.
/// @return @a true if the type @a a is a true subtype of the other type @a b, @a false otherwise.
Ring1_CheckReturn() bool
Mkx_Type_isTrueSubTypeOf
  (
    const Mkx_Type* a,
    const Mkx_Type* b
  );

/// @brief Get if this type has descendant types.
/// @param type A pointer to the type.
/// @return @a true if this type has descendant types, @a false otherwise.
/// @todo Also consider interfaces.
int
Mkx_Type_hasDescendants
  (
    bool *result,
    Mkx_Type* type
  );

#endif // MKX_TYPE_H_INCLUDED
