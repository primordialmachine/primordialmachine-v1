/// @file Mkx/Scribe/Cas/Nodes/VectorNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/VectorNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_VectorNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_VectorNode* self
  );

static void
Mkx_Scribe_Cas_VectorNode_constructClass
  (
    Mkx_Scribe_Cas_VectorNode_Class *self
  );

static void
Mkx_Scribe_Cas_VectorNode_destruct
  (
    Mkx_Scribe_Cas_VectorNode* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_VectorNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_VectorNode_visit,
                         &Mkx_Scribe_Cas_VectorNode_construct,
                         &Mkx_Scribe_Cas_VectorNode_destruct,
                         &Mkx_Scribe_Cas_VectorNode_constructClass,
                         NULL)

static void
checkIndex
  (
    Mkx_Scribe_Cas_VectorNode* self,
    int64_t elementIndex
  )
{
  if (elementIndex < 0 || elementIndex >= self->numberOfElements)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
}

static void
Mkx_Scribe_Cas_VectorNode_destruct
  (
    Mkx_Scribe_Cas_VectorNode* self
  )
{
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

static void
Mkx_Scribe_Cas_VectorNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_VectorNode* self
  )
{
  for (int64_t i = 0, n = self->numberOfElements; i < n; ++i) {
      Mkx_Scribe_Cas_Node* element = self->elements[i];
      if (element) {
        Ring2_Gc_visit(gc, element);
      }
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node* node
  )
{
  if (!node) {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Vector != Mkx_Scribe_Cas_Node_getKind(node)) {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_VectorNode* vectorNode = Ring1_cast(Mkx_Scribe_Cas_VectorNode*, node);
  for (Ring2_Integer i = 0, n = vectorNode->numberOfElements; i < n; ++i) {
    if (!vectorNode->elements[i]) {
      Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
  }
}

static Mkx_Scribe_Cas_VectorNode*
clone
  (
    Mkx_Scribe_Cas_VectorNode* self
  )
{
  Mkx_Scribe_Cas_VectorNode* clone = Mkx_Scribe_Cas_VectorNode_create(self->numberOfElements);
  for (Ring2_Integer i = 0, n = self->numberOfElements; i < n; ++i) {
      Mkx_Scribe_Cas_Node* nodeSelf = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VectorNode_getElement(self, i));
      Mkx_Scribe_Cas_Node* nodeClone = Mkx_Scribe_Cas_Node_clone(nodeSelf);
      Mkx_Scribe_Cas_VectorNode_setElement(clone, i, nodeClone);
  }
  return clone;
}

static void
emit
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_Node* vector =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "vector")));

  Mkx_Scribe_Cas_Node
    * elementSeparator = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ", "))),
    * rowSeparator = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ", ")));

  Mkx_Scribe_Cas_Node
    * rowListOpeningDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
    * rowListClosingDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_Node
    * rowOpeningDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
    * rowClosingDelimiter = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, vector);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowListOpeningDelimiter);
  for (int64_t i = 0, n = self->numberOfElements; i < n; ++i) {
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->elements[i]);
      if (i != self->numberOfElements - 1) {
        Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, elementSeparator);
      }
  }
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rowListClosingDelimiter);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
}

static Ring2_Integer
getNumberOfChildren
  (
    Mkx_Scribe_Cas_VectorNode* self
  )
{ return self->numberOfElements; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer index
  )
{
  Ring2_Integer n = self->numberOfElements;
  if (index < 0 || index >= n)
  {
    Ring1_Log_error("%s:%d: index out of range\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->elements[index];
}

static void
setChildAt
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer index,
    Mkx_Scribe_Cas_Node* node
  )
{
  Ring2_Integer n = self->numberOfElements;
  if (index < 0 || index >= n)
  {
    Ring1_Log_error("%s:%d: index out of range\n", __FILE__, __LINE__);
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
Mkx_Scribe_Cas_VectorNode_construct
  (
    Mkx_Scribe_Cas_VectorNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring2_Integer numberOfElements = Ring2_Value_getInteger(&arguments[0]);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Vector;
  self->numberOfElements = numberOfElements;
  self->capacity = numberOfElements;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&self->elements, Ring1_cast(size_t, self->capacity),
                                 sizeof(Mkx_Scribe_Cas_Node*)))
  {
    Ring1_Log_error("%s:%d: allocation failed\n", __FILE__, __LINE__);
    Ring2_jump();
  }
  for (int64_t i = 0, n = self->capacity; i < n; ++i)
  {
    self->elements[i] = NULL;
  }
  for (int64_t i = 0, n = self->numberOfElements; i < n; ++i)
  {
    self->elements[i] = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  }
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_VectorNode_getType());
}

Mkx_Scribe_Cas_VectorNode*
Mkx_Scribe_Cas_VectorNode_create
  (
    Ring2_Integer numberOfElements
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_VectorNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], numberOfElements);
  Mkx_Scribe_Cas_VectorNode* self = Ring1_cast(Mkx_Scribe_Cas_VectorNode*,
                                               Machine_allocateClassObject(ty,
                                                                           NUMBER_OF_ARGUMENTS,
                                                                           arguments));
  return self;
}

static void
Mkx_Scribe_Cas_VectorNode_constructClass
  (
    Mkx_Scribe_Cas_VectorNode_Class *self
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
Mkx_Scribe_Cas_VectorNode_swapElements
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer firstElementIndex, 
    Ring2_Integer secondElementIndex
  )
{
  checkIndex(self, firstElementIndex);
  checkIndex(self, secondElementIndex);
  Mkx_Scribe_Cas_Node* element = self->elements[firstElementIndex];
  self->elements[firstElementIndex] = self->elements[secondElementIndex];
  self->elements[secondElementIndex] = element;
}

void
Mkx_Scribe_Cas_VectorNode_setElement
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer elementIndex,
    Mkx_Scribe_Cas_Node* node
  )
{
  if (elementIndex < 0 || elementIndex >= self->numberOfElements)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  self->elements[elementIndex] = node;
}

Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_VectorNode_getElement
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer elementIndex
  )
{
  if (elementIndex < 0 || elementIndex >= self->numberOfElements)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->elements[elementIndex];
}

Ring2_Integer
Mkx_Scribe_Cas_VectorNode_getNumberOfElements
  (
    Mkx_Scribe_Cas_VectorNode* self
  )
{ return self->numberOfElements; }

void
Mkx_Scribe_Cas_VectorNode_copyIndices
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer sourceElementIndex,
    Ring2_Integer targetElementIndex
  )
{
  checkIndex(self, sourceElementIndex);
  checkIndex(self, targetElementIndex);
  if (sourceElementIndex == targetElementIndex)
  { return; }
  self->elements[targetElementIndex] = self->elements[sourceElementIndex];
}

void
Mkx_Scribe_Cas_VectorNode_deleteElement
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer elementIndex
  )
{
  if (elementIndex < 0 || elementIndex >= self->numberOfElements)
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  for (Ring2_Integer k = elementIndex; k < (self->numberOfElements - 1); ++k)
  {
    Mkx_Scribe_Cas_VectorNode_copyIndices(self, k + 1, k + 0);
  }
  self->numberOfElements--;
}
