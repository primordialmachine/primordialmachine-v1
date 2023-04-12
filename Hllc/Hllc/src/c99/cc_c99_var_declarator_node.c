#include "c99/cc_c99_var_declarator_node.h"

#include "spectre/cc_c99_node.h"
#include "spectre/c99/type_node.h"

static void cc_c99_var_declarator_node_visit(cc_c99_var_declarator_node* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->type);
}

static void write_var_declarator(cc_c99_var_declarator_node* self, cc_emit* emit)
{
  emit->indent += 1;
  cc_emit_write_indent(emit, emit->indent);
  size_t count = 0;
  cc_c99_node* base = self->type;
  if (base->kind == CC_C99_NODE_KIND_POINTER_TYPE_DECLARATOR)
  {
    base = cc_c99_pointer_type_declarator_get_base((cc_c99_pointer_type_declarator_node*)base, &count);
  }
  if (base->kind == CC_C99_NODE_KIND_NAMED_TYPE_DECLARATOR)
  {
    cc_c99_named_type_declarator_node* named_type = (cc_c99_named_type_declarator_node*)base;
    cc_emit_write_f(emit, "%s", named_type->name->p);
    for (size_t i = 0, n = count; i < n; ++i)
    {
      cc_emit_write_f(emit, "*");
    }
    cc_emit_write_f(emit, " ");
    cc_emit_write_f(emit, "%s", self->name->p);
  }
  else if (base->kind == CC_C99_NODE_KIND_FUNCTION_TYPE_DECLARATOR)
  {
    cc_c99_function_declarator_node* function_declarator_node = (cc_c99_function_declarator_node*)((cc_c99_function_type_declarator_node *)base)->declarator;
    cc_emit_write_node(emit, function_declarator_node->result_type);
    cc_emit_write_f(emit, " ");
    cc_emit_write_f(emit, "(");
    for (size_t i = 0, n = count; i < n; ++i)
    {
      cc_emit_write_f(emit, "*");
    }
    cc_emit_write_f(emit, "%s", self->name->p);
    cc_emit_write_f(emit, ")");
    cc_emit_write_f(emit, "\n");
    emit->indent += 1;
    cc_emit_write_node(emit, (cc_c99_node*)function_declarator_node->params);
    emit->indent -= 1;
  }
  cc_emit_write_f(emit, ";\n");
  emit->indent -= 1;
}

CC_DEFINE_CLASS(cc_c99_var_declarator_node, cc_c99_node, &cc_c99_var_declarator_node_visit, NULL, NULL, NULL)

cc_c99_var_declarator_node* cc_c99_node_create_var_declarator(cc_cstring* name, bool is_static, cc_c99_node* type)
{
  cc_c99_var_declarator_node* self = (cc_c99_var_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_var_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_VAR_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_var_declarator;
  self->name = name;
  self->type = type;
  self->is_static = is_static;
  return self;
}
