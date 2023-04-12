/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/*
 * Emit phase.
 */

#if !defined(CC_EMIT_H_INCLUDED)
#define CC_EMIT_H_INCLUDED


#include "cc_options.h"
typedef struct cc_c99_names cc_c99_names;
typedef struct cc_c99_node cc_c99_node;
typedef struct cc_spectre_names cc_spectre_names;
typedef struct cc_options cc_options;

typedef enum cc_emit_state_flag
{
  CC_EMIT_STATE_FLAG_INLINE = (1 << 1),
  CC_EMIT_STATE_FLAG_BLOCK = (1 << 2),
} cc_emit_state_flag;

typedef uint32_t cc_emit_state_flags;

typedef enum cc_clang_section_context
{
  CC_CLANG_SECTION_CONTEXT_OBJECT_STRUCT_DECL,
  CC_CLANG_SECTION_CONTEXT_CLASS_STRUCT_DECL,
  CC_CLANG_SECTION_CONTEXT_FUNCTION_DECLS,
  CC_CLANG_SECTION_CONTEXT_FUNCTION_DEFNS,
} cc_clang_section_context;

typedef enum cc_clang_file_context
{
  CC_CLANG_FILE_CONTEXT_PUBLIC,
  
  CC_CLANG_FILE_CONTEXT_PROTECTED,
  
  /// The header inlay file.
  CC_CLANG_FILE_CONTEXT_HEADER_INLAY,
  
  /// The footer inlay file.
  CC_CLANG_FILE_CONTEXT_FOOTER_INLAY,

} cc_clang_file_context;

BEGIN_DECLARE_COMPONENT(cc_emit)

  cc_options* options;

  cc_spectre_names* names;

  /// The file context.
  cc_clang_file_context file_context;

  /// The section context.
  cc_clang_section_context section_context;
  
  /// @brief Output buffer.
  cc_cstring_buffer* output;
  
  /// @brief Temporary buffer.
  cc_cstring_buffer* temporary;

  /// @brief Group node containing the runtime includes.
  cc_c99_node* RUNTIME_INCLUDES;

  cc_syms* symbols;

  /// @brief The indent. Default is @a 0.
  int indent;

  /// @brief Denotes if margins are considered or not.
  /// When evaluating epresssions, the CC_EMIT_STATE_FLAG_INLINE is set.
  /// When evaluating declarations, the CC_EMIT_STATE_FLAG_BLOCK is set.
  cc_emit_state_flags state_flags;

  //cc_cstring* INTEGER8_DEFAULT_VALUE;
  //cc_cstring* INTEGER16_DEFAULT_VALUE;
  //cc_cstring* INTEGER32_DEFAULT_VALUE;
  //cc_cstring* INTEGER64_DEFAULT_VALUE;

  //cc_cstring* NATURAL8_DEFAULT_VALUE;
  //cc_cstring* NATURAL16_DEFAULT_VALUE;
  //cc_cstring* NATURAL32_DEFAULT_VALUE;
  //cc_cstring* NATURAL64_DEFAULT_VALUE;

  //cc_cstring* SIZE_DEFAULT_VALUE;

  //cc_cstring* REFERENCE_DEFAULT_VALUE;

  cc_c99_names* c99_names;

END_DECLARE_COMPONENT(cc_emit)

void cc_emit_run(cc_emit* self);


#endif // CC_EMIT_H_INCLUDED
