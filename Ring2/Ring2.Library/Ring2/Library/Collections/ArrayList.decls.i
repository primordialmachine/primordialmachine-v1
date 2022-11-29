
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Ring2_Collections_ArrayList_Class {
  Machine_Object_Class _parent;
};

struct Ring2_Collections_ArrayList {
  Machine_Object _parent;
  Ring2_Value* values;
  int64_t size;
  int64_t capacity;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
ensureFreeCapacity
  (
    Ring2_Context* context,
    Ring2_Collections_ArrayList* self,
    int64_t required
  );

static void
grow
  (
    Ring2_Collections_ArrayList* self,
    int64_t required
  );
  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_ArrayList* self
  );

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_ArrayList const* self
  );

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_ArrayList const* self
  );
  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collections.List
static void
append
  (
    Ring2_Collections_ArrayList* self,
    Ring2_Value value
  );

// Ring2.Collections.List
static Ring2_Value
getAt
  (
    Ring2_Collections_ArrayList const* self,
    int64_t index
  );

// Ring2.Collections.List
static void
insertAt
  (
    Ring2_Collections_ArrayList* self,
    int64_t index,
    Ring2_Value value
  );

// Ring2.Collections.List
static void
prepend
  (
    Ring2_Collections_ArrayList* self,
    Ring2_Value value
  );

// Ring2.Collections.List
static void
removeAt
  (
    Ring2_Collections_ArrayList* self,
    int64_t index
  );

// Ring2.Collections.List
static void
removeAtFast
  (
    Ring2_Collections_ArrayList* self,
    int64_t index
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_Collections_ArrayList_destruct
  (
    Ring2_Collections_ArrayList* self
  );

static void
Ring2_Collections_ArrayList_visit
  (
    Ring2_Collections_ArrayList* self
  );
  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  );

static void
implement_Ring2_Collections_List
  (
    Ring2_Collections_List_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
