#include "Mkx/Scribe/Cas/Extensions/CreateMatrix2d.h"

#include "Mkx/Interpreter/Library.h"


Ring1_CheckReturn() Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_createMatrix2d
  (
    Ring2_Integer numberOfRows,
    Ring2_Integer numberOfColumns,
    Ring2_String*variableName
  )
{
  Mkx_Scribe_Cas_MatrixNode* matrixNode = Mkx_Scribe_Cas_MatrixNode_create(numberOfRows, numberOfColumns);
  for (int64_t i = 0, n = numberOfRows; i < n; ++i)
  {
    for (int64_t j = 0, m = numberOfColumns; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* variableNode = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_VariableNode_create(variableName));
      Mkx_Scribe_Cas_Node* indexNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_Index2dNode_create(i, j, variableNode));
      Mkx_Scribe_Cas_MatrixNode_setElement(matrixNode, i, j, indexNode);
    }
  }
  return matrixNode;
}
