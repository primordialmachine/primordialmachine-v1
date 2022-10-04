
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Ring2_ArrayList_Class {
  Machine_Object_Class _parent;
};

struct Ring2_ArrayList {
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
    Ring2_ArrayList* self,
    int64_t required
  );

static void
grow
  (
    Ring2_ArrayList* self,
    int64_t required
  );
  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collection
static void
clear
  (
    Ring2_ArrayList* self
  );

// Ring2.Collection
static int64_t
getSize
  (
    Ring2_ArrayList const* self
  );

// Ring2.Collection
static bool
isEmpty
  (
    Ring2_ArrayList const* self
  );
  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.List
static void
append
  (
    Ring2_ArrayList* self,
    Ring2_Value value
  );

// Ring2.List
static Ring2_Value
getAt
  (
    Ring2_ArrayList const* self,
    int64_t index
  );

// Ring2.List
static void
insertAt
  (
    Ring2_ArrayList* self,
    int64_t index,
    Ring2_Value value
  );

// Ring2.List
static void
prepend
  (
    Ring2_ArrayList* self,
    Ring2_Value value
  );

// Ring2.List
static void
removeAt
  (
    Ring2_ArrayList* self,
    int64_t index
  );

// Ring2.List
static void
removeAtFast
  (
    Ring2_ArrayList* self,
    int64_t index
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_ArrayList_destruct
  (
    Ring2_ArrayList* self
  );

static void
Ring2_ArrayList_visit
  (
    Ring2_ArrayList* self
  );
  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
implement_Ring2_Collection
  (
    Ring2_Collection_Dispatch* self
  );

static void
implement_Ring2_List
  (
    Ring2_List_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
