// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Emit/Cpp/IndexOptions.h
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_CAS_EMIT_CPP_INDEXOPTIONS_H_INCLUDED)
#define MKX_SCRIBE_CAS_EMIT_CPP_INDEXOPTIONS_H_INCLUDED

#include "Mkx/Scribe/Common.h"


MACHINE_DECLARE_ENUMERATIONTYPE(Mkx_Scribe_Cas_IndexEmissionOption)

/// @brief How one or higher dimensional indices are emitted.
enum Mkx_Scribe_Cas_IndexEmissionOption {

  /// <code>[a, b, ...]</code>.
  Mkx_Scribe_Cas_IndexEmissionOption_Hll,

  /// <code>[a][b]...</code>.
  Mkx_Scribe_Cas_IndexEmissionOption_Cxx,

};


#endif // MKX_SCRIBE_CAS_EMIT_CPP_INDEXOPTIONS_H_INCLUDED
