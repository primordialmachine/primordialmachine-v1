#pragma once


#include "Mkx/Scribe/Cas.h"
#include "Mkx/Scribe/Test/SafeExecute.h"


Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_safeExecute
  (
    Mkx_Interpreter_Context* context,
    void (*function)(Mkx_Interpreter_Context *)
  );

#define TestBegin(NAME, UNEVALUATED, EVALUATED) \
static void \
NAME \
  ( \
    Mkx_Interpreter_Context* context \
  ) \
{ \
  Mkx_Scribe_Cas_EmissionContext *emissionContext = Mkx_Scribe_Cas_EmissionContext_create(context); \
  Mkx_Scribe_Cas_EvaluationVisitor *evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create(context); \
  Mkx_Interpreter_String *unevaluatedExpected = Mkx_Interpreter_Ffi_String_create(context, UNEVALUATED), \
                         *evaluatedExpected = Mkx_Interpreter_Ffi_String_create(context, EVALUATED); \
  Mkx_Interpreter_String *unevaluatedReceived = NULL, \
                         *evaluatedReceived = NULL; \
  Mkx_Scribe_Cas_Node *unevaluatedNode = NULL, \
                      *evaluatedNode = NULL;


#define TestEnd() \
  if (!unevaluatedNode) \
  { \
    Mkx_Interpreter_emitf(context, Mkx_Interpreter_Ffi_String_create(context, "null == unevaluatedNode\n")); \
    Mkx_Interpreter_ErrorHandler_raise(Mkx_Interpreter_Context_getErrorHandler(context), -1); \
  } \
\
  if (!evaluatedNode) \
  { \
    Mkx_Interpreter_emitf(context, Mkx_Interpreter_Ffi_String_create(context, "null == evaluatedNode\n")); \
    Mkx_Interpreter_ErrorHandler_raise(Mkx_Interpreter_Context_getErrorHandler(context), -1); \
  } \
\
  Mkx_Scribe_Cas_EmissionContext_reset(context, emissionContext); \
  Mkx_Scribe_Cas_EmissionContext_emit(context, emissionContext, unevaluatedNode); \
  unevaluatedReceived = Mkx_Interpreter_Library_StringBuffer_toString(context, emissionContext->outputStringBuffer); \
  if (!Mkx_Interpreter_String_equalTo(context, unevaluatedReceived, unevaluatedExpected)) \
  { \
    Mkx_Interpreter_emitf(context, Mkx_Interpreter_Ffi_String_create(context, "unexpected unevaluated result: received %s, expected %s\n"), unevaluatedReceived, unevaluatedExpected); \
    Mkx_Interpreter_ErrorHandler_raise(Mkx_Interpreter_Context_getErrorHandler(context), -1); \
  } \
\
  Mkx_Scribe_Cas_EmissionContext_reset(context, emissionContext); \
  Mkx_Scribe_Cas_EmissionContext_emit(context, emissionContext, evaluatedNode); \
  evaluatedReceived = Mkx_Interpreter_Library_StringBuffer_toString(context, emissionContext->outputStringBuffer); \
  if (!Mkx_Interpreter_String_equalTo(context, evaluatedReceived, evaluatedExpected)) \
  { \
    Mkx_Interpreter_emitf(context, Mkx_Interpreter_Ffi_String_create(context, "unexpected evaluated result: received %s, expected %s\n"), evaluatedReceived, evaluatedExpected); \
    Mkx_Interpreter_ErrorHandler_raise(Mkx_Interpreter_Context_getErrorHandler(context), -1); \
  } \
\
  Mkx_Interpreter_emitf(context, Mkx_Interpreter_Ffi_String_create(context, "%s -> %s\n"), unevaluatedReceived, evaluatedReceived); \
}
