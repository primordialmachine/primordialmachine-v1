#include "Mkx/Scribe/Cas/Extensions/CreateMatrix1d.h"


#include "Ring1/Log.h"
#include "Mkx/Interpreter/Library.h"


Ring1_CheckReturn() Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_createMatrix1d
  (
    Ring2_Integer numberOfRows,
    Ring2_Integer numberOfColumns,
    Ring2_String* variableName
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s[%i]");

  Mkx_Scribe_Cas_MatrixNode* matrixNode = Mkx_Scribe_Cas_MatrixNode_create(numberOfRows, numberOfColumns);
  for (Ring2_Integer i = 0, n = numberOfRows; i < n; ++i) {
    for (Ring2_Integer j = 0, m = numberOfColumns; j < m; ++j) {
      Ring2_String* fullName = Ring2_String_printf(Ring2_Context_get(), format, variableName, i * numberOfColumns + j);
      Mkx_Scribe_Cas_VariableNode* variableNode = Mkx_Scribe_Cas_VariableNode_create(fullName);
      Mkx_Scribe_Cas_MatrixNode_setElement(matrixNode, i, j, Ring1_cast(Mkx_Scribe_Cas_Node*, variableNode));
    }
  }
  return matrixNode;
}
