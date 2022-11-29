// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/Initialize.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_IO_INITIALIZE_H_INCLUDED)
#define RING2_LIBRARY_IO_INITIALIZE_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Io/Initialize.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
typedef struct Ring2_Context Ring2_Context; // Forward declaration.
typedef struct Ring2_String Ring2_String; // Forward declaration.

void
Machine_Io_initialize
  (
  );

Ring2_String*
Machine_Io_makePathname
  (
    Ring2_Context* context,
    const Ring2_String* source
  );

#endif // RING2_LIBRARY_IO_INITIALIZE_H_INCLUDED
