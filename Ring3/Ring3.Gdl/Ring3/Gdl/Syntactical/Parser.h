/// @file Ring3/Gdl/Syntactical/Parser.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_SYNTACTICAL_PARSER_H_INCLUDED)
#define RING3_GDL_SYNTACTICAL_PARSER_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Syntactical/Parser.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Parser)

struct Machine_Gdl_Parser_Class {
  Machine_Object_Class parent;
};

struct Machine_Gdl_Parser {
  Machine_Object __parent;
  Machine_Gdl_Scanner* scanner;
};

/// @brief Create a GDL parser.
/// @return A pointer to the GDL parser.
Machine_Gdl_Parser*
Machine_Gdl_Parser_create
  (
  );

/// @brief Parse the specified input.
/// @param self This parser.
/// @param inputName, inputBytes The input.
Machine_Gdl_Node*
Machine_Gdl_Parser_parse
  (
    Machine_Gdl_Parser* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  );

#endif // MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED
