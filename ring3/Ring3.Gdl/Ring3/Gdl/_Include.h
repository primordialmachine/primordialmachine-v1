/// @file Ring3/Gdl/_Include.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL__INCLUDE_H_INCLUDED)
#define RING3_GDL__INCLUDE_H_INCLUDED

#pragma push_macro("RING3_GDL_PRIVATE")
#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Context.h"
#include "Ring3/Gdl/Extensions.h"
#include "Ring3/Gdl/Lexical/Scanner.h"
#include "Ring3/Gdl/Syntactical/Node.h"
#include "Ring3/Gdl/Syntactical/Parser.h"
#undef RING3_GDL_PRIVATE
#pragma pop_macro("RING3_GDL_PRIVATE")

#endif // RING3_GDL__INCLUDE_H_INCLUDED
