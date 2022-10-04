
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
grow
  (
    Ring2_ArrayStack* self,
    int64_t required
  )
{ CollectionUtilities_grow(Ring2_Context_get(), &self->values, &self->size, &self->capacity, required); }

static void
ensureFreeCapacity
  (
    Ring2_ArrayStack *self,
    int64_t required
  )
{ CollectionUtilities_ensureFreeCapacity(Ring2_Context_get(), &self->values, &self->size, &self->capacity, required); }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collection
static void
clear
  (
    Ring2_ArrayStack* self
  )
{ self->size = 0; }

// Ring2.Collection
static int64_t
getSize
  (
    Ring2_ArrayStack const* self
  )
{ return self->size; }

// Ring2.Collection
static bool
isEmpty
  (
    Ring2_ArrayStack const* self
  )
{ return 0 == self->size; }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Stack
static Ring2_Value
pop
  (
    Ring2_ArrayStack* self
  )
{
  Ring2_Value value = *(self->values + self->size - 1);
  self->size--;
  return value;
}

// Ring2.Stack
static void
push
  (
    Ring2_ArrayStack* self,
    Ring2_Value value
  )
{
  ensureFreeCapacity(self, 1);
  *(self->values + self->size) = value;
  self->size++;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_ArrayStack_destruct
  (
    Ring2_ArrayStack *self
  )
{
  if (self->values) {
    Ring1_Memory_deallocate(self->values);
    self->values = NULL;
  }
}

static void
Ring2_ArrayStack_visit
  (
    Ring2_ArrayStack *self
  )
{
  if (self->values) {
    Ring2_Gc* gc = Ring2_Gc_get();
    for (int64_t i = 0, n = self->size; i < n; ++i) {
      Ring2_Value_visit(gc, self->values + i);
    }
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
implement_Ring2_Collection
  (
    Ring2_Collection_Dispatch* self
  )
{
  self->clear = (void (*)(Ring2_Collection*)) & clear;
  self->getSize = (int64_t (*)(Ring2_Collection const*)) & getSize;
  self->isEmpty = (bool (*)(Ring2_Collection const*)) & isEmpty;
}

static void
implement_Ring2_Stack
  (
    Ring2_Stack_Dispatch* self
  )
{
  self->pop = (Ring2_Value (*)(Ring2_Stack *)) & pop;
  self->push = (void (*)(Ring2_Stack *, Ring2_Value)) & push;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring2_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collection);
  Machine_ClassType_implement(self, Ring2_Stack_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Stack);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
