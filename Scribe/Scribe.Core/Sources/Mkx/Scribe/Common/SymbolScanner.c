#define MKX_SCRIBE_COMMON_PRIVATE (1)
#include "Mkx/Scribe/Common/SymbolScanner.h"
#undef MKX_SCRIBE_COMMON_PRIVATE

static void
Mkx_SymbolScanner_visit
  (
    Ring2_Gc* gc,
    Mkx_SymbolScanner* self
  );

static void
Mkx_SymbolScanner_constructClass
  (
    Mkx_SymbolScanner_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_SymbolScanner, Machine_Object,
                         &Mkx_SymbolScanner_visit, &Mkx_SymbolScanner_construct,
                         NULL, &Mkx_SymbolScanner_constructClass, NULL)

void
Mkx_SymbolScanner_construct
  (
    Mkx_SymbolScanner* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->inputString = Ring2_Value_getString(&arguments[0]);
  
  self->inputPathname = Ring2_Value_getString(&arguments[1]);
  self->inputLineNumber = 1;

  self->inputBytes = Ring2_String_getBytes(self->inputString);

  self->offsets.begin = 0;
  self->offsets.end = Ring2_String_getNumberOfBytes(self->inputString);
  self->offsets.current = self->offsets.begin;

  Machine_setClassType((Machine_Object*)self, Mkx_SymbolScanner_getType());
}

static void
Mkx_SymbolScanner_visit
  (
    Ring2_Gc* gc,
    Mkx_SymbolScanner* self
  )
{
  if (NULL != self->inputString)
  {
    Ring2_Gc_visit(gc, self->inputString);
  }
  if (NULL != self->inputPathname)
  {
    Ring2_Gc_visit(gc, self->inputPathname);
  }
}

static void
Mkx_SymbolScanner_constructClass
  (
    Mkx_SymbolScanner_Class* self
  )
{ }

Mkx_SymbolScanner*
Mkx_SymbolScanner_create
  (
    Ring2_String  *inputString,
    Ring2_String* inputPathname
  )
{
  Machine_Type* ty = Mkx_SymbolScanner_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&arguments[0], inputString);
  Ring2_Value_setString(&arguments[1], inputPathname);
  Mkx_SymbolScanner *self = Ring1_cast(Mkx_SymbolScanner*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

int
Mkx_SymbolScanner_current
  (
    Mkx_SymbolScanner* self
  )
{
  if (self->offsets.current == self->offsets.end)
  {
    return Mkx_Symbol_EndOfInput;
  }
  else
  {
    return *(self->inputBytes + self->offsets.current);
  }
}

int64_t
Mkx_SymbolScanner_beginOffset
  (
    Mkx_SymbolScanner* self
  )
{ return (int64_t)(self->offsets.begin); }

int64_t
Mkx_SymbolScanner_endOffset
  (
    Mkx_SymbolScanner* self
  )
{ return (int64_t)(self->offsets.end); }

int64_t
Mkx_SymbolScanner_currentOffset
  (
    Mkx_SymbolScanner* self
  )
{ return (int64_t)(self->offsets.current); }

void
Mkx_SymbolScanner_setInputBytes
  (
    Mkx_SymbolScanner* self,
    Ring2_String* inputString,
    Ring2_String* inputPathname,
    int64_t inputLineNumber,
    uint64_t offsetBegin,
    uint64_t offsetEnd,
    uint64_t offsetCurrent
  )
{
  self->inputString = inputString;

  self->inputPathname = inputPathname;
  self->inputLineNumber = inputLineNumber;
  
  self->inputBytes = Ring2_String_getBytes(inputString);

  self->offsets.begin = offsetBegin;
  self->offsets.end = offsetEnd;
  self->offsets.current = offsetCurrent;
}

void
Mkx_SymbolScanner_setInput
  (
    Mkx_SymbolScanner* self,
    Ring2_String* inputString,
    Ring2_String* inputPathname
  )
{
  self->inputString = inputString;
  
  self->inputPathname = inputPathname;
  self->inputLineNumber = 1;

  self->inputBytes = Ring2_String_getBytes(inputString);

  self->offsets.begin = 0;
  self->offsets.end = Ring2_String_getNumberOfBytes(inputString);
  self->offsets.current = self->offsets.begin;
}

/// @brief Increment the current position.
/// @error The current position is the end position.
void
Mkx_SymbolScanner_increment
  (
    Mkx_SymbolScanner* self
  )
{
  if (self->offsets.current == self->offsets.end)
  {
    Ring2_emitf(Ring2_Context_get(),
                Ring2_String_fromC(false, "%s:%i: attempt to increment iterator past the end"),
                Ring2_String_fromC(false, __FILE__),
                __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  self->offsets.current++;
}

void
Mkx_SymbolScanner_increment_n
  (
    Mkx_SymbolScanner* self,
    int64_t n
  )
{
  if (n < 0)
  {
    Ring2_emitf(Ring2_Context_get(),
                Ring2_String_fromC(false, "%s:%i: increment must be non-negative"),
                Ring2_String_fromC(false, __FILE__),
                __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  while (n > 0)
  {
    Mkx_SymbolScanner_increment(self);
    n--;
  }
}

Ring2_String*
Mkx_SymbolScanner_getInputPathname
  (
    Mkx_SymbolScanner* self
  )
{ return self->inputPathname; }

int64_t
Mkx_SymbolScanner_getInputLineNumber
  (
    Mkx_SymbolScanner* self
  )
{ return self->inputLineNumber; }

void
Mkx_SymbolScanner_incrementInputLineNumber
  (
    Mkx_SymbolScanner* self
  )
{ self->inputLineNumber++; }

bool
Mkx_SymbolScanner_is
  (
    Mkx_SymbolScanner* self,
    int c
  )
{ return c == Mkx_SymbolScanner_current(self); }

bool
Mkx_SymbolScanner_isAnyOf
  (
    Mkx_SymbolScanner* self,
    size_t numberOfElements,
    const int* elements
  )
{
  bool is = false;
  for (size_t i = 0, n = numberOfElements; i < n; ++i)
  {
    if (elements[i] == Mkx_SymbolScanner_current(self))
    {
      return true;
    }
  }
  return false;
}

bool
Mkx_SymbolScanner_isInRange
  (
    Mkx_SymbolScanner* self,
    int x,
    int y
  )
{
  if (x > y)
  {
    Ring2_emitf(Ring2_Context_get(),
                Ring2_String_fromC(false, "%s:%i: first symbol must be smaller than or equal to last symbol"),
                Ring2_String_fromC(false, __FILE__),
                __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  int c = Mkx_SymbolScanner_current(self);
  return x <= c && c <= y;
}
