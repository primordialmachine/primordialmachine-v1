#include "c99/type/type.h"

#include "c99/type/bool_type.h"
#include "c99/type/enum_type.h"
#include "c99/type/floating_point_type.h"
#include "c99/type/integer_type.h"
#include "c99/type/struct_type.h"

CC_DEFINE_CLASS(cc_c99_type, cc_object, NULL, NULL, NULL, NULL)

static const char KEY[] = "cc:c99:types";

static void cc_c99_types_visit(cc_c99_types* self)
{
  CC_VISIT(self->BOOL);
  CC_VISIT(self->FLOAT);
  CC_VISIT(self->DOUBLE);
  CC_VISIT(self->INT);
}

static cc_c99_types* cc_c99_types_factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_c99_types_get_type)();
  cc_c99_types* self = (cc_c99_types*)cc_object_allocate_2(type);

  self->types = cc_arraylist_create(0);

  self->BOOL = (cc_c99_type*)cc_c99_bool_type_create(cc_cstring_create("bool"));
  cc_arraylist_append(self->types, (cc_object *)self->BOOL);

  self->FLOAT = (cc_c99_type*)cc_c99_bool_type_create(cc_cstring_create("float"));
  cc_arraylist_append(self->types, (cc_object*)self->FLOAT);

  self->DOUBLE = (cc_c99_type*)cc_c99_bool_type_create(cc_cstring_create("double"));
  cc_arraylist_append(self->types, (cc_object*)self->DOUBLE);

  self->INT = (cc_c99_type *)cc_c99_integer_type_create(cc_cstring_create("int"));
  cc_arraylist_append(self->types, (cc_object*)self->INT);

  return self;

}

DEFINE_COMPONENT(cc_c99_types, &cc_c99_types_factory, &cc_c99_types_visit, NULL)
