#pragma once


#include "Mkx/Scribe/Cas/Nodes.h"


/// @brief Create an identity matrix.
/// @param numberOfRows The number of rows.
/// @param numberOfColumns The number of columns.
/// @return The matrix.
/// @error @a numberOfRows and @a numberOfColumns are not equal.
Ring1_CheckReturn() Mkx_Scribe_Cas_MatrixNode*
Mkx_Scribe_Cas_createIdentityMatrix
  (
    Ring2_Integer numberOfRows,
    Ring2_Integer numberOfColumns
  );
