/// @@brief Compute the determinant of this matrix.
/// @@param result A pointer to a <code>double</code> variable.
/// @@param self A pointer to this matrix.
/// @@return #Mkx_Status_Success on success, a failure status code on failure.
/// @@success <code>*result</code> was assigned the determinant of this matrix.
/// @@failure <code>result</code> was not dereferenced.
Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_determinant
  (
    double *result,
    Mkx_Matrix@(rows)x@(columns)@(type) *self
  );

/// @@brief Compute the adjguate of this matrix.
/// @@param result A pointer to a <code>double</code> variable.
/// @@param self A pointer to this matrix.
/// @@return #Mkx_Status_Success on success, a failure status code on failure.
/// @@success <code>*result</code> was assigned a pointer to the adjugate of this matrix.
/// The caller acquired a reference to the product matrix.
/// @@failure <code>result</code> was not dereferenced.
Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_adjugate
  (
    Mkx_Matrix@(rows)x@(columns)@(type)** result,
    Mkx_Matrix@(rows)x@(columns)@(type)* self
  );

/// @@brief Compute the inverse of this matrix.
/// @@param result A pointer to a <code>Mkx_Matrix@(rows)x@(columns)@(type) *</code> variable.
/// @@param self A pointer to this matrix.
/// @@return #Mkx_Status_Success on success, a failure status code on failure.
/// @@success <code>*result</code> was assigned a pointer to the inverse matrix of this matrix.
/// The caller acquired a reference to the inverse matrix.
/// @@failure <code>result</code> was not dereferenced.
Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_inverse
  (
    Mkx_Matrix@(rows)x@(columns)@(type)** result,
    Mkx_Matrix@(rows)x@(columns)@(type)* self
  );
