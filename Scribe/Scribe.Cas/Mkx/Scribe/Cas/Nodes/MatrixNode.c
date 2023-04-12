/// @file Mkx/Scribe/Cas/Nodes/MatrixNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/MatrixNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_MatrixNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_MatrixNode* self
  );

static void
Mkx_Scribe_Cas_MatrixNode_constructClass
  (
    Mkx_Scribe_Cas_MatrixNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_MatrixNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_MatrixNode_visit,
                         &Mkx_Scribe_Cas_MatrixNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_MatrixNode_constructClass,
                         NULL)

static void
checkIndex2d
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t rowIndex,
    int64_t columnIndex
  )
{
  if (rowIndex < 0 || rowIndex >= self->numberOfRows)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (columnIndex < 0 || columnIndex >= self->numberOfColumns)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
}

static void
checkIndex1d
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t index
  )
{
  if (index < 0 || index >= self->numberOfRows * self->numberOfColumns)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
}

static int64_t
index1d
  (
    int64_t stride,
    int64_t row,
    int64_t column
  )
{ return column + row * stride; }

static void
finalize
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_MatrixNode* self
  )
{
  if (self->elements)
  {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

static void
Mkx_Scribe_Cas_MatrixNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_MatrixNode* self
  )
{
  for (int64_t i = 0, n = self->numberOfRows; i < n; ++i)
  {
    for (int64_t j = 0, m = self->numberOfColumns; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* element = self->elements[index1d(self->stride, i, j)];
      if (element)
      {
        Ring2_Gc_visit(gc, element);
      }
    }
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node* node
  )
{
  if (!node)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MatrixNode* matrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, node);
  for (int64_t i = 0, n = matrixNode->numberOfRows; i < n; ++i)
  {
    for (int64_t j = 0, m = matrixNode->numberOfColumns; j < m; ++j)
    {
      if (!matrixNode->elements[index1d(matrixNode->stride, i, j)])
      {
        Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
    }
  }
}

static Mkx_Scribe_Cas_MatrixNode*
clone
  (
    Mkx_Scribe_Cas_MatrixNode* self
  )
{
  Mkx_Scribe_Cas_MatrixNode *clone = Mkx_Scribe_Cas_MatrixNode_create(self->numberOfRows, self->numberOfColumns);
  for (int64_t i = 0, n = self->numberOfRows; i < n; ++i)
  {
    for (int64_t j = 0, m = self->numberOfColumns; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* nodeSelf = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_MatrixNode_getElement(self, i, j));
      Mkx_Scribe_Cas_Node *nodeClone = Mkx_Scribe_Cas_Node_clone(nodeSelf);
      Mkx_Scribe_Cas_MatrixNode_setElement(clone, i, j, nodeClone);
    }
  }
  return clone;
}

static void
emit
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

#define EMISSION_STYLE_FUNCTIONAL (1)
#define EMISSION_STYLE_IMPERATIVE (2)

#define EMISSION_STYLE EMISSION_STYLE_IMPERATIVE

#if EMISSION_STYLE == EMISSION_STYLE_FUNCTIONAL

  Mkx_Scribe_Cas_Node* matrix = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC("matrix")));

  Mkx_Scribe_Cas_Node
    * elementSeparator = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(", "))),
    * rowSeparator = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(", ")));

  Mkx_Scribe_Cas_Node
    *rowListOpeningDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC("("))),
    *rowListClosingDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(")")));


  Mkx_Scribe_Cas_Node
    *rowOpeningDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC("("))),
    *rowClosingDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, matrix);


  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowListOpeningDelimiter);
  
  for (int64_t i = 0, n = self->numberOfRows; i < n; ++i)
  {
    if (emissionContext->matrixEmissionOption == Mkx_Scribe_Cas_MatrixEmissionOption_RowDelimiters)
    {
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowOpeningDelimiter);
    }
    for (int64_t j = 0, m = self->numberOfColumns; j < m; ++j)
    {
      int64_t index = index1d(self->stride, i, j);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->elements[index]);
      if (j != self->numberOfColumns - 1)
      {
        Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, elementSeparator);
      }
    }
    if (emissionContext->matrixEmissionOption == Mkx_Scribe_Cas_MatrixEmissionOption_RowDelimiters)
    {
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowClosingDelimiter);
    }
    if (i != self->numberOfRows - 1)
    {
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowSeparator);
    }
  }

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowListClosingDelimiter);

#elif EMISSION_STYLE == EMISSION_STYLE_IMPERATIVE

  Mkx_Scribe_Cas_Node
    * beginMatrix = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "beginMatrix()\n"))),
    * endMatrix = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "endMatrix()\n")));

  Mkx_Scribe_Cas_Node
    * beginMatrixRow = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "beginMatrixRow()\n"))),
    * endMatrixRow = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "endMatrixRow()\n")));

  Mkx_Scribe_Cas_Node
    * setMatrixElementSuffix = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")\n")));

  Mkx_Scribe_Cas_Node
    * comma = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ","))),
    * whitespace = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, " "))),
    * newline = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, " ")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, beginMatrix);

  for (int64_t i = 0, n = self->numberOfRows; i < n; ++i)
  {
    if (emissionContext->matrixEmissionOption == Mkx_Scribe_Cas_MatrixEmissionOption_RowDelimiters)
    {
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, beginMatrixRow);
    }
    for (int64_t j = 0, m = self->numberOfColumns; j < m; ++j)
    {
      Ring2_String* setElementPrefixString = Ring2_String_printf(Ring2_Context_get(), Ring2_String_fromC(false, "setMatrixElement(%i, %i, "), i, j);
      Mkx_Scribe_Cas_Node* setElementPrefix = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(setElementPrefixString));
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, setElementPrefix);
      int64_t index = index1d(self->stride, i, j);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->elements[index]);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, setMatrixElementSuffix);

    }
    if (emissionContext->matrixEmissionOption == Mkx_Scribe_Cas_MatrixEmissionOption_RowDelimiters)
    {
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, endMatrixRow);
    }
  }

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, endMatrix);

#else
#error("EMISSION_STYLE not well-defined")
#endif

}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_MatrixNode* self
  )
{ return self->numberOfRows * self->numberOfColumns; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t index
  )
{
  int64_t n = self->numberOfRows * self->numberOfColumns;
  if (index < 0 || index >= n)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->elements[index];
}

static void
setChildAt
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node* node
  )
{
  int64_t n = self->numberOfRows * self->numberOfColumns;
  if (index < 0 || index >= n)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (NULL == node)
  {
    Ring1_Log_error("%s:%d: null pointer\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->elements[index] = node;
}

void
Mkx_Scribe_Cas_MatrixNode_construct
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Matrix;
  self->numberOfRows = Ring2_Value_getInteger(&arguments[0]);
  self->numberOfColumns = Ring2_Value_getInteger(&arguments[1]);
  self->stride = self->numberOfColumns;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&self->elements,
                                 Ring1_cast(size_t, self->numberOfRows * self->numberOfColumns),
                                 sizeof(Mkx_Scribe_Cas_Node*)))
  { 
    Ring1_Log_error("%s:%d: allocation failed\n", __FILE__, __LINE__);
    Ring2_jump();
  }
  for (int64_t i = 0, n = self->numberOfRows; i < n; ++i)
  {
    for (int64_t j = 0, m = self->numberOfColumns; j < m; ++j)
    { 
      self->elements[index1d(self->stride, i, j)] = NULL;
    }
  }
  for (int64_t i = 0, n = self->numberOfRows; i < n; ++i)
  {
    for (int64_t j = 0, m = self->numberOfColumns; j < m; ++j)
    {
      self->elements[index1d(self->stride, i, j)] = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_ZeroNode_create());
    }
  }
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_MatrixNode_getType());
}

Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_MatrixNode_create
  (
    int64_t numberOfRows,
    int64_t numberOfColumns
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_MatrixNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], numberOfRows);
  Ring2_Value_setInteger(&arguments[1], numberOfColumns);
  Mkx_Scribe_Cas_MatrixNode* self = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*,
                                               Machine_allocateClassObject(ty,
                                                                           NUMBER_OF_ARGUMENTS,
                                                                           arguments));
  return self;
}

static void
Mkx_Scribe_Cas_MatrixNode_constructClass
  (
    Mkx_Scribe_Cas_MatrixNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t(*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}

void
Mkx_Scribe_Cas_MatrixNode_swapElements
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t firstElementRowIndex, int64_t firstElementColumnIndex,
    int64_t secondElementRowIndex, int64_t secondElementColumnIndex
  )
{
  int64_t firstElementIndex = index1d(self->stride, firstElementRowIndex, firstElementColumnIndex),
          secondElementIndex = index1d(self->stride, secondElementRowIndex, secondElementColumnIndex);
  Mkx_Scribe_Cas_Node* element = self->elements[firstElementIndex];
  self->elements[firstElementIndex] = self->elements[secondElementIndex];
  self->elements[secondElementIndex] = element;
}

void
Mkx_Scribe_Cas_MatrixNode_setElement
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t rowIndex,
    int64_t columnIndex,
    Mkx_Scribe_Cas_Node* node
  )
{
  if (rowIndex < 0 || rowIndex >= self->numberOfRows)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (columnIndex < 0 || columnIndex >= self->numberOfColumns)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  self->elements[index1d(self->stride, rowIndex, columnIndex)] = node;
}

Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_MatrixNode_getElement
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t rowIndex,
    int64_t columnIndex
  )
{
  if (rowIndex < 0 || rowIndex >= self->numberOfRows)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (columnIndex < 0 || columnIndex >= self->numberOfColumns)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->elements[index1d(self->stride, rowIndex, columnIndex)];
}

int64_t
Mkx_Scribe_Cas_MatrixNode_getNumberOfRows
  (
    Mkx_Scribe_Cas_MatrixNode* self
  )
{ return self->numberOfRows; }

int64_t
Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns
  (
    Mkx_Scribe_Cas_MatrixNode* self
  )
{ return self->numberOfColumns; }

void
Mkx_Scribe_Cas_MatrixNode_copyIndices
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t sourceRowIndex,
    int64_t sourceColumnIndex,
    int64_t targetRowIndex,
    int64_t targetColumnIndex
  )
{
  checkIndex2d(self, sourceRowIndex, sourceColumnIndex);
  checkIndex2d(self, targetRowIndex, targetColumnIndex);
  if (sourceRowIndex == targetRowIndex && sourceColumnIndex == targetColumnIndex)
  { return; }
  int64_t sourceIndex = index1d(self->stride, sourceRowIndex, sourceColumnIndex),
          targetIndex = index1d(self->stride, targetRowIndex, targetColumnIndex);
  self->elements[targetIndex] = self->elements[sourceIndex];
}

void
Mkx_Scribe_Cas_MatrixNode_copyRow
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t sourceRowIndex,
    int64_t targetRowIndex
  )
{
  if (sourceRowIndex == targetRowIndex)
  { return; }
  // Copy (sourceRowIndex, 0) over (targetRowIndex, 0),
  // copy (sourceRowIndex, 1) over (targetRowIndex, 1),
  // ...,
  // copy (sourceRowIndex, numberOfColumns - 1) over (targetRowIndex, numberOfColumns - 1).
  for (int64_t k = 0; k < self->numberOfColumns; ++k)
  {
    Mkx_Scribe_Cas_MatrixNode_copyIndices(self, sourceRowIndex, k, targetRowIndex, k);
  }
}

void
Mkx_Scribe_Cas_MatrixNode_copyColumn
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t sourceColumnIndex,
    int64_t targetColumnIndex
  )
{
  if (sourceColumnIndex == targetColumnIndex)
  { return; }
  // Copy (0,sourceColumnIndex) over (0,targetColumnIndex),
  // copy (1,sourceColumnIndex) over (1,targetColumnIndex),
  // ...,
  // copy (numberOfRows - 1, sourceColumnIndex) over (numberOfRows - 1, targetColumnIndex).
  for (int64_t k = 0; k < self->numberOfRows; ++k)
  {
    Mkx_Scribe_Cas_MatrixNode_copyIndices(self, k, sourceColumnIndex, k, targetColumnIndex);
  }
}

void
Mkx_Scribe_Cas_MatrixNode_deleteRow
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t rowIndex
  )
{
  if (rowIndex < 0 || rowIndex >= self->numberOfRows)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  // Copy row rowIndex + 1 over row rowIndex + 0,
  // copy row rowIndex + 2 over row rowIndex + 1,
  // ...,
  // copy row numberOfRows - 1 over row rowNumberOfRows - 2.
  for (int64_t k = rowIndex; k < (self->numberOfRows - 1); ++k)
  {
    Mkx_Scribe_Cas_MatrixNode_copyRow(self, k + 1, k + 0);
  }
  self->numberOfRows--;
}

void
Mkx_Scribe_Cas_MatrixNode_deleteColumn
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t columnIndex
  )
{
  if (columnIndex < 0 || columnIndex >= self->numberOfColumns)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  // Copy column columnIndex + 1 over column columnIndex + 0,
  // copy column columnIndex + 2 over column columnIndex + 1,
  // ...,
  // copy column numberOfColumns - 1 over column columnNumberOfRows - 2.
  for (int64_t k = columnIndex; k < (self->numberOfColumns - 1); ++k)
  {
    Mkx_Scribe_Cas_MatrixNode_copyColumn(self, k + 1, k + 0);
  }
  self->numberOfColumns--;
}
