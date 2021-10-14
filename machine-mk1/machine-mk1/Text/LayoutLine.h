#if !defined(MACHINE_TEXT_LAYOUTLINE_H_INCLUDED)
#define MACHINE_TEXT_LAYOUTLINE_H_INCLUDED


#include "_Runtime.h"


/**
 * @brief A text layout line.
 */
MACHINE_DECLARE_CLASSTYPE(Machine_Text_LayoutLine)

struct Machine_Text_LayoutLine_Class {
  Machine_Object_Class parent;
};

struct Machine_Text_LayoutLine {
  Machine_Object parent;

  /** @brief Index into Machine_Text_Layout::text. */
  Machine_Integer start;

  /** @brief The length of the line. */
  Machine_Integer length;

  /** @brief The position, in points, of this line. */
  float left;

  /** @brief The position, in points, of this line. */
  float top;

  /** @brief The width, in points, of this line. */
  float width;

  /** @brief The height, in points, of this line. */
  float height;

};

Machine_Text_LayoutLine* Machine_Text_LayoutLine_create(Machine_Integer start, Machine_Integer length);


#endif // MACHINE_TEXT_LAYOUTLINE_H_INCLUDED
