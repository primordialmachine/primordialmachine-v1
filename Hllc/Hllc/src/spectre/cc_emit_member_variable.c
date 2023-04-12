#include "cc_emit_member_variable.h"

#include "cc_emit_expression.h"
#include "cc_c99_node.h"
#include "spectre/emit/configuration.h"

static bool condition(cc_emit* self, cc_symbol* sym)
{
  bool condition = true;

  // File context must be "public file" and section context must be "struct decl".
  // Symbol must be a member variable symbol.
  condition = condition && self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC;
  condition = condition && self->section_context == CC_CLANG_SECTION_CONTEXT_OBJECT_STRUCT_DECL;
  condition = condition && (sym->flags & CC_SYMBOL_FLAGS_MEMBER_VARIABLE) == CC_SYMBOL_FLAGS_MEMBER_VARIABLE;

  return condition;
}

cc_c99_node *cc_emit_member_variable(cc_emit* self, cc_symbol* sym)
{
  if (!condition(self, sym))
  { return NULL; }

  if (sym->enclosing == NULL)
  { cc_error(CC_EINVAL); }

  if ((sym->enclosing->flags & CC_SYMBOL_FLAGS_ENUMERATION) == CC_SYMBOL_FLAGS_ENUMERATION)
  {
#if C99_ENUM_VARIABLES_CASING == C99_CASING_RETAIN
    cc_cstring* c99_name = cc_emit_compute_name(self, sym, false);
#elif C99_ENUM_VARIABLES_CASING == C99_CASING_UPPER
    cc_cstring* c99_name = cc_emit_compute_name(self, sym, true);
#else
    #error("invalid configuration")
#endif
    cc_c99_node* c99_initializer = NULL;
    if (((cc_syms_member_variable*)sym)->initializer)
    {
      c99_initializer = cc_c99_create_expression(((cc_syms_member_variable*)sym)->initializer);
    }
    cc_c99_enum_element_declarator_node *c99_enum_element_decl = cc_c99_node_create_enum_element_declarator(c99_name, c99_initializer);
    return (cc_c99_node*)c99_enum_element_decl;
  }
  else if ((sym->enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
  {
    cc_cstring* c99_name = sym->name;
    cc_c99_node* c99_type = to_c99_type(self, sym->type);
    cc_c99_var_declarator_node* c99_var_decl = cc_c99_node_create_var_declarator(c99_name, false, c99_type);
    return (cc_c99_node*)c99_var_decl;
  }
  else
  { cc_error(CC_EINVAL); }
}
