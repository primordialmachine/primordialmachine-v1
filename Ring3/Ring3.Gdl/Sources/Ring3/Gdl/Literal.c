#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Literal.h"
#undef RING3_GDL_PRIVATE

#include "Ring3/Gdl/parse.h"

static void
Ring3_Gdl_Literal_visit
  (
    Ring3_Gdl_Literal* self
  )
{
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_Literal /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring3_Gdl_Literal_visit /*visit*/,
                         &Ring3_Gdl_Literal_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

void
Ring3_Gdl_Literal_construct
  (
    Ring3_Gdl_Literal* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gdl_Literal_getType());
}
