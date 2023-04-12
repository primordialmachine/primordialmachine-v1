/// @file Ring3/Input/_Include.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3__INPUT_H_INCLUDED)
#define RING3__INPUT_H_INCLUDED

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/KeyboardKeyEvent.h"
#include "Ring3/Input/MouseButtonEvent.h"
#include "Ring3/Input/MousePointerEvent.h"
#include "Ring3/Input/Signals.h"
#undef RING3_INPUT_PRIVATE

#endif // RING3__INPUT_H_INCLUDED
