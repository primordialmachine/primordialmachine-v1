// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/InterfaceType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_OBJECT_INTERFACETYPE_H_INCLUDED)
#define MKX_OBJECT_INTERFACETYPE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/InterfaceType.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/Type.h"


#define MKX_INTERFACETYPE(pointer) ((Mkx_InterfaceType *)(pointer))
typedef struct Mkx_InterfaceType Mkx_InterfaceType;


/// @todo Should not be part of the public API.
/// @brief Get if this interface is a prerequisite of another interface.
/// @param self This interface.
/// @param other The other interface.
/// @return @a true if @a self is a prerequisite of @a other, @a false otherwise.
/// @remark An interface type is always a prerequisite of itself.
Ring1_NonNull(1, 2) bool
Mkx_InterfaceType_isPrerequisite
  (
    const Mkx_InterfaceType *self,
    const Mkx_InterfaceType *other
  );

/// @todo Should not be part of the public API.
/// @brief Get if this interface is a direct prerequisite of another interface.
/// @param self This interface.
/// @param other The other interface.
/// @return @a true if @a self is a prerequisite of @a other, @a false otherwise.
/// @remark An interface type is always a direct prerequisite of itself.
Ring1_NonNull(1, 2) bool
Mkx_InterfaceType_isDirectPrerequisite
  ( 
    const Mkx_InterfaceType* self,
    const Mkx_InterfaceType* other
  );

/// @brief Add another interface as a prerequisite to this interface.
/// @param self This interface.
/// @param other The other interface.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @remark If the other interface is already a prerequisite of this interface,
/// then this function succeeds and does not observably modify the typ system.
Ring1_NonNull() int
Mkx_InterfaceType_addPrerequisite
  (
    Mkx_InterfaceType *self,
    Mkx_InterfaceType *other
  );

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_InterfaceType_ensureInitialized
  (
    Mkx_InterfaceType* self
  );

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_InterfaceType_ensureUninitialized
  (
    Mkx_InterfaceType* self
  );

#endif // MKX_OBJECT_INTERFACETYPE_H_INCLUDED
