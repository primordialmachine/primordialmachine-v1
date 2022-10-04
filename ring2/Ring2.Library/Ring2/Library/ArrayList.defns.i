
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
ensureFreeCapacity
  (
    Ring2_Context* context,
    Ring2_ArrayList* self,
    int64_t required
  )
{ CollectionUtilities_ensureFreeCapacity(context, &self->values, &self->size, &self->capacity, required); }

static void
grow
  (
    Ring2_ArrayList* self,
    int64_t required
  )
{ CollectionUtilities_grow(Ring2_Context_get(), &self->values, &self->size, &self->capacity, required); }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collection
static void
clear
  (
    Ring2_ArrayList* self
  )
{ self->size = 0; }

// Ring2.Collection
static int64_t
getSize
  (
    Ring2_ArrayList const* self
  )
{ return self->size; }

// Ring2.Collection
static bool
isEmpty
  (
    Ring2_ArrayList const* self
  )
{ return 0 == self->size; }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.List
static void
append
  (
    Ring2_ArrayList* self,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, self->size); }

// Ring2.List
static Ring2_Value
getAt
  (
    Ring2_ArrayList const* self,
    int64_t index 
  )
{
  if (index < 0 || index >= self->size) {
    fprintf(stderr, "index out of bounds");
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return *(self->values + index);
}

// Ring2.List
static void
insertAt
  (
    Ring2_ArrayList* self,
    int64_t index,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, index); }

// Ring2.List
static void
prepend
  (
    Ring2_ArrayList* self,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, 0); }

// Ring2.List
static void
removeAt
  (
    Ring2_ArrayList* self,
    int64_t index 
  )
{ CollectionUtilities_removeAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, index); }

// Ring2.List
static void
removeAtFast
  (
    Ring2_ArrayList* self,
    int64_t index 
  )
{ CollectionUtilities_removeAtFast(Ring2_Context_get(), &self->values, &self->size, &self->capacity, index); }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_ArrayList_destruct
  (
    Ring2_ArrayList *self
  )
{
  if (self->values) {
    Ring1_Memory_deallocate(self->values);
    self->values = NULL;
  }
}

static void
Ring2_ArrayList_visit
  (
    Ring2_ArrayList *self
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
implement_Ring2_List
  (
    Ring2_List_Dispatch* self
  )
{
  self->append = (void (*)(Ring2_List *, Ring2_Value)) & append;
  self->getAt = (Ring2_Value(*)(Ring2_List const *, int64_t index)) & getAt;
  self->insertAt = (void (*)(Ring2_List*, int64_t, Ring2_Value)) & insertAt;
  self->prepend = (void (*)(Ring2_List *, Ring2_Value)) & prepend;
  self->removeAt = (void (*)(Ring2_List*, int64_t)) & removeAt;
  self->removeAtFast = (void (*)(Ring2_List*, int64_t)) & removeAtFast;
}

static void 
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring2_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collection);
  Machine_ClassType_implement(self, Ring2_List_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_List);
}