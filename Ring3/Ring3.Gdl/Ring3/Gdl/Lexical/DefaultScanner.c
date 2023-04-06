/// @file Ring3/Gdl/Lexical/DefaultScanner.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Lexical/DefaultScanner.h"

#include "Ring3/Gdl/Lexical/Scanner.h"
#include "Ring3/Gdl/Lexical/DefaultScanner.private.c.i"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"

static void
implement_Ring3_Gdl_Scanner
  (
    Ring3_Gdl_Scanner_Dispatch* self
  )
{
  self->step = (void (*)(Ring3_Gdl_Scanner*)) & stepImpl;
  self->getToken = (Ring3_Gdl_Token*(*)(Ring3_Gdl_Scanner const*self)) & getTokenImpl;
  self->setInput = (void (*)(Ring3_Gdl_Scanner*,Ring2_String*,Ring2_ByteBuffer*)) &setInputImpl;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self,
                              Ring3_Gdl_Scanner_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring3_Gdl_Scanner);
}

static void
Ring3_Gdl_DefaultScanner_visit
  (
    Ring3_Gdl_DefaultScanner* self
  )
{
  if (self->input.name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->input.name);
  }
  if (self->input.bytes) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->input.bytes);
  }
  if (self->lexemeBuffer) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->lexemeBuffer);
  }
  if (self->keywords) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->keywords);
  }
}

static void
Ring3_Gdl_DefaultScanner_construct
  (
    Ring3_Gdl_DefaultScanner* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  
  self->input.name = Ring2_Value_getString(&arguments[0]);

  self->input.bytes = Ring2_ByteBuffer_create();
  Ring2_ByteBuffer* inputBytes = (Ring2_ByteBuffer*)Ring2_Value_getObject(&arguments[1]);
  Ring2_ByteBuffer_appendBytes(self->input.bytes, Ring2_ByteBuffer_getBytes(inputBytes), Ring2_ByteBuffer_getNumberOfBytes(inputBytes));

  self->input.start = 0;
  self->input.end = Ring2_ByteBuffer_getNumberOfBytes(self->input.bytes);

  self->keywords = makeKeywords();

  self->current = 0;
  
  self->lexemeBuffer = Ring2_ByteBuffer_create();
  
  self->token = Ring3_Gdl_Token_create(Ring3_Gdl_TokenKind_StartOfInput,
                                       Ring2_String_fromC(false, "<start of input>"),
                                       0,
                                       0);

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Gdl_DefaultScanner_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_DefaultScanner /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring3_Gdl_DefaultScanner_visit /*visit*/,
                         &Ring3_Gdl_DefaultScanner_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         &implementInterfaces /*implementInterfaces*/)

Ring1_NoDiscardReturn() Ring3_Gdl_DefaultScanner*
Ring3_Gdl_DefaultScanner_create
  (
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  )
{
  Machine_Type* ty = Ring3_Gdl_DefaultScanner_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setString(&arguments[0], inputName);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,inputBytes));
  Ring3_Gdl_DefaultScanner* self = Ring1_cast(Ring3_Gdl_DefaultScanner*,
                                              Machine_allocateClassObject(ty,
                                                                          NUMBER_OF_ARGUMENTS,
                                                                          arguments));
  return self;
}
