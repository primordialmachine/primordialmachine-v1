#pragma once


#include "Mkx/Scribe/Cas/Nodes.h"


/// @brief Create a vector with variables as its elements.
/// The name of a variable is <code>&lt;variableName&gt;[&lt;index&gt;]</code> where
/// - <code>variableName</code> is the given variable name prefix
/// - <code>index</code> is the index of the element.
/// @return The matrix.
Ring1_CheckReturn() Mkx_Scribe_Cas_VectorNode*
Mkx_Scribe_Cas_createVector
  (
    Ring2_Integer numberOfElements,
    Ring2_String* variableName
  );
