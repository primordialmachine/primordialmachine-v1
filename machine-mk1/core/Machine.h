/// @file Machine.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_H_INCLUDED)
#define MACHINE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "./Runtime/PrimitiveTypes.h"
#include "./Runtime/Status.h"
#include <setjmp.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of the <code>String</code> type.
typedef struct Machine_String Machine_String;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of the <code>Object</code> type.
typedef struct Machine_Object Machine_Object;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Machine_Value Machine_Value;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Machine_JumpTarget Machine_JumpTarget;

struct Machine_JumpTarget {
  Machine_JumpTarget* previous;
  jmp_buf environment;
};

/**
 * @brief Push a jump target on the jump target stack.
 * @param jumpTarget A pointer to the jump target.
 */
void Machine_pushJumpTarget(Machine_JumpTarget *jumpTarget);

/**
 * @brief Pop a jump target from the jump target stack.
 */
void Machine_popJumpTarget();

/**
 * @brief Jump to the top of the jump target stack.
 * @warning Undefined if the jump target stack is empty.
 */
NORETURN void Machine_jump();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief Type of a finalize callback function.
 * @param object The object to finalize.
 */
typedef void (Machine_FinalizeCallback)(void* object);

/**
 * @brief Type of a visit callback function.
 * @param object The object to visit.
 */
typedef void (Machine_VisitCallback)(void*);

typedef struct Machine_Tag Machine_Tag;
#define Machine_Flag_White (1)
#define Machine_Flag_Black (2)
#define Machine_Flag_Gray (Machine_Flag_White | Machine_Flag_Black)
#define Machine_Flag_Root (4)

struct Machine_Tag {
  Machine_Tag* next;
  Machine_Tag* gray;
  uint64_t lockCount;
  uint32_t flags;
  size_t size;
  Machine_VisitCallback* visit;
  Machine_FinalizeCallback* finalize;
};

/**
 * @brief Startup the machine.
 * @warning Undefined if the machine is already initialized.
 * @return #Machine_Status_Success on success, a non-zero Machine_Status value on failure.
 */
int Machine_startup();

/**
 * @brief Shutdown the machine.
 * Finalize and deallocate all payloads.
 * @warning Undefined if the machine is already uninitialized.
 */
void Machine_shutdown();

void Machine_update();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief Allocate a payload.
 * @param size The size, in Bytes, of the payload.
 * @param visit A pointer to the Machine_VisitCallback function for the object or a null pointer.
 * @param finalize A pointer to the Machine_FinalizeCallback function for the object or a null pointer.
 * @return A pointer to the object on success, a null pointer on failure.
 */
void* Machine_allocate(size_t size, Machine_VisitCallback *visit, Machine_FinalizeCallback *finalize);

/**
 * @undefined Invoked outside of visit callback.
 */
void Machine_visit(void* object);

/// @brief Increment the lock count of an object.
/// @param object A pointer to the object.
void Machine_lock(void* object);

/// @brief Decrement the lock count of an object.
/// @param object A pointer to the object.
void Machine_unlock(void* object);

/**
 * @brief Set if an object is marked as a root object.
 * @undefined Invoked in visit callback or finalize callback.
 */
void Machine_setRoot(void* object, bool isRoot);

/**
 * @brief Get if an object is marked as a root object.
 * @param object the object.
 */
bool Machine_getRoot(void* object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Boolean (1)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Integer (2)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Object (3)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_ForeignProcedure (4)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Real (5)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_String (6)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Void (7)



typedef struct Machine_Value {

  uint8_t tag;

  union {

    Machine_Boolean booleanValue;

    Machine_Integer integerValue;

    Machine_Object* objectValue;

    Machine_ForeignProcedure* foreignProcedureValue;

    Machine_Real realValue;

    Machine_String* stringValue;

    Machine_Void voidValue;

  };

} Machine_Value;


INLINE void Machine_Value_setBoolean(Machine_Value* self, Machine_Boolean value) {
  self->tag = Machine_ValueFlag_Boolean;
  self->booleanValue = value;
}

INLINE Machine_Boolean Machine_Value_getBoolean(const Machine_Value* self) {
  return self->booleanValue;
}

INLINE bool Machine_Value_isBoolean(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Boolean;
}


INLINE void Machine_Value_setInteger(Machine_Value* self, Machine_Integer value) {
  self->tag = Machine_ValueFlag_Integer;
  self->integerValue = value;
}

INLINE Machine_Integer Machine_Value_getInteger(const Machine_Value* self) {
  return self->integerValue;
}

INLINE bool Machine_Value_isInteger(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Integer;
}


INLINE void Machine_Value_setObject(Machine_Value* self, Machine_Object* value) {
  self->tag = Machine_ValueFlag_Object;
  self->objectValue = value;
}

INLINE Machine_Object* Machine_Value_getObject(const Machine_Value* self) {
  return self->objectValue;
}

INLINE bool Machine_Value_isObject(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Object;
}


INLINE void Machine_Value_setForeignProcedure(Machine_Value* self, Machine_ForeignProcedure* value) {
  self->tag = Machine_ValueFlag_ForeignProcedure;
  self->foreignProcedureValue = value;
}

INLINE Machine_ForeignProcedure* Machine_Value_getForeignProcedure(const Machine_Value* self) {
  return self->foreignProcedureValue;
}

INLINE bool Machine_Value_isForeignProcedure(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_ForeignProcedure;
}


INLINE void Machine_Value_setReal(Machine_Value* self, Machine_Real value) {
  self->tag = Machine_ValueFlag_Real;
  self->realValue = value;
}

INLINE Machine_Real Machine_Value_getReal(const Machine_Value* self) {
  return self->realValue;
}

INLINE bool Machine_Value_isReal(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Real;
}


INLINE void Machine_Value_setString(Machine_Value* self, Machine_String* value) {
  self->tag = Machine_ValueFlag_String;
  self->stringValue = value;
}

INLINE Machine_String* Machine_Value_getString(const Machine_Value* self) {
  return self->stringValue;
}

INLINE bool Machine_Value_isString(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_String;
}


INLINE void Machine_Value_setVoid(Machine_Value* self, Machine_Void value) {
  self->tag = Machine_ValueFlag_Void;
  self->voidValue = value;
}

INLINE Machine_Void Machine_Value_getVoid(const Machine_Value* self) {
  return self->voidValue;
}

INLINE bool Machine_Value_isVoid(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Void;
}

INLINE void Machine_Value_visit(Machine_Value* self) {
  switch (self->tag) {
    case Machine_ValueFlag_Object:
      Machine_visit(self->objectValue);
    break;
    case Machine_ValueFlag_String:
      Machine_visit(self->stringValue);
    break;
  };
}

bool Machine_Value_isEqualTo(const Machine_Value* x, const Machine_Value* y);

size_t Machine_Value_getHashValue(const Machine_Value* x);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Load a <code>Boolean</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadBoolean(Machine_Boolean value);

/// @brief Load an <code>Integer</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadInteger(Machine_Integer value);

/// @brief Load a <code>ForeignProcedure</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadForeignProcedure(Machine_ForeignProcedure* value);

/// @brief Load an <code>Object</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadObject(Machine_Object* value);

/// @brief Load a <code>Real</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadReal(Machine_Real value);

/// @brief Load a <code>String</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadString(Machine_String* value);

/// @brief Load a <code>Void</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadVoid(Machine_Void value);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** C level representation of a class type. */
typedef struct Machine_ClassType Machine_ClassType;

/** @brief Tag flag indicating a class type object tag. */
#define Machine_Flag_Class (32)

typedef struct Machine_ClassObjectTag {
  Machine_ClassType* classType;
  Machine_Tag tag;
} Machine_ClassObjectTag;

/// @brief Invoked when the class type is removed.
typedef void (Machine_ClassTypeRemovedCallback)();

/**
 * @brief Type of an object visit callback.
 * @param self A pointer to the object.
 */
typedef void (Machine_ClassObjectVisitCallback)(void* self);

/**
 * @brief Type of an object visiti callback.
 * @param self A pointer to the object.
 * @param numberOfArguments The number of elements in the array pointed to by @a arguments.
 * @param arguments A pointer to an array of @a numberOfArguments arguments.
 */
typedef void (Machine_ClassObjectConstructCallback)(void* self, size_t numberOfArguments, const Machine_Value* arguments);

/**
 * @brief Type of an object destruct callback.
 * @param self A pointer to the object.
 */
typedef void (Machine_ClassObjectDestructCallback)(void* self);

typedef struct Machine_Object {
  size_t(*getHashValue)(const Machine_Object* x);
  bool(*isEqualTo)(const Machine_Object* x, const Machine_Object* y);
} Machine_Object;

Machine_ClassType* Machine_Object_getClassType();

/// @brief Get the hash value of this object.
/// @param self This object.
/// @return The hash value.
size_t Machine_Object_getHashValue(const Machine_Object* self);

/// @brief Get if an object is equal to another object.
/// @param self This object.
/// @param other The other object.
/// @return @a true if this object is equal to another object, @a false otherwise.
bool Machine_Object_isEqualTo(const Machine_Object* self, const Machine_Object* other);

/// @brief Construct this object.
/// @param self This object.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_Object_construct(Machine_Object* self, size_t numberOfArguments, const Machine_Value* arguments);

/**
 * @param visit Pointer to a Machine_ObjectVisitCallback function or a null pointer.
 * @param construct Pointer to a Machine_ObjectConstructCallback function or a null pointer.
 * @param destruct Pointer to a Machine_ObjectDestructCallback function or a null pointer.
 * @retrn A pointer to the classed type.
 */
Machine_ClassType* Machine_createClassType(Machine_ClassType* parent, size_t size, Machine_ClassTypeRemovedCallback* typeRemoved, Machine_ClassObjectVisitCallback* visit, Machine_ClassObjectConstructCallback* construct, Machine_ClassObjectDestructCallback* destruct);

/**
 * @brief Create an object.
 * @param type A pointer to the class type.
 * @param numberOfArguments The number of elements in the array pointed to by @a arguments.
 * @param arguments A pointer to an array of @a numberOfArguments elements.
 */
Machine_Object *Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, const Machine_Value* arguments);

/// @brief Set the class type of an object.
/// @param object The object.
/// @param classType The class type.
void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType);

/// @brief Get the class type of an object.
/// @param object The object.
/// @return The class type.
Machine_ClassType* Machine_getClassType(Machine_Object* object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_DECLARE_CLASSTYPE(NAME) \
  typedef struct NAME NAME; \
  Machine_ClassType *NAME##_getClassType();

#define MACHINE_DEFINE_CLASSTYPE(NAME) \
  static Machine_ClassType *g_##NAME##_ClassType = NULL; \
\
  static void NAME##_onTypeDestroyed() { \
    g_##NAME##_ClassType = NULL; \
  }

#define MACHINE_DEFINE_CLASSTYPE_EX(THIS_TYPE, PARENT_TYPE, VISIT, CONSTRUCT, DESTRUCT) \
  Machine_ClassType* THIS_TYPE##_getClassType() { \
    if (!g_##THIS_TYPE##_ClassType) { \
      g_##THIS_TYPE##_ClassType = \
        Machine_createClassType \
          ( \
            PARENT_TYPE##_getClassType(), \
            sizeof(THIS_TYPE), \
            (Machine_ClassTypeRemovedCallback*)&THIS_TYPE##_onTypeDestroyed, \
            (Machine_ClassObjectVisitCallback*)VISIT, \
            (Machine_ClassObjectConstructCallback*)CONSTRUCT, \
            (Machine_ClassObjectDestructCallback*)DESTRUCT \
          ); \
    } \
    return g_##THIS_TYPE##_ClassType; \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_ASSERT_NOTNULL(e) \
  if (!(e)) \
  { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "e == NULL\n"); \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief If defined and @a 1, then logging functionality is compiled into the machine.
 */
#define MACHINE_WITH_LOG (1)

#if defined(MACHINE_WITH_LOG) && 1 == MACHINE_WITH_LOG

#define Machine_LogFlags_ToErrors (2)
#define Machine_LogFlags_ToWarnings (1)
#define Machine_LogFlags_ToInformations (0)

/**
 * @brief Write a log message.
 * @param flags Bitwise or of Machine_LogFlags_* constants.
 */
void Machine_log(int flags, const char* file, int line, const char* format, ...);

#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_H_INCLUDED
