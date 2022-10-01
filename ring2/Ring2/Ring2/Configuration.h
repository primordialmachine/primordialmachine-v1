// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Configuration.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_CONFIGURATION_H_INCLUDED)
#define RING2_CONFIGURATION_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Configuration.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#define Ring2_Configuration_withArray (0)

#define Ring2_Configuration_withBoolean (1)

#define Ring2_Configuration_withForeignProcedure (1)

#define Ring2_Configuration_withInteger (1)

#define Ring2_Configuration_withObject (1)

#define Ring2_Configuration_withReal (1)

#define Ring2_Configuration_withString (1)

#define Ring2_Configuration_withVoid (1)

#endif // RING2_CONFIGURATION_H_INCLUDED
