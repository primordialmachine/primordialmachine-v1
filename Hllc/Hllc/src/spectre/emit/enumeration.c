#include "spectre/emit/enumeration.h"


#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"

#include "spectre/cc_emit_method.h"
#include "spectre/cc_emit_member_variable.h"


static cc_c99_group_node* write_members(cc_emit* self, cc_symbol* sym)
{
  cc_c99_group_node* group_node = cc_c99_node_create_group_node();
  if (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC)
  {
    for (size_t i = 0, n = cc_arraylist_get_size(sym->enclosed); i < n; ++i)
    {
      cc_symbol* child = (cc_symbol*)cc_arraylist_get_at(sym->enclosed, i);
      if ((child->flags & CC_SYMBOL_FLAGS_MEMBER_VARIABLE) == CC_SYMBOL_FLAGS_MEMBER_VARIABLE)
      {
        cc_c99_node* xx = cc_emit_member_variable(self, child);
        if (xx) cc_c99_group_node_append(group_node, xx);
      }
    }
  }
  return group_node;
}

cc_c99_enum_declarator_node *cc_emit_make_enumeration_type_enum(cc_emit* self, cc_symbol* sym)
{
  cc_cstring* name;
  cc_c99_node* node;

  name = cc_emit_compute_name(self, sym, false);
  cc_c99_enum_declarator_node* DECLARATOR = cc_c99_node_create_enum_declarator(name);

  cc_arraylist* BODY = cc_arraylist_create(0);
  DECLARATOR->body = BODY;

  cc_clang_section_context old_section_context = self->section_context;
  self->section_context = CC_CLANG_SECTION_CONTEXT_OBJECT_STRUCT_DECL;
  node = (cc_c99_node*)write_members(self, sym);
  cc_arraylist_append(BODY, (cc_object*)node);
  self->section_context = old_section_context;

  return DECLARATOR;
}
