Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_multiply
  (
    Mkx_Matrix@(rows)x@(columns)@(type) **r,
    Mkx_Matrix@(rows)x@(columns)@(type) *a,
    Mkx_Matrix@(rows)x@(columns)@(type) *b
  )
{
  Mkx_Matrix@(rows)x@(columns)@(type)* temporary;
  Mkx_Matrix@(rows)x@(columns)@(type)_createIdentity(&temporary);
  product_@(rows)_@(columns)(NULL, temporary->elements, a->elements, b->elements);
  *r = temporary;
  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_transpose
  (
    Mkx_Matrix@(rows)x@(columns)@(type) **r,
    Mkx_Matrix@(rows)x@(columns)@(type) *a
  )
{
  Mkx_Matrix@(rows)x@(columns)@(type)* temporary;
  Mkx_Matrix@(columns)x@(rows)@(type)_createIdentity(&temporary);
  transpose_@(rows)_@(columns)(NULL, temporary->elements, a->elements);
  *r = temporary;
  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_matrixScalarProduct
  (
    Mkx_Matrix@(rows)x@(columns)@(type)** result,
    Mkx_Matrix@(rows)x@(columns)@(type) *self,
    double scalar
  )
{
  Mkx_Matrix@(rows)x@(columns)@(type)* temporary;
  Mkx_Matrix@(columns)x@(rows)@(type)_createIdentity(&temporary);
  product_scalar_@(rows)_@(columns)(NULL, temporary->elements, scalar, self->elements);
  *result = temporary;
  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_determinant
  (
    double *result,
    Mkx_Matrix@(rows)x@(columns)@(type) *self
  )
{
  determinant_@(rows)_@(columns)(NULL, result, self->elements);
  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_adjugate
  (
    Mkx_Matrix@(rows)x@(columns)@(type)** result,
    Mkx_Matrix@(rows)x@(columns)@(type)* self
  )
{
  Mkx_Matrix@(rows)x@(columns)@(type)* temporary;
  Mkx_Matrix@(columns)x@(rows)@(type)_createIdentity(&temporary);
  adjugate_@(rows)_@(columns)(NULL, temporary->elements, self->elements);
  *result = temporary;
  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_inverse
  (
    Mkx_Matrix@(rows)x@(columns)@(type)** result,
    Mkx_Matrix@(rows)x@(columns)@(type)* self
  )
{
  double determinant;
  if (Mkx_Unlikely(Mkx_Matrix@(rows)x@(columns)@(type)_determinant(&determinant, self)))
  { return 1; }
  if (0. == determinant)
  { return 1; }

  Mkx_Matrix@(rows)x@(columns)@(type)* adjugate;
  if (Mkx_Unlikely(Mkx_Matrix@(rows)x@(columns)@(type)_adjugate(&adjugate, self)))
  { return 1; }

  Mkx_Matrix@(rows)x@(columns)@(type)* inverse;
  if (Mkx_Unlikely(Mkx_Matrix@(rows)x@(columns)@(type)_matrixScalarProduct(&inverse, adjugate, 1. / determinant)))
  {
    Mkx_Object_unreference(MKX_OBJECT(adjugate));
    return 1;
  }
  Mkx_Object_unreference(MKX_OBJECT(adjugate));

  *result = inverse;

  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_Matrix@(rows)x@(columns)@(type)_getElement
  (
    double *result,
    Mkx_Matrix@(rows)x@(columns)@(type)* self,
    int64_t rowIndex,
    int64_t columnIndex
  )
{
  if (Mkx_Unlikely(!result || !self || rowIndex < 0 || rowIndex >= @(rows) || columnIndex < 0 || columnIndex >= @(columns)))
  { return Mkx_Status_InvalidArgument; }
  *result = self->elements[rowIndex][columnIndex];
  return Mkx_Status_Success;
}
