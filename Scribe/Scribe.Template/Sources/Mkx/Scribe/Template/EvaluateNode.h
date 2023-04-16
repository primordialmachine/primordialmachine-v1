#if !defined(MKX_SCRIBE_TEMPLATE_NODES_EVALUATENODE_H_INCLUDED)
#define MKX_SCRIBE_TEMPLATE_NODES_EVALUATENODE_H_INCLUDED


#include "Mkx/Scribe/Environment.h"
#include "Mkx/Scribe/Hll.h"


/// @brief Evaluate a node.
/// @param context The context.
/// @param self The node.
/// @param environment The environment.
void
Mkx_Template_evaluateNode
  (
    Mkx_Scribe_Hll_Node* self,
    Mkx_Scribe_Environment* environment
  );

#endif // MKX_SCRIBE_TEMPLATE_NODES_EVALUATENODE_H_INCLUDED
