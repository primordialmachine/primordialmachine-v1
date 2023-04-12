// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Tool.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#pragma once

#include "Mkx/Interpreter/Library.h"

typedef struct Mkx_Scribe_ProgramInfo Mkx_Scribe_ProgramInfo;

struct Mkx_Scribe_ProgramInfo
{
  /// @brief The program name.
  /// <code>&lt;program name&gt;</code>.
  /// @brief The copyright notice.
  /// <code>Copyright (c) &lt;from year&gt; - &lt;to year&gt;, &lt;organization&gt;. All rights reserved.</code>
  Ring2_String* copyright;
  /// @brief List of authors.
  /// An array of <code>&lt;author&gt; (&lt;email&gt;)</code> strings.
  Ring2_Array* authors;
};

Mkx_Scribe_ProgramInfo*
Mkx_Scribe_ProgramInfo_create
  (
    Ring2_Context* context
  );

void
Scribe_Cas_main
  (
    Ring2_Context* context,
    Ring2_CommandLine_ArgumentList* argumentList
  );
