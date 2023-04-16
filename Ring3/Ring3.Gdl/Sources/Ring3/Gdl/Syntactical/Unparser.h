/// @file Ring3/Gdl/Syntactical/Unparser.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_SYNTACTICAL_UNPARSER_H_INCLUDED)
#define RING3_GDL_SYNTACTICAL_UNPARSER_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Syntactical/Unparser.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Unparser)

struct Machine_Gdl_Unparser_Class {
  Machine_Object_Class parent;
};

struct Machine_Gdl_Unparser {
  Machine_Object __parent;
  Ring2_String* colon;
  Ring2_String* leftCurlyBracket;
  Ring2_String* leftSquareBracket;
  Ring2_String* newLine;
  Ring2_String* rightCurlyBracket;
  Ring2_String* rightSquareBracket;
  Ring2_String* space;
  Ring2_String* comma;
  /// @brief The current level of indention.
  /// Least level is 0. 
  Ring2_Integer indent;
};

/// @brief Create a GDL unparser.
/// @return A pointer to the GDL unparser.
Ring1_NoDiscardReturn() Machine_Gdl_Unparser*
Machine_Gdl_Unparser_create
  (
  );

/// @brief Unparse the specified node.
/// @param self This unparser.
/// @param outputName The name of the output.
/// @param outputStringBuffer The String buffer to append the output string to.
void
Machine_Gdl_Unparser_unparse
  (
    Machine_Gdl_Unparser* self,
    Machine_Gdl_Node *node,
    Ring2_String* outputName,
    Ring2_StringBuffer* outputStringBuffer
  );

#endif // MACHINE_GDL_SYNTACTICAL_UNPARSER_H_INCLUDED
