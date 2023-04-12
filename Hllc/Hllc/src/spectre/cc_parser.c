/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_parser.h"


#include "spectre/cc_names.h"
#include "spectre/cc_tree.h"
#include "spectre/cc_scanner.h"
#include "cc_os_lib.h"
#include <string.h>
#include <inttypes.h>


static const char KEY[] = "cc:spectre:parser";

static void cc_parser_visit(cc_parser* self)
{ 
  CC_VISIT(self->names);
  CC_VISIT(self->scanner);
  CC_VISIT(self->tree_factory);
  CC_VISIT(self->scratch_buffer);
}

static int get(cc_parser* self)
{
  return cc_scanner_get_kind(self->scanner);
}

static cc_name* get_text(cc_parser* self)
{
  return cc_scanner_get_text(self->scanner);
}

static bool is(cc_parser* parser, int tkt)
{
  return tkt == get(parser);
}

static void next(cc_parser* parser)
{
  do
  {
    cc_scanner_step(parser->scanner);
  } while (is(parser, CC_TKT_COMMENT_LINE));
}

static cc_parser* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_parser_get_type)();
  cc_parser* self = (cc_parser*)cc_object_allocate_2(type);

  self->names = cc_spectre_names_get_instance(ctx);
  self->scanner = cc_scanner_get_instance(ctx);
  self->tree_factory = cc_tree_factory_get_instance(ctx);
  self->scratch_buffer = cc_bytebuffer_create();
  
  return self;
}

DEFINE_COMPONENT(cc_parser, &factory, &cc_parser_visit, NULL)

void cc_parser_set_input(cc_parser* self, cc_cstring* file_path)
{
  cc_scanner_set_input(self->scanner, file_path);
}

static bool check_and_next(cc_parser* parser, int token_kind)
{
  if (!is(parser, token_kind))
  {
    return false;
  }
  next(parser);
  return true;
}

/// @brief Create the anchor position for the current token.
/// @param self This parser.
/// @return The anchor position for the current token.
static cc_position* make_pos(cc_parser* self)
{
  cc_line_map* line_map = cc_scanner_get_line_map(self->scanner);
  cc_file_offset offset = cc_scanner_get_start_offset(self->scanner);
  return cc_position_create(line_map, offset);
}

static void expect_and_next(cc_parser* parser, int token_kind)
{
  if (!check_and_next(parser, token_kind))
  {
    cc_cstring* file_string = cc_scanner_get_file_path(parser->scanner);
    cc_file_offset start_offset = cc_scanner_get_start_offset(parser->scanner);
    cc_line_map* line_map = cc_scanner_get_line_map(parser->scanner);
    if (start_offset > SIZE_MAX) {
      cc_error(CC_EINVAL);
    }
    uint32_t line = cc_line_map_get_line(line_map, (size_t)start_offset);
    uint32_t column = cc_line_map_get_column(line_map, (size_t)start_offset);
    cc_cstring* expected_token_kind_string = cc_token_kind_to_string(token_kind);
    cc_cstring* received_token_kind_string = cc_token_kind_to_string(get(parser));
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%"PRIu32":%"PRIu32": expected %s, received %s\n", file_string->p, line, column, expected_token_kind_string->p, received_token_kind_string->p);
    cc_error(CC_EINVAL);
  }
}

static cc_tree* parse_expression(cc_parser* parser);

static cc_tree* parse_unary_expression(cc_parser* parser);

static cc_tree* parse_literal_expression(cc_parser* parser);

static cc_tree* parse_additive_expression(cc_parser* parser);

static cc_tree* parse_multiplicative_expression(cc_parser* parser);

/// <code>
/// expression : additiveExpression
/// </code> 
static cc_tree* parse_expression(cc_parser* parser)
{
  return parse_additive_expression(parser);
}

// <code>
// literalExpression : INTEGER
//                   | STRING
// </code>
static cc_tree* parse_literal_expression(cc_parser* parser)
{
  if (is(parser, CC_TKT_INTEGER))
  {
    cc_position* position = make_pos(parser);
    cc_name* text = get_text(parser);
    cc_tree* tree = (cc_tree *)cc_tree_create_integer_literal_expression(parser->tree_factory, text->string, position);
    next(parser);
    return tree;
  }
  else if (is(parser, CC_TKT_STRING))
  {
    cc_position* position = make_pos(parser);
    cc_name* text = get_text(parser);
    cc_tree* tree = (cc_tree *)cc_tree_create_string_literal_expression(parser->tree_factory, text->string, position);
    next(parser);
    return tree;
  }
  else
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: expected %s or %s, received\n", __FILE__, __LINE__,
               cc_token_kind_to_string(CC_TKT_INTEGER)->p, cc_token_kind_to_string(CC_TKT_STRING)->p, cc_token_kind_to_string(get(parser))->p);
    cc_error(CC_EINVAL);
  }
}

/// <code>
/// unaryExpression : literalExpression
///                 | ('+'|'-') unaryExpression
///                 | '(' expression ')'
/// </code> 
static cc_tree* parse_unary_expression(cc_parser* parser)
{
  if (is(parser, CC_TKT_PLUS))
  {
    cc_position* position = make_pos(parser);
    cc_tree* operand = parse_unary_expression(parser);
    return (cc_tree*)cc_tree_create_unary_plus_expression(parser->tree_factory, operand, position);
  }
  else if (is(parser, CC_TKT_MINUS))
  {
    cc_position* position = make_pos(parser);
    cc_tree* operand = parse_unary_expression(parser);
    return (cc_tree*)cc_tree_create_unary_minus_expression(parser->tree_factory, operand, position);
  }
  else if (is(parser, CC_TKT_LEFT_PARENTHESIS))
  {
    next(parser);
    cc_tree* operand = parse_expression(parser);
    expect_and_next(parser, CC_TKT_RIGHT_PARENTHESIS);
    return operand;
  }
  else
  {
    return parse_literal_expression(parser);
  }
}

/// <code>
/// multiplicativeExpression : unaryExpression (('*'|'/') unaryExpression)*
/// </code> 
static cc_tree* parse_multiplicative_expression(cc_parser* parser)
{
  cc_tree* node = parse_unary_expression(parser);
  while (is(parser, CC_TKT_STAR) || is(parser, CC_TKT_SLASH))
  {
    cc_position * position = make_pos(parser);
    int kind = get(parser);
    cc_tree* node1 = parse_unary_expression(parser);
    switch (kind)
    {
    case CC_TKT_STAR:
      node = (cc_tree*)cc_tree_create_binary_star_expression(parser->tree_factory, position, node, node1);
      break;
    case CC_TKT_SLASH:
      node = (cc_tree*)cc_tree_create_binary_slash_expression(parser->tree_factory, position, node, node1);
      break;
    default:
      {
        CC_UNREACHABLE_ERROR();
      }
    };
  }
  return node;
}

/// <code>
/// additiveExpression : multiplicativeExpression (('+'|'-') multiplicativeExpression)*
/// </code> 
static cc_tree* parse_additive_expression(cc_parser* parser)
{
  cc_tree* node = parse_multiplicative_expression(parser);
  while (is(parser, CC_TKT_PLUS) || is(parser, CC_TKT_MINUS))
  {
    cc_position * position = make_pos(parser);
    int kind = get(parser);
    cc_tree* node1 = parse_multiplicative_expression(parser);
    switch (kind)
    {
    case CC_TKT_PLUS:
      node = (cc_tree*)cc_tree_create_binary_plus_expression(parser->tree_factory, position, node, node1);
      break;
    case CC_TKT_MINUS:
      node = (cc_tree*)cc_tree_create_binary_minus_expression(parser->tree_factory, position, node, node1);
      break;
    default:
      {
        CC_UNREACHABLE_ERROR();
      }
    };
  }
  return node;
}

/// <code>
/// name := NAME
/// </code>
cc_cstring* parse_name(cc_parser* parser)
{
  if (!is(parser, CC_TKT_NAME))
  {
    cc_error(CC_EINVAL);
  }
  cc_name* name = get_text(parser);
  next(parser);
  return name->string;
}

/// <code>
/// qualifiedName : NAME ('.' NAME)*
/// </code> 
cc_cstring *parse_qname(cc_parser* parser)
{
  // TODO: Add a scratch buffer to the parser and re-use that buffer.
  cc_bytebuffer* buffer = parser->scratch_buffer;
  cc_bytebuffer_clear(buffer);
  if (!is(parser, CC_TKT_NAME))
  {
    // @todo
    // in the case of a 'variable : ' we receive the message
    // 'expected <name>, received <error>.
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "%s:%d: expected %s, received %s\n", __FILE__, __LINE__,
               cc_token_kind_to_string(CC_TKT_NAME)->p, cc_token_kind_to_string(get(parser))->p);
    cc_error(CC_EINVAL);
  }
  cc_name* s = get_text(parser);
  cc_bytebuffer_append_bytes(buffer, s->string->p, strlen(s->string->p));
  next(parser);
  while (is(parser, CC_TKT_PERIOD))
  {
    cc_bytebuffer_append_byte(buffer, '.');
    next(parser);
    if (!is(parser, CC_TKT_NAME))
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "expected 'name'\n");
      cc_error(CC_EINVAL);
    }
    s = get_text(parser);
    cc_bytebuffer_append_bytes(buffer, s->string->p, strlen(s->string->p));
    next(parser);
  }
  cc_bytebuffer_append_byte(buffer, '\0');
  return cc_cstring_create_l(buffer->p, buffer->sz);
}

static bool is_modifier(cc_parser* parser)
{
  switch (get(parser))
  {
    // class and method modifiers
  case CC_TKT_ABSTRACT:
  case CC_TKT_SEALED:
  case CC_TKT_STATIC:
    // parameter modifiers
  case CC_TKT_OUT:
    // access modifiers
  case CC_TKT_PUBLIC:
  case CC_TKT_PROTECTED:
  case CC_TKT_PRIVATE:
    // method modifiers
  case CC_TKT_OVERRIDE:
    // destructor modifiers
  case CC_TKT_FOREIGN:
    return true;
  default:
    return false;
  };
}

static bool is_namespace_element(cc_parser* parser)
{
  return is(parser, CC_TKT_CLASS)
      || is(parser, CC_TKT_NAMESPACE)
      || is(parser, CC_TKT_ENUMERATION)
      || is_modifier(parser);
}

/// <code>
/// typeReference : qualifiedName '[' ']'
/// </code>
cc_tree* parse_type_reference(cc_parser* parser)
{
  cc_position * position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);
  cc_tree* type = (cc_tree*)cc_tree_factory_create_direct_type_reference(parser->tree_factory, position, name);
  if (is(parser, CC_TKT_LEFT_SQUARE_BRACKET))
  {
    next(parser);
    expect_and_next(parser, CC_TKT_RIGHT_SQUARE_BRACKET);
    type = (cc_tree*)cc_tree_factory_create_array_type_reference(parser->tree_factory, CC_IGNORE(position,) type);
  }
  return type;
}

/// <code>
/// modifiers : modifier*
/// </code>
void parse_modifiers(cc_parser* parser, cc_arraylist* modifiers)
{
  while (is_modifier(parser))
  {
    cc_modifier_tree* modifier = NULL;
    if (false)
    {

    }
    // destructor modifier
    // @todo should be a constructor, destructor, and method modifier
    else if (is(parser, CC_TKT_FOREIGN))
    {
      modifier = cc_tree_factory_create_foreign_modifier(parser->tree_factory, make_pos(parser));
    }
    // class and method modifiers
    else if (is(parser, CC_TKT_ABSTRACT))
    {
      modifier = cc_tree_factory_create_abstract_modifier(parser->tree_factory, make_pos(parser));
    }
    else if (is(parser, CC_TKT_SEALED))
    {
      modifier = cc_tree_factory_create_sealed_modifier(parser->tree_factory, make_pos(parser));
    }
    else if (is(parser, CC_TKT_STATIC))
    {
      modifier = cc_tree_factory_create_static_modifier(parser->tree_factory, make_pos(parser));
    }
    // parameter modifiers
    else if (is(parser, CC_TKT_OUT))
    {
      modifier = cc_tree_factory_create_out_modifier(parser->tree_factory, make_pos(parser));
    }
    // access modifiers
    else if (is(parser, CC_TKT_PUBLIC))
    {
      modifier = cc_tree_factory_create_public_modifier(parser->tree_factory, make_pos(parser));
    }
    else if (is(parser, CC_TKT_PROTECTED))
    {
      modifier = cc_tree_factory_create_protected_modifier(parser->tree_factory, make_pos(parser));
    }
    else if (is(parser, CC_TKT_PRIVATE))
    {
      modifier = cc_tree_factory_create_private_modifier(parser->tree_factory, make_pos(parser));
    }
    // method modifiers
    else if (is(parser, CC_TKT_OVERRIDE))
    {
      modifier = cc_tree_factory_create_override_modifier(parser->tree_factory, make_pos(parser));
    }
    // destructor modifiers
    else if (is(parser, CC_TKT_FOREIGN))
    {
      modifier = cc_tree_factory_create_foreign_modifier(parser->tree_factory, make_pos(parser));
    }
    else
    {
      CC_UNREACHABLE_ERROR();
    }
    next(parser);
    cc_arraylist_append(modifiers, (cc_object*)modifier);
  }
}

cc_arraylist *parse_parameter_list(cc_parser* parser)
{
  expect_and_next(parser, CC_TKT_LEFT_PARENTHESIS);
  cc_arraylist* parameter_variables = cc_arraylist_create(0);
  while (is(parser, CC_TKT_NAME))
  {
    cc_position* name_position = make_pos(parser);
    cc_cstring* name = parse_qname(parser);
    cc_arraylist* modifiers = cc_arraylist_create(0);
    parse_modifiers(parser, modifiers);
    cc_tree* type_reference = parse_type_reference(parser);
    cc_var_tree* parameter_variable = cc_tree_factory_create_parameter_variable(parser->tree_factory, name, name_position, type_reference);
    parameter_variable->modifiers = modifiers;
    cc_arraylist_append(parameter_variables, (cc_object*)parameter_variable);
    if (!check_and_next(parser, CC_TKT_COMMA))
    {
      break;
    }
  }
  expect_and_next(parser, CC_TKT_RIGHT_PARENTHESIS);
  return parameter_variables;
}

void parse_constructor(cc_parser* parser, cc_arraylist* modifiers, cc_defn_tree* parent)
{
  cc_position* keyword_position = make_pos(parser);
  expect_and_next(parser, CC_TKT_CONSTRUCTOR);
  cc_position* suffix_position = NULL;
  cc_cstring* suffix = NULL;
  if (is(parser, CC_TKT_PERIOD))
  {
    next(parser);
    suffix_position = make_pos(parser);
    suffix = parse_name(parser);
  }
  cc_arraylist* parameter_list_node = parse_parameter_list(parser);
  cc_proc_tree* constructor_node = cc_tree_factory_create_constructor(parser->tree_factory, keyword_position, suffix, suffix_position, parameter_list_node);
  constructor_node->modifiers = modifiers;
  cc_arraylist_append(parent->members, (cc_object*)constructor_node);
}

void parse_destructor(cc_parser* parser, cc_arraylist* modifiers, cc_defn_tree* parent)
{
  cc_position * keyword_position = make_pos(parser);
  expect_and_next(parser, CC_TKT_DESTRUCTOR);
  cc_arraylist* parameter_list_node = parse_parameter_list(parser);
  cc_proc_tree* destructor_node = cc_tree_factory_create_destructor(parser->tree_factory, keyword_position, parameter_list_node);
  destructor_node->modifiers = modifiers;
  cc_arraylist_append(parent->members, (cc_object*)destructor_node);
}

void parse_method_or_variable(cc_parser* parser, cc_arraylist* modifiers, cc_defn_tree* parent)
{
  cc_position * position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);
  if (is(parser, CC_TKT_LEFT_PARENTHESIS))
  {
    cc_arraylist* parameter_list = parse_parameter_list(parser);
    cc_tree* type = parse_type_reference(parser);
    cc_proc_tree* method = cc_tree_factory_create_method(parser->tree_factory, position, name, type, parameter_list);
    method->modifiers = modifiers;
    cc_arraylist_append(parent->members, (cc_object*)method);
  }
  else
  {
    cc_tree* type = parse_type_reference(parser);
    cc_var_tree* variable = cc_tree_factory_create_member_variable(parser->tree_factory, CC_IGNORE(position,) name, type);
    variable->modifiers = modifiers;
    cc_arraylist_append(parent->members, (cc_object*)variable);
  }
}

/// <code>
/// enumerationElement : name ('=' expression)
/// </code>
bool parse_enumeration_element(cc_parser* parser, cc_defn_tree* parent)
{
  cc_position* position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);

  cc_tree* type = (cc_tree*)cc_tree_factory_create_direct_type_reference(parser->tree_factory, position, parser->names->RING2_INTEGER->string);
  cc_var_tree* variable = cc_tree_factory_create_member_variable(parser->tree_factory, CC_IGNORE(position,) name, type);

  if (is(parser, CC_TKT_ASSIGN))
  {
    next(parser);
    cc_tree* initializer = parse_expression(parser);
    variable->initializer = initializer;
  }
  cc_arraylist_append(parent->members, (cc_object*)variable);
  return true;
}

bool parse_class(cc_parser* parser, cc_arraylist* modifiers, cc_namespace_tree* namespace)
{
  cc_position* keyword_position = make_pos(parser);
  if (!check_and_next(parser, CC_TKT_CLASS))
  { return false; }
  cc_position* name_position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);
  cc_defn_tree* node = cc_tree_factory_create_class(parser->tree_factory, keyword_position, name, name_position);
  node->modifiers = modifiers;
  cc_arraylist_append(namespace->definitions, (cc_object*)node);
  if (is(parser, CC_TKT_EXTENDS))
  {
    next(parser);
    cc_tree* extends_name = parse_type_reference(parser);
    if (!extends_name)
    { return false; }
    cc_defn_tree_add_extends(node, extends_name);
  }

  expect_and_next(parser, CC_TKT_LEFT_CURLY_BRACKET);

  while (is(parser, CC_TKT_CONSTRUCTOR) || is(parser, CC_TKT_DESTRUCTOR) || is(parser, CC_TKT_NAME) || is_modifier(parser))
  {
    modifiers = cc_arraylist_create(0);
    parse_modifiers(parser, modifiers);
    if (is(parser, CC_TKT_CONSTRUCTOR))
    {
      parse_constructor(parser, modifiers, node);
    }
    else if (is(parser, CC_TKT_DESTRUCTOR))
    {
      parse_destructor(parser, modifiers, node);
    }
    else if (is(parser, CC_TKT_NAME))
    {
      parse_method_or_variable(parser, modifiers, node);
    }
    else
    {
      return false;
    }
  }

  expect_and_next(parser, CC_TKT_RIGHT_CURLY_BRACKET);

  return true;
}

bool parse_enumeration(cc_parser* parser, cc_arraylist* modifiers, cc_namespace_tree* namespace)
{
  cc_position* keyword_position = make_pos(parser);
  if (!check_and_next(parser, CC_TKT_ENUMERATION))
  { return false; }
  cc_position* name_position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);
  cc_defn_tree* node = cc_tree_factory_create_enumeration(parser->tree_factory, keyword_position, name, name_position);
  node->modifiers = modifiers;
  cc_arraylist_append(namespace->definitions, (cc_object*)node);
  expect_and_next(parser, CC_TKT_LEFT_CURLY_BRACKET);

  while (is(parser, CC_TKT_NAME))
  {
    if (!parse_enumeration_element(parser, node))
    { return false; }
    if (!check_and_next(parser, CC_TKT_COMMA))
    { break; }
  }

  if (is(parser, CC_TKT_SEMICOLON))
  {
    next(parser);
    while (is(parser, CC_TKT_NAME) || is_modifier(parser))
    {
      modifiers = cc_arraylist_create(0);
      parse_modifiers(parser, modifiers);
      parse_method_or_variable(parser, modifiers, node);
    }
  }

  expect_and_next(parser, CC_TKT_RIGHT_CURLY_BRACKET);

  return true;
}

bool parse_namespace(cc_parser* parser, cc_tree* parent)
{
  cc_position* keyword_position = make_pos(parser);
  if (!check_and_next(parser, CC_TKT_NAMESPACE))
  { return false; }

  cc_position* name_position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);
  cc_namespace_tree* namespace = cc_tree_factory_create_namespace(parser->tree_factory, keyword_position, name, name_position);
  if ((parent->flags & CC_TT_NAMESPACE) == CC_TT_NAMESPACE)
    cc_arraylist_append(cc_tree_to_namespace(parent)->definitions, (cc_object*)namespace);
  else if ((parent->flags & CC_TT_MODULE) == CC_TT_MODULE)
    cc_arraylist_append(cc_tree_to_module(parent)->definitions, (cc_object*)namespace);
  else {
    cc_error(CC_EINVAL);
  }
  expect_and_next(parser, CC_TKT_LEFT_CURLY_BRACKET);

  while (is_namespace_element(parser))
  {
    cc_arraylist* modifiers = cc_arraylist_create(0);
    parse_modifiers(parser, modifiers);
    if (is(parser, CC_TKT_CLASS))
    {
      if (!parse_class(parser, modifiers, namespace))
      { return false; }
    }
    else if (is(parser, CC_TKT_ENUMERATION))
    {
      if (!parse_enumeration(parser, modifiers, namespace))
      { return false; }
    }
    else if (is(parser, CC_TKT_NAMESPACE))
    {
      if (!parse_namespace(parser, (cc_tree*)namespace))
      { return false; }
    }
    else
    {
      return false;
    }
  }

  expect_and_next(parser, CC_TKT_RIGHT_CURLY_BRACKET);

  return true;
}

bool parse_module(cc_parser* parser, cc_compilation_unit_tree* compilation_unit)
{
  cc_position* keyword_position = make_pos(parser);
  if (!check_and_next(parser, CC_TKT_MODULE))
  { 
    cc_cstring* file_path = cc_scanner_get_file_path(parser->scanner);
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "raised in [%s:%d]: file %s: expected x, received y\n", __FILE__, __LINE__, file_path->p);
    return false;
  }
  cc_position* name_position = make_pos(parser);
  cc_cstring* name = parse_qname(parser);
  cc_module_tree *module = cc_tree_factory_create_module(parser->tree_factory, keyword_position, name, name_position);
  cc_arraylist_append(compilation_unit->modules, (cc_object*)module);

  expect_and_next(parser, CC_TKT_LEFT_CURLY_BRACKET);

  while (is(parser, CC_TKT_NAMESPACE))
  {
    if (!parse_namespace(parser, (cc_tree*)module))
    { return false; }
  }

  expect_and_next(parser, CC_TKT_RIGHT_CURLY_BRACKET);

  return true;
}

bool cc_parser_run(cc_parser* parser, cc_program_tree *program)
{
  cc_compilation_unit_tree* compilation_unit = cc_tree_factory_create_compilation_unit(parser->tree_factory, make_pos(parser));
  cc_arraylist_append(program->compilation_units, (cc_object*)compilation_unit);

  if (!check_and_next(parser, CC_TKT_SOI))
  { return false; }

  while (is(parser, CC_TKT_MODULE))
  {
    if (!parse_module(parser, compilation_unit))
    { return false; }
  }

  if (!is(parser, CC_TKT_EOI))
  { return false; }

  return true;
}
