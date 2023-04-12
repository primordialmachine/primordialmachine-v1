// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/VectorNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_VectorNode)

struct Mkx_Scribe_Cas_VectorNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_VectorNode {
  Mkx_Scribe_Cas_Node _parent;
  Ring2_Integer numberOfElements;
  Ring2_Integer capacity;
  Mkx_Scribe_Cas_Node** elements;
};

/// @brief Construct this matrix node with the values of a zero matrix.
/// @param context The context.
/// @param self This matrix node.
/// @param numberOfElements The number of elements.
/// Must be non-negative.
/// @param m The number of columns.
void
Mkx_Scribe_Cas_VectorNode_construct
  (
    Mkx_Scribe_Cas_VectorNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_VectorNode*
Mkx_Scribe_Cas_VectorNode_create
  (
    Ring2_Integer numberOfElements
  );

/// @brief Swap two elements of this matrix node.
/// @param context The context.
/// @param self This matrix node.
/// @param firstElementIndex The index of one element.
/// Must be within bounds.
/// @param secondElementIndex The index of another element.
/// Must be within bounds.
/// @remark If indices are within bounds and <code>firstElementIndex == secondElementIndex</code> then this function is a no op.
void
Mkx_Scribe_Cas_VectorNode_swapElements
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer firstElementIndex,
    Ring2_Integer secondElementIndex
  );

/// @brief Set an element of this matrix node.
/// @param context The context.
/// @param self This matrix node.
/// @param i, j The indices of one element.
/// @param element The element node.
void
Mkx_Scribe_Cas_VectorNode_setElement
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer elementIndex,
    Mkx_Scribe_Cas_Node* node
  );

/// @brief Get an element of this matrix node.
/// @param context The context.
/// @param self This matrix node.
/// @param elementIndex The index of the element.
/// @return The element node.
Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_VectorNode_getElement
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer elementIndex
  );

/// @brief Get the number of elements of this vector node.
/// @param context The context.
/// @param self This vector node.
/// @return The number of elements.
int64_t
Mkx_Scribe_Cas_VectorNode_getNumberOfElements
  (
    Mkx_Scribe_Cas_VectorNode* self
  );

/// @brief Delete a colum from this matrix node.
/// @param context The context.
/// @param self This matrix node.
/// @param elementIndex The element index.
/// Must be within bounds.
void
Mkx_Scribe_Cas_VectorNode_deleteElement
  (
    Mkx_Scribe_Cas_VectorNode* self,
    Ring2_Integer elementIndex
  );
