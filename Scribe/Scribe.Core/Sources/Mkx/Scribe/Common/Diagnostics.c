#define MKX_SCRIBE_COMMON_PRIVATE (1)
#include "Mkx/Scribe/Common/Diagnostics.h"
#undef MKX_SCRIBE_COMMON_PRIVATE

#include "Ring2/_Include.h"

static void
Mkx_Scribe_Diagnostics_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Diagnostics* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Diagnostics,
                         Machine_Object,
                         &Mkx_Scribe_Diagnostics_visit,
                         &Mkx_Scribe_Diagnostics_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Mkx_Scribe_Diagnostics_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Diagnostics* self
  )
{
  if (self->received) {
    Ring2_Gc_visit(gc, self->received);
  }
  if (self->expected) {
    Ring2_Gc_visit(gc, self->expected);
  }
  if (self->position) {
    Ring2_Gc_visit(gc, self->position);
  }
  if (self->positionFormatString) {
    Ring2_Gc_visit(gc, self->positionFormatString);
  }
}

void
Mkx_Scribe_Diagnostics_construct
  (
    Mkx_Scribe_Diagnostics *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*,self), numberOfArguments, arguments);
  self->expected = Ring2_Collections_HashSet_create(Ring2_Context_get());
  self->received = NULL;
  self->position = NULL;
  self->positionFormatString = Ring2_String_fromC(false, "%s:%i:");
  Machine_setClassType(Ring1_cast(Machine_Object*,self), Mkx_Scribe_Diagnostics_getType());
}

Mkx_Scribe_Diagnostics*
Mkx_Scribe_Diagnostics_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Diagnostics_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Mkx_Scribe_Diagnostics *self = Ring1_cast(Mkx_Scribe_Diagnostics*,
                                            Machine_allocateClassObject(ty,
                                                                        NUMBER_OF_ARGUMENTS,
                                                                        ARGUMENTS));
  return self;
}

void
Mkx_Scribe_Diagnostics_clear
  (
    Mkx_Scribe_Diagnostics* self
  )
{
  Ring2_Collections_Collection_clear(Ring1_cast(Ring2_Collections_Collection *, self->expected));
  self->position = NULL;
  self->received = NULL;
}

void
Mkx_Scribe_Diagnostics_setPosition
  (
    Mkx_Scribe_Diagnostics* self,
    Mkx_Scribe_Position* position
  )
{
  self->position = position;
}

void
Mkx_Scribe_Diagnostics_setReceived
  (
    Mkx_Scribe_Diagnostics* self,
    Ring2_String* received
  )
{
  self->received = received;
}

void
Mkx_Scribe_Diagnostics_addExpected
  (
    Mkx_Scribe_Diagnostics* self,
    Ring2_String* expected
  )
{
  Ring2_Value value;
  Ring2_Value_setString(&value, expected);
  Ring2_Collections_Set_add(Ring1_cast(Ring2_Collections_Set *, self->expected), value);
}

Ring2_String*
Mkx_Scribe_Diagnostics_makeMessage
  (
    Mkx_Scribe_Diagnostics* self
  )
{
  if (!self->position || !self->received || 0 == Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, self->expected)))
  {
    return Ring2_String_fromC(false, "<internal error>");
  }
  Ring2_StringBuffer *stringBuffer = Ring2_StringBuffer_create(Ring2_Context_get());
  Ring2_StringBuffer_appendString(stringBuffer, Ring2_String_printf(Ring2_Context_get(), self->positionFormatString,
                                  Mkx_Scribe_Position_getPathName(self->position),
                                  Mkx_Scribe_Position_getLineNumber(self->position)));
  Ring2_Collections_List* list = Ring2_Collections_Set_toList(Ring1_cast(Ring2_Collections_Set *, self->expected));
  int64_t l = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, list));
  if (l == 1)
  {
    Ring2_Value element;
    
    element = Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List*, list), 0);
    Ring2_StringBuffer_appendBytes(stringBuffer, "expected", (int64_t)(sizeof("expected ") - 1));
  }
  else if (l == 2)
  {
    Ring2_Value element;

    element = Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List*, list), 0);
    Ring2_StringBuffer_appendBytes(stringBuffer, "expected", (int64_t)(sizeof("expected ") - 1));
    Ring2_StringBuffer_appendString(stringBuffer, Ring2_Value_getString(&element));
    Ring2_StringBuffer_appendBytes(stringBuffer, " or ", (int64_t)(sizeof(" or ") - 1));
    element = Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List*, list), 1);
    Ring2_StringBuffer_appendString(stringBuffer, Ring2_Value_getString(&element));
  }
  else
  {
    Ring2_Value element;
    int64_t i = 0;
    element =  Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List*, list), ++i);
    Ring2_StringBuffer_appendBytes(stringBuffer, "expected", (int64_t)(sizeof("expected ") - 1));
    for (; i < l - 1; ++i)
    {
      element =  Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List*, list), i);
      Ring2_StringBuffer_appendBytes(stringBuffer, ", ", (int64_t)(sizeof(", ") - 1));
      Ring2_StringBuffer_appendString(stringBuffer, Ring2_Value_getString(&element));
    }
    element =  Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List*, list), i);
    Ring2_StringBuffer_appendBytes(stringBuffer, ", or ", (int64_t)(sizeof(", or ") - 1));
    Ring2_StringBuffer_appendString(stringBuffer, Ring2_Value_getString(&element));
  }
  return Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, stringBuffer));
}
