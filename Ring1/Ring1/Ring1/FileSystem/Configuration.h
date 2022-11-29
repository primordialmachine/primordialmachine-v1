// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Configuration.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_CONFIGURATION_H_INCLUDED)
#define RING1_FILESYSTEM_CONFIGURATION_H_INCLUDED

#define RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC (0)
#define RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI (1)
#define RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX (2)

#if defined(_WIN32)
#define RING1_FILESYSTEM_CONFIGURATION_BACKEND                                 \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI
#else
  #error("backend nor supported")
#endif

#endif // RING1_FILESYSTEM_CONFIGURATION_H_INCLUDED
