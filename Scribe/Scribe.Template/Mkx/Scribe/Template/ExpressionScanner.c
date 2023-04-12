// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/ExpressionScanner.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/ExpressionScanner.h"


#include "Mkx/Scribe/Common.h"


static void
Mkx_Template_ExpressionScanner_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_ExpressionScanner* self
  );

static void
Mkx_Template_ExpressionScanner_constructClass
  (
    Mkx_Template_ExpressionScanner_Class* self
  );

/// @brief The maximal offset.
#define Mkx_Template_ExpressionScanner_Offset_Maximum (INT64_MAX)

MACHINE_DEFINE_CLASSTYPE(Mkx_Template_ExpressionScanner, Mkx_Scribe_Hll_Scanner,
                         &Mkx_Template_ExpressionScanner_visit,
                         &Mkx_Template_ExpressionScanner_construct,
                         NULL,
                         &Mkx_Template_ExpressionScanner_constructClass,
                         NULL)

#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

void
Mkx_Template_ExpressionScanner_construct
  (
    Mkx_Template_ExpressionScanner* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Hll_Scanner_construct(Ring1_cast(Mkx_Scribe_Hll_Scanner*, self), numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Mkx_Template_ExpressionScanner_getType());
}

static void
Mkx_Template_ExpressionScanner_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_ExpressionScanner* self
  )
{ }

Mkx_Template_ExpressionScanner *
Mkx_Template_ExpressionScanner_create
    (
      Mkx_SymbolScanner* symbolScanner
    )
{
  Machine_Type* ty = Mkx_Template_ExpressionScanner_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,symbolScanner));
  Mkx_Template_ExpressionScanner* self = Ring1_cast(Mkx_Template_ExpressionScanner*,
                                                    Machine_allocateClassObject(ty,
                                                                                NUMBER_OF_ARGUMENTS,
                                                                                arguments));
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TYPE Mkx_Template_ExpressionScanner
#include "Mkx/Scribe/Hll/Scanlets.Core.i"
#include "Mkx/Scribe/Hll/Scanlets.scanNewlinesWhitespaces.i"
#include "Mkx/Scribe/Hll/Scanlets.scanName.i"
#include "Mkx/Scribe/Hll/Scanlets.scanInteger.i"
#include "Mkx/Scribe/Hll/Scanlets.scanString.i"
#undef TYPE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
step
  (
    Mkx_Template_ExpressionScanner* self
  )
{
  while (true)
  {
    Ring2_StringBuffer_clear(PARENT(self)->buffer);
    if (PARENT(self)->token.type == Mkx_Scribe_Hll_TokenType_EndOfInput ||
        PARENT(self)->token.type == Mkx_Scribe_Hll_TokenType_Error)
    {
      return;
    }
    switch (current(Ring2_Context_get(), self))
    {
    // `String`
    case '"':
    {
      scanString(Ring2_Context_get(), self);
      return;
    } break;
    case '{':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_LeftCurlyBracket;
      return;
    } break;
    case '}':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_RightCurlyBracket;
      return;
    } break;
    case '(':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_LeftParenthesis;
      return;
    } break;
    case ')':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_RightParenthesis;
      return;
    } break;
    case '>':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_RightAngleBracket;
      return;
    } break;
    break;
    case '\n':
    case '\r':
    {
      scanNewlinesWhitespaces(Ring2_Context_get(), self, NULL);
    } break;
    case ' ':
    case '\t':
    {
      next(Ring2_Context_get(), self);
    } break;
    case '+':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Plus;
      return;
    } break;
    case '-':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Minus;
      return;
    } break;
    case '*':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Star;
      return;
    } break;
    case '/':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Slash;
      return;
    } break;
    case '=':
    {
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Equal;
      return;
    } break;
    default:
    {
      static const bool WITH_STATEMENT = true;
      if (WITH_STATEMENT)
      {
        switch (current(Ring2_Context_get(), self))
        {
        case ';':
        {
          saveAndNext(Ring2_Context_get(), self);
          PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
          PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Semicolon;
          return;
        } break;
        }
      }
      // Name := (Underscore|Alphabetic) (Underscore|Alphabetic|Digit)*
      if (isUnderscore(Ring2_Context_get(), self) || isAlphabetic(Ring2_Context_get(), self))
      {
        scanName(Ring2_Context_get(), self);
      }
      // Numeral := Digit+
      else if (isDigit(Ring2_Context_get(), self))
      {
        scanNumeral(Ring2_Context_get(), self);
      }
      else
      {
        PARENT(self)->token.text = Ring2_String_fromC(false, "<error>");
        PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Error;
      }
      return;
    } break;
    };
  }
}

static void
Mkx_Template_ExpressionScanner_constructClass
  (
    Mkx_Template_ExpressionScanner_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Hll_Scanner_Class *, self)->step = (void (*)(Mkx_Scribe_Hll_Scanner*))&step;
}
