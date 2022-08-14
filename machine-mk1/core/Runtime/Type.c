/// @file Runtime/Type.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Ring2/_Include.h"

#include "Ring1/InlineArray.h"
#include "Ring1/Status.h"

void
Machine_Type_ensureInitialized
  (
    Machine_Type* self
  )
{
  if (Machine_Type_isClass(self)) {
    Machine_ClassType_ensureInitialized((Machine_ClassType*)self);
  } else if (Machine_Type_isInterface(self)) {
    Machine_InterfaceType_ensureInitialized((Machine_InterfaceType*)self);
  }
}

// @internal
// @brief Get if is a class type @a x is a sub-type of a class type @a y.
// @param x The class type @a x.
// @param y The class type @a y.
// @return @a true if @a x is a sub-type of @a y, @a false otherwise.
static bool cnc(Machine_ClassType const* x, Machine_ClassType const* y) {
  Machine_ClassType const* z = x;
  do {
    if (z == y) {
      return true;
    }
    z = z->parent;
  } while (z != NULL);
  return false;
}

// @internal
// @brief Get if an interface type x is a sub-type of an interface type y.
// @param x The interface type @a x.
// @param y The interface type @a y.
// @return @a true if @a x is a sub-type of @a y, @a false otherwise.
static bool ini(Machine_InterfaceType const* x, Machine_InterfaceType const* y) {
  if (x == y) {
    return true;
  }
  for (size_t i = 0, n = x->extends.size; i < n; ++i) {
    Machine_InterfaceType const* z = (Machine_InterfaceType const*)Ring1_InlineArray_getAt(
        (Ring1_InlineArray*)&x->extends, i);
    if (ini(z, y)) {
      return true;
    }
  }
  return false;
}

// @internal
// @brief Get if a class type x is a sub-type of an interface type y.
// @param x The class type @a x.
// @param y The interface type @a y.
// @return @a true if @a x is a sub-type of @a y, @a false otherwise.
static bool cni(Machine_ClassType const* x, Machine_InterfaceType const* y) {
  // an interface implemented by x is a sub type of y
  // => x is a sub type of y
  for (size_t i = 0, n = ((Machine_ClassType*)x)->interfaces.implementations2.size; i < n; ++i) {
    Machine_InterfaceImplementation const* implementation
        = (Machine_InterfaceImplementation*)Ring1_InlineArray_getAt(
            &(((Machine_ClassType*)x)->interfaces.implementations2), i);
    if (ini(implementation->interfaceType, (Machine_InterfaceType const*)y)) {
      return true;
    }
  }
  // if x has a parent class and that parent class is a sub type of y
  // => x is a sub type of y
  if (((Machine_ClassType*)x)->parent) {
    return cni(((Machine_ClassType*)x)->parent, y);
  }
  // otherwise x is an ot a sub type of y.
  return false;
}

Ring1_CheckReturn() bool
Machine_Type_isSubTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  )
{
  if (!self || !other) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (self == other) {
    // CASE I.
    // self and other are the same type.
    return true;
  }
  if (Ring2_TypeFlag_isSet(other, Ring2_TypeFlags_Class)) {
    if (Ring2_TypeFlag_isSet(self, Ring2_TypeFlags_Class)) {
      // Case II.1.
      // self is class type.
      // other is class type.
      return cnc((Machine_ClassType const*)self, (Machine_ClassType const*)other);
    } else if (Ring2_TypeFlag_isSet(self, Ring2_TypeFlags_Interface)) {
      // CASE II.2.
      // self is an interface type.
      // other is a class type.
      return false;
    } else {
      // CASE II.3.
      return false;
    }
  } else if (Ring2_TypeFlag_isSet(other, Ring2_TypeFlags_Interface)) {
    if (Ring2_TypeFlag_isSet(self, Ring2_TypeFlags_Class)) {
      // CASE III.1.
      // self is class type.
      // other is interface type.
      return cni((Machine_ClassType const*)self, (Machine_InterfaceType const*)other);
    } else if (Ring2_TypeFlag_isSet(self, Ring2_TypeFlags_Interface)) {
      // CASE III.2.
      // self is an interface type.
      // other is an interface type.
      return ini((Machine_InterfaceType const*)self, (Machine_InterfaceType const*)other);
    } else {
      // CASE III.3.
      return false;
    }
  } else {
    // CASE IV.
    return false;
  }
}

Ring1_CheckReturn() bool
Machine_Type_isTrueSubTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  )
{ return self != other && Machine_Type_isSubTypeOf(self, other); }

Ring1_CheckReturn() bool
Machine_Type_isSuperTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  )
{ return Machine_Type_isSubTypeOf(other, self); }

Ring1_CheckReturn() bool
Machine_Type_isTrueSuperTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  )
{ return Machine_Type_isTrueSubTypeOf(other, self); }
