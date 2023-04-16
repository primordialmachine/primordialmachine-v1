#include "Mkx/Scribe/Template/EvaluateNode.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Hll.h"
#include "Mkx/Scribe/Template/parseAndEvalTemplate.h"


/// @brief Check the received number of operands of a node is equal to the expected number of operands.
/// @param context The context.
/// @param node The node.
/// @param expected The expected number of operands.
static void
checkOperandCount
  (
    Mkx_Scribe_Hll_Node* node,
    int64_t expected
  )
{
  int64_t received = Mkx_Scribe_Hll_Node_getNumberOfChildren(node);
  if (received != expected)
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s node requires %i arguments, %i given"), expected, received);
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
}

/// @todo Incorporate this into the stack API.
static Ring2_String*
getStringValueChecked
  (
    Ring2_Integer index
  )
{
  if (index >= Mkx_Interpreter_Stack_getSize(Ring2_Context_get()))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack index %i greater than or equal to stack size %i"), index, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()));
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (!Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), index))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack element at stack index %i is not a string"), index);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), index);
}

/// @todo Incorporate this into the stack API.
static Ring2_Integer
getIntegerValueChecked
  (
    Ring2_Integer index
  )
{
  if (index >= Mkx_Interpreter_Stack_getSize(Ring2_Context_get()))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack index %i greater than or equal to stack size %i"), index, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()));
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), index))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack element at stack index %i is not an integer"), index);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), index);
}

static void
pop
  (
    Ring2_Integer count
  )
{
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), count);
}

static void
pushInteger
  (
    Ring2_Integer value
  )
{
  Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), value);
}

static void
pushString
  (
    Ring2_String* value
  )
{
  Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), value);
}

static Mkx_Scribe_Variable *
getOrCreateVariable
  (
    Mkx_Scribe_Environment* environment,
    Ring2_String* name
  )
{
  Mkx_Scribe_Variable* variable = Mkx_Scribe_Environment_get(environment, name);
  if (!variable)
  {
    variable = Mkx_Scribe_Variable_create(name);
    Mkx_Scribe_Environment_set(environment, variable);
  }
  return variable;
}

/// @todo Incorporate this into the stack API.
static Ring2_Value
getValueChecked
  (
    Ring2_Integer index
  )
{
  if (index >= Mkx_Interpreter_Stack_getSize(Ring2_Context_get()))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack index %i greater than or equal to stack size %i"), index, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()));
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (!Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), index))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack element at stack index %i is not a string"), index);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return *Mkx_Interpreter_Stack_getAt(Ring2_Context_get(), index);
}

void
Mkx_Template_evaluateNode
  (
    Mkx_Scribe_Hll_Node* self,
    Mkx_Scribe_Environment* environment
  )
{
  switch (Mkx_Scribe_Hll_Node_getKind(self))
  {
  case Mkx_Scribe_Hll_NodeType_Task:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* leftNode = Mkx_Scribe_Hll_Node_getChildAt(self, 0),
                       * rightNode = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    Mkx_Template_evaluateNode(leftNode, environment);
    Mkx_Template_evaluateNode(rightNode, environment);

    Ring2_String* sourcePathname = getStringValueChecked(1),
                * targetPathname = getStringValueChecked(0);
    pop(2);

    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "  source pathname: %s\n"), sourcePathname);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "  target pathname: %s\n"), targetPathname);

    Ring2_StringBuffer* buffer = Ring2_StringBuffer_create(Ring2_Context_get());
    Mkx_Template_parseAndEvalTemplate(sourcePathname, environment, buffer);
    Machine_setFileContentsString(targetPathname, Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, buffer)));
  } break;
  case Mkx_Scribe_Hll_NodeType_TaskList:
  {
    for (int64_t i = 0, n = Mkx_Scribe_Hll_Node_getNumberOfChildren(self); i < n; ++i)
    {
      Mkx_Template_evaluateNode(Mkx_Scribe_Hll_Node_getChildAt(self, i), environment);
    }
  } break;
  case Mkx_Scribe_Hll_NodeType_CreateTable:
  {
    // if we have pairs (x_i,y_i)(x_i+1,y_i+1) we push them in the order (y_i+1,x_i+1)(y_i,x_i)
    for (int64_t i = Mkx_Scribe_Hll_Node_getNumberOfChildren(self); i > 0; --i)
    {
      Mkx_Template_evaluateNode(Mkx_Scribe_Hll_Node_getChildAt(self, i - 1), environment);
    }
    Mkx_Scribe_Environment* table = Mkx_Scribe_Environment_create();
    for (int64_t i = 0; i < Mkx_Scribe_Hll_Node_getNumberOfChildren(self); i += 2)
    {
      Ring2_Value value = getValueChecked(1);
      Ring2_String* name = getStringValueChecked(0);
      Mkx_Scribe_Variable* variable = Mkx_Scribe_Variable_create(name);
      Mkx_Scribe_Variable_set(variable, value);
      Mkx_Scribe_Environment_set(table, variable);
      pop(2);
    }
    Mkx_Interpreter_Stack_pushObject(Ring2_Context_get(), Ring1_cast(Machine_Object *, table));
  } break;
  case Mkx_Scribe_Hll_NodeType_Statements:
  {
    for (int64_t i = 0, n = Mkx_Scribe_Hll_Node_getNumberOfChildren(self); i < n; ++i)
    {
      Mkx_Scribe_Hll_Node* element = Mkx_Scribe_Hll_Node_getChildAt(self, i);
      Mkx_Template_evaluateNode(element, environment);
    }
  } break;
  case Mkx_Scribe_Hll_NodeType_AssignmentStatement:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* lhsNode = Mkx_Scribe_Hll_Node_getChildAt(self, 0);
    if (Mkx_Scribe_Hll_NodeType_Name != Mkx_Scribe_Hll_Node_getKind(lhsNode))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s:%i: assignment statement node's lhs node must be a name node"),
                                       Mkx_Scribe_Position_getPathName(position),
                                       Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    Mkx_Scribe_Hll_Node* rhs = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    Mkx_Template_evaluateNode(rhs, environment);
    Mkx_Scribe_Hll_LiteralNode* lhsNameNode = Ring1_cast(Mkx_Scribe_Hll_LiteralNode*, lhsNode);
    Ring2_String* name = Mkx_Scribe_Hll_LiteralNode_getName(lhsNameNode);
    Mkx_Scribe_Variable *variable = getOrCreateVariable(environment, name);
    Ring2_Value value = getValueChecked(0);
    Mkx_Scribe_Variable_set(variable, value);
    pop(1);
  } break;
  case Mkx_Scribe_Hll_NodeType_Integer:
  {
    Ring2_Integer value = Mkx_Scribe_Hll_LiteralNode_getInteger(Ring1_cast(Mkx_Scribe_Hll_LiteralNode*, self));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), value);
  } break;
  case Mkx_Scribe_Hll_NodeType_String:
  {
    Ring2_String* value = Mkx_Scribe_Hll_LiteralNode_getString(Ring1_cast(Mkx_Scribe_Hll_LiteralNode*, self));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), value);
  } break;
  case Mkx_Scribe_Hll_NodeType_ProcedureCallExpression:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* leftNode = Mkx_Scribe_Hll_Node_getChildAt(self, 0),
                       * rightNode = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    if (Mkx_Scribe_Hll_Node_getKind(leftNode) != Mkx_Scribe_Hll_NodeType_Name)
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s:%i: node is not of type %s"),
                                       Mkx_Scribe_Position_getPathName(position),
                                       Mkx_Scribe_Position_getLineNumber(position),
                                       Mkx_Scribe_Hll_NodeKind_toString(Mkx_Scribe_Hll_NodeType_Name));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    if (Mkx_Scribe_Hll_Node_getKind(rightNode) != Mkx_Scribe_Hll_NodeType_ArgumentList)
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s:%i: node is not of type %s"),
                                       Mkx_Scribe_Position_getPathName(position),
                                       Mkx_Scribe_Position_getLineNumber(position),
                                       Mkx_Scribe_Hll_NodeKind_toString(Mkx_Scribe_Hll_NodeType_ArgumentList));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    Ring2_String* variableName = Mkx_Scribe_Hll_LiteralNode_getName(Ring1_cast(Mkx_Scribe_Hll_LiteralNode*, leftNode));
    Mkx_Scribe_Variable* variable = Mkx_Scribe_Environment_getRecursive(environment, variableName);
    if (variable)
    {
      if (Mkx_Scribe_Variable_isForeignFunctionValue(variable))
      {
        Ring2_ForeignProcedure* procedure = Mkx_Scribe_Variable_getForeignFunctionValue(variable);
        static Ring2_Value value = Ring2_Value_StaticInitializerVoid();
        Ring2_Value result = Ring2_Value_StaticInitializerVoid();
        (*procedure)(Ring2_Context_get(), &result, 0, &value);
      }
      else
      {
        Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
        Ring2_emitf(Ring2_Context_get(),
                    Ring2_String_fromC(false, "%s:%i: variable %s is not of type foreign function\n"),
                    Mkx_Scribe_Position_getPathName(position),
                    Mkx_Scribe_Position_getLineNumber(position),
                    variableName);
        Ring1_Status_set(Ring1_Status_InvalidArgumentType);
        Ring2_jump();
      }
    }
    else
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: variable %s not defined\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position),
                  variableName);
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
  } break;
  case Mkx_Scribe_Hll_NodeType_IncludeDirective:
  {
    checkOperandCount(self, 1);
    Mkx_Scribe_Hll_Node* pathnameNode = Mkx_Scribe_Hll_Node_getChildAt(self, 0);
    Mkx_Template_evaluateNode(pathnameNode, environment);
    Ring2_String* pathname = getStringValueChecked(0);
    pop(1);

    Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create(Ring2_Context_get());
    Mkx_Scribe_Environment* newEnvironment = Mkx_Scribe_Environment_create(Ring2_Context_get());
    Mkx_Scribe_Environment_setEnclosing(newEnvironment, environment);
    Mkx_Template_parseAndEvalTemplate(pathname, newEnvironment, stringBuffer);
    Ring2_String* string = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, stringBuffer));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), string);
  } break;
  case Mkx_Scribe_Hll_NodeType_Name:
  {
    Ring2_String *variableName = Mkx_Scribe_Hll_LiteralNode_getName(Ring1_cast(Mkx_Scribe_Hll_LiteralNode*, self));
    Mkx_Scribe_Variable* variable = Mkx_Scribe_Environment_getRecursive(environment, variableName);
    if (variable)
    {
      if (Mkx_Scribe_Variable_isIntegerValue(variable))
      {
        Ring2_Integer integerValue = Mkx_Scribe_Variable_getIntegerValue(variable);
        pushInteger(integerValue);
      }
      else if (Mkx_Scribe_Variable_isStringValue(variable))
      {
        Ring2_String* stringValue = Mkx_Scribe_Variable_getStringValue(variable);
        pushString(stringValue);
      }
      else
      {
        Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
        Ring2_emitf(Ring2_Context_get(),
                    Ring2_String_fromC(false, "%s:%i: variable %s is neither of type Integer nor of type String\n"),
                    Mkx_Scribe_Position_getPathName(position),
                    Mkx_Scribe_Position_getLineNumber(position),
                    variableName);
        Ring1_Status_set(Ring1_Status_InvalidArgumentType);
        Ring2_jump();
      }
    }
    else
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: variable %s not defined\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position),
                  variableName);
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
  } break;
  case Mkx_Scribe_Hll_NodeType_Template:
  {
    int64_t m = Mkx_Scribe_Hll_Node_getNumberOfChildren(self);
    int64_t oldStackSize = Mkx_Interpreter_Stack_getSize(Ring2_Context_get());
    Ring2_StringBuffer* temporary = Ring2_StringBuffer_create(Ring2_Context_get());
    for (int64_t i = 0, n = m; i < n; ++i)
    {
      int64_t oldStackSize = Mkx_Interpreter_Stack_getSize(Ring2_Context_get());
      Mkx_Scribe_Hll_Node* element = Mkx_Scribe_Hll_Node_getChildAt(self, i);
      Mkx_Template_evaluateNode(element, environment);
      int64_t newStackSize = Mkx_Interpreter_Stack_getSize(Ring2_Context_get());
      if (newStackSize < oldStackSize)
      {
        Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
        Ring2_emitf(Ring2_Context_get(),
                    Ring2_String_fromC(false, "%s:%i: stack underflow"),
                    Mkx_Scribe_Position_getPathName(position),
                    Mkx_Scribe_Position_getLineNumber(position));
        Ring1_Status_set(Ring1_Status_StackCorruption);
        Ring2_jump();
      }
      else if (newStackSize > oldStackSize)
      {
        if (newStackSize - oldStackSize > 1)
        {
          int64_t delta = newStackSize - oldStackSize;
          Mkx_Interpreter_Stack_pop(Ring2_Context_get(), delta);
          Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
          Ring2_emitf(Ring2_Context_get(),
                      Ring2_String_fromC(false, "%s:%i: %i return values received, expected %i\n"),
                      Mkx_Scribe_Position_getPathName(position),
                      Mkx_Scribe_Position_getLineNumber(position),
                      delta,
                      1);
          Ring1_Status_set(Ring1_Status_InvalidNumberOfOutputs);
          Ring2_jump();
        }
        // Coerce to string.
        if (Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0))
        {
          Ring2_Integer integerValue = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
          Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
          Ring2_String* stringValue = Ring2_Integer_toString(Ring2_Context_get(), integerValue);
          Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), stringValue);
        }
        else if (Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), 0))
        {
          /*Nothing to do.*/
        }
        else
        {
          Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
          Ring2_emitf(Ring2_Context_get(),
                      Ring2_String_fromC(false, "%s:%i: operand not of type Integer or of type String\n"),
                      Mkx_Scribe_Position_getPathName(position),
                      Mkx_Scribe_Position_getLineNumber(position));
          Ring1_Status_set(Ring1_Status_InvalidArgumentType);
          Ring2_jump();
        }
        // Sanity check.
        if (!Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), 0))
        {
          Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
          Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
          Ring2_emitf(Ring2_Context_get(),
                      Ring2_String_fromC(false, "%s:%i: return value at stack index %i is not of type String\n"),
                      Mkx_Scribe_Position_getPathName(position),
                      Mkx_Scribe_Position_getLineNumber(position),
                      0);
          Ring1_Status_set(Ring1_Status_InvalidOutputType);
          Ring2_jump();
        }
        Ring2_String* s = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
        Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
        // Append to buffer.
        Ring2_StringBuffer_appendString(temporary, s);
      }
    }
    int64_t newStackSize = Mkx_Interpreter_Stack_getSize(Ring2_Context_get());
    if (newStackSize != oldStackSize)
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: stack corruption\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_StackCorruption);
      Ring2_jump();
    }
    Ring2_String* string = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, temporary));
    pushString(string);
  } break;
  case Mkx_Scribe_Hll_NodeType_UnaryPlus:
  {
    checkOperandCount(self, 1);
    Mkx_Scribe_Hll_Node *child = Mkx_Scribe_Hll_Node_getChildAt(self, 0);
    Mkx_Template_evaluateNode(child, environment);
    if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    /// @todo Make this an instruction "UnaryPlus".
  } break;
  case Mkx_Scribe_Hll_NodeType_UnaryMinus:
  {
    checkOperandCount(self, 1);
    Mkx_Scribe_Hll_Node* child = Mkx_Scribe_Hll_Node_getChildAt(self, 0);
    Mkx_Template_evaluateNode(child, environment);
    if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    /// @todo Make this an instruction "UnaryMinus".
    Ring2_Integer value = getIntegerValueChecked(0);
    pop(1);
    pushInteger(-value);
  } break;
  case Mkx_Scribe_Hll_NodeType_Star:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* leftChild = Mkx_Scribe_Hll_Node_getChildAt(self, 0),
                       * rightChild = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    Mkx_Template_evaluateNode(leftChild, environment);
    Mkx_Template_evaluateNode(rightChild, environment);
    if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 1))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    /// @todo Make this an instruction "Star".
    Ring2_Integer leftValue = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 1),
                  rightValue = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
    pop(2);
    pushInteger(leftValue * rightValue);
  } break;
  case Mkx_Scribe_Hll_NodeType_Slash:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* leftChild = Mkx_Scribe_Hll_Node_getChildAt(self, 0),
                       * rightChild = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    Mkx_Template_evaluateNode(leftChild, environment);
    Mkx_Template_evaluateNode(rightChild, environment);
    if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 1))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    if (!Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0))
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    /// @todo Make this an instruction "Slash".
    Ring2_Integer leftValue = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 1),
                  rightValue = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
    pop(2);
    pushInteger(leftValue / rightValue);
  } break;
  case Mkx_Scribe_Hll_NodeType_Plus:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* leftChild = Mkx_Scribe_Hll_Node_getChildAt(self, 0),
                       * rightChild = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    Mkx_Template_evaluateNode(leftChild, environment);
    Mkx_Template_evaluateNode(rightChild, environment);
    if (Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), 0)) {
      Ring2_String* leftValue = getStringValueChecked(1),
                  * rightValue = getStringValueChecked(0);
      pop(2);
      Ring2_String* value =
          Ring2_String_concatenate(Ring2_Context_get(), leftValue, rightValue);
      pushString(value);
    } else if (Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0)) {
        Ring2_Integer leftValue = getIntegerValueChecked(1),
                      rightValue = getIntegerValueChecked(0);
      pop(2);
      pushInteger(leftValue + rightValue);
    } else {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                 Ring2_String_fromC(false, "%s:%i: + operands not of supported types\n"),
                 Mkx_Scribe_Position_getPathName(position),
                 Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }

  } break;
  case Mkx_Scribe_Hll_NodeType_Minus:
  {
    checkOperandCount(self, 2);
    Mkx_Scribe_Hll_Node* leftChild = Mkx_Scribe_Hll_Node_getChildAt(self, 0),
                       * rightChild = Mkx_Scribe_Hll_Node_getChildAt(self, 1);
    Mkx_Template_evaluateNode(leftChild, environment);
    Mkx_Template_evaluateNode(rightChild, environment);
    /// @todo Make this an instruction "Minus".
    Ring2_Integer leftValue = getIntegerValueChecked(1),
                  rightValue = getIntegerValueChecked(0);
    pop(2);
    pushInteger(leftValue - rightValue);
  } break;
  case Mkx_Scribe_Hll_NodeType_ToString:
  {
    checkOperandCount(self, 1);
    Mkx_Scribe_Hll_Node* child = Mkx_Scribe_Hll_Node_getChildAt(self, 0);
    Mkx_Template_evaluateNode(child, environment);
    if (Mkx_Interpreter_Stack_isIntegerAt(Ring2_Context_get(), 0))
    {
      Ring2_Integer integerValue = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
      Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
      Ring2_String *stringValue = Ring2_Integer_toString(Ring2_Context_get(), integerValue);
      Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), stringValue);
    }
    else if (Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), 0))
    {
      /*Nothing to do.*/
    }
    else
    {
      Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
      Ring2_emitf(Ring2_Context_get(),
                  Ring2_String_fromC(false, "%s:%i: operand not of type Integer or of type String\n"),
                  Mkx_Scribe_Position_getPathName(position),
                  Mkx_Scribe_Position_getLineNumber(position));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
  } break;
  default:
  {
    Mkx_Scribe_Position* position = Mkx_Scribe_Hll_Node_getPosition(self);
    Ring2_emitf(Ring2_Context_get(),
                Ring2_String_fromC(false, "%s:%i: unknown/unsupported node kind %s\n"),
                Mkx_Scribe_Position_getPathName(position),
                Mkx_Scribe_Position_getLineNumber(position),
                Mkx_Scribe_Hll_NodeKind_toString(Mkx_Scribe_Hll_Node_getKind(self)));
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  } break;
  };
}
