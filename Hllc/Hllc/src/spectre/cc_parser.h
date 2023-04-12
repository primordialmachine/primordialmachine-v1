/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// Parser.

#if !defined(CC_PARSER_H_INCLUDED)
#define CC_PARSER_H_INCLUDED


#include "cc_tree.h"
#include "cc_context.h"
typedef struct cc_scanner cc_scanner;


BEGIN_DECLARE_COMPONENT(cc_parser)

  /// @brief The names.
  cc_spectre_names* names;

  /// @brief Scanner used for lexical analysis.
  cc_scanner* scanner;

  /// @brief Tree factory for creating trees.
  cc_tree_factory* tree_factory;

  /// @brief A scratch buffer.
  cc_bytebuffer* scratch_buffer;

END_DECLARE_COMPONENT(cc_parser)

void cc_parser_set_input(cc_parser* self, cc_cstring* file_path);

bool cc_parser_run(cc_parser* parser, cc_program_tree *progam);


#endif // CC_PARSER_H_INCLUDEd
