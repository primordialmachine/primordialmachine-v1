// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Configuration.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CONFIGURATION_H_INCLUDED)
#define RING1_INTRINSIC_CONFIGURATION_H_INCLUDED

/// @brief It this symbolic constant is defined to @a 1, then deprecated functionality is compiled in. */
#define Ring1_Intrinsic_WithDeprecations (1)

/// @brief If defined to <code>(1)</code>, then support for IEEE754 32 bit floating-point numbers is compiled in.
#define Ring1_Intrinsic_WithFp32 (1)

/// @brief If defined to <code>(1)</code>, then support for IEEE754 64 bit floating-point nubmers is compiled in.
#define Ring1_Intrinsic_WithFp64 (1)

#endif // RING1_INTRINSIC_CONFIGURATION_H_INCLUDED
