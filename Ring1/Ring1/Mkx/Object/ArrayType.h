// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Object/ArrayType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_OBJECT_ARRAYTYPE_H_INCLUDED)
#define RING1_OBJECT_ARRAYTYPE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Ring1/Object/ArrayType.h' directly, include 'Ring1/Object.h' instead.")
#endif


#include "Mkx/Object/Type.h"


#define MKX_ARRAYTYPE(pointer) ((Mkx_ArrayType *)(pointer))
typedef struct Mkx_ArrayType Mkx_ArrayType;


#endif // MKX_OBJECT_ARRAYTYPE_H_INCLUDED
