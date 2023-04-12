#pragma once


#include "Mkx/Scribe/Cas/Nodes.h"


/// @brief Create a matrix with variables as its elements.
/// The name of a variable is <code>&lt;variableName&gt;[&lt;index&gt;]</code> where
/// - <code>variableName</code> is the given variable name prefix
/// - <code>index</code> and <code>columnIndex</code> is the index of the element.
/// <code>index</code> is computed by <code>rowIndex * numberOfColumns + columnIndex</code>.
/// @return The matrix.
Ring1_CheckReturn() Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_createMatrix1d
  (
    Ring2_Integer numberOfRows,
    Ring2_Integer numberOfColumns,
    Ring2_String* variableName
  );
