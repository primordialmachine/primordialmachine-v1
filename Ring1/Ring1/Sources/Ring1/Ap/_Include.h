#if !defined(RING1_AP__INCLUDE_H_INCLUDED)
#define RING1_AP__INCLUDE_H_INCLUDED

#include "Ring1/Module.h"

Ring1_Module_Declare(Ring1, Ap)

#pragma push_macro("RING1_AP_PRIVATE")
#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApBool.h"
#include "Ring1/Ap/ApInt.h"
#include "Ring1/Ap/ApNat.h"
#include "Ring1/Ap/ApReal.h"
#undef RING1_AP_PRIVATE
#pragma pop_macro("RING1_AP_PRIVATE")

#endif // RING1_AP_APINT_H_INCLUDED
