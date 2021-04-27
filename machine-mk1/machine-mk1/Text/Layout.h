#if !defined(MACHINE_TEXT_LAYOUT_H_INCLUDED)
#define MACHINE_TEXT_LAYOUT_H_INCLUDED

#include "./../Machine.h"

typedef struct Machine_Text_Layout Machine_Text_Layout;

struct Machine_Text_Layout {
  Machine_String* text;
  Machine_PointerArray* lines;
};

/**
 * @brief Create a layout with the specified text.
 * @param text The text.
 */
Machine_Text_Layout* Machine_Text_Layout_create(Machine_String* text);

#endif // MACHINE_TEXT_LAYOUT_H_INCLUDED
