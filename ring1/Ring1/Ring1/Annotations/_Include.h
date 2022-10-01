// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_ANNOTATIONS__INCLUDE_H_INCLUDED)
#define RING1_ANNOTATIONS__INCLUDE_H_INCLUDED

#define RING1_PRIVATE (1)
#include "Ring1/Annotations/CheckReturn.h"
#include "Ring1/Annotations/Deprecated.h"
#include "Ring1/Annotations/Inline.h"
#include "Ring1/Annotations/Likely.h"
#include "Ring1/Annotations/NonNull.h"
#include "Ring1/Annotations/NoReturn.h"
#include "Ring1/Annotations/Obsolete.h"
#include "Ring1/Annotations/Unlikely.h"
#undef RING1_PRIVATE

/// @brief Macro unconditionally casting an expression into a type.
/// @param t The type.
/// @param e The expression.
/// @remark
/// @code
/// Ring1_cast(T,e)
/// @endcode
/// is equivalent to
/// @code
/// ((T)(E))
/// @endcode
#define Ring1_cast(t,e) ((t)(e))

#endif // RING1_ANNOTATIONS__INCLUDE_H_INCLUDED
