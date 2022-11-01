// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPESYSTEM_H_INCLUDED)
#define RING2_TYPESYSTEM_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/TypeSystem.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"
#include "Ring1/Module.h"


#include "Ring2/Gc.h"
typedef struct Machine_Type Machine_Type;

Ring1_Module_Declare(Ring2, TypeSystemModule)

Ring1_CheckReturn() Machine_Type*
Ring2_Type_allocate
  (
    size_t size,
    Ring2_Gc_Type const *type
  );

#endif // RING2_TYPESYSTEM_H_INCLUDED
