#pragma once


#include "Mkx/Scribe/Cas.h"
#include "Mkx/Scribe/Test/SafeExecute.h"


Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_safeExecute
  (
    void (*function)()
  );

#define TestBegin(NAME, UNEVALUATED, EVALUATED) \
static void \
NAME \
  ( \
  ) \
{ \
  static const char *testName = #NAME; \
  Ring2_String *testNameString = Ring2_String_fromC(false, testName); \
  Mkx_Scribe_Cas_EmissionContext *emissionContext = Mkx_Scribe_Cas_EmissionContext_create(); \
  Mkx_Scribe_Cas_EvaluationVisitor *evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create(); \
  Ring2_String *unevaluatedExpected = Ring2_String_fromC(false, UNEVALUATED), \
               *evaluatedExpected = Ring2_String_fromC(false, EVALUATED); \
  Ring2_String *unevaluatedReceived = NULL, \
               *evaluatedReceived = NULL; \
  Mkx_Scribe_Cas_Node *unevaluatedNode = NULL, \
                      *evaluatedNode = NULL;


#define TestEnd() \
  if (!unevaluatedNode) \
  { \
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "null == unevaluatedNode\n")); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  } \
\
  if (!evaluatedNode) \
  { \
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "null == evaluatedNode\n")); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  } \
\
  Mkx_Scribe_Cas_EmissionContext_reset(emissionContext); \
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, unevaluatedNode); \
  unevaluatedReceived = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer)); \
  if (!Ring2_String_isEqualTo(Ring2_Context_get(), unevaluatedReceived, unevaluatedExpected)) \
  { \
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "test `%s`: unexpected unevaluated result: received\n%s\nexpected\n%s\n"), \
                                     testNameString, unevaluatedReceived, unevaluatedExpected); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  } \
\
  Mkx_Scribe_Cas_EmissionContext_reset(emissionContext); \
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, evaluatedNode); \
  evaluatedReceived = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer)); \
  if (!Ring2_String_isEqualTo(Ring2_Context_get(), evaluatedReceived, evaluatedExpected)) \
  { \
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "test `%s`: unexpected evaluated result: received\n%s\nexpected\n%s\n"), \
                                     testNameString, evaluatedReceived, evaluatedExpected); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  } \
\
  Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s -> %s\n"), unevaluatedReceived, evaluatedReceived); \
}
