// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Tool.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Cas/Tool.h"


#include <stdio.h>
#include "Ring2/Operations.h"
#include "Mkx/Scribe/Cas.h"

static void
matrixHelp
  (
    Ring2_Context* context,
    Ring2_String* generator
  )
{
  Ring2_emitf(context, Ring2_String_fromC(false, "cas %s (--help | [option] ...)\n"
                                                 "[option]\n"
                                                 "--numberOfRows=<numberOfRows> The number of rows\n"
                                                 "--numberOfColumns=<numberOfColumns> The number of columns\n"
                                                 "--pathname=<pathname> The pathname\n"), generator);
}

static void
vectorHelp
  (
    Ring2_Context* context,
    Ring2_String* generator
  )
{
  Ring2_emitf(context, Ring2_String_fromC(false, "cas %s (--help | [option] ...)\n"
                                                 "[option]\n"
                                                 "--numberOfElements=<numberOfElements> The number of elements\n"
                                                 "--pathname=<pathname> The pathname\n"), generator);
}

static void
getMatrixParams
  (
    Ring2_Context* context,
    Ring2_CommandLine_ArgumentList* argumentList,
    Ring2_String* generator,
    Ring2_String** numberOfRows,
    Ring2_String** numberOfColumns,
    Ring2_String** pathname
  )
{
  Ring2_String
    * numberOfRows_ = NULL,
    * numberOfColumns_ = NULL,
    * pathname_ = NULL;

  if (Ring2_CommandLine_ArgumentList_getSize(argumentList) != 3) {
    Ring2_emitf(context, Ring2_String_fromC(false, "too few arguments\n"));
    matrixHelp(context, generator);
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  for (int64_t i = 0, n = Ring2_CommandLine_ArgumentList_getSize(argumentList); i < n; ++i) {
    Ring2_CommandLine_Argument* a = Ring2_CommandLine_ArgumentList_getAt(argumentList, i);
    if (!Ring2_CommandLine_Argument_getName(a) || !Ring2_CommandLine_Argument_getValue(a))
    {
      Ring2_emitf(context, Ring2_String_fromC(false, "invalid argument\n"));
      matrixHelp(context, generator);
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    Ring2_String *k = Ring2_CommandLine_Argument_getName(a),
                 *v = Ring2_CommandLine_Argument_getValue(a);
    if (Ring2_String_isEqualTo(context, k, Ring2_String_fromC(false, "numberOfRows"))) {
      if (numberOfRows_) { 
        Ring2_emitf(context, Ring2_String_fromC(false, "argument %s specified more than once\n"), k);
        matrixHelp(context, generator);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      numberOfRows_ = v;
    }
    if (Ring2_String_isEqualTo(context, k, Ring2_String_fromC(false, "numberOfColumns")))
    {
      if (numberOfColumns_)
      {
        Ring2_emitf(context, Ring2_String_fromC(false, "argument %s specified more than once\n"), k);
        matrixHelp(context, generator);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      numberOfColumns_ = v;
    }
    if (Ring2_String_isEqualTo(context, k, Ring2_String_fromC(false, "pathname")))
    {
      if (pathname_)
      {
        Ring2_emitf(context, Ring2_String_fromC(false, "argument %s specified more than once\n"), k);
        matrixHelp(context, generator);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      pathname_ = v;
    }
  }
  if (!numberOfRows_)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  *numberOfRows = numberOfRows_;
  if (!numberOfColumns_)
  { 
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  *numberOfColumns = numberOfColumns_;
  if (!pathname_)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  *pathname = pathname_;
}

static void
getVectorParams
  (
    Ring2_Context* context,
    Ring2_CommandLine_ArgumentList* argumentList,
    Ring2_String* generator,
    Ring2_String** numberOfElements,
    Ring2_String** pathname
  )
{
  Ring2_String *numberOfElements_ = NULL,
               *pathname_ = NULL;

  if (Ring2_CommandLine_ArgumentList_getSize(argumentList) != 2) {
    Ring2_emitf(context, Ring2_String_fromC(false, "too few arguments\n"));
    vectorHelp(context, generator);
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  for (int64_t i = 0, n = Ring2_CommandLine_ArgumentList_getSize(argumentList); i < n; ++i) {
    Ring2_CommandLine_Argument *a = Ring2_CommandLine_ArgumentList_getAt(argumentList, i);
    if (!Ring2_CommandLine_Argument_getName(a) || !Ring2_CommandLine_Argument_getValue(a)) {
      Ring2_emitf(context, Ring2_String_fromC(false, "invalid argument\n"));
      vectorHelp(context, generator);
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    Ring2_String *k = Ring2_CommandLine_Argument_getName(a),
                 *v = Ring2_CommandLine_Argument_getValue(a);
    if (Ring2_String_isEqualTo(context, k, Ring2_String_fromC(false, "numberOfElements"))) {
      if (numberOfElements_) {
        Ring2_emitf(context, Ring2_String_fromC(false, "argument %s specified more than once\n"), k);
        vectorHelp(context, generator);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      numberOfElements_ = v;
    }
    if (Ring2_String_isEqualTo(context, k, Ring2_String_fromC(false, "pathname"))) {
      if (pathname_) {
        Ring2_emitf(context, Ring2_String_fromC(false, "argument %s specified more than once\n"), k);
        vectorHelp(context, generator);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      pathname_ = v;
    }
  }
  if (!numberOfElements_) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  *numberOfElements = numberOfElements_;
  if (!pathname_) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  *pathname = pathname_;
}

static void
vectorVectorMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
vectorVectorDivision
  (
    Ring2_Context* context
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinarySlashNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
scalarVectorMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VariableNode_create(Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
scalarMatrixMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a =
    Ring1_cast
      (
        Mkx_Scribe_Cas_Node*,
        Mkx_Scribe_Cas_VariableNode_create
          (
            Ring2_String_fromC(false, "a")
          )
      );

  Mkx_Scribe_Cas_Node* b =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(
      numberOfRows,
      numberOfColumns,
      Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d =
    Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
vectorAddition
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                 Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                 Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(a, b));

  Mkx_Scribe_Cas_Node* d =
    Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
adjugateMatrix
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                   numberOfColumns,
                                                                   Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_AdjugateNode_create(a));

  Mkx_Scribe_Cas_Node* d =
    Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, b);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixAddition
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
vectorSubtraction
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
dotProduct
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DotProductNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixSubtraction
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixPositionMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfElements,
                                                                                          numberOfElements,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_VectorNode_setElement(Ring1_cast(Mkx_Scribe_Cas_VectorNode*, b), numberOfElements - 1,
                                       Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OneNode_create()));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixVectorMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfElements,
                                                                                          numberOfElements,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixDirectionMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  { 
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
  
  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfElements,
                                                                                          numberOfElements,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createVector(numberOfElements,
                                                                                        Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_VectorNode_setElement(Ring1_cast(Mkx_Scribe_Cas_VectorNode *, b), numberOfElements - 1,
                                       Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_ZeroNode_create()));

  Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixMultiplication
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  { 
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
  
  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "b")));

  Mkx_Scribe_Cas_Node* c =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));

  Mkx_Scribe_Cas_Node* d =
    Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, c);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, d);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixDeterminant
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeterminantNode_create(a));

  Mkx_Scribe_Cas_Node* c = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, b);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, c);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
matrixTranspose
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(numberOfRows,
                                                                                          numberOfColumns,
                                                                                          Ring2_String_fromC(false, "a")));

  Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_TransposeNode_create(a));

  Mkx_Scribe_Cas_Node* c = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, b);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, c);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
zeroMatrix
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a =
    Ring1_cast
      (
        Mkx_Scribe_Cas_Node*,
        Mkx_Scribe_Cas_MatrixNode_create
          (
            numberOfRows,
            numberOfColumns
          )
      );

  Mkx_Scribe_Cas_Node* b = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, a);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, b);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
zeroVector
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 2)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of elements.
  Ring2_Integer numberOfElements = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VectorNode_create(numberOfElements));

  Mkx_Scribe_Cas_Node* b = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, a);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, b);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

static void
identityMatrix
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  emissionContext->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Cxx;
  emissionContext->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters;
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  // Get and validate the number of arguments.
  Ring2_Integer numberOfArguments = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  if (numberOfArguments != 3)
  {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the pathname.
  Ring2_String* pathname = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of columns.
  Ring2_Integer numberOfColumns = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  // Get the number of rows.
  Ring2_Integer numberOfRows = Mkx_Interpreter_Stack_getIntegerAt(Ring2_Context_get(), 0);
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);

  Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createIdentityMatrix(numberOfRows,
                                                                                                numberOfColumns));

  Mkx_Scribe_Cas_Node* b = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, a);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, b);
  Ring2_String* s = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
  Machine_setFileContentsString(pathname, s);
}

void
Scribe_Cas_main
  (
    Ring2_Context* context,
    Ring2_CommandLine_ArgumentList* argumentList
  )
{
  if (Ring2_CommandLine_ArgumentList_getSize(argumentList) < 1) {
    fprintf(stderr, "too few arguments\n");
    fprintf(stderr, "usage:\n" "<program> cas [generator] ([generator arguments] ...)\n");
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }

  Ring2_String* generator = Ring2_CommandLine_Argument_getValue(Ring2_CommandLine_ArgumentList_getAt(argumentList, 0));
  Ring2_CommandLine_ArgumentList_removeAt(argumentList, 0);

  if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixDeterminant"))) {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    matrixDeterminant();
  } else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixVectorMultiplication"))) {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    matrixVectorMultiplication();
  } else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixPositionMultiplication"))) {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(context, Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(context, pathname);
    Mkx_Interpreter_Stack_pushInteger(context, 2);
    matrixPositionMultiplication();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixDirectionMultiplication")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    matrixDirectionMultiplication();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "zeroVector")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    zeroVector();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "vectorVectorMultiplication")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    vectorVectorMultiplication(context);
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "vectorVectorDivision")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    vectorVectorDivision(context);
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "scalarVectorMultiplication")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    scalarVectorMultiplication();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "vectorAddition")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    vectorAddition();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "vectorSubtraction")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    vectorSubtraction();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "dotProduct")))
  {
    Ring2_String* numberOfElements, * pathname;
    getVectorParams(context, argumentList, generator, &numberOfElements, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfElements));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 2);
    dotProduct();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "adjugateMatrix")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    adjugateMatrix();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "scalarMatrixMultiplication")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    scalarMatrixMultiplication();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixAddition")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    matrixAddition();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixSubtraction")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    matrixSubtraction();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixMultiplication")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    matrixMultiplication();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "matrixTranspose")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    matrixTranspose();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "zeroMatrix")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    zeroMatrix();
  }
  else if (Ring2_String_isEqualTo(Ring2_Context_get(), generator, Ring2_String_fromC(false, "identityMatrix")))
  {
    Ring2_String* numberOfRows, * numberOfColumns, * pathname;
    getMatrixParams(context, argumentList, generator, &numberOfRows, &numberOfColumns, &pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfRows));
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), Ring2_Integer_fromString(Ring2_Context_get(), numberOfColumns));
    Mkx_Interpreter_Stack_pushString(Ring2_Context_get(), pathname);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), 3);
    identityMatrix();
  }
  else
  {
    fprintf(stderr, "unknown generator\n");
    fprintf(stderr, "usage:\n" "<program> cas [generator] ([generator arguments] ...)\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}
