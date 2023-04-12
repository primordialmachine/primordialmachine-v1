/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_OS_H_INCLUDED)
#define CC_OS_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>

#include "cc_os_hash.h"
#include "cc_os_memory.h"

#if defined(_MSC_VER)
  #define CC_NORETURN() __declspec(noreturn)
#else
  #error(environment not supported)
#endif

#if defined(_MSC_VER)
  #pragma warning(disable : 4200) // Disable "nonstandard extension used : zero-sized array in struct/union".
  #pragma warning(disable : 4201) // Disable "nonstandard extension used : nameless struct/union".
  #pragma warning(disable : 4324) // Disable "'struct_name' : structure was padded due to __declspec(align()))".
  #pragma warning(disable : 4100) // Disable "'identifier' : unreferenced formal parameter".
#else
  #error(environment not supported)
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Forward declaration. */
typedef struct cc_cstring cc_cstring;

/* Forward declaration. */
typedef struct cc_cstring_buffer cc_cstring_buffer;

/* Forward declaration. */
typedef struct cc_jt cc_jt;

/* Forward declaration. */
typedef struct cc_object cc_object;

/* Forward declaration. */
typedef struct cc_type cc_type;

/* Forward declaration. */
typedef struct cc_arraylist cc_arraylist;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Jump Target for longjmp-style jumps.
struct cc_jt
{
  cc_jt* previous;
  jmp_buf env;
};

/// @brief Push a jump target on the jump target stack.
/// @param jt A pointer to a jump target.
void cc_push_jt(cc_jt* jt);

/// @brief Pop a jump target from the jump target stack.
void cc_pop_jt();

/// @brief Jump to the jump target on the top of the jump target stack.
CC_NORETURN() void cc_j();

CC_NORETURN() void cc_error(int status);

/// @brief Macro to unconditionally cast an expression into a cc_visit_callback_ptr expression.
/// @param expr The expression to cast.
/// @remark
/// The expression
/// <code>
/// CC_VISIT_CALLBACK_PTR(e)
/// </code>
/// expands to
/// <code>
/// ((cc_visit_callback_ptr)(e))
/// </code>
#define CC_VISIT_CALLBACK_PTR(expr) ((cc_visit_callback_ptr)(expr))

/// @brief Type definition of a cc_visit_callback function.
/// @param object The object to visit.
typedef void (cc_visit_callback)(cc_object* object);

/// @brief Type definition of a pointer to a cc_visit_callback function.
typedef cc_visit_callback* cc_visit_callback_ptr;

/// @brief Macro to unconditionally cast an expression into a cc_visit_callback_ptr expression.
/// @param expr The expression to cast.
/// @remark
/// The expression
/// <code>
/// CC_VISIT_CALLBACK_PTR(e)
/// </code>
/// expands to
/// <code>
/// ((cc_visit_callback_ptr)(e))
/// </code>
#define CC_FINALIZE_CALLBACK_PTR(expr) ((cc_finalize_callback_ptr)(expr))

/// @brief Type definition of a cc_finalize_callback function.
/// @param object The object to finalize.
typedef void (cc_finalize_callback)(cc_object* object);

/// @brief Type definition of a pointer to a cc_finalize_callback function.
typedef cc_finalize_callback *cc_finalize_callback_ptr;

struct cc_type
{
  cc_type* next;
  size_t hash_value;
  cc_type* parent;
  size_t object_size;
  cc_visit_callback* visit;
  cc_finalize_callback* finalize;
};

struct cc_object
{
  cc_object* next;
  cc_type* type;
};

/// @brief Utility macro to add a prefix and a suffix to a name in order to avoid naming clashes.
/// @param NAME The name to decorate.
#define CC_DECORATE(NAME) NAME##_f612c3ed_bff9_4751_b7b5_421f0ebd8850

cc_type* CC_DECORATE(cc_object_get_type)();

/// @brief Macro to forward declare a class.
/// @param SELF The name of the class e.g. cc_string.
#define CC_FORWARD_DECLARE_CLASS(SELF) \
  typedef struct SELF SELF;

/// @brief Macro to declare a non-abstract class.
/// @param SELF The name of the class e.g. cc_string.
/// @param PARENT The name of the parent class e.g. cc_object.
#define CC_DECLARE_CLASS(SELF, PARENT) \
  cc_type* CC_DECORATE(SELF##_get_type)(); \
  typedef struct SELF SELF;

/// @brief Macro to declare an abstract class.
/// @param SELF The name of the class e.g. cc_string.
/// @param PARENT The name of the parent class e.g. cc_object.
#define CC_DECLARE_ABSTRACT_CLASS(SELF, PARENT) \
  CC_DECLARE_CLASS(SELF, PARENT)

/// @brief Macro to define a non-abstract class.
/// @param SELF The name of the class e.g. cc_string.
/// @param PARENT The name of the parent class e.g. cc_object.
#define CC_DEFINE_CLASS(SELF, PARENT, VISIT, FINALIZE, STATIC_INITIALIZER, STATIC_UNINITIALIZER) \
  static cc_type *CC_DECORATE(SELF##_type) = NULL; \
  cc_type* CC_DECORATE(SELF##_get_type)() \
  { \
    if (!CC_DECORATE(SELF##_type)) \
    { \
      const cc_type_spec spec =  { \
        .object_size = sizeof(SELF), \
        .parent = CC_DECORATE(PARENT##_get_type)(), \
        .visit = CC_VISIT_CALLBACK_PTR(VISIT), \
        .finalize = CC_FINALIZE_CALLBACK_PTR(FINALIZE), \
      }; \
      CC_DECORATE(SELF##_type) = cc_type_get_or_create(&spec); \
    } \
    return CC_DECORATE(SELF##_type); \
  }

/// @brief Macro to define an abstract class.
/// @param SELF The name of the class e.g. cc_string.
/// @param PARENT The name of the parent class e.g. cc_object.
#define CC_DEFINE_ABSTRACT_CLASS(SELF, PARENT, VISIT, FINALIZE, STATIC_INITIALIZER, STATIC_UNINITIALIZER) \
  CC_DEFINE_CLASS(SELF, PARENT, VISIT, FINALIZE, STATIC_INITIALIZER, STATIC_UNINTIALIZER)

#define CC_BEGIN_CTOR(TYPE) \
  cc_type* CC_DECORATE(type) = CC_DECORATE(TYPE##_get_type)();

#define CC_END_CTOR(TYPE) \
  ((cc_object*)self)->type = CC_DECORATE(type);

/// @brief Startup the environment.
/// @return @a true on success, @a false on failure.
bool cc_startup();

/// @brief Shutdown the environment.
void cc_shutdown();

void cc_visit(cc_object* o);

#if defined(CC_VISIT)
#error(CC_VISIT already defined)
#endif
#define CC_VISIT(expr) \
  if ((expr) != NULL) \
  { \
    cc_visit((cc_object*)(expr)); \
  }

/// @brief Get or a create a type.
/// @param parent A pointer to the parent type or a null pointer.
/// @param object_size The object size.
/// @param visit A pointer to the cc_visit_callback function or a null pointer.
/// @param finalize A pointer to the cc_finalize_callback function or a null pointer.
/// @return A pointer to the type or a null pointer.
/// @error CC_ENOMEM An allocation failed.
/// @error CC_EINVAL @a parent is not null and <code>parent->object_size</code> is greater than @a object_size
/// @remark This funcion sets the status variable to an error status on failure and returns NULL.
cc_type* cc_type_get_or_create_no_raise(cc_type* parent, size_t object_size, cc_visit_callback_ptr visit, cc_finalize_callback_ptr finalize);

typedef struct cc_type_spec {
  /// @brief A pointer to the parent type or a null pointer.
  cc_type* parent;
  /// @brief The object size.
  size_t object_size;
  /// @brief A pointer to the cc_visit_callback function or a null pointer.
  cc_visit_callback_ptr visit;
  /// @brief A pointer to the cc_finalize_callback function or a null pointer.
  cc_finalize_callback_ptr finalize;
} cc_type_spec;

/// @brief Get or a create a type.
/// @param spec A pointer to a cc_type_spec object which provides the information on the type.
/// @return A pointer to the type.
/// @error CC_ENOMEM An allocation failed.
/// @error CC_EINVAL @a parent is not null and <code>parent->object_size</code> is greater than @a object_size
/// @remark This funcion sets the status variable to an error status on failure and then jumps.
/// Call cc_get_status() to get extended error information.
cc_type* cc_type_get_or_create(const cc_type_spec* spec);

/// @brief Allocate an object.
/// @param type A pointer to the type.
/// @return A pointer to the object on success, a null pointer on failure.
/// @error CC_EINVAL @a type is a null pointer.
/// @error CC_ENOMEM An allocation failed.
cc_object* cc_object_allocate_no_raise_2(cc_type* type);

/// @brief Allocate an object.
/// @param type The type of the object.
/// @return A pointer to the object.
/// @raise CC_EINVAL @a type is a null pointer.
/// @raise CC_ENOMEM An allocation failed.
cc_object* cc_object_allocate_2(cc_type* type);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define CC_EINVAL (1) /* Invalid argument */
#define CC_ENOENT (2) /* No such file or directory */
#define CC_ENOMEM (3) /* Out of memory */
#define CC_EPERM (4)  /* Operation not permitted */
#define CC_EOVERFLOW (5) /* Value too large to be stored in data type */


#define CC_SUCCESS (0)

/// @brief Get the value of the status variable.
/// @return The value.
int cc_get_status();

/// @brief Set the status variable value.
/// @param status The value.
void cc_set_status(int status);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define CC_UNREACHABLE_ERROR() \
  cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: unreachable code reached\n", __FILE__, __LINE__); \
  cc_error(CC_EINVAL);

#define CC_ASSERTION_FAILED_ERROR(expr_string) \
  cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: assertion `%s` failed\n", __FILE__, __LINE__, expr_string); \
  cc_error(CC_EINVAL); \

/// @brief Assert a pointer expression is not null.
/// @param expr The expression.
#define CC_ASSERT_NOT_NULL(expr) \
  if ((expr) == NULL) \
  { \
    CC_ASSERTION_FAILED_ERROR(#expr " != NULL"); \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char* cc_asprintf(const char* format, ...);

char* cc_to_upper(const char* w);

char* cc_strdup(const char* w);

int cc_strcmp(const char* v, const char* w);

void cc_replace_c(char* s, char c1, char c2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A zero-terminated string.
/// @extends cc_object
CC_DECLARE_CLASS(cc_cstring, cc_object)

struct cc_cstring
{
  cc_object parent;
  char* p;
};

/// @brief Create a string.
/// @param p A pointer to an array of Bytes.
/// Reads Bytes from @a p until a zero terminator is encountered.
/// The Bytes read are then used to create the string.
/// @return The string.
cc_cstring* cc_cstring_create(const char *p);

/// @brief Create a string.
/// @param p A pointer to an array of Bytes.
/// Reads Bytes from @a p until either
/// - @a n Bytes were read or
/// - a zero terminator is encountered.
/// The Bytes read are then used to create the string.
/// @param n The maximum number of Bytes to use.
/// @return The string.
cc_cstring* cc_cstring_create_l(const char* p, size_t n);

cc_cstring* cc_cstring_to_upper(cc_cstring* self);

/// @brief Get if this string is equal to the other string.
/// @param self This string.
/// @param other The other string.
/// @return @a true if this string is equal to the other string, @a false otherwise.
bool cc_cstring_equal(cc_cstring const* const self, cc_cstring const* const y);

/// @brief Get the length, in Bytes, of this string.
/// @param self This string.
/// @return The length, in Bytes, of this string.
size_t cc_cstring_get_length(cc_cstring const* const self);

/// @brief Split a string into an ordered list of substrings.
/// @param self This string.
/// @param separator The separator. Must not be '\0'.
/// @param list A pointer to a list. If this is null, then a list is created.
/// The sub strings are appended to that list.
/// @param separator Can bw any value between 0 and 255. Can be '\0'.
/// @return A pointer to the list the elements were appended to.
cc_arraylist* cc_cstring_split(cc_cstring const* const self, char separator, cc_arraylist* list);

/// @brief Get if a string ends with another string.
/// @param string The string.
/// @param suffix The suffix.
/// @return @a true if  @a string ends with @a suffix, @a false otherwise.
bool cc_cstring_ends_with(cc_cstring const* string, cc_cstring const* suffix);

/// @brief Concatenate two string.
/// @param prefix The prefix.
/// @param suffix The suffix.
/// @return The concatenation of @a prefix with @a suffix. 
cc_cstring* cc_cstring_concatenate(cc_cstring const* prefix, cc_cstring const* suffix);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // CC_OS_H_INCLUDED
