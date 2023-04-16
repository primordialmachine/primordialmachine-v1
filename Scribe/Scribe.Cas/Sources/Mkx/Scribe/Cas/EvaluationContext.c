// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/EvaluationContext.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Cas/EvaluationContext.h"

static void
Mkx_Scribe_Cas_EvaluationContext_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_EvaluationContext* self
  );

static void
Mkx_Scribe_Cas_EvaluationContext_constructClass
  (
    Mkx_Scribe_Cas_EvaluationContext_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_EvaluationContext, Machine_Object,
                         &Mkx_Scribe_Cas_EvaluationContext_visit,
                         &Mkx_Scribe_Cas_EvaluationContext_construct,
                         NULL,
                         &Mkx_Scribe_Cas_EvaluationContext_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_EvaluationContext_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_EvaluationContext* self
  )
{ }

static void
Mkx_Scribe_Cas_EvaluationContext_constructClass
  (
    Mkx_Scribe_Cas_EvaluationContext_Class* self
  )
{ }

void
Mkx_Scribe_Cas_EvaluationContext_construct
  (
    Mkx_Scribe_Cas_EvaluationContext *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_EvaluationContext_getType());
}

Mkx_Scribe_Cas_EvaluationContext*
Mkx_Scribe_Cas_EvaluationContext_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_EvaluationContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Mkx_Scribe_Cas_EvaluationContext *self = Ring1_cast(Mkx_Scribe_Cas_EvaluationContext*,
                                                      Machine_allocateClassObject(ty, 
                                                                                  NUMBER_OF_ARGUMENTS,
                                                                                  ARGUMENTS));
  return self;
}
