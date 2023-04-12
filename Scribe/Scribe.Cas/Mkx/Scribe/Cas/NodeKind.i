/// @brief
/// Kind of a node representing the expression
/// \f$e_0 \cdot e_1\$
/// i.e. the multiplication of an expression \f$e_0\f$ (multiplicand) and an expression \f$e_1\f$ (multiplier).
/// - for matrices x matrix: the matrix product is computed.
/// - for vector x vector:   the component-wise product is computed.
/// - for matrix x scalar:   the matrix scalar product is computed.
/// - for vector x scalar:   the vector scalar product is computed.
Define(BinaryStar)

/// @brief
/// Kind of a node representing the expression
/// \f$e_0 / e_1\f$
/// i.e. the division of an expression \f$e_0\f$ (dividend) and an expression \f$e_1\f$ (divisor).
Define(BinarySlash)

/// @brief
/// Kind of a node representing an variable.
Define(Variable)

/// @brief
/// Kind of a node representing the expression
/// \f$minor(e, i, j)\f$
/// i.e. the minor of the \f$i\f$-th row and the \f$j\f$-th column of a matrix expression \$fe\f$.
/// @remark
/// The minor of the \f$i\f$-th row and the \f$j\f$-th column of a square matrix \f$m\f$ of an order \f$\geq 1\f$ is defined
/// as the matrix obtained by removing the \f$i\f$-th row and the \f$j\f$-th column of \f$m\f$ and computing the determinated
/// of the resulting matrix.
/// @remark
/// The minor of of a \f$0 \times 0\f$ matrix is defined to be the determinant of that matrix.
/// @see See Mkx_Scribe_Cas_MinorNode for more information.
Define(Minor)

/// @brief
/// Kind of a node representing the expression
/// \$cofactor(i, j, e)\f$
/// i.e. the cofactor of the \f$i\f$-th row and the \f$j\f$-th column of a matrix expression \$fe\f$.
/// @remark
/// The cofactor of the \f$i\f$-row and the \f$j\f$ column is the minor of that row and that column
/// multiplied by \f$(-1)^(i + j + 2)\f$ (with zero-based indices).
/// @see See Mkx_Scribe_Cas_CofactorNode for more information.
Define(Cofactor)

/// @brief
/// Kind of a node representing the expression
/// \$Determinant(e)\f$
/// i.e. the determinant of the matrix expression \f$e\f$.
/// @remark
/// The determinant of a 1 x 1 matrix
/// \[
/// \begin{matrix}
/// a
/// \end{matrix}
/// \]
/// is simply
/// \[
/// a
/// \]
/// The determinant of a 2 x 2 matrix
/// \[
/// \begin{matrix}
/// a & b \\
/// c & d \\
/// \end{matrix}
/// \]
/// is simply
/// \[
/// ad - bc
/// \]
/// @remark
/// The determinant of an \f$n \times n\f$, \f$n > 0\$ is computed by considering the elements of the top row and their respective cofactors.
/// For each element in the top row from left to right, take the product of the element and its cofactor. Then sum up all the
/// resulting products.
/// @remark
/// The determinant of an \f$0 \times 0\f$ matrix is defined to be \f$1\f$.
/// @remark
/// By the definitions above,
/// the determinant of the \f$1 \times 1\f$ matrix \f$\begin{matrix}m_{0,0}\end{matrix}\f$ is \f$m_{0,0} cof(0,0,\begin{matrix}m_{0,0}\end{matrix}) = 
/// m_{0,0} \cdot (-1)^2 minor(0, 0, \begin{matrix}m_{0,0}\end{matrix}) = m_{0,0} minor(0,0 \begin{matrix}m_{0,0}\end{matrix})
/// = m_{0,0} det(0) = m_{0,0}\f$.
Define(Determinant)

/// @brief
/// Kind of a node representing the expression
/// \$e_0 + e_1\f$
/// i.e. the addition of an expression \f$e_1\f$ (augend) and an expression \f$e_0\f$ (addend).
Define(BinaryPlus)

/// @brief
/// Kind of a node representing the expression
/// \f$e_0 - e_1\f$
/// i.e. the subtraction of an expression \f$e_1\f$ (minuend) and an expression \f$e_0\f$ (subtrahend).
Define(BinaryMinus)

/// @brief
/// Kind of a node representing the expression
/// \$+e\f$
/// i.e. the arithmetic affirmation of an expression \f$e\$.
Define(UnaryPlus)

/// @brief Kind of a node representing the expression
/// \$-e\f$
/// i.e. the arithmetic negation of an expression \f$e\$.
Define(UnaryMinus)

/// @brief Kind of a node representing the expression
/// \f$(e)\f$
/// i.e. the enclosing an expression \f$e\f$ in parentheses.
Define(Group)

/// @brief Kind of a node representing a matrix.
Define(Matrix)

/// @brief Kind of a node representing vector.
Define(Vector)

/// @brief Kind of a node representing the expression
/// \f$transpose(e)\$
/// i.e. the transpose of a matrix expression \f$e\f$.
Define(Transpose)

/// @brief Kind of a node representing the deletation of a row of a matrix
/// \f$deleteRow(i,e)\$.
Define(DeleteRow)

/// @brief Kind of a node representing the deletation of a column of a matrix
/// \f$deleteColumn(i,e)\$.
Define(DeleteColumn)

/// @brief
/// Kind of a node representing the expression
/// \f$adjugate(e)\f$
/// of computing the adjugate of a matrix expression \f$e\f$.
/// @remark
/// The adjugate matrix of a non-empty square matrix \f$M\f$
/// is the matrix \f$M' = transpose(cofactorMatrix(M)\f$.
Define(Adjugate)

/// @brief Kind of a node representing the expression
/// \$cofactorMatrix(e)\f$
/// of computing the cofactor matrix of a matrix expression \f$e\f$.
/// @remark
/// The cofactor matrix of a non-empt square matrix \f$M\f$
/// is the  matrix \f$M'\f$ such that \f$M'_{i,j} = cofactor(M,i,j)\f$.
Define(CofactorMatrix)

/// @brief Kind of a node representing the expression
/// \f$1\f$
/// of computing the constant \f$1\f$.
Define(One)

/// @brief Kind of a node representing the expression
/// \f$0\f$
/// of computing the constant \f$0\f$.
Define(Zero)

/// @brief Kind of a node representing the expression
/// \f$Inverse(e)\f$
/// of computing the inverse of a matrix expression \f$e\f$.
Define(Inverse)

/// @brief Kind of a node representing an output expression.
Define(Output)

/// @brief Kind of a 1D index node.
Define(Index1d)

/// @brief Kind of a 2D index node.
Define(Index2d)

/// @brief Kind of a dot product node.
/// Computes the dot product of vectors and matrices.
/// Note that this software distinguishes between vectors and matrices.
Define(DotProduct)
