// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/ScalarType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_OBJECT_SCALARTYPE_H_INCLUDED)
#define MKX_OBJECT_SCALARTYPE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/ScalarType.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/Type.h"


#define MKX_SCALARTYPE(pointer) ((Mkx_ScalarType *)(pointer))
typedef struct Mkx_ScalarType Mkx_ScalarType;


#endif // MKX_OBJECT_SCALARTYPE_H_INCLUDED
