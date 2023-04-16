// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/EnvironmentParser.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_ENVIRONMENT_ENVIRONMENTPARSER_H_INCLUDED)
#define MKX_SCRIBE_ENVIRONMENT_ENVIRONMENTPARSER_H_INCLUDED


#include "Mkx/Scribe/Environment/EnvironmentScanner.h"
#include "Mkx/Scribe/Hll.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Template_EnvironmentParser)

struct Mkx_Template_EnvironmentParser_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Template_EnvironmentParser {
  Machine_Object _parent;
  Mkx_Template_EnvironmentScanner* scanner;
};

void
Mkx_Template_EnvironmentParser_construct
  (
    Mkx_Template_EnvironmentParser* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Mkx_Template_EnvironmentParser*
Mkx_Template_EnvironmentParser_create
  (
    Mkx_Template_EnvironmentScanner* scanner
  );

Mkx_Scribe_Hll_Node*
Mkx_Template_EnvironmentParser_run
  (
    Mkx_Template_EnvironmentParser* self
  );

#endif // MKX_SCRIBE_ENVIRONMENT_ENVIRONMENTPARSER_H_INCLUDED
