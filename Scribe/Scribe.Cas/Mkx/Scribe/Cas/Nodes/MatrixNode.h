// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/MatrixNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_MatrixNode)

struct Mkx_Scribe_Cas_MatrixNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_MatrixNode {
  Mkx_Scribe_Cas_Node _parent;
  int64_t numberOfRows;
  int64_t numberOfColumns;
  int64_t stride; ///< @brief Number of array elements between one row and another row.
  Mkx_Scribe_Cas_Node** elements;
};

/// @brief Construct this matrix node with the values of a zero matrix.
/// @param self This matrix node.
/// Must be non-negative.
/// @param numberOfRows The number of rows.
/// Must be non-negative.
/// @param numberOfColumns The number of columns.
/// Must be non-negative.
void
Mkx_Scribe_Cas_MatrixNode_construct
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_MatrixNode *
Mkx_Scribe_Cas_MatrixNode_create
  (
    int64_t numberOfRows,
    int64_t numberOfColumns
  );

/// @brief Swap two elements of this matrix node.
/// @param self This matrix node.
/// @param firstElementRowIndex, firstElementColumnIndex The indices of one element.
/// Must be within bounds.
/// @param secondElementRowIndex, secondElementColumnIndex The indices of another element.
/// Must be within bounds.
/// @remark If indices are within bounds and <code>i == k</code> and <code>j == l</code> then this function is a no op.
void
Mkx_Scribe_Cas_MatrixNode_swapElements
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t firstElementRowIndex, int64_t firstElementColumnIndex,
    int64_t secondElementRowIndex, int64_t secondElementColumnIndex
  );

/// @brief Set an element of this matrix node.
/// @param self This matrix node.
/// @param rowIndex, columnIndex The row and the column index of the element.
/// Must be within bounds.
/// @param element The element node.
void
Mkx_Scribe_Cas_MatrixNode_setElement
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t rowIndex,
    int64_t columnIndex,
    Mkx_Scribe_Cas_Node *node
  );

/// @brief Get an element of this matrix node.
/// @param self This matrix node.
/// @param rowIndex, columnIndex The row and the column index of the element.
/// @return The element node.
Mkx_Scribe_Cas_Node *
Mkx_Scribe_Cas_MatrixNode_getElement
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t rowIndex,
    int64_t columnIndex
  );

/// @brief Get the number of rows of this matrix node.
/// @param self This matrix node.
/// @return The number of rows.
int64_t
Mkx_Scribe_Cas_MatrixNode_getNumberOfRows
  (
    Mkx_Scribe_Cas_MatrixNode* self
  );

/// @brief Get the number of columns of this matrix node.
/// @param self This matrix node.
/// @return The number of columns.
int64_t
Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns
  (
    Mkx_Scribe_Cas_MatrixNode* self
  );

/// @brief Delete a row from this matrix node.
/// @param self This matrix node.
/// @param rowIndex The row index.
void
Mkx_Scribe_Cas_MatrixNode_deleteRow
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t rowIndex
  );

/// @brief Delete a colum from this matrix node.
/// @param self This matrix node.
/// @param columnIndex The column index.
void
Mkx_Scribe_Cas_MatrixNode_deleteColumn
  (
    Mkx_Scribe_Cas_MatrixNode* self,
    int64_t columnIndex
  );

/// @brief Copy the row at a source index to a target index.
/// @param self This matrix node.
/// @param sourceRowIndex The source index.
/// @param targetRowIndex The target index.
void
Mkx_Scribe_Cas_MatrixNode_copyRow
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t sourceRowIndex,
    int64_t targetRowIndex
  );
  
/// @brief Copy the column at a source index to a target index.
/// @param self This matrix node.
/// @param sourceColumnIndex The source index.
/// @param targetColumnIndex The target index.
void
Mkx_Scribe_Cas_MatrixNode_copyColumn
  (
    Mkx_Scribe_Cas_MatrixNode *self,
    int64_t sourceColumnIndex,
    int64_t targetColumnIndex
  );
