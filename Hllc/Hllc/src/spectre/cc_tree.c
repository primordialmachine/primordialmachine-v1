/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_tree.h"

#include "cc_os_lib.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_tree_visit(cc_tree* self)
{ }

CC_DEFINE_CLASS(cc_tree, cc_object, &cc_tree_visit, NULL, NULL, NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint32_t cc_t_get_kind(cc_tree* t)
{
  return t->flags;
}

cc_cstring* cc_t_get_name(cc_tree* t)
{
  uint32_t kind = cc_t_get_kind(t);
  switch (kind)
  {
  case CC_TT_CLASS:
  case CC_TT_ENUMERATION:
    return cc_tree_to_defn(t)->name;
  case CC_TT_MODULE:
    return cc_tree_to_module(t)->name;
  case CC_TT_NAMESPACE:
    return cc_tree_to_namespace(t)->name;
  case CC_TT_CONSTRUCTOR:
  case CC_TT_DESTRUCTOR:
  case CC_TT_METHOD:
    return cc_tree_to_proc(t)->name;
  case CC_TT_MEMBER_VARIABLE:
  case CC_TT_PARAMETER_VARIABLE:
    return cc_tree_to_var(t)->name;
  default:
    cc_error(CC_EINVAL);
  };
}

#if 0
cc_cstring* cc_t_get_type(cc_tree* t)
{
  uint32_t kind = cc_t_get_kind(t);
  switch (kind)
  {
  case CC_TT_MEMBER_VARIABLE:
  case CC_TT_PARAMETER_VARIABLE:
    return cc_tree_to_var(t)->type;
  default:
    cc_error(CC_EINVAL);
};
}
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_proc_tree_visit(cc_proc_tree* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->type);
  CC_VISIT(self->parameters);
  CC_VISIT(self->keyword_position);
  CC_VISIT(self->suffix);
  CC_VISIT(self->suffix_position);
  CC_VISIT(self->modifiers);
}

CC_DEFINE_CLASS(cc_proc_tree, cc_tree, &cc_proc_tree_visit, NULL, NULL, NULL)

cc_proc_tree* cc_tree_factory_create_constructor(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* suffix, cc_position* suffix_position, cc_arraylist *parameters)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(keyword_position);
  /*CC_ASSERT_NOT_NULL(suffix);*/ // Can be null.
  /*CC_ASSERT_NOT_NULL(suffix_position);*/ // Can be null.
  CC_ASSERT_NOT_NULL(parameters);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_proc_tree_get_type)();
  cc_proc_tree* tree = (cc_proc_tree *)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_CONSTRUCTOR;
  tree->keyword_position = keyword_position;
  tree->suffix = suffix;
  tree->suffix_position = suffix_position;
  tree->parameters = parameters;
  
  return tree;
}

cc_proc_tree* cc_tree_factory_create_destructor(cc_tree_factory* self, cc_position* keyword_position, cc_arraylist* parameters)
{
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_proc_tree_get_type)();
  cc_proc_tree* tree = (cc_proc_tree *)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_DESTRUCTOR;
  tree->keyword_position = keyword_position;
  tree->parameters = parameters;
  
  return tree;
}

cc_proc_tree* cc_tree_factory_create_method(cc_tree_factory* self, cc_position* position, cc_cstring* name, cc_tree* type, cc_arraylist* parameters)
{
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_proc_tree_get_type)();
  cc_proc_tree* tree = (cc_proc_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_METHOD;
  tree->parameters = parameters;
  tree->name = name;
  tree->type = type;

  return tree;
}

cc_tree* cc_proc_tree_get_result_type(cc_proc_tree* self)
{
  CC_ASSERT_NOT_NULL(self);
  
  if (!cc_tree_is_method_kind((cc_tree *)self))
  { cc_error(CC_EINVAL); }
  
  return self->type;
}

cc_arraylist* cc_proc_tree_get_parameters(cc_proc_tree* self)
{
  CC_ASSERT_NOT_NULL(self);
  return self->parameters;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_var_tree_visit(cc_var_tree* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->type);
  CC_VISIT(self->initializer);
  CC_VISIT(self->modifiers);
}

CC_DEFINE_CLASS(cc_var_tree, cc_tree, &cc_var_tree_visit, NULL, NULL, NULL)

cc_var_tree* cc_tree_factory_create_member_variable(cc_tree_factory* self, cc_cstring* name, cc_tree* type)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(type);
  if ((type->flags & (CC_TT_DIRECT_TYPE_REFERENCE | CC_TT_ARRAY_TYPE_REFERENCE)) == 0)
  {
    cc_error(CC_EINVAL);
  }
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_var_tree_get_type)();
  cc_var_tree* tree = (cc_var_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree *)tree)->flags = CC_TT_MEMBER_VARIABLE;
  tree->name = name;
  tree->type = type;

  return tree;
}

cc_var_tree* cc_tree_factory_create_parameter_variable(cc_tree_factory* self, cc_cstring* name, cc_position* name_position, cc_tree* type)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(name_position);
  CC_ASSERT_NOT_NULL(type);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_var_tree_get_type)();
  cc_var_tree* tree = (cc_var_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_PARAMETER_VARIABLE;
  tree->name = name;
  tree->type = type;

  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_program_tree_visit(cc_program_tree* self)
{
  CC_VISIT(self->compilation_units);
}

CC_DEFINE_CLASS(cc_program_tree, cc_tree, &cc_program_tree_visit, NULL, NULL, NULL)

cc_program_tree* cc_tree_factory_create_program(cc_tree_factory* self)
{
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_program_tree_get_type)();
  cc_program_tree* tree = (cc_program_tree *)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_PROGRAM;
  tree->compilation_units = cc_arraylist_create(0);
  
  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_compilation_unit_tree_visit(cc_compilation_unit_tree* self)
{
  CC_VISIT(self->modules);
  CC_VISIT(self->position);
}

CC_DEFINE_CLASS(cc_compilation_unit_tree, cc_tree, &cc_compilation_unit_tree_visit, NULL, NULL, NULL)

cc_compilation_unit_tree* cc_tree_factory_create_compilation_unit(cc_tree_factory* self, cc_position *position)
{
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_compilation_unit_tree_get_type)();
  cc_compilation_unit_tree* tree = (cc_compilation_unit_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree *)tree)->flags = CC_TT_COMPILATION_UNIT;
  tree->position = position;
  tree->modules = cc_arraylist_create(0);

  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_module_tree_visit(cc_module_tree* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->definitions);
}

CC_DEFINE_CLASS(cc_module_tree, cc_tree, &cc_module_tree_visit, NULL, NULL, NULL)

cc_module_tree* cc_tree_factory_create_module(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(keyword_position);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(name_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_module_tree_get_type)();
  cc_module_tree* tree = (cc_module_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree *)tree)->flags = CC_TT_MODULE;
  tree->name = name;
  tree->definitions = cc_arraylist_create(0);
  
  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_namespace_tree_visit(cc_namespace_tree* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->definitions);
}

CC_DEFINE_CLASS(cc_namespace_tree, cc_tree, &cc_namespace_tree_visit, NULL, NULL, NULL)

cc_namespace_tree* cc_tree_factory_create_namespace(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(keyword_position);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(name_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_namespace_tree_get_type)();
  cc_namespace_tree* tree = (cc_namespace_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree *)tree)->flags = CC_TT_NAMESPACE;
  tree->definitions = cc_arraylist_create(0);
  tree->name = name;
  
  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_defn_tree_visit(cc_defn_tree* self)
{
  CC_VISIT(self->keyword_position);
  CC_VISIT(self->name);
  CC_VISIT(self->members);
  CC_VISIT(self->extends);
  CC_VISIT(self->implements);
  CC_VISIT(self->modifiers);
}

CC_DEFINE_CLASS(cc_defn_tree, cc_tree, &cc_defn_tree_visit, NULL, NULL, NULL)

cc_defn_tree* cc_tree_factory_create_class(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(keyword_position);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(name_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_defn_tree_get_type)();
  cc_defn_tree* tree = (cc_defn_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_CLASS;
  tree->keyword_position = keyword_position;
  tree->members = cc_arraylist_create(0);
  tree->name = name;
  tree->extends = cc_arraylist_create(0);
  tree->implements = cc_arraylist_create(0);

  return tree;
}

cc_defn_tree* cc_tree_factory_create_enumeration(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(keyword_position);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(name_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_defn_tree_get_type)();
  cc_defn_tree* tree = (cc_defn_tree *)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree *)tree)->flags = CC_TT_ENUMERATION;
  tree->members = cc_arraylist_create(0);
  tree->name = name;
  
  return tree;
}

cc_defn_tree* cc_tree_factory_create_interface(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(keyword_position);
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(name_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_defn_tree_get_type)();
  cc_defn_tree* tree = (cc_defn_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_INTERFACE;
  tree->members = cc_arraylist_create(0);
  tree->name = name;

  return tree;
}

void cc_defn_tree_add_extends(cc_defn_tree* self, cc_tree* type)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(type);

  if (!cc_tree_is_direct_type_reference_kind(type))
  { cc_error(CC_EINVAL); }

  cc_arraylist_append(self->extends, (cc_object*)type);
}

void cc_defn_tree_add_implements(cc_defn_tree* self, cc_tree* type)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(type);

  if (!cc_tree_is_direct_type_reference_kind(type))
  { cc_error(CC_EINVAL); }

  cc_arraylist_append(self->implements, (cc_object*)type);
}

cc_arraylist* cc_defn_tree_get_members(cc_defn_tree* self)
{
  CC_ASSERT_NOT_NULL(self);
  return self->members;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_modifier_tree_visit(cc_modifier_tree* self)
{
  CC_VISIT(self->modifier);
  CC_VISIT(self->position);
}

CC_DEFINE_CLASS(cc_modifier_tree, cc_tree, &cc_modifier_tree_visit, NULL, NULL, NULL)

cc_modifier_tree* cc_tree_factory_create_abstract_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->ABSTRACT->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_sealed_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->SEALED->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_static_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->STATIC->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_out_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree *)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->OUT->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_public_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->PUBLIC->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_protected_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->PROTECTED->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_private_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->PRIVATE->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_override_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);
  
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->OVERRIDE->string;
  tree->position = position;
  
  return tree;
}

cc_modifier_tree* cc_tree_factory_create_foreign_modifier(cc_tree_factory* self, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_modifier_tree_get_type)();
  cc_modifier_tree* tree = (cc_modifier_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_MODIFIER;
  tree->modifier = self->names->FOREIGN->string;
  tree->position = position;

  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_direct_type_reference_tree_visit(cc_direct_type_reference_tree* self)
{
  CC_VISIT(self->position);
  CC_VISIT(self->name);
}

CC_DEFINE_CLASS(cc_direct_type_reference_tree, cc_tree, &cc_direct_type_reference_tree_visit, NULL, NULL, NULL)

cc_direct_type_reference_tree* cc_tree_factory_create_direct_type_reference(cc_tree_factory* self, cc_position* position, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(position);
  CC_ASSERT_NOT_NULL(name);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_direct_type_reference_tree_get_type)();
  cc_direct_type_reference_tree* tree = (cc_direct_type_reference_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_DIRECT_TYPE_REFERENCE;
  tree->position = position;
  tree->name = name;
  
  return tree;
}

static void cc_array_type_reference_tree_visit(cc_array_type_reference_tree* self)
{
  CC_VISIT(self->inner_type);
}

CC_DEFINE_CLASS(cc_array_type_reference_tree, cc_tree, &cc_array_type_reference_tree_visit, NULL, NULL, NULL)

cc_array_type_reference_tree* cc_tree_factory_create_array_type_reference(cc_tree_factory* self, cc_tree *inner_type)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(inner_type);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_array_type_reference_tree_get_type)();
  cc_array_type_reference_tree* tree = (cc_array_type_reference_tree *)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_ARRAY_TYPE_REFERENCE;
  tree->inner_type = inner_type;
  
  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_literal_expression_tree_visit(cc_literal_expression_tree* self)
{
  CC_VISIT(self->literal);
}

CC_DEFINE_CLASS(cc_literal_expression_tree, cc_tree, &cc_literal_expression_tree_visit, NULL, NULL, NULL)

cc_literal_expression_tree* cc_tree_create_integer_literal_expression(cc_tree_factory* self, cc_cstring* literal, cc_position* literal_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(literal);
  CC_ASSERT_NOT_NULL(literal_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_literal_expression_tree_get_type)();
  cc_literal_expression_tree* tree = (cc_literal_expression_tree *)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_INTEGER_EXPRESSION;
  tree->literal = literal;
  
  return tree;
}

cc_literal_expression_tree* cc_tree_create_string_literal_expression(cc_tree_factory* self, cc_cstring* literal, cc_position* literal_position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(literal);
  CC_ASSERT_NOT_NULL(literal_position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_literal_expression_tree_get_type)();
  cc_literal_expression_tree* tree = (cc_literal_expression_tree *)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_STRING_EXPRESSION;
  tree->literal = literal;
  
  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_unary_expression_tree_visit(cc_unary_expression_tree* self)
{
  CC_VISIT(self->operand);
}

CC_DEFINE_CLASS(cc_unary_expression_tree, cc_tree, &cc_unary_expression_tree_visit, NULL, NULL, NULL)

cc_unary_expression_tree* cc_tree_create_unary_plus_expression(cc_tree_factory* self, cc_tree* operand, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(operand);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_unary_expression_tree_get_type)();
  cc_unary_expression_tree* tree = (cc_unary_expression_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_UNARY_PLUS_EXPRESSION;
  tree->operand = operand;

  return (cc_unary_expression_tree*)tree;
}

cc_unary_expression_tree* cc_tree_create_unary_minus_expression(cc_tree_factory* self, cc_tree* operand, cc_position* position)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(operand);
  CC_ASSERT_NOT_NULL(position);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_unary_expression_tree_get_type)();
  cc_unary_expression_tree* tree = (cc_unary_expression_tree *)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_UNARY_MINUS_EXPRESSION;
  tree->operand = operand;
  
  return (cc_unary_expression_tree*)tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_binary_expression_tree_visit(cc_binary_expression_tree* self)
{
  CC_VISIT(self->left_operand);
  CC_VISIT(self->right_operand);
}

CC_DEFINE_CLASS(cc_binary_expression_tree, cc_tree, &cc_binary_expression_tree_visit, NULL, NULL, NULL)

cc_binary_expression_tree* cc_tree_create_binary_minus_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(left_operand);
  CC_ASSERT_NOT_NULL(right_operand);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_binary_expression_tree_get_type)();
  cc_binary_expression_tree* tree = (cc_binary_expression_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_BINARY_MINUS_EXPRESSION;
  tree->left_operand = left_operand;
  tree->right_operand = right_operand;
  
  return tree;
}

cc_binary_expression_tree* cc_tree_create_binary_plus_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(left_operand);
  CC_ASSERT_NOT_NULL(right_operand);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_binary_expression_tree_get_type)();
  cc_binary_expression_tree* tree = (cc_binary_expression_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_BINARY_PLUS_EXPRESSION;
  tree->left_operand = left_operand;
  tree->right_operand = right_operand;
  
  return tree;
}

cc_binary_expression_tree* cc_tree_create_binary_slash_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(left_operand);
  CC_ASSERT_NOT_NULL(right_operand);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_binary_expression_tree_get_type)();
  cc_binary_expression_tree* tree = (cc_binary_expression_tree*)cc_object_allocate_2(CC_DECORATE(type));

  ((cc_tree*)tree)->flags = CC_TT_BINARY_SLASH_EXPRESSION;
  tree->left_operand = left_operand;
  tree->right_operand = right_operand;
  
  return tree;
}

cc_binary_expression_tree* cc_tree_create_binary_star_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(left_operand);
  CC_ASSERT_NOT_NULL(right_operand);

  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_binary_expression_tree_get_type)();
  cc_binary_expression_tree* tree = (cc_binary_expression_tree*)cc_object_allocate_2(CC_DECORATE(type));
  
  ((cc_tree*)tree)->flags = CC_TT_BINARY_STAR_EXPRESSION;
  tree->left_operand = left_operand;
  tree->right_operand = right_operand;
  
  return tree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const char KEY[] = "tree-factory";

static void cc_tree_factory_visit(cc_tree_factory* self)
{
  CC_VISIT(self->ctx);
  CC_VISIT(self->names);
}

static cc_tree_factory* factory(cc_ctx* ctx)
{
  cc_type* CC_DECORATE(type) = CC_DECORATE(cc_tree_factory_get_type)();
  cc_tree_factory* self = (cc_tree_factory *)cc_object_allocate_2(CC_DECORATE(type));

  self->names = cc_spectre_names_get_instance(ctx);
  
  return self;
}

DEFINE_COMPONENT(cc_tree_factory, &factory, &cc_tree_factory_visit, NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
