// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Object/Types.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_OBJECT_TYPES_H_INCLUDED)
#define RING1_OBJECT_TYPES_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Ring1/Object/Types.h' directly, include 'Ring1/Object.h' instead.")
#endif


#include "Ring1/Module.h"
#include "Mkx/Object/Type.h"

#include "Mkx/Object/ArrayType.h"
#include "Mkx/Object/ClassType.h"
#include "Mkx/Object/EnumerationType.h"
#include "Mkx/Object/InterfaceType.h"
#include "Mkx/Object/ScalarType.h"

#include "Mkx/Object/TypeDeclaration.h"
#include "Mkx/Object/TypeDefinition.h"

/// @brief Macro getting the @a Mkx_Type object of a type.
/// @param NAME The C name of the type.
/// @return A pointer to the @a Mkx_Type object on success, a null pointer on failure.
#define MKX_TYPE_GET(NAME) __##NAME##_getType__()


// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_registerclasstype
Mkx_Type*
Mkx_registerClassType
  (
    void (*notifyTypeRemoved)(),
    const Mkx_ClassTypeRegistrationInfo *info
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_registerenumerationtype
Mkx_Type*
Mkx_registerEnumerationType
  (
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_registerinterfacetype
Mkx_Type*
Mkx_registerInterfaceType
  (
    const char* name,
    void (*notifyTypeRemoved)(),
    int (*addPrerequisites)(Mkx_InterfaceType *self),
    size_t dispatchSize
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_registerscalartype
Mkx_Type*
Mkx_registerScalarType
  (
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  );

#endif  // RING1_OBJECT_TYPES_H_INCLUDED
