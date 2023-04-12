/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_TREE_H_INCLUDED)
#define CC_TREE_H_INCLUDED


#include "cc_file_manager.h"
#include "cc_names.h"

/// @brief Utility macro for declaring a type derived from cc_tree.
/// @param name The canonical name of the tree type e.g. "binary_expression".
/// @param mask Bitwise or of the tree kinds represented by this tree type.
#define CC_DECLARE_TREE_CLASS(NAME, MASK) \
  static inline bool cc_tree_is_##NAME(cc_tree* self) \
  { \
    CC_ASSERT_NOT_NULL(self); \
    return (self->flags & (MASK)) != 0; \
  } \
\
  static inline cc_##NAME##_tree* cc_tree_to_##NAME(cc_tree* self) \
  { \
    if (!cc_tree_is_##NAME(self)) \
    { cc_error(CC_EINVAL); } \
    return (cc_##NAME##_tree *)self; \
  }


CC_FORWARD_DECLARE_CLASS(cc_tree );

FORWARD_DECLARE_COMPONENT(cc_tree_factory);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum cc_tree_kind
{

#define DEFINE_3(CNAME, NAME, NAME_UPPERCASE, DESCRIPTION, INDEX) \
  CC_TT_##NAME_UPPERCASE = (1 << INDEX),

  #include "cc_tree_kind.i"

#undef DEFINE_3

} cc_tree_kind;

/// @brief The base of all trees.
struct cc_tree
{
  cc_object __parent;

  uint32_t flags;
};

#define DEFINE_3(CNAME, NAME, NAME_UPPERCASE, DESCRIPTION, INDEX) \
  static inline bool cc_tree_is_##NAME##_kind(cc_tree *tree) \
  { \
    return (tree->flags & CC_TT_##NAME_UPPERCASE) == CC_TT_##NAME_UPPERCASE; \
  }

#include "cc_tree_kind.i"

#undef DEFINE_3

uint32_t cc_t_get_kind(cc_tree* t);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// A program consists of compilation units.
/// <code>
/// program : compilation_unit*
/// </code>
CC_DECLARE_CLASS(cc_program_tree, cc_tree)

struct cc_program_tree
{
  
  cc_tree CC_DECORATE(parent);

  cc_arraylist* compilation_units;

};

/// <code>
/// program : compilationUnit*
/// </code>
cc_program_tree* cc_tree_factory_create_program(cc_tree_factory* self);

CC_DECLARE_TREE_CLASS(program, CC_TT_PROGRAM)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// A compilation unit consists of modules.
/// <code>
/// compilation_unit : modules*
/// </code>
CC_DECLARE_CLASS(cc_compilation_unit_tree, cc_tree)

struct cc_compilation_unit_tree
{

  cc_tree CC_DECORATE(parent);

  cc_position* position;

  cc_arraylist* modules;

};

/// <code>
/// compilationUnit : module*
/// </code>
cc_compilation_unit_tree* cc_tree_factory_create_compilation_unit(cc_tree_factory* self, cc_position *position);

CC_DECLARE_TREE_CLASS(compilation_unit, CC_TT_COMPILATION_UNIT)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_module_tree, cc_tree)

struct cc_module_tree
{

  cc_tree CC_DECORATE(parent);
  
  /// @brief The name of the module.
  cc_cstring* name;

  /// @brief List of definitions in this module in this compilation unit.
  cc_arraylist* definitions;

};

/// <code>
/// module : qualifiedName@name moduleBody
/// </code>
cc_module_tree* cc_tree_factory_create_module(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position);

CC_DECLARE_TREE_CLASS(module, CC_TT_MODULE)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief
/// A defn tree is used to represent:
/// - class definitions,
/// - interface definitions, and
/// - enumeration definitions
CC_DECLARE_CLASS(cc_defn_tree, cc_tree)

struct cc_defn_tree
{
  
  cc_tree CC_DECORATE(parent);

  /// @brief The keyword position.
  cc_position* keyword_position;

  /// @brief The unqualified name of the definition.
  cc_cstring* name;

  /// @brief The members list of the definition.
  cc_arraylist* members;

  /// @brief The extends list of the definition.
  cc_arraylist* extends;

  /// @brief The implements list of the definition.
  cc_arraylist* implements;

  /// @brief The modifiers of the definition.
  cc_arraylist* modifiers;

};

/// <code>
/// class : 'class' qualifiedName@name ( 'extends' qualifiedName (',' qualifiedName)* )? classBody
/// </code>
cc_defn_tree* cc_tree_factory_create_class(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position);

/// <code>
/// enumeration : 'enumeration' qualifiedName@name enumerationBody
/// </code>
cc_defn_tree* cc_tree_factory_create_enumeration(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position);

/// <code>
/// interface : 'interface' qualifiedName@name interfaceBody
/// </code>
cc_defn_tree* cc_tree_factory_create_interface(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* name, cc_position* name_position);

/// @deprecated
/// @brief Add a type reference tree to the extends list of this defn tree.
/// @param self This defn tree.
/// @param type The reference tree.
void cc_defn_tree_add_extends(cc_defn_tree* self, cc_tree* type);

/// @deprecated
/// @brief Add a type reference to the implements list of this defn tree.
/// @param self This defn tree.
/// @param type The reference tree.
void cc_defn_tree_add_implements(cc_defn_tree* self, cc_tree* type);

cc_arraylist* cc_defn_tree_get_members(cc_defn_tree* self);

CC_DECLARE_TREE_CLASS(defn, CC_TT_CLASS | CC_TT_ENUMERATION | CC_TT_INTERFACE)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_namespace_tree, cc_tree)

struct cc_namespace_tree
{

  cc_tree CC_DECORATE(parent);

  cc_cstring* name;
  
  cc_arraylist* definitions;

};

/// <code>
/// namespace : 'namespace' qualifiedName@name namespaceBody
/// </code>
cc_namespace_tree* cc_tree_factory_create_namespace(cc_tree_factory* self, cc_position *keyword_position, cc_cstring *name, cc_position* name_position);

CC_DECLARE_TREE_CLASS(namespace, CC_TT_NAMESPACE)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief
/// A proc tree is used to represent:
/// - definitions of constructors,
/// - definitions of destructors, and
/// - definitions of methods
CC_DECLARE_CLASS(cc_proc_tree, cc_tree)

struct cc_proc_tree
{

  cc_tree CC_DECORATE(parent);

  cc_position* keyword_position;

  /// @brief
  /// For methods:      The unqualified name of the method.
  /// For constructors: <constructor>.
  /// For destructors:  <destructor>.
  cc_cstring* name;

  /// @brief
  /// For methods:      The result type.
  /// For constructors: null.
  /// For destructors:  null.
  cc_tree* type;

  cc_cstring* suffix;
  
  cc_position* suffix_position;

  /// @brief
  /// For methods:      List of parameters.
  /// For constructors:         "
  /// For destructors:          "
  /// @remark For the curious: Syntactically valid destructors may have parameters.
  ///                          Semantically valid destructors may not have parameters.
  cc_arraylist* parameters;

  cc_arraylist* modifiers;

};

/// <code>
/// 'constructor'@{keyword_position = this.position} ('.' name@{suffix = this.text})? parameterList@parameters
/// </code>
cc_proc_tree* cc_tree_factory_create_constructor(cc_tree_factory* self, cc_position* keyword_position, cc_cstring* suffix, cc_position* suffix_position, cc_arraylist* parameters);

/// <code>
/// destructor : 'destructor'@{keyword_position = this.position} parameterList@parameters
/// </code>
cc_proc_tree* cc_tree_factory_create_destructor(cc_tree_factory* self, cc_position* keyword_position, cc_arraylist* parameters);

/// <code>
/// method : name@name@{position = this.position} parameterList@parameters typeReference@type
/// </code>
cc_proc_tree* cc_tree_factory_create_method(cc_tree_factory* self, cc_position* position, cc_cstring* name, cc_tree* type, cc_arraylist* parameters);

/// @internal
/// @brief Get the parameters tree of a proc tree.
/// @param self The proc tree.
/// @return The parameters tree.
cc_arraylist* cc_proc_tree_get_parameters(cc_proc_tree* self);

/// @internal
/// @brief Get the result type tree of a proc tree.
/// @param self The proc tree.
/// @return The result type tree.
cc_tree* cc_proc_tree_get_result_type(cc_proc_tree* self);

CC_DECLARE_TREE_CLASS(proc, CC_TT_CONSTRUCTOR | CC_TT_DESTRUCTOR | CC_TT_METHOD)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief
/// A var tree is used to represent:
/// - definitions of member variables and
/// - definitions of parameter variables
CC_DECLARE_CLASS(cc_var_tree, cc_tree)

struct cc_var_tree
{

  cc_tree CC_DECORATE(parent);

  cc_cstring* name;
  
  cc_tree* type;
  
  cc_tree* initializer;
  
  cc_arraylist* modifiers;

};

/// <code>
/// memberVariable : name@name typeReference@type
/// </code>
cc_var_tree* cc_tree_factory_create_member_variable(cc_tree_factory* self, cc_cstring *name, cc_tree *type);

/// <code>
/// parameterVariable : name@name qualifiedName@type
/// </code>
cc_var_tree* cc_tree_factory_create_parameter_variable(cc_tree_factory* self, cc_cstring* name, cc_position* name_position, cc_tree* type);

CC_DECLARE_TREE_CLASS(var, CC_TT_MEMBER_VARIABLE | CC_TT_PARAMETER_VARIABLE)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_modifier_tree, cc_tree)

struct cc_modifier_tree
{
  
  cc_tree CC_DECORATE(parent);
  
  cc_cstring* modifier;
  
  cc_position* position;

};

/// <code>
/// modifierAbstract : 'abstract'
/// </code>
cc_modifier_tree* cc_tree_factory_create_abstract_modifier(cc_tree_factory* self, cc_position *position);

/// <code>
/// modifierSealed : 'sealed'
/// </code>
cc_modifier_tree* cc_tree_factory_create_sealed_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierStatic : 'static'
/// </code>
cc_modifier_tree* cc_tree_factory_create_static_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierOut : 'out'
/// </code>
cc_modifier_tree* cc_tree_factory_create_out_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierPublic : 'public'
/// </code>
cc_modifier_tree* cc_tree_factory_create_public_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierPrivate : 'private'
/// </code>
cc_modifier_tree* cc_tree_factory_create_protected_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierProtected : 'protected'
/// </code>
cc_modifier_tree* cc_tree_factory_create_private_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierOverride : 'override'
/// </code>
cc_modifier_tree* cc_tree_factory_create_override_modifier(cc_tree_factory* self, cc_position* position);

/// <code>
/// modifierForeign : 'foreign'
/// </code>
cc_modifier_tree* cc_tree_factory_create_foreign_modifier(cc_tree_factory* self, cc_position* position);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_direct_type_reference_tree, cc_tree)

struct cc_direct_type_reference_tree
{
  cc_tree CC_DECORATE(parent);

  /// @brief The qualified name.
  cc_cstring* name;

  /// @brief The position of the qualified name.
  cc_position* position;
};

/// <code>
/// directTypeReference : qualifiedName@name
/// </code>
cc_direct_type_reference_tree* cc_tree_factory_create_direct_type_reference(cc_tree_factory* self, cc_position* position, cc_cstring* name);

CC_DECLARE_TREE_CLASS(direct_type_reference, CC_TT_DIRECT_TYPE_REFERENCE)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_array_type_reference_tree, cc_tree)

struct cc_array_type_reference_tree
{
  cc_tree CC_DECORATE(parent);
  cc_tree* inner_type;
};

/// <code>
/// arrayTypeReference : typeReference@inner_type '[' ']'
/// </code>
cc_array_type_reference_tree* cc_tree_factory_create_array_type_reference(cc_tree_factory* self, cc_tree* inner_type);

CC_DECLARE_TREE_CLASS(array_type_reference, CC_TT_ARRAY_TYPE_REFERENCE)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// <code>
/// literalExpression : integerLiteralExpression | stringLiteralExpression
/// </code>
CC_DECLARE_CLASS(cc_literal_expression_tree, cc_tree)

struct cc_literal_expression_tree
{
  cc_tree parent;
  cc_cstring* literal;
};

/// <code>
/// integerLiteralExpression : INTEGER@{literal = this.text}@{literal_position = this.position}
/// </code>
cc_literal_expression_tree* cc_tree_create_integer_literal_expression(cc_tree_factory* self, cc_cstring* literal, cc_position* literal_position);

/// <code>
/// stringLiteralExpression : STRING@{literal = this.text}@{literal_position = this.position}
/// </code>
cc_literal_expression_tree* cc_tree_create_string_literal_expression(cc_tree_factory* self, cc_cstring* literal, cc_position* literal_position);

CC_DECLARE_TREE_CLASS(literal_expression, CC_TT_INTEGER_EXPRESSION | CC_TT_STRING_EXPRESSION)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief
/// An unary plus expression tree is used to represent the following expressions:
/// - unary plus expression and
/// - unary minus expression
CC_DECLARE_CLASS(cc_unary_expression_tree, cc_tree)

struct cc_unary_expression_tree
{

  cc_tree CC_DECORATE(parent);

  cc_tree* operand;

};

/// <code>
/// unaryPlusExpression : '+'@{position = this.position} expression@operand
/// </code>
cc_unary_expression_tree* cc_tree_create_unary_plus_expression(cc_tree_factory* self, cc_tree* operand, cc_position* position);

/// <code>
/// unaryMinusExpression : '-'@{position = this.position} expression@operand
/// </code>
cc_unary_expression_tree* cc_tree_create_unary_minus_expression(cc_tree_factory* self, cc_tree* operand, cc_position* position);

CC_DECLARE_TREE_CLASS(unary_expression, CC_TT_UNARY_PLUS_EXPRESSION | CC_TT_UNARY_MINUS_EXPRESSION)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief
/// A binary expression tree is used to represent the following expressions:
/// - binary plus expression,
/// - binary minus expression,
/// - binary star expression, and
/// - binary slash expression
CC_DECLARE_CLASS(cc_binary_expression_tree, cc_tree)

struct cc_binary_expression_tree
{

  cc_tree CC_DECORATE(parent);

  cc_tree* left_operand;

  cc_tree* right_operand;

};

/// <code>
/// binaryMinusExpression : expression@left_operand '+'@{position = this.position} expression@right_operand
/// </code>
cc_binary_expression_tree* cc_tree_create_binary_minus_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand);

/// <code>
/// binaryMinusExpression : expression@left_operand '-'@{position = this.position} expression@right_operand
/// </code>
cc_binary_expression_tree* cc_tree_create_binary_plus_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand);

/// <code>
/// binarySlashExpression : expression@left_operand '/'@{position = this.position} expression@right_operand
/// </code>
cc_binary_expression_tree* cc_tree_create_binary_slash_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand);

/// <code>
/// binaryStarExpression : expression@left_operand '*'@{position = this.position} expression@right_operand
/// </code>
cc_binary_expression_tree* cc_tree_create_binary_star_expression(cc_tree_factory* self, cc_position* position, cc_tree* left_operand, cc_tree* right_operand);

CC_DECLARE_TREE_CLASS(binary_expression, CC_TT_BINARY_PLUS_EXPRESSION|CC_TT_BINARY_MINUS_EXPRESSION|CC_TT_BINARY_STAR_EXPRESSION|CC_TT_BINARY_SLASH_EXPRESSION)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BEGIN_DECLARE_COMPONENT(cc_tree_factory)

cc_spectre_names* names;

END_DECLARE_COMPONENT(cc_tree_factory)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @deprecated
/// @brief Get the name of a class, enumeration, method, module, or (member|parameter) variable node.
cc_cstring* cc_t_get_name(cc_tree* t);


#if !defined(CC_DECLARE_TREE_CLASS)
#error(CC_DECLARE_TREE_CLASS is not defined)
#endif
#undef CC_DECLARE_TREE_CLASS

#endif // CC_TREE_H_INCLUDED
