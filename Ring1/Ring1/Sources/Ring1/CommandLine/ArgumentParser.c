// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/CommandLine/ArgumentParser.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/CommandLine/ArgumentParser.h"

#include "Ring1/Crt/_Include.h"
#include "Ring1/CommandLine/Argument.h"
#include <stdio.h>

static Ring1_NoDiscardReturn() Ring1_Result
parseSwitchOrNamedArgument
  (
    Ring1_CommandLine_Argument** result,
    Ring1_CommandLine_ArgumentParser* parser
  );

static Ring1_NoDiscardReturn() Ring1_Result
parseValueArgument
  (
    Ring1_CommandLine_Argument** result,
    Ring1_CommandLine_ArgumentParser* parser
  );

static Ring1_NoDiscardReturn() Ring1_Result
parseSwitchOrNamedArgument
  (
    Ring1_CommandLine_Argument** result,
    Ring1_CommandLine_ArgumentParser* parser
  )
{
  char* name = NULL, * value = NULL;
  // <name>
  while (*parser->current != '\0' && *parser->current != '=') {
    parser->current++;
  }
  if (parser->start == parser->current ||
    *parser->start == '\0') {
    fprintf(stderr, "invalid command-line argument\n");
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    return Ring1_Result_Failure;
  }
  name = crt_malloc(parser->current - parser->start + 1);
  if (!name) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  crt_memcpy(name, parser->start, parser->current - parser->start);
  name[parser->current - parser->start] = '\0';
  //
  if (*parser->current == '=') {
    parser->current++;
    parser->start = parser->current;
    while (*parser->current != '\0') {
      parser->current++;
    }
    if (parser->current == parser->start) {
      fprintf(stderr, "invalid command-line argument\n");
      Ring1_Status_set(Ring1_Status_InvalidSyntactics);
      return Ring1_Result_Failure;
    }
    value = crt_malloc(parser->current - parser->start + 1);
    if (!value) {
      crt_free(name);
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    crt_memcpy(value, parser->start, parser->current - parser->start);
    value[parser->current - parser->start] = '\0';
  }
  //
  Ring1_Result r = Ring1_CommandLine_Argument_create(result, name, value);
  crt_free(value);
  crt_free(name);
  return r;
}

Ring1_Result
parseValueArgument
  (
    Ring1_CommandLine_Argument** result,
    Ring1_CommandLine_ArgumentParser* parser
  )
{
  //
  while (*parser->current != '\0') {
    parser->current++;
  }
  char* value = crt_strndup(parser->start, parser->current - parser->start);
  if (!value) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  //
  Ring1_Result r = Ring1_CommandLine_Argument_create(result, NULL, value);
  crt_free(value);
  return r;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_CommandLine_ArgumentParser_parse
  (
    Ring1_CommandLine_Argument** result,
    Ring1_CommandLine_ArgumentParser* parser
  )
{
  if (*parser->current == '-') {
    parser->current++;
    if (*parser->current == '-') {
      parser->current++;
    }
    parser->start = parser->current;
    return parseSwitchOrNamedArgument(result, parser);
  } else {
    return parseValueArgument(result, parser);
  }
}
