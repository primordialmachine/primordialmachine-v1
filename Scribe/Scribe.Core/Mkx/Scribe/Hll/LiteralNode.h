// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/ConstantExpression.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_HLL_CONSTANTEXPRESSIONNODE_H_INCLUDED)
#define MKX_SCRIBE_HLL_CONSTANTEXPRESSIONNODE_H_INCLUDED


#include "Mkx/Scribe/Hll/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Hll_LiteralNode)

struct Mkx_Scribe_Hll_LiteralNode_Class {
  Mkx_Scribe_Hll_Node _parent;
};

/// @brief A node representing a <code>LiteralNode</code> node.
/// A literal node is used to represent the following syntactic elements:
/// - <code>StringLiteral</code>, <code>IntegerLiteral</code>, <code>RealLiteral</code>, 
/// - <code>BooleanLiteral</code>, 
/// - <code>VoidLiteral</code>,
/// - <code>Name</code>.
struct Mkx_Scribe_Hll_LiteralNode {
  Mkx_Scribe_Hll_Node _parent;
  Ring2_Value value;
};

void
Mkx_Scribe_Hll_LiteralNode_construct
  (
    Mkx_Scribe_Hll_LiteralNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a <code>LiteralNode</code> node.
/// @param literalString The literal string of an integer.
/// @return The <code>ConstantExpression</code> node.
Mkx_Scribe_Hll_LiteralNode*
Mkx_Scribe_Hll_LiteralNode_createFromIntegerLiteralString
    (
      Mkx_Scribe_Position* position,
      Ring2_String*literalString
    );

/// @brief Create a <code>LiteralNode</code> node.
/// @param literalString The literal string of a string.
/// @return The <code>ConstantExpression</code> node.
Mkx_Scribe_Hll_LiteralNode*
Mkx_Scribe_Hll_LiteralNode_createFromStringLiteralString
  (
    Mkx_Scribe_Position* position,
    Ring2_String*literalString
  );

/// @brief Create a <code>LiteralNode</code> node.
/// @param literalString The literal string of a name.
/// @return The <code>ConstantExpression</code> node.
Mkx_Scribe_Hll_LiteralNode*
Mkx_Scribe_Hll_LiteralNode_createFromNameLiteralString
  (
    Mkx_Scribe_Position* position,
    Ring2_String* literalString
  );

Ring2_Integer
Mkx_Scribe_Hll_LiteralNode_getInteger
  (
    Mkx_Scribe_Hll_LiteralNode* self
  );

Ring2_String*
Mkx_Scribe_Hll_LiteralNode_getString
  (
    Mkx_Scribe_Hll_LiteralNode*self
  );

Ring2_String*
Mkx_Scribe_Hll_LiteralNode_getName
  (
    Mkx_Scribe_Hll_LiteralNode* self
  );

#endif // MKX_SCRIBE_HLL_CONSTANTEXPRESSIONNODE_H_INCLUDED
