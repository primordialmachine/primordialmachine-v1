// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/TemplateScanner.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_TEMPLATE_TEMPLATESCANNER_H_INCLUDED)
#define MKX_SCRIBE_TEMPLATE_TEMPLATESCANNER_H_INCLUDED


#include "Mkx/Scribe/Hll.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Template_TemplateScanner)

struct Mkx_Template_TemplateScanner_Class {
  Mkx_Scribe_Hll_Scanner_Class _parent;
};

struct Mkx_Template_TemplateScanner {
  Mkx_Scribe_Hll_Scanner _parent;
};

void
Mkx_Template_TemplateScanner_construct
  (
    Mkx_Template_TemplateScanner* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Template_TemplateScanner*
Mkx_Template_TemplateScanner_create
  (
    Mkx_SymbolScanner* symbolScanner
  );

#endif // MKX_SCRIBE_TEMPLATE_TEMPLATESCANNER_H_INCLUDED
