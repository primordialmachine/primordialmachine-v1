// Copyright (c) 2019 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/Obsolete.h
/// @copyright Copyright (c) 2019 Simulacrum Technology. All rights reserved.
/// @author Simulacrum Technology (contact@simulacrum.technology)

#if !defined(MKX_INTRINSIC_OBSOLETE_H_INCLUDED)
#define MKX_INTRINSIC_OBSOLETE_H_INCLUDED


#include "Ring1/Intrinsic/Configuration.h"


/// @brief Function annotation indicating a function is obsolete i.e. must not be used.
/// @param message A string literal with information on the obsolete function.
#define Mkx_Intrinsic_Obsolete(message)

#if defined(Mkx_Intrinsic_WithDeprecations) && 1 == Mkx_Intrinsic_WithDeprecations
  #define Mkx_Obsolete(message) Mkx_Intrinsic_Obsolete(message)
#endif


#endif // MKX_INTRINSIC_OBSOLETE_H_INCLUDED
