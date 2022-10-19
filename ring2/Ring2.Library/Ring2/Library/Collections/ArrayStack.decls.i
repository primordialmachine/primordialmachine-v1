
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Ring2_Collections_ArrayStack_Class {
  Machine_Object_Class _parent;
};

struct Ring2_Collections_ArrayStack {
  Machine_Object _parent;
  Ring2_Value* values;
  int64_t size;
  int64_t capacity;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
ensureFreeCapacity
  (
    Ring2_Collections_ArrayStack* self,
    int64_t required
  );

static void
grow
  (
    Ring2_Collections_ArrayStack* self,
    int64_t required
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collection
static void
clear
  (
    Ring2_Collections_ArrayStack* self
  );

// Ring2.Colletions.Collection
static int64_t
getSize
  (
    Ring2_Collections_ArrayStack const* self
  );

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_ArrayStack const* self
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collections.Stack
static Ring2_Value
pop
  (
    Ring2_Collections_ArrayStack* self
  );

// Ring2.Collections.Stack
static void
push
  (
    Ring2_Collections_ArrayStack* self,
    Ring2_Value value
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_Collections_ArrayStack_destruct
  (
    Ring2_Collections_ArrayStack* self
  );

static void
Ring2_Collections_ArrayStack_visit
  (
    Ring2_Collections_ArrayStack* self
  );

static void
implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  );

static void
implement_Ring2_Collections_Stack
  (
    Ring2_Collections_Stack_Dispatch* self
  );


static void
implementInterfaces
  (
    Machine_ClassType* self
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
