#include "spectre/c99/type_node.h"

#include "spectre/cc_c99_node.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_c99_named_type_declarator_node_visit(cc_c99_named_type_declarator_node* self)
{
  CC_VISIT(self->name);
}

static void write_named_type_declarator(cc_c99_named_type_declarator_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "%s", self->name->p);
}

CC_DEFINE_CLASS(cc_c99_named_type_declarator_node, cc_object, &cc_c99_named_type_declarator_node_visit, NULL, NULL, NULL)

cc_c99_named_type_declarator_node* cc_c99_node_create_named_type_declarator(cc_cstring* name)
{
  cc_c99_named_type_declarator_node* self = (cc_c99_named_type_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_named_type_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_NAMED_TYPE_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_named_type_declarator;
  self->name = name;
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_c99_pointer_type_declarator_node_visit(cc_c99_pointer_type_declarator_node *self)
{
  CC_VISIT(self->inner);
}

static void write_pointer_type_declarator(cc_c99_pointer_type_declarator_node* self, cc_emit* emit)
{
  size_t count;
  cc_c99_node* base = cc_c99_pointer_type_declarator_get_base(self, &count);
  if (base->kind == CC_C99_NODE_KIND_NAMED_TYPE_DECLARATOR)
  {
    cc_c99_named_type_declarator_node* named_type = (cc_c99_named_type_declarator_node*)base;
    cc_emit_write_f(emit, "%s", named_type->name->p);
    for (size_t i = 0, n = count; i < n; ++i)
    {
      cc_emit_write_f(emit, "*");
    }
  }
  else if (base->kind == CC_C99_NODE_KIND_FUNCTION_TYPE_DECLARATOR)
  {
    cc_c99_function_declarator_node* function_declarator_node = ((cc_c99_function_type_declarator_node*)base)->declarator;
    cc_emit_write_node(emit, function_declarator_node->result_type);
    cc_emit_write_f(emit, "(");
    for (size_t i = 0, n = count; i < n; ++i)
    {
      cc_emit_write_f(emit, "*");
    }
    cc_emit_write_f(emit, ")");
    cc_c99_types_list_node* type_list_node = cc_c99_params_list_to_params_type_list(function_declarator_node->params, false);
    cc_emit_write_node(emit, (cc_c99_node *)type_list_node);
  }
  else
  {
    CC_UNREACHABLE_ERROR();
  }
}

CC_DEFINE_CLASS(cc_c99_pointer_type_declarator_node, cc_object, &cc_c99_pointer_type_declarator_node_visit, NULL, NULL, NULL)

cc_c99_pointer_type_declarator_node* cc_c99_node_create_pointer_type_declarator(cc_c99_node* inner)
{
  CC_ASSERT_NOT_NULL(inner);
  if (inner->kind != CC_C99_NODE_KIND_POINTER_TYPE_DECLARATOR &&
      inner->kind != CC_C99_NODE_KIND_NAMED_TYPE_DECLARATOR &&
      inner->kind != CC_C99_NODE_KIND_FUNCTION_TYPE_DECLARATOR)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: inner must be either a pointer type declarator, named type declarator, or function type declarator\n");
    cc_error(CC_EINVAL);
  }
  cc_c99_pointer_type_declarator_node* self = (cc_c99_pointer_type_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_pointer_type_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_POINTER_TYPE_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_pointer_type_declarator;
  self->inner = inner;
  return self;
}

cc_c99_node* cc_c99_pointer_type_declarator_get_base(cc_c99_pointer_type_declarator_node* self, size_t *count)
{
  cc_c99_node* base = self->inner;
  (*count) = 1;
  while (base->kind == CC_C99_NODE_KIND_POINTER_TYPE_DECLARATOR)
  {
    base = ((cc_c99_pointer_type_declarator_node*)base)->inner;
    (*count)++;
  }
  return base;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_c99_function_type_declarator_node_visit(cc_c99_function_type_declarator_node* self)
{
  CC_VISIT(self->declarator);
}

static void write_function_type_declarator(cc_c99_function_type_declarator_node* self, cc_emit* emit)
{
  cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: can not directly emit a function type declarator\n", __FILE__, __LINE__);
}

CC_DEFINE_CLASS(cc_c99_function_type_declarator_node, cc_object, &cc_c99_function_type_declarator_node_visit, NULL, NULL, NULL)

cc_c99_function_type_declarator_node* cc_c99_node_create_function_type_declarator(cc_c99_function_declarator_node* declarator)
{
  cc_c99_function_type_declarator_node* self = (cc_c99_function_type_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_function_type_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_FUNCTION_TYPE_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_function_type_declarator;
  self->declarator = declarator;
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
