#include "spectre/emit/class.h"


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
      else if ((child->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD)
      {
        cc_c99_node* xx = cc_emit_method(self, child);
        if (xx) cc_c99_group_node_append(group_node, xx);
      }
    }
  }

  return group_node;
}

cc_c99_struct_declarator_node *
cc_emit_make_class_type_struct
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_cstring* name, * type;
  cc_c99_node* node;

  name = cc_emit_compute_name(self, sym, false);
  cc_c99_struct_declarator_node* DECLARATOR = cc_c99_node_create_struct_declarator(name);

  cc_arraylist* BODY = cc_arraylist_create(0);
  DECLARATOR->body = BODY;

  if (sym->parent)
  {
    name = cc_cstring_create("parent");
    type = cc_emit_compute_name(self, sym->parent, false);
    node = (cc_c99_node*)cc_c99_node_create_var_declarator(name, false, (cc_c99_node*)cc_c99_node_create_named_type_declarator(type));
    cc_arraylist_append(BODY, (cc_object*)node);
  }
  else
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: internal error: class has no parent type\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }

  cc_clang_section_context old_section_context = self->section_context;
  self->section_context = CC_CLANG_SECTION_CONTEXT_OBJECT_STRUCT_DECL;
  node = (cc_c99_node*)write_members(self, sym);
  cc_arraylist_append(BODY, (cc_object*)node);
  self->section_context = old_section_context;

  return DECLARATOR;
}
