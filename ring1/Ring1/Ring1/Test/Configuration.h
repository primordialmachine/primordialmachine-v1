// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Test/Configuration.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_TEST_CONFIGURATION_H_INCLUDED)
#define RING1_TEST_CONFIGURATION_H_INCLUDED

#if !defined(RING1_TEST_PRIVATE) || 1 != RING1_TEST_PRIVATE
#error("Do not include `Ring1/Test/Configuration.h` directly. Include `Ring1/Test.h` instead.")
#endif

/// @brief It this symbolic constant is defined to @a 1, then deprecated functionality is compiled in. */
#define RING1_TEST_WITH_DEPRECATIONS (1)

#endif // RING1_TEST_CONFIGURATION_H_INCLUDED
