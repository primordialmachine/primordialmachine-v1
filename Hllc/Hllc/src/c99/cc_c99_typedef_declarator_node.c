#include "c99/cc_c99_typedef_declarator_node.h"

#include "c99/ast/_include.h"
#include "spectre/cc_emit-protected.h"
#include "spectre/c99/type_node.h"
#include "c99/cc_c99_struct_declarator_node.h"

static void cc_c99_typedef_decl_node_visit(cc_c99_typedef_decl_node* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->declarator);
}

static void write_typedef_decl(cc_c99_typedef_decl_node* self, cc_emit* emit)
{
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "typedef ");
  size_t count = 0;
  cc_c99_node* base = self->declarator;
  if (base->kind == CC_C99_NODE_KIND_POINTER_TYPE_DECLARATOR)
  {
    base = cc_c99_pointer_type_declarator_get_base((cc_c99_pointer_type_declarator_node*)base, &count);
  }
  if (base->kind == CC_C99_NODE_KIND_FUNCTION_TYPE_DECLARATOR)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_INTERNAL, "%s:%d: not yet implemented\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
  else if (base->kind == CC_C99_NODE_KIND_NAMED_TYPE_DECLARATOR)
  {
    for (size_t i = 0, n = count; i < n; ++i)
    {
      cc_emit_write_f(emit, "*");
    }
    cc_emit_write_f(emit, " ");
  }
  else if (base->kind == CC_C99_NODE_KIND_STRUCT_DECLARATOR)
  {
    cc_emit_write_f(emit, "struct");
    cc_c99_struct_declarator_node* struct_base = (cc_c99_struct_declarator_node*)base;
    cc_emit_write_f(emit, " ");
    cc_emit_write_f(emit, "%s", struct_base->name->p);
    if (struct_base->body)
    {
      cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: not yet implemented\n", __FILE__, __LINE__);
      cc_error(CC_EINVAL);
    }
    else
    {
      cc_emit_write_f(emit, " ");
    }
    for (size_t i = 0, n = count; i < n; ++i)
    {
      cc_emit_write_f(emit, "*");
    }
  }
  cc_emit_write_f(emit, "%s;\n", self->name->p);
}

CC_DEFINE_CLASS(cc_c99_typedef_decl_node, cc_c99_node, &cc_c99_typedef_decl_node_visit, NULL, NULL, NULL)

cc_c99_typedef_decl_node* cc_c99_node_create_typedef_decl(cc_cstring* name, cc_c99_node* declarator)
{
  cc_c99_typedef_decl_node* self = (cc_c99_typedef_decl_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_typedef_decl_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_TYPEDEF_DECL;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_typedef_decl;
  self->name = name;
  self->declarator = declarator;
  return self;
}
