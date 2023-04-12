// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/TemplateParser.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/TemplateParser.h"

static void
Mkx_Template_TemplateParser_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_TemplateParser* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Template_TemplateParser, Machine_Object,
                         &Mkx_Template_TemplateParser_visit,
                         &Mkx_Template_TemplateParser_construct,
                         NULL,
                         NULL,
                         NULL)

#define PARENT(expression) ((Mkx_Scribe_Node *)(expression))

static void
Mkx_Template_TemplateParser_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_TemplateParser* self
  )
{
  if (self->scanner) {
    Ring2_Gc_visit(gc, self->scanner);
  }
}

void
Mkx_Template_TemplateParser_construct
  (
    Mkx_Template_TemplateParser* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->scanner = (Mkx_Template_TemplateScanner *)Ring2_Value_getObject(&arguments[0]);
  Machine_setClassType((Machine_Object*)self, Mkx_Template_TemplateParser_getType());
}

Mkx_Template_TemplateParser*
Mkx_Template_TemplateParser_create
  (
    Mkx_Template_TemplateScanner* scanner
  )
{
  Machine_Type* ty = Mkx_Template_TemplateParser_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,scanner));
  Mkx_Template_TemplateParser *self = Ring1_cast(Mkx_Template_TemplateParser*,
                                                 Machine_allocateClassObject(ty,
                                                                             NUMBER_OF_ARGUMENTS,
                                                                             arguments));
  return self;
}
