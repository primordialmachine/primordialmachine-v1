#if !defined(MKX_INTERPRETER_INSTRUCTIONS_H_INCLUDED)
#define MKX_INTERPRETER_INSTRUCTIONS_H_INCLUDED

#pragma push_macro("RING2_PRIVATE")
#define RING2_PRIVATE (1)
#include "Ring2/Instructions/Affirmate.h"
#include "Ring2/Instructions/Arithmetic.h"
#include "Ring2/Instructions/Concatenate.h"
#include "Ring2/Instructions/Logical.h"
#include "Ring2/Instructions/Negate.h"
#include "Ring2/Instructions/Relational.h"
#undef RING2_PRIVATE
#pragma pop_macro("RING2_PRIVATE")

#endif // MKX_INTERPRETER_INSTRUCTIONS_H_INCLUDED
