// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Void.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_VOID_H_INCLUDED)
#define RING2_TYPES_VOID_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

/// @brief The C-level representation of the "Void" type.
typedef char Ring2_Void;

/// @brief Symbolic constant evaluating to the C-level representation of the "void" value.
#define Ring2_Void_Void (0)

#endif // Ring2_Configuration_withVoid

#endif // RING2_TYPES_VOID_H_INCLUDED
