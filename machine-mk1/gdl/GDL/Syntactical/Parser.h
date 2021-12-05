/// @file Gdl/Syntactical/Parser.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED)
#define MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED


#include "./../Lexical/Scanner.h"
#include "./../Syntactical/Node.h"
#include "./../../GDL/Context.h"


MACHINE_DECLARE_CLASSTYPE(Machine_GDL_Parser)

struct Machine_GDL_Parser_Class {
  Machine_Object_Class parent;
};

struct Machine_GDL_Parser {
  Machine_Object __parent;
  Machine_GDL_Scanner* scanner;
};

Machine_GDL_Parser* Machine_GDL_Parser_create();

/// @brief Parse the specified input.
/// @param self This parser.
/// @param inputName, inputBytes The input. 
Machine_GDL_Node *Machine_GDL_Parser_parse(Machine_GDL_Parser* self, Machine_String* inputName, Machine_ByteBuffer* inputBytes);


#endif // MACHINE_GDL_SYNTACTICAL_PARSER_H_INCLUDED
