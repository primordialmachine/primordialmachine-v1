#if !defined(MKX_SCRIBE_HLL_NODEFACTORY_H_INCLUDED)
#define MKX_SCRIBE_HLL_NODEFACTORY_H_INCLUDED

#include "Mkx/Scribe/Hll/Node.h"

/// @brief Create a <code>ProcedureCall</code> node.
/// @param position The position of the node.
/// @return The <code>ProcedureCall</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createProcedureCall
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>ArgumentList</code> node.
/// @param position The position of the node.
/// @return The <code>ArgumentList</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createArgumentList
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>Task</code> node.
/// @param position The position of the node.
/// @return The <code>Task</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createTask
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>CreateTable</code> node.
/// @param position The position of the node.
/// @return The <code>CreateTable</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createCreateTable
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>Template</code> node.
/// @param position The position of the node.
/// @return The <code>Template</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createTemplate
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create an <code>UnaryPlus</code> node.
/// @param position The position of the node.
/// @return The <code>UnaryPlus</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createUnaryPlus
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create an <code>UnaryMinus</code> node.
/// @param position The position of the node.
/// @return The <code>UnaryMinus</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createUnaryMinus
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create an <code>Plus</code> node.
/// @param position The position of the node.
/// @return The <code>Plus</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createPlus
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create an <code>Minus</code> node.
/// @param position The position of the node.
/// @return The <code>Minus</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createMinus
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create an <code>Star</code> node.
/// @param position The position of the node.
/// @return The <code>Star</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createStar
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create an <code>Slash</code> node.
/// @param position The position of the node.
/// @return The <code>Slash</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createSlash
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>ToString</code> node.
/// @param position The position of the node.
/// @return The <code>Tostring</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createToString
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>Statements</code> node.
/// @param position The position of the node.
/// @return The <code>Statements</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createStatements
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>AssignmentStatement</code> node.
/// @param position The position of the node.
/// @return The <code>AssignmentStatement</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createAssignmentStatement
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>ExpressionStatement</code> node.
/// @param position The position of the node.
/// @return The <code>ExpressionStatement</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createExpressionStatement
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>Include</code> node.
/// @param position The position of the node.
/// @return The <code>Include</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createIncludeExpression
  (
    Mkx_Scribe_Position* position
  );

/// @brief Create a <code>Name</code> node.
/// @param position The position of the node.
/// @return The <code>Name</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createNameLiteral
  (
    Mkx_Scribe_Position* position,
    Ring2_String* nameLiteral
  );

/// @brief Create an <code>Integer</code> node.
/// @param position The position of the node.
/// @return The <code>Integer</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createIntegerLiteral
  (
    Mkx_Scribe_Position* position,
    Ring2_String* integerLiteral
  );

/// @brief Create a <code>String</code> node.
/// @param position The position of the node.
/// @return The <code>String</code> node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createStringLiteral
  (
    Mkx_Scribe_Position *position,
    Ring2_String* stringLiteral
  );

#endif // MKX_SCRIBE_HLL_NODEFACTORY_H_INCLUDED
