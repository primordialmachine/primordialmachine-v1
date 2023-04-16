// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/parseEnvironment.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#pragma once


#include "Mkx/Scribe/Environment.h"
#include "Mkx/Scribe/Common.h"

/**
 * @brief Parse an environment.
 * @param symbolScanner The underlying symbol scanner.
 * @return the environment
 * @code
 * environment : element*
 * variable : name ':' value
 * name : NAME | STRING
 * value : STRING+
 * @endcode
 */
Mkx_Scribe_Environment*
Mkx_Template_parseEnvironment
  (
    Mkx_SymbolScanner *symbolScanner
  );
