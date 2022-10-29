// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY__INCLUDE_H_INCLUDED)
#define RING2_LIBRARY__INCLUDE_H_INCLUDED

#pragma push_macro("RING2_LIBRARY_PRIVATE")
#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ArgumentsUtilities.h"
#include "Ring2/Library/ByteBuffer.h"
#include "Ring2/Library/ByteBufferReader.h"
#include "Ring2/Library/Collections/_Include.h"
#include "Ring2/Library/Io.h"
#include "Ring2/Library/StringBuffer.h"
#include "Ring2/Library/StringExtensions.h"
#include "Ring2/Library/Time.h"
#include "Ring2/Library/WeakReference.h"
#undef RING2_LIBRARY_PRIVATE
#pragma pop_macro("RING2_LIBRARY_PRIVATE")

#endif // RING2_LIBRARY__INCLUDE_H_INCLUDED
