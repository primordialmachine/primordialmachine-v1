#if !defined(MKX_SCRIBE_TEMPLATE_PARSEANDEVALTEMPLATE_H_INCLUDED)
#define MKX_SCRIBE_TEMPLATE_PARSEANDEVALTEMPLATE_H_INCLUDED


#include "Mkx/Scribe/Environment.h"


void
Mkx_Template_parseAndEvalTemplate
  (
    Ring2_String* pathname,
    Mkx_Scribe_Environment* env,
    Ring2_StringBuffer* output
  );

#endif // MKX_SCRIBE_TEMPLATE_PARSEANDEVALTEMPLATE_H_INCLUDED
