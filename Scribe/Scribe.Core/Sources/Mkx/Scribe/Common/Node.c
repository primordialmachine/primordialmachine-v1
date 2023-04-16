#define MKX_SCRIBE_COMMON_PRIVATE (1)
#include "Mkx/Scribe/Common/Node.h"
#undef MKX_SCRIBE_COMMON_PRIVATE

static void
visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Node* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Node, Machine_Object, &visit, &Mkx_Scribe_Node_construct,
                         NULL, NULL, NULL);

static void
visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Node* self
  )
{ }

void
Mkx_Scribe_Node_construct
  (
    Mkx_Scribe_Node* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Node_getType());
}
