// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/ClassTypeDeclaration.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_OBJECT_TYPEDECLARATION_H_INCLUDED)
#define MKX_OBJECT_TYPEDECLARATION_H_INCLUDED


/// @brief Macro to declare a class type.
/// @param NAME The name (as in the typesystem) of the type e.g. <code>"Mkx.Media.WindowManager"</code>.
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_WindowManager</code>.
/// @param CUPPERCASENAME The upper case name (as in "C") of the type e.g. <code>MKX_MEDIA_WINDOWMANAGER</code>.
#define Mkx_Type_DeclareClassType(NAME, CNAME, CUPPERCASENAME) \
\
  Mkx_Type* \
  __##CNAME##_getType__ \
    ( \
    ); \
\
\
  typedef struct CNAME CNAME; \
\
  static inline CNAME * \
  CUPPERCASENAME \
    ( \
      void* pointer \
    ) \
  { return (CNAME *)pointer; } \
\
\
  typedef struct CNAME##_Dispatch CNAME##_Dispatch; \
\
  static inline CNAME##_Dispatch * \
  CUPPERCASENAME##_DISPATCH \
    ( \
      void* pointer \
    ) \
  { return (CNAME##_Dispatch *)pointer; }


/// @brief Macro to declare an enumeration type.
/// @param NAME The name (as in the typesystem) of the type e.g. <code>"Mkx.Media.PixelFormat"</code>.
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_PixelFormat</code>.
#define Mkx_Type_DeclareEnumerationType(NAME, CNAME) \
\
  Mkx_Type* \
  __##CNAME##_getType__ \
    ( \
    ); \
\
\
  typedef enum CNAME CNAME;


/// @brief Macro to declare an interface type.
/// @param NAME The name (as in the typesystem) of the type e.g. <code>"Mkx.Media.WindowManager"</code>.
/// @param CNAME The name (as in "C") of the type e.g. <code>Mkx_Media_WindowManager</code>.
/// @param CUPPERCASENAME The upper case name (as in "C") of the type e.g. <code>MKX_MEDIA_WINDOWMANAGER</code>.
#define Mkx_Type_DeclareInterfaceType(NAME, CNAME, CUPPERCASENAME) \
\
  Mkx_Type* \
  __##CNAME##_getType__ \
    ( \
    ); \
\
\
  typedef struct CNAME CNAME; \
\
  static inline CNAME * \
  CUPPERCASENAME \
    ( \
      void* pointer \
    ) \
  { return (CNAME *)pointer; } \
\
\
  typedef struct CNAME##_Dispatch CNAME##_Dispatch; \
\
  static inline CNAME##_Dispatch * \
  CUPPERCASENAME##_DISPATCH \
    ( \
      void* pointer \
    ) \
  { return (CNAME##_Dispatch *)pointer; }


#endif // MKX_OBJECT_TYPEDECLARATION_H_INCLUDED
