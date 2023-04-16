
/// @brief <code>Integer</code> node.
Define(Integer, "<Integer>")

/// @brief <code>String</code> node.
Define(String, "<String>")

/// @brief <code>Name</code> node.
Define(Name, "<Name>")

/// @brief <code>ArgumentList := expression*</code> node.
/// Represents the arguments to a function call or a method call.
/// @todo Shall consists of zero or more expression \(e_0\),\(e_1\),...,\(e_{n-1}\) such that the expression
/// \(e_i\) evaluates to the value of the \(i\)-th argument.
Define(ArgumentList, "<ArgumentList")

/// @brief <code>FunctionCallExpression</code> node.
/// Represents a call to a call of the form <code>ProcedureCallExpression := Name '(' ')'</code>.
/// The currently known callables are
/// - GeneratorVendor : [...] -> [..., e], type(e) = String
/// The vendor of this generator ("Michael Heilmann").
/// - GeneratorName : [...] -> [..., e], type(e) = String
/// The name of this generator ("Scribe").
Define(ProcedureCallExpression, "<ProcedureCallExpression>")

/// @brief <code>Task</code> node.
/// <code>Task</code> nodes represent the processing
/// of a source file into a target file. Such a node
/// has two operands which both must evaluate to
/// values of type <code>String</code>. The first
/// operand's evaluation result denotes the path
/// name of the source file, the second operand's evaluation
/// result denotes the path name of the target file.
Define(Task, "<Task>")

/// @brief <code>TaskList</code> node.
/// Zero or more children.
/// Each child is either <code>Task</code> or a <code>TaskList</code> node.
Define(TaskList, "<TaskList>")

Define(IncludeDirective, "<IncludeDirective>")

Define(Template, "<Template>")

/// @brief <code>UnaryMinus</code> node.
/// Single operand must be an integer.
Define(UnaryMinus, "<UnaryMinus>")
  
/// @brief <code>UnaryPlus</code> node.
/// Single operand must be an integer.
Define(UnaryPlus, "<UnaryPlus>")
  
/// @brief <code>Plus</code> node.
/// Left operand and right operand must be <code>Integer</code> nodes.
Define(Plus, "<Plus>")
  
/// @brief <code>Minus</code> node.
/// Left operand and right operand must be <code>Integer</code> nodes.
Define(Minus, "<Minus>")
  
/// @brief Left operand and right operand must be <code>Integer</code> nodes.
Define(Star, "<Star>")

/// @brief Left operand and right operand must be <code>Integer</code> nodes.
Define(Slash, "<Slash>")
  
/// @brief Single argument must be a <code>Constant</code> node.
Define(ToString, "<ToString>")

/// n*2, n >= 0 arguments. Two consecutive values are a key value pair of which the first element is a key and the second element is a value.
Define(CreateTable, "<CreateTable>")
  
/// @brief List of <code>n &ge; 0</code> <code>Statement</code> nodes.
Define(Statements, "<Statement>")
  
/// @brief
/// <code>AssignmentStatement</code> node.
/// Left operand must be a <code>VariableNode</code> node.
/// Right operand must be a <code>Expression</code> node.
Define(AssignmentStatement, "<AssignmentStatement>")

/// @brief <code>ExpressionStatement</code> node.
/// Singe operand must be a <code>Expression</code> node.
Define(ExpressionStatement, "<ExpressionStatement>")
