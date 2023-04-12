DEFINE_3(cc_program_tree, program, PROGRAM, "<program>", 1)

DEFINE_3(cc_compilation_unit_tree, compilation_unit, COMPILATION_UNIT, "<compilation unit>", 2)

DEFINE_3(cc_module_tree, module, MODULE, "<module>", 3)

DEFINE_3(cc_namespace_tree, namespace, NAMESPACE, "<namespace>", 4)

DEFINE_3(cc_defn_tree, enumeration, ENUMERATION, "<enumeration>", 5) // member can be removed from cc_tree.

DEFINE_3(cc_var_tree, member_variable, MEMBER_VARIABLE, "<member variable>", 6) // member can be removed from cc_tree.

DEFINE_3(cc_proc_tree, method, METHOD, "<method>", 7) // member can be removed from cc_tree.

DEFINE_3(cc_defn, class, CLASS, "<class>", 8) // member can be removed from cc_tree.

DEFINE_3(cc_proc_tree, constructor, CONSTRUCTOR, "<constructor>", 9) // member can be removed from cc_tree.

DEFINE_3(cc_proc_tree, destructor, DESTRUCTOR, "<destructor>", 10) // member can be removed from cc_tree.

DEFINE_3(cc_defn_tree, interface, INTERFACE, "<interface>", 11) // member can be removed from cc_tree.

DEFINE_3(cc_var_tree, parameter_variable, PARAMETER_VARIABLE, "<parameter variable>", 12) // member can be removed from cc_tree.

DEFINE_3(cc_direct_type_reference, direct_type_reference, DIRECT_TYPE_REFERENCE, "<direct type reference>", 14)

DEFINE_3(cc_array_type_reference, array_type_reference, ARRAY_TYPE_REFERENCE, "<array type reference>", 15)

DEFINE_3(cc_modifier_tree, modifier, MODIFIER, "<modifier>", 16) // member can be removed from cc_tree.


DEFINE_3(cc_literal_expression_tree, integer_expression, INTEGER_EXPRESSION, "<integer expression>", 18)

DEFINE_3(cc_literal_expression_tree, string_expression, STRING_EXPRESSION, "<string expression>", 19)


DEFINE_3(cc_unary_expression_tree, unary_plus_expression, UNARY_PLUS_EXPRESSION, "<unary plus expression>", 20) // member can be removed from cc_tree.

DEFINE_3(cc_unary_expression_tree, unary_minus_expression, UNARY_MINUS_EXPRESSION, "<unary minus expression>", 21) // member can be removed from cc_tree.


DEFINE_3(cc_binary_expression, binary_plus_expression, BINARY_PLUS_EXPRESSION, "<binary plus expression>", 22) // member can be removed from cc_tree.

DEFINE_3(cc_binary_expression, binary_minus_expression, BINARY_MINUS_EXPRESSION, "<binary minus expression>", 23) // member can be removed from cc_tree.

DEFINE_3(cc_binary_expression, binary_star_expression, BINARY_STAR_EXPRESSION, "<binary star expression>", 24) // member can be removed from cc_tree.

DEFINE_3(cc_binary_expression, binary_slash_expression, BINARY_SLASH_EXPRESSION, "<binary slash expression>", 25) // member can be removed from cc_tree.
