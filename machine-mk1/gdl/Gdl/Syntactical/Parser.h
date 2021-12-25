/// @file Gdl/Syntactical/Parser.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED)
#define MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED

#include "Gdl/Context.h"
#include "Gdl/Lexical/Scanner.h"
#include "Gdl/Syntactical/Node.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Parser)

struct Machine_Gdl_Parser_Class {
  Machine_Object_Class parent;
};

struct Machine_Gdl_Parser {
  Machine_Object __parent;
  Machine_Gdl_Scanner* scanner;
};

Machine_Gdl_Parser* Machine_Gdl_Parser_create();

/// @brief Parse the specified input.
/// @param self This parser.
/// @param inputName, inputBytes The input.
Machine_Gdl_Node* Machine_Gdl_Parser_parse(Machine_Gdl_Parser* self, Machine_String* inputName,
                                           Machine_ByteBuffer* inputBytes);

#endif // MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED
