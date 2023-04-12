// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/EnvironmentScanner.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Environment/EnvironmentScanner.h"


void
Mkx_Template_EnvironmentScanner_constructClass
  (
    Mkx_Template_EnvironmentScanner_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Template_EnvironmentScanner,
                         Mkx_Scribe_Hll_Scanner,
                         NULL,
                         &Mkx_Template_EnvironmentScanner_construct,
                         NULL,
                         &Mkx_Template_EnvironmentScanner_constructClass,
                         NULL)

#define PARENT(expression) ((Mkx_Scribe_Hll_Scanner *)(expression))

void
Mkx_Template_EnvironmentScanner_construct
  (
    Mkx_Template_EnvironmentScanner* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Hll_Scanner_construct(Ring1_cast(Mkx_Scribe_Hll_Scanner *, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Mkx_Template_EnvironmentScanner_getType());
}

Mkx_Template_EnvironmentScanner*
Mkx_Template_EnvironmentScanner_create
  (
    Mkx_SymbolScanner *symbolScanner
  )
{
  Machine_Type* ty = Mkx_Template_EnvironmentScanner_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,symbolScanner));
  Mkx_Template_EnvironmentScanner *self = Ring1_cast(Mkx_Template_EnvironmentScanner*,
                                                     Machine_allocateClassObject(ty,
                                                                                 NUMBER_OF_ARGUMENTS,
                                                                                 arguments));
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TYPE Mkx_Template_EnvironmentScanner
#include "Mkx/Scribe/Hll/Scanlets.Core.i"
#include "Mkx/Scribe/Hll/Scanlets.scanNewlinesWhitespaces.i"
#include "Mkx/Scribe/Hll/Scanlets.scanName.i"
#include "Mkx/Scribe/Hll/Scanlets.scanInteger.i"
#include "Mkx/Scribe/Hll/Scanlets.scanString.i"
#undef TYPE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @shortcut
static bool
isColon
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{ return is(context, self, ':'); }

/// @shortcut
static bool
isComma
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{ return is(context, self, ','); }

/// @shortcut
static bool
isStar
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{ return is(context, self, '*'); }

/// @shortcut
static bool
isSlash
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{ return is(context, self, '/'); }

/// @shortcut
static bool
isHash
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{ return is(context, self, '#'); }

static void
scanSingleLineCommentRest
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{
  Ring2_StringBuffer_clear(PARENT(self)->buffer);
  while (!is(context, self, Mkx_Symbol_EndOfInput) && !isNewline(context, self))
  {
    saveAndNext(context, self);
  }
  PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Comment;
  PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
}

/// @brief Raise an "unclosed multi line comment" error.
/// @param context A pointer to the context.
/// @param self A pointer to the scanner.
Ring1_NoReturn() static void
errorUnclosedMultiLineComment
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{
  Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%i: unclosed multi line comment\n"),
              getInputLineNumber(context, self));
  Ring1_Status_set(Ring1_Status_InvalidLexics);
  Ring2_jump();
}

static void
scanSlashStarMultiLineCommentRest
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self,
    int64_t *lineCounter
  )
{
  Ring2_StringBuffer_clear(PARENT(self)->buffer);
  while (true) {
    if (is(context, self, Mkx_Symbol_EndOfInput)) {
      errorUnclosedMultiLineComment(context, self);
    } else if (isStar(context, self)) {
      next(context, self);
      if (isSlash(context, self)) {
        next(context, self);
        break; // Comment is done.
      } else {
        writeAndNext(context, self, '*');
      }
    } else if (isNewline(context, self)) {
      do {
        int old = current(context, self);
        saveAndNext(context, self);
        if (isNewline(context, self) && old != current(context, self)) {
          saveAndNext(context, self);
        }
        if (lineCounter) (*lineCounter)++;
      } while (isNewline(context, self));
    } else {
      saveAndNext(context, self);
    }
  }
  PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Comment;
  PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
}

/// @brief Scan <code>SingleLineCommentHash := Hash CharactersInLine*</code>.
/// @param context The context.
/// @param self The scanner.
void
scanSingleLineCommentHash
  (
    Ring2_Context* context,
    Mkx_Template_EnvironmentScanner* self
  )
{
  if (!isHash(context, self))
  {
    Ring2_emitf(context, Ring2_String_fromC(false, "%i: expected '#'\n"),
                getInputLineNumber(context, self));
    Ring1_Status_set(Ring1_Status_InvalidLexics);
    Ring2_jump();
  }
  next(context, self);
  scanSingleLineCommentRest(context, self);
}

static void
step
  (
    Mkx_Template_EnvironmentScanner* self
  )
{
  static bool WithSlashStarMultiLineComment = false;
  static bool WithSlashSlashSingleLineComment = false;
  static bool WithHashSingleLineComment = true;
  if (PARENT(self)->token.type == Mkx_Scribe_Hll_TokenType_EndOfInput)
  {
    return;
  }

  while (true)
  {
    scanNewlinesWhitespaces(Ring2_Context_get(), self, &Ring1_cast(Mkx_Scribe_Hll_Scanner*, self)->symbolScanner->inputLineNumber);

    // start of input.
    if (is(Ring2_Context_get(), self, Mkx_Symbol_StartOfInput))
    {
      PARENT(self)->token.text = Ring2_String_fromC(false, "<start of input>");
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_StartOfInput;
      next(Ring2_Context_get(), self);
    }

    // String.
    if (isDoubleQuote(Ring2_Context_get(), self))
    {
      scanString(Ring2_Context_get(), self);
      return;
    }
    // Name := (Alphabetic | Underscore) (Alphabetic | Underscore | Digit)*
    else if (isAlphabetic(Ring2_Context_get(), self) || isUnderscore(Ring2_Context_get(), self))
    {
      scanName(Ring2_Context_get(), self);
      return;
    }
    else if (is(Ring2_Context_get(), self, '+'))
    {
      Ring2_StringBuffer_clear(PARENT(self)->buffer);
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Plus;
      return;
    }
    else if (is(Ring2_Context_get(), self, '-'))
    {
      Ring2_StringBuffer_clear(PARENT(self)->buffer);
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Minus;
      return;
    }
    // Integer := Digit+
    else if (isDigit(Ring2_Context_get(), self))
    {
      scanNumeral(Ring2_Context_get(), self);
      return;
    }
    // Comma.
    else if (isComma(Ring2_Context_get(), self))
    {
      Ring2_StringBuffer_clear(PARENT(self)->buffer);
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Comma;
      return;
    }
    // Colon.
    else if (isColon(Ring2_Context_get(), self))
    {
      Ring2_StringBuffer_clear(PARENT(self)->buffer);
      saveAndNext(Ring2_Context_get(), self);
      PARENT(self)->token.text = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, PARENT(self)->buffer));
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_Colon;
      return;
    }
    // Comment.
    else if (WithHashSingleLineComment && isHash(Ring2_Context_get(), self))
    {
      next(Ring2_Context_get(), self);
      scanSingleLineCommentRest(Ring2_Context_get(), self);
      // Simply keep going.
    }
    else if ((WithSlashSlashSingleLineComment || WithSlashStarMultiLineComment) && isSlash(Ring2_Context_get(), self))
    {
      next(Ring2_Context_get(), self);
      if (WithSlashSlashSingleLineComment && isSlash(Ring2_Context_get(), self)) {
        next(Ring2_Context_get(), self);
        scanSingleLineCommentRest(Ring2_Context_get(), self);
        // Simply keep going.
      }
      else if (WithSlashStarMultiLineComment && isStar(Ring2_Context_get(), self)) {
        next(Ring2_Context_get(), self);
        scanSlashStarMultiLineCommentRest(Ring2_Context_get(), self, &Ring1_cast(Mkx_Scribe_Hll_Scanner*,self)->symbolScanner->inputLineNumber);
        // Simply keep going.
      }
      else {
        Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%i: unexpected symbol %i\n"),
                    getInputLineNumber(Ring2_Context_get(), self), current(Ring2_Context_get(), self));
        Ring1_Status_set(Ring1_Status_InvalidLexics);
        Ring2_jump();
      }
    }
    // EndOfInput.
    else if (is(Ring2_Context_get(), self, Mkx_Symbol_EndOfInput))
    {
      PARENT(self)->token.text = Ring2_String_fromC(false, "<end of input>");
      PARENT(self)->token.type = Mkx_Scribe_Hll_TokenType_EndOfInput;
      return;
    }
    else
    {
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%i: unexpected symbol %i\n"),
                  getInputLineNumber(Ring2_Context_get(), self), current(Ring2_Context_get(), self));
      Ring1_Status_set(Ring1_Status_InvalidLexics);
      Ring2_jump();
    }
  }
}

static void
Mkx_Template_EnvironmentScanner_constructClass
  (
    Mkx_Template_EnvironmentScanner_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Hll_Scanner_Class *, self)->step = (void (*)(Mkx_Scribe_Hll_Scanner*)) &step;
}
