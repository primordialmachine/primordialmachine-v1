#include "Mkx/Scribe/Cas/Extensions/CreateMatrix1d.h"


#include "Ring1/Log.h"
#include "Mkx/Interpreter/Library.h"


Ring1_CheckReturn() Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_createIdentityMatrix
  (
    Ring2_Integer numberOfRows,
    Ring2_Integer numberOfColumns
  )
{
  if (numberOfRows != numberOfColumns) {
    Ring1_Log_error("%s:%d: numberOfRows != numberOfColumns argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MatrixNode* matrixNode = Mkx_Scribe_Cas_MatrixNode_create(numberOfRows, numberOfColumns);
  for (Ring2_Integer i = 0, n = numberOfRows; i < n; ++i) {
      Mkx_Scribe_Cas_Node* oneNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
      Mkx_Scribe_Cas_MatrixNode_setElement(matrixNode, i, i, oneNode);
  }
  return matrixNode;
}
