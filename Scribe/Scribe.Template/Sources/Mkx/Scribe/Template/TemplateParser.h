// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/TemplateParser.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_TEMPLATEPARSER_H_INCLUDED)
#define MKX_SCRIBE_TEMPLATEPARSER_H_INCLUDED


#include "Mkx/Scribe/Template/TemplateScanner.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Template_TemplateParser)

struct Mkx_Template_TemplateParser_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Template_TemplateParser {
  Machine_Object _parent;
  Mkx_Template_TemplateScanner* scanner;
};

void
Mkx_Template_TemplateParser_construct
  (
    Mkx_Template_TemplateParser* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Template_TemplateParser*
Mkx_Template_TemplateParser_create
  (
    Mkx_Template_TemplateScanner* scanner
  );

#endif // MKX_SCRIBE_TEMPLATEPARSER_H_INCLUDED
