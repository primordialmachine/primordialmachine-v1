// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/EnvironmentScanner.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_ENVIRONMENT_ENVIRONMENTSCANNER_H_INCLUDED)
#define MKX_SCRIBE_ENVIRONMENT_ENVIRONMENTSCANNER_H_INCLUDED


#include "Mkx/Scribe/Hll.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Template_EnvironmentScanner)

struct Mkx_Template_EnvironmentScanner_Class {
  Mkx_Scribe_Hll_Scanner_Class _parent;
};

struct Mkx_Template_EnvironmentScanner {
  Mkx_Scribe_Hll_Scanner _parent;
};

void
Mkx_Template_EnvironmentScanner_construct
  (
    Mkx_Template_EnvironmentScanner* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Mkx_Template_EnvironmentScanner *
Mkx_Template_EnvironmentScanner_create
  (
    Mkx_SymbolScanner *symbolScanner
  );

#endif // MKX_SCRIBE_ENVIRONMENT_ENVIRONMENTSCANNER_H_INCLUDED
