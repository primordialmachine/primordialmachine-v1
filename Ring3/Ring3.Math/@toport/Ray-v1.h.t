/// https://primordialmachine.com/reference/transform-rays
Mkx_CheckReturn() Mkx_Status
Mkx_Ray@(dimensionality)@(type)_transform
  (
    Mkx_Ray@(dimensionality)@(type) **result,
    Mkx_Ray@(dimensionality)@(type) *self,
    Mkx_Matrix@(dimensionality+1)x@(dimensionality+1)@(type) *transform
  );
