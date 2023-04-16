// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Object/EnumerationType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_ENUMERATIONTYPE_H_INCLUDED)
#define RING1_ENUMERATIONTYPE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/EnumerationType.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/Type.h"


#define MKX_ENUMERATIONTYPE(pointer) ((Mkx_EnumerationType *)(pointer))
typedef struct Mkx_EnumerationType Mkx_EnumerationType;




#endif // RING1_ENUMERATIONTYPE_H_INCLUDED
