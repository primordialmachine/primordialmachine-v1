#define MKX_SCRIBE_COMMON_PRIVATE (1)
#include "Mkx/Scribe/Common/Position.h"
#undef MKX_SCRIBE_COMMON_PRIVATE

static void
Mkx_Scribe_Position_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Position* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Position,
                         Machine_Object,
                         &Mkx_Scribe_Position_visit,
                         &Mkx_Scribe_Position_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Mkx_Scribe_Position_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Position* self
  )
{
  if (self->pathName) {
    Ring2_Gc_visit(gc, self->pathName);
  }
}

void
Mkx_Scribe_Position_construct
  (
    Mkx_Scribe_Position* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->pathName = Ring2_Value_getString(&arguments[0]);
  if (!self->pathName) { 
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->lineNumber = Ring2_Value_getInteger(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Position_getType());
}

Ring1_NoDiscardReturn() Mkx_Scribe_Position*
Mkx_Scribe_Position_create
  (
    Ring2_String* pathName,
    Ring2_Integer lineNumber
  )
{
  Machine_Type* ty = Mkx_Scribe_Position_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&arguments[0], pathName);
  Ring2_Value_setInteger(&arguments[1], lineNumber);
  Mkx_Scribe_Position *self = Ring1_cast(Mkx_Scribe_Position*,
                                         Machine_allocateClassObject(ty, 
                                                                     NUMBER_OF_ARGUMENTS,
                                                                     arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring2_String*
Mkx_Scribe_Position_getPathName
  (
	  Mkx_Scribe_Position* self
  )
{ return self->pathName; }

Ring1_NoDiscardReturn() Ring2_Integer
Mkx_Scribe_Position_getLineNumber
  (
	  Mkx_Scribe_Position* self
  )
{ return self->lineNumber; }
