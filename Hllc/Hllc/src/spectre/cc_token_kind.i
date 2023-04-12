// Control tokens.
DEFINE(EOI, "<end of input>")
DEFINE(SOI, "<start of input>")
DEFINE(ERR, "<error>")

// definition keywords
DEFINE(STRUCTURE, "structure")
DEFINE(CLASS, "class")
DEFINE(CONSTRUCTOR, "constructor")
DEFINE(DESTRUCTOR, "destructor")
DEFINE(ENUMERATION, "enumeration")
DEFINE(NAMESPACE, "namespace")
DEFINE(MODULE, "module")
DEFINE(EXTENDS, "extends")
DEFINE(IMPLEMENTS, "implements")

// class and method modifier keywords
DEFINE(ABSTRACT, "abstract")
DEFINE(STATIC, "static")
DEFINE(SEALED, "sealed")

// parameter modifier keyword
DEFINE(OUT, "out")

// method modifier keyword
DEFINE(OVERRIDE, "override")

// access modifiers
DEFINE(PRIVATE, "private")
DEFINE(PROTECTED, "protected")
DEFINE(PUBLIC, "public")

// destructor modifier keywords
// @todo Should be a constructor, destructor, and method keyword.
DEFINE(FOREIGN, "foreign")

// Separator tokens.
DEFINE(COMMA, ",")
DEFINE(SEMICOLON, ";")
DEFINE(LEFT_CURLY_BRACKET, "{")
DEFINE(RIGHT_CURLY_BRACKET, "}")
DEFINE(LEFT_PARENTHESIS, "(")
DEFINE(RIGHT_PARENTHESIS, ")")
DEFINE(PERIOD, ".")
DEFINE(LEFT_SQUARE_BRACKET, "[")
DEFINE(RIGHT_SQUARE_BRACKET, "]")

// Operators.
DEFINE(ASSIGN, "=")
DEFINE(PLUS, "+")
DEFINE(MINUS, "-")
DEFINE(STAR, "*")
DEFINE(SLASH, "/")

DEFINE(NAME, "<name>")       // Name.
DEFINE(INTEGER, "<integer>") // Integer literal.
DEFINE(STRING, "<string>")   // String literal.

// Comments tokens.
DEFINE(COMMENT_LINE, "<comment line>")
