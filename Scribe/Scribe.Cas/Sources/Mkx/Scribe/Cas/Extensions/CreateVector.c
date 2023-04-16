#include "Mkx/Scribe/Cas/Extensions/CreateVector.h"

#include "Mkx/Interpreter/Library.h"


Ring1_CheckReturn() Mkx_Scribe_Cas_VectorNode*
Mkx_Scribe_Cas_createVector
  (
    Ring2_Integer numberOfElements,
    Ring2_String* variableName
  )
{
  Mkx_Scribe_Cas_VectorNode* vectorNode = Mkx_Scribe_Cas_VectorNode_create(numberOfElements);
  for (int64_t i = 0, n = numberOfElements; i < n; ++i)
  {
      Mkx_Scribe_Cas_Node* variableNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VariableNode_create(variableName));
      Mkx_Scribe_Cas_Node* indexNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_Index1dNode_create(i, variableNode));
      Mkx_Scribe_Cas_VectorNode_setElement(vectorNode, i, indexNode);
  }
  return vectorNode;
}
