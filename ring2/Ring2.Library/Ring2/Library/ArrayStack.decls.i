
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Ring2_ArrayStack_Class {
  Machine_Object_Class _parent;
};

struct Ring2_ArrayStack {
  Machine_Object _parent;
  Ring2_Value* values;
  int64_t size;
  int64_t capacity;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
ensureFreeCapacity
  (
    Ring2_ArrayStack* self,
    int64_t required
  );

static void
grow
  (
    Ring2_ArrayStack* self,
    int64_t required
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Collection
static void
clear
  (
    Ring2_ArrayStack* self
  );

// Ring2.Collection
static int64_t
getSize
  (
    Ring2_ArrayStack const* self
  );

// Ring2.Collection
static bool
isEmpty
  (
    Ring2_ArrayStack const* self
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Ring2.Stack
static Ring2_Value
pop
  (
    Ring2_ArrayStack* self
  );

// Ring2.Stack
static void
push
  (
    Ring2_ArrayStack* self,
    Ring2_Value value
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void
Ring2_ArrayStack_destruct
  (
    Ring2_ArrayStack* self
  );

static void
Ring2_ArrayStack_visit
  (
    Ring2_ArrayStack* self
  );

static void
implement_Ring2_Collection
  (
    Ring2_Collection_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
