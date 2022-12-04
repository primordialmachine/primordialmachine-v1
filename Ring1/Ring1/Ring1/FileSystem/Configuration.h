// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Configuration.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_CONFIGURATION_H_INCLUDED)
#define RING1_FILESYSTEM_CONFIGURATION_H_INCLUDED

#define RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX (0)
#define RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS (1)
#define RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX (2)

#if defined(_WIN32)
#define RING1_FILESYSTEM_CONFIGURATION_BACKEND                                 \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS
#else
  #error("backend nor supported")
#endif

#endif // RING1_FILESYSTEM_CONFIGURATION_H_INCLUDED
