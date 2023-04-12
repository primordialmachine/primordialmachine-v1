#include "Mkx/Scribe/Hll/NodeFactory.h"


#include "Mkx/Scribe/Hll/LiteralNode.h"


Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createProcedureCall
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_ProcedureCallExpression, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createArgumentList
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_ArgumentList, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createTask
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Task, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createCreateTable
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_CreateTable, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createTemplate
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Template, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createUnaryPlus
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_UnaryPlus, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createUnaryMinus
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_UnaryMinus, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createPlus
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Plus, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createMinus
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Minus, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createStar
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Star, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createSlash
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Slash, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createToString
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_ToString, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createStatements
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_Statements, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createAssignmentStatement
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_AssignmentStatement, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createExpressionStatement
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_ExpressionStatement, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createIncludeExpression
  (
    Mkx_Scribe_Position* position
  )
{ return Mkx_Scribe_Hll_Node_create(Mkx_Scribe_Hll_NodeType_IncludeDirective, position); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createNameLiteral
  (
    Mkx_Scribe_Position* position,
    Ring2_String* nameLiteral
  )
{ return Ring1_cast(Mkx_Scribe_Hll_Node*, Mkx_Scribe_Hll_LiteralNode_createFromNameLiteralString(position, nameLiteral)); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createIntegerLiteral
  (
    Mkx_Scribe_Position* position,
    Ring2_String* integerLiteral
  )
{ return Ring1_cast(Mkx_Scribe_Hll_Node*, Mkx_Scribe_Hll_LiteralNode_createFromIntegerLiteralString(position, integerLiteral)); }

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_createStringLiteral
  (
    Mkx_Scribe_Position* position,
    Ring2_String* stringLiteral
  )
{ return Ring1_cast(Mkx_Scribe_Hll_Node*, Mkx_Scribe_Hll_LiteralNode_createFromStringLiteralString(position, stringLiteral)); }
