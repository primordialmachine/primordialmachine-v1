#pragma once


#include "Mkx/Scribe/Cas/Nodes.h"


/// @brief Create a matrix with variables as its elements.
/// The name of a variable is <code>&lt;variableName&gt;[&lt;rowIndex&gt;,&lt;columnIndex&gt;]</code> where
/// - <code>variableName</code> is the given variable name prefix
/// - <code>rowIndex</code> is the row index of the element
/// - <code>columnIndex</code> is the column index of the element
/// @return The matrix.
Ring1_CheckReturn() Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_createMatrix2d
  (
    Ring2_Integer numberOfRows,
    Ring2_Integer numberOfColumns,
    Ring2_String* variableName
  );
