#if !defined(MACHINE_TEXT_LAYOUTLINE_H_INCLUDED)
#define MACHINE_TEXT_LAYOUTLINE_H_INCLUDED


#include "./../Machine.h"


/**
 * @brief A text layout line.
 */
typedef struct Machine_Text_LayoutLine Machine_Text_LayoutLine;

struct Machine_Text_LayoutLine {
  
  /**
   * @brief Index into Machine_Text_Layout::text.
   */
  int start;

  /**
   * @brief The length of the line.
   */
  int length;

};

Machine_Text_LayoutLine* Machine_Text_LayoutLine_create(int start, int length);


#endif // MACHINE_TEXT_LAYOUTLINE_H_INCLUDED
