// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/TypeDefinition.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_OBJECT_TYPEDEFINITION_H_INCLUDED)
#define MKX_OBJECT_TYPEDEFINITION_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/TypeDefinition.h' directly, include 'Mkx/Object.h' instead.")
#endif


/// @brief Grouping macro for implementing interface types in class types.
#define Mkx_Type_ImplementInterfaces(...) __VA_ARGS__

/// @brief Grouping macro for extending interface types in interface types.
#define Mkx_Type_ExtendInterfaces(...) __VA_ARGS__

/// @brief Macro to ensure that an interface ("the extending interface") extends another interface ("the extended interface").
/// @param EXTENDING The C name of the extending interface.
/// @param EXTENDED The C name of the extended interface.
#define Mkx_Type_ExtendInterface(EXTENDING, EXTENDED) \
  { \
    Mkx_InterfaceType *extending = MKX_INTERFACETYPE(g_##EXTENDING.type), \
                      *extended = MKX_INTERFACETYPE(MKX_TYPE_GET(EXTENDED)); \
    if (!extending || !extended) { \
      return Ring1_Status_NotFound; \
    } \
    if (Mkx_InterfaceType_addPrerequisite(extending, extended)) { \
      return Ring1_Status_InvalidOperation; \
    } \
  }

#define Mkx_Type_UseMemoryManager(CNAME) CNAME##_get()
#define Mkx_Type_UseDefaultMemoryManager() Mkx_Type_UseMemoryManager(Mkx_DefaultMemoryManager)


/// @brief Macro to define a class type.
/// @param NAME The name (as in the typesystem) of the type e.g. <code>"Mkx.Media.WindowManager</code>.
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_WindowManager</code>.
/// @param CUPPERCASENAME The upper case name (as in "C") of the type e.g. <code>MKX_MEDIA_WINDOWMANAGER</code>.
/// @param CPARENTNAME The name (as in "C") of the parent type e.g. <code>Mkx_Object</code>.
#define Mkx_Type_DefineClassType(NAME, CNAME, CUPPERCASENAME, CPARENTNAME, USEMEMORYMANAGER, IMPLEMENTINTERFACES) \
  Ring1_NonNull() static void \
  CNAME##_destruct \
    ( \
      CNAME* self \
    ); \
\
  Ring1_CheckReturn() Ring1_NonNull() static int \
  CNAME##_Dispatch_construct \
    ( \
      CNAME##_Dispatch* self \
    ); \
\
  Ring1_NonNull() static void \
  CNAME##_Dispatch_destruct \
    ( \
      CNAME##_Dispatch* self \
    ); \
\
  static Mkx_Type *g_##CNAME##_type = NULL; \
  static bool g_##CNAME##_interfacesImplementationsDone = false; \
\
  static inline void \
  CNAME##_typeRemoved \
    ( \
    ) \
  { \
    g_##CNAME##_interfacesImplementationsDone = false; \
    g_##CNAME##_type = NULL; \
  } \
\
  Mkx_Type* \
  __##CNAME##_getType__ \
    ( \
    ) \
  { \
    if (!g_##CNAME##_type) \
    { \
      Mkx_Type *parent = MKX_TYPE_GET(CPARENTNAME); \
      if (!parent) return NULL; \
      Mkx_ClassTypeRegistrationInfo info = \
      { \
        .name = NAME, \
        .parent = parent, \
        .destruct = (void (*)(void*)) & CNAME##_destruct, \
        .size = sizeof(CNAME), \
        .memoryManager = MKX_MEMORYMANAGER(USEMEMORYMANAGER), \
        .dispatchSize = sizeof(CNAME##_Dispatch), \
        .constructDispatch = MKX_OBJECT_CONSTRUCTDISPATCHFUNCTION(&CNAME##_Dispatch_construct), \
        .destructDispatch = MKX_OBJECT_DESTRUCTDISPATCHFUNCTION(&CNAME##_Dispatch_destruct), \
      }; \
      g_##CNAME##_type = Mkx_registerClassType(&CNAME##_typeRemoved, &info); \
    } \
    if (!g_##CNAME##_interfacesImplementationsDone) \
    { \
      IMPLEMENTINTERFACES \
      g_##CNAME##_interfacesImplementationsDone = true; \
    } \
    return g_##CNAME##_type; \
  }

typedef struct EnumerationDefinition
{
  Mkx_Type* type;
} EnumerationDefinition;

/// @brief Macro to define an enumeration type.
/// @param NAME The name (as in the typesystem) of the type e.g. <code>"Mkx.Media.PixelFormat"</code>.
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_PixelFormat</code>.
#define Mkx_Type_DefineEnumerationType(NAME, CNAME) \
  static EnumerationDefinition g_##CNAME = { .type = NULL }; \
\
  static inline void \
  CNAME##_typeRemoved \
    ( \
    ) \
  { g_##CNAME.type = NULL; } \
\
  Mkx_Type* \
  __##CNAME##_getType__ \
    ( \
    ) \
  { \
    if (!g_##CNAME.type) \
    { \
      g_##CNAME.type = Mkx_registerEnumerationType(NAME, &CNAME##_typeRemoved, sizeof(CNAME)); \
    } \
    return g_##CNAME.type; \
  }

typedef struct InterfaceDefinition
{
  Mkx_Type* type;
  struct
  {
    bool complete;
  } configuration;
} InterfaceDefinition;

/// @brief Macro to define an interface type.
/// @param NAME The name (as in the typesystem) of the type e.g. <code>"Mkx.Media.WindowManager"</code>.
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_WindowManager</code>.
/// @param CUPPERCASENAME The upper case name (as in "C") of the type e.g. <code>MKX_MEDIA_WINDOWMANAGER</code>.
#define Mkx_Type_DefineInterfaceType(NAME, CNAME, CUPPERCASENAME, EXTENDINTERFACES) \
  static InterfaceDefinition g_##CNAME## = { .type = NULL, .configuration.complete = false }; \
  \
  static inline void \
  CNAME##_typeRemoved \
    (\
    ) \
  { \
    g_##CNAME##.configuration.complete = false; \
    g_##CNAME##.type = NULL; \
  } \
  \
  static inline Ring1_Status \
  CNAME##_extendInterfaces \
    ( \
      Mkx_InterfaceType *extender \
    ) \
  { \
    EXTENDINTERFACES \
    return Ring1_Status_Success; \
  } \
  \
  Mkx_Type* \
  __##CNAME##_getType__ \
    ( \
    ) \
  { \
    if (!g_##CNAME.type) \
    { \
      g_##CNAME.type = Mkx_registerInterfaceType(NAME, &CNAME##_typeRemoved, NULL, sizeof(CNAME##_Dispatch)); \
      if (!g_##CNAME.type) return NULL; \
    } \
    if (!g_##CNAME.configuration.complete) \
    { \
      if (CNAME##_extendInterfaces(MKX_INTERFACETYPE(g_##CNAME.type))) \
      { \
        return NULL; \
      } \
      g_##CNAME.configuration.complete = true; \
    } \
    return g_##CNAME.type; \
  }


/// @brief Macro defining an implementation of an interface type (in a class type).
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_WindowManager</code>.
/// @param CFUNCTIONPTR A pointer to a implement interface function.
#define Mkx_Type_ImplementInterface(CCLASSNAME, CINTERFACENAME, CFUNCTIONPTR) \
  { \
    Mkx_Type* interfaceType = MKX_TYPE_GET(CINTERFACENAME); \
    if (Ring1_Unlikely(!interfaceType)) return NULL; \
    bool isClassType, isInterfaceType; \
    if (Ring1_Unlikely(Mkx_Type_isClassType(&isClassType, g_##CCLASSNAME##_type) || Mkx_Type_isInterfaceType(&isInterfaceType, interfaceType))) return NULL; \
    if (Ring1_Unlikely(!isClassType || !isInterfaceType)) return NULL; \
    if (Mkx_ClassType_addInterfaceImplementation(MKX_CLASSTYPE(g_##CCLASSNAME##_type), MKX_INTERFACETYPE(interfaceType), CFUNCTIONPTR)) return NULL; \
  }



#endif // MKX_OBJECT_TYPEDEFINITION_H_INCLUDED
