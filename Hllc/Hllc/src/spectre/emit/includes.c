#include "spectre/emit/includes.h"

#include "c99/cc_c99_typedef_declarator_node.h"
#include "spectre/emit/referenced_symbols.h"

static cc_cstring*
get_include_file_name_for
  (
    cc_emit* self,
    cc_symbol* symbol
  )
{
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);

  cc_cstring* fully_qualified_name = cc_sym_get_fqn(symbol);
  cc_cstring_buffer_append_s(buffer, fully_qualified_name);
  cc_cstring_buffer_replace(buffer, '.', '/');
  cc_cstring_buffer_append_p(buffer, ".h");

  return cc_cstring_buffer_to_string(buffer);
}

static cc_c99_group_node*
additional_includes_for_public_header
  (
    cc_emit* self,
    cc_symbol* symbol
  )
{
  cc_c99_group_node* group = cc_c99_node_create_group_node();

  // Return null if the type is
  // a) a builtin type or
  // b) neither a class nor an enumeration type.
  if ((symbol->flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION)) == 0)
  { return NULL; }
  if ((symbol->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  { return NULL; }

  cc_c99_group_node_append(group, self->RUNTIME_INCLUDES);

  cc_arraylist* includes = cc_emit_get_referenced_symbols(self, symbol);
  for (size_t i = 0, n = cc_arraylist_get_size(includes); i < n; ++i)
  {
    cc_symbol* include = (cc_symbol*)cc_arraylist_get_at(includes, i);
    if ((include->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      if ((symbol->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS && symbol->parent == include)
      {
        cc_cstring* include_string = get_include_file_name_for(self, include);
        cc_c99_node* xx = (cc_c99_node*)cc_c99_node_create_pp_include_directive(include_string);
        cc_c99_group_node_append(group, xx);
      }
      else
      {
        cc_cstring* include_string = cc_emit_compute_name(self, include, false);
        cc_c99_node* struct_node = (cc_c99_node*)cc_c99_node_create_struct_declarator(include_string);
        cc_c99_node* xx = (cc_c99_node*)cc_c99_node_create_typedef_decl(include_string, struct_node);
        cc_c99_group_node_append(group, xx);
      }
    }
    else
    {
      cc_cstring* include_string = get_include_file_name_for(self, include);
      cc_c99_node* xx = (cc_c99_node*)cc_c99_node_create_pp_include_directive(include_string);
      cc_c99_group_node_append(group, xx);
    }
  }

  return group;
}


cc_c99_group_node*
cc_emit_get_additional_includes_for
  (
    cc_emit* self,
    cc_emit_additional_includes_strategy strategy,
    cc_symbol* symbol
  )
{
  // Return null if the type is
  // a) a builtin type or
  // b) neither a class nor an enumeration type.
  if ((symbol->flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION)) == 0)
  {
    return NULL;
  }
  if ((symbol->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  {
    return NULL;
  }


  switch (strategy)
  {
  case CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_PUBLIC_HEADER:
    return additional_includes_for_public_header(self, symbol);
  case CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_PROTECTED_HEADER:
  {
    cc_c99_group_node* group_node = cc_c99_node_create_group_node();
    cc_cstring* include_file_name = get_include_file_name_for(self, symbol);
    cc_c99_pp_include_directive_node* include_directive_node = cc_c99_node_create_pp_include_directive(include_file_name);
    cc_c99_group_node_append(group_node, (cc_c99_node *)include_directive_node);
    return group_node;
  }
  case CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_HEADER_INLAY:
  {
    cc_c99_group_node* group_node = cc_c99_node_create_group_node();
    cc_cstring* include_file_name = get_include_file_name_for(self, symbol);
    cc_c99_pp_include_directive_node *include_directive_node = cc_c99_node_create_pp_include_directive(include_file_name);
    cc_c99_group_node_append(group_node, (cc_c99_node *)include_directive_node);
    return group_node;
  }
  default:
    cc_error(CC_EINVAL);
  };
}
