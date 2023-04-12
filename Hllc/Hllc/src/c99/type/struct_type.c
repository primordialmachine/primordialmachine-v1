#include "c99/type/struct_type.h"

static void
cc_c99_struct_type_visit
  (
    cc_c99_struct_type* self
  )
{
  CC_VISIT(self->name);
}

CC_DEFINE_CLASS(cc_c99_struct_type, cc_c99_type, NULL, NULL, NULL, NULL)

cc_c99_struct_type*
cc_c99_struct_type_create
  (
    cc_cstring* name
  )
{
  cc_c99_struct_type* self = (cc_c99_struct_type*)cc_object_allocate_2(CC_DECORATE(cc_c99_struct_type_get_type)());
  ((cc_c99_type*)self)->kind = CC_C99_TYPE_KIND_STRUCT;
  self->name = name;
  return self;
}
