// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/TemplateScanner.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/TemplateScanner.h"


#include "Mkx/Scribe/Hll.h"


static void
Mkx_Template_TemplateScanner_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_TemplateScanner* self
  );

static void
Mkx_Template_TemplateScanner_constructClass
  (
    Mkx_Template_TemplateScanner_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Template_TemplateScanner, Mkx_Scribe_Hll_Scanner,
                         &Mkx_Template_TemplateScanner_visit,
                         &Mkx_Template_TemplateScanner_construct,
                         NULL,
                         &Mkx_Template_TemplateScanner_constructClass,
                         NULL)

#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

static void
Mkx_Template_TemplateScanner_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_TemplateScanner* self
  )
{ }

void
Mkx_Template_TemplateScanner_construct
  (
    Mkx_Template_TemplateScanner* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Hll_Scanner_construct(Ring1_cast(Mkx_Scribe_Hll_Scanner*, self), numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Mkx_Template_TemplateScanner_getType());
}

Mkx_Template_TemplateScanner*
Mkx_Template_TemplateScanner_create
  (
    Mkx_SymbolScanner* symbolScanner
  )
{
  Machine_Type* ty = Mkx_Template_TemplateScanner_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,symbolScanner));
  Mkx_Template_TemplateScanner* self = Ring1_cast(Mkx_Template_TemplateScanner*,
                                                  Machine_allocateClassObject(ty,
                                                                              NUMBER_OF_ARGUMENTS,
                                                                              arguments));
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TYPE Mkx_Template_TemplateScanner
#include "Mkx/Scribe/Hll/Scanlets.Core.i"
#undef TYPE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static bool
isNewLine
  (
    Ring2_Context* context,
    Mkx_Template_TemplateScanner* self
  )
{
  static const int SYMBOLS[] = { '\n', '\r' };
  return Mkx_SymbolScanner_isAnyOf(PARENT(self)->symbolScanner, 2, SYMBOLS);
}

static void
scanTemplateText
  (
    Ring2_Context* context,
    Mkx_Template_TemplateScanner* self
  )
{
  Ring2_StringBuffer_clear(PARENT(self)->buffer);
  // Scen until until end of the input or expression opening delimiter symbol is encountered.
  // Perform line counting while scanning.
  while (!is(context, self, Mkx_Symbol_EndOfInput) && !is(context, self, '@'))
  {
    if (isNewLine(context, self))
    {
      int old = current(context, self);
      saveAndNext(context, self);
      if (isNewLine(context, self) && old != current(context, self))
      {
        saveAndNext(context, self);
      }
      Mkx_Scribe_Hll_Scanner_incrementInputLineNumber(PARENT(self));
    }
    else
    {
      saveAndNext(context, self);
    }
  }
  PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_String;
  PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
}

static void
step
  (
    Mkx_Template_TemplateScanner* self
  )
{
  // EndOfInput
  if (is(Ring2_Context_get(), self, Mkx_Symbol_EndOfInput))
  {
    PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_EndOfInput;
    PARENT(self)->token.text = Ring2_String_fromC(false, "<end of input>");
  }
  // TemplateText
  else if (!is(Ring2_Context_get(), self, Mkx_Symbol_EndOfInput) && !is(Ring2_Context_get(), self, '@'))
  {
    scanTemplateText(Ring2_Context_get(), self);
  }
  // TemplateExpressionOpeningDelimiter
  else if (is(Ring2_Context_get(), self, '@'))
  {
    next(Ring2_Context_get(), self); // Skip '@'.
    if (is(Ring2_Context_get(), self, '@'))
    {
      next(Ring2_Context_get(), self); // Skip '@'.
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_String;
      PARENT(self)->token.text = Ring2_String_fromC(false, "@");
    }
    else if (is(Ring2_Context_get(), self, '*'))
    {
      while (true)
      {
        while (!is(Ring2_Context_get(), self, Mkx_Symbol_EndOfInput) && !is(Ring2_Context_get(), self, '*'))
        {
          next(Ring2_Context_get(), self);
        }
        if (is(Ring2_Context_get(), self, Mkx_Symbol_EndOfInput))
        {
          Ring2_emitf(Ring2_Context_get(),
                      Ring2_String_fromC(false, "%s:%i: unexpected end of comment. Received %s, expected %s.\n"),
                      getInputPathname(Ring2_Context_get(), self),
                      getInputLineNumber(Ring2_Context_get(), self),
                      Ring2_String_fromC(false, "<end of input>"),
                      Ring2_String_fromC(false, "`*)`"));
          Ring1_Status_set(Ring1_Status_InvalidLexics);
          Ring2_jump();
        }
        else if (is(Ring2_Context_get(), self, '*'))
        {
          next(Ring2_Context_get(), self);
          if (is(Ring2_Context_get(), self, '@'))
          {
            next(Ring2_Context_get(), self);
            break;
          }
        }
      }
      // @todo Remove recursion.
      step(self);
    }
    else if (is(Ring2_Context_get(), self, '('))
    {
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_ExpressionOpeningDelimiter;
      PARENT(self)->token.text = Ring2_String_fromC(false, "@(");
    }
    else if (is(Ring2_Context_get(), self, '{'))
    {
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_StatementOpeningDelimiter;
      PARENT(self)->token.text = Ring2_String_fromC(false, "@{");
    }
    else
    {
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s:%i: malformed opening delimiter: expected '(' or '@'.\n"),
                  getInputPathname(Ring2_Context_get(), self),
                  getInputLineNumber(Ring2_Context_get(), self));
      Ring1_Status_set(Ring1_Status_InvalidLexics);
      Ring2_jump();
    }
  }
}

static void
Mkx_Template_TemplateScanner_constructClass
  (
    Mkx_Template_TemplateScanner_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Hll_Scanner_Class *, self)->step = (void (*)(Mkx_Scribe_Hll_Scanner*)) & step;
}
