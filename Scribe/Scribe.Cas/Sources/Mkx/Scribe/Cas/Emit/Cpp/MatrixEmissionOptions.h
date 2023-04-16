// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Emit/Cpp/MatrixEmissionOptions.h
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_CAS_EMIT_CPP_MATRIXEMISSIONOPTIONS_H_INCLUDED)
#define MKX_SCRIBE_CAS_EMIT_CPP_MATRIXEMISSIONOPTIONS_H_INCLUDED

#include "Mkx/Scribe/Common.h"


MACHINE_DECLARE_ENUMERATIONTYPE(Mkx_Scribe_Cas_MatrixEmissionOption)

/// @brief How matrices are emitted.
enum Mkx_Scribe_Cas_MatrixEmissionOption {

  /// <code>(...)</code>.
  Mkx_Scribe_Cas_MatrixEmissionOption_RowDelimiters,
  
  /// <code>...</code>.
  Mkx_Scribe_Cas_MatrixEmissionOption_NoRowDelimiters,

};


#endif // MKX_SCRIBE_CAS_EMIT_CPP_MATRIXEMISSIONOPTIONS_H_INCLUDED
