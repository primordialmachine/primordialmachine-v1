#if !defined(MKX_SCRIBE_TEMPLATE_LIBRARY_H_INCLUDED)
#define MKX_SCRIBE_TEMPLATE_LIBRARY_H_INCLUDED

#include "Mkx/Scribe/Common.h"
#include "Mkx/Scribe/Environment.h"

/// @brief Register the library procedure with the specified environment.
/// The following procedures are registered.
/// - GeneratorVendor : [...] -> [..., e], type(e) = String
/// Get the vendor of this generator ("Michael Heilmanny").
/// - GeneratorName : [...] -> [..., e], type(e) = String
/// Get the name of this generator ("Scribe").
/// @remark This overwrites any entry of the specified names.
void
Mkx_Scribe_Template_Library_register
  (
    Mkx_Scribe_Environment *environment
  );

#endif // MKX_SCRIBE_TEMPLATE_LIBRARY_H_INCLUDED
