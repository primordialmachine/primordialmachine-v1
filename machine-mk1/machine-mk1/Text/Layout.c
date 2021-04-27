#include "./../Text/Layout.h"

#include "./../Text/LayoutLine.h"

static void visit(Machine_Text_Layout* self) {
  Machine_visit(self->text);
  Machine_visit(self->lines);
}

static void parse(Machine_String* text, Machine_PointerArray* lines) {
  const char* start = Machine_String_getBytes(text),
            * end = Machine_String_getBytes(text) + Machine_String_getNumberOfBytes(text);

  const char* lineStart = start,
            * lineEnd = start;

  while (lineEnd != end) {
    // terminates a line
    if (*lineEnd == '\n' || *lineEnd == '\r') {
      int old = *lineEnd;
      lineEnd++;
      if (old != *lineEnd && (*lineEnd == '\n' || *lineEnd == '\r')) {
        lineEnd++;
      }
      Machine_Text_LayoutLine* line = Machine_Text_LayoutLine_create(lineStart - start, lineEnd - lineStart);
      Machine_PointerArray_append(lines, line);
      lineStart = lineEnd;
    }
    lineEnd++;
  }
  if (lineEnd != lineStart) {
    Machine_Text_LayoutLine* line = Machine_Text_LayoutLine_create(lineStart - start, lineEnd - lineStart);
    Machine_PointerArray_append(lines, line);
  }
}

Machine_Text_Layout* Machine_Text_Layout_create(Machine_String* text) {
  if (text == NULL) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Text_Layout* self = Machine_allocate(sizeof(Machine_Text_Layout), (Machine_VisitCallback *)&visit, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->text = text;
  self->lines = Machine_PointerArray_create();
  parse(self->text, self->lines);
  return self;
}
