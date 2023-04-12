#if !defined(MKX_SCRIBE_NODE_H_INCLUDED)
#define MKX_SCRIBE_NODE_H_INCLUDED

#if !defined(MKX_SCRIBE_COMMON_PRIVATE)
#error Do not include `Mkx/Scribe/Common/Node.h` directly. Include `Mkx/Scribe/Common.h` instead
#endif

#include "Mkx/Scribe/Common/Includes.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Node)

struct Mkx_Scribe_Node_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Scribe_Node {
  Machine_Object _parent;
};

void
Mkx_Scribe_Node_construct
  (
    Mkx_Scribe_Node *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

#endif // MKX_SCRIBE_NODE_H_INCLUDED
