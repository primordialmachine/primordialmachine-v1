#if !defined(RING3_TEXT_LAYOUTLINE_H_INCLUDED)
#define RING3_TEXT_LAYOUTLINE_H_INCLUDED

#if !defined(RING3_TEXT_PRIVATE)
#error("Do not include `Ring3/Text/LayoutLine.h` directly. Include `Ring3/Text/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

/// @brief A text layout line.
MACHINE_DECLARE_CLASSTYPE(Machine_Text_LayoutLine)

struct Machine_Text_LayoutLine_Class {
  Machine_Object_Class parent;
};

struct Machine_Text_LayoutLine {
  Machine_Object parent;

  /** @brief Index into Machine_Text_Layout::text. */
  Ring2_Integer start;

  /** @brief The length of the line. */
  Ring2_Integer length;

  /** @brief The position, in points, of this line. */
  float left;

  /** @brief The position, in points, of this line. */
  float top;

  /** @brief The width, in points, of this line. */
  float width;

  /** @brief The height, in points, of this line. */
  float height;

};

Machine_Text_LayoutLine* Machine_Text_LayoutLine_create(Ring2_Integer start, Ring2_Integer length);


#endif // RING3_TEXT_LAYOUTLINE_H_INCLUDED
