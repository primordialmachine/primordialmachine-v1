/// @file Runtime/Configuration.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_CONFIGURATION_H_INCLUDED)
#define MACHINE_RUNTIME_CONFIGURATION_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

/// @brief If defined and @a 1, then logging functionality is compiled into the machine.
#if !defined(MACHINE_WITH_LOG)
#define MACHINE_WITH_LOG (1)
#endif

#endif // MACHINE_RUNTIME_CONFIGURATION_H_INCLUDED
