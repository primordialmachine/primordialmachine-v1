Mkx_CheckReturn() Mkx_Status
Mkx_Ray@(dimensionality)@(type)_transform
  (
    Mkx_Ray@(dimensionality)@(type) **result,
    Mkx_Ray@(dimensionality)@(type) *self,
    Mkx_Matrix@(dimensionality+1)x@(dimensionality+1)@(type) *transform
  )
{
  if (Mkx_Unlikely(!result || !self || !transform))
  { return Mkx_Status_InvalidArgument; }
  // Compute a and b.
  Mkx_Vector@(dimensionality)@(type) *a = NULL, *b = NULL;
  if (Mkx_Unlikely(Mkx_Ray@(dimensionality)@(type)_getPoint(&a, self, 0.) || Mkx_Ray@(dimensionality)@(type)_getPoint(&b, self, 1.)))
  {
    if (b)
    {
      Mkx_Object_unreference(MKX_OBJECT(b));
      b = NULL;
    }
    if (a)
    {
      Mkx_Object_unreference(MKX_OBJECT(a));
      a = NULL;   
    }
    return 1;
  }
  
  Mkx_Vector@(dimensionality)@(type) *c = NULL, *d = NULL;
  if (Mkx_transformPosition3F64(&c, a, transform) || Mkx_transformPosition3F64(&d, b, transform))
  {
    if (d)
    {
      Mkx_Object_unreference(MKX_OBJECT(d));
      d = NULL;
    }
    if (c)
    {
      Mkx_Object_unreference(MKX_OBJECT(c));
      c = NULL;   
    }
    Mkx_Object_unreference(MKX_OBJECT(b));
    b = NULL;
    Mkx_Object_unreference(MKX_OBJECT(a));
    a = NULL;
    return 1;
  }
  Mkx_Object_unreference(MKX_OBJECT(b));
  b = NULL;
  Mkx_Object_unreference(MKX_OBJECT(a));
  a = NULL;
  
  Mkx_Ray@(dimensionality)@(type) *ray;
  if (Mkx_Ray@(dimensionality)@(type)_create_fromPoints(&ray, c, d))
  {
    Mkx_Object_unreference(MKX_OBJECT(d));
    d = NULL;
    Mkx_Object_unreference(MKX_OBJECT(c));
    c = NULL;   
    return 1;
  }
  Mkx_Object_unreference(MKX_OBJECT(d));
  d = NULL;
  Mkx_Object_unreference(MKX_OBJECT(c));
  c = NULL;   
  *result = ray;
  return Mkx_Status_Success;
}
