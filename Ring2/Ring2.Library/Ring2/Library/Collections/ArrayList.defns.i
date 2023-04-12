
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
ensureFreeCapacity
  (
    Ring2_Context* context,
    Ring2_Collections_ArrayList* self,
    int64_t required
  )
{ CollectionUtilities_ensureFreeCapacity(context, &self->values, &self->size, &self->capacity, required); }

static void
grow
  (
    Ring2_Collections_ArrayList* self,
    int64_t required
  )
{ CollectionUtilities_grow(Ring2_Context_get(), &self->values, &self->size, &self->capacity, required); }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_ArrayList* self
  )
{ self->size = 0; }

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_ArrayList const* self
  )
{ return self->size; }

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_ArrayList const* self
  )
{ return 0 == self->size; }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collections.List
static void
append
  (
    Ring2_Collections_ArrayList* self,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, self->size); }

// Ring2.Collections.List
static Ring2_Value
getAt
  (
    Ring2_Collections_ArrayList const* self,
    int64_t index 
  )
{
  if (index < 0 || index >= self->size) {
    Ring1_Log_error("index out of bounds");
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return *(self->values + index);
}

// Ring2.Collections.List
static void
insertAt
  (
    Ring2_Collections_ArrayList* self,
    int64_t index,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, index); }

// Ring2.Collections.List
static void
prepend
  (
    Ring2_Collections_ArrayList* self,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, 0); }

// Ring2.Collections.List
static void
removeAt
  (
    Ring2_Collections_ArrayList* self,
    int64_t index 
  )
{ CollectionUtilities_removeAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, index); }

// Ring2.Collections.List
static void
removeAtFast
  (
    Ring2_Collections_ArrayList* self,
    int64_t index 
  )
{ CollectionUtilities_removeAtFast(Ring2_Context_get(), &self->values, &self->size, &self->capacity, index); }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_Collections_ArrayList_destruct
  (
    Ring2_Collections_ArrayList *self
  )
{
  if (self->values) {
    Ring1_Memory_deallocate(self->values);
    self->values = NULL;
  }
}

static void
Ring2_Collections_ArrayList_visit
  (
    Ring2_Collections_ArrayList *self
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
implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  )
{
  self->clear = (void (*)(Ring2_Collections_Collection*)) & clear;
  self->getSize = (int64_t (*)(Ring2_Collections_Collection const*)) & getSize;
  self->isEmpty = (bool (*)(Ring2_Collections_Collection const*)) & isEmpty;
}

static void
implement_Ring2_Collections_List
  (
    Ring2_Collections_List_Dispatch* self
  )
{
  self->append = (void (*)(Ring2_Collections_List *, Ring2_Value)) & append;
  self->getAt = (Ring2_Value(*)(Ring2_Collections_List const *, int64_t index)) & getAt;
  self->insertAt = (void (*)(Ring2_Collections_List*, int64_t, Ring2_Value)) & insertAt;
  self->prepend = (void (*)(Ring2_Collections_List *, Ring2_Value)) & prepend;
  self->removeAt = (void (*)(Ring2_Collections_List*, int64_t)) & removeAt;
  self->removeAtFast = (void (*)(Ring2_Collections_List*, int64_t)) & removeAtFast;
}

static void 
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring2_Collections_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collections_Collection);
  Machine_ClassType_implement(self, Ring2_Collections_List_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collections_List);
}
