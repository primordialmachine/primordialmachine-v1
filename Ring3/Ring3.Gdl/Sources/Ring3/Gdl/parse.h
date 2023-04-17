// @file Ring3/Gdl/parse.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/_Include.h"

typedef struct Parse {
  char const* start;
  char const* end;
  char const* current;
} Parse;

static bool
isPlus
  (
    Parse const* p
  )
{
  return p->current != p->end
      && ('+' == *p->current);
}

static bool
isMinus
  (
    Parse const* p
  )
{
  return p->current != p->end
      && ('-' == *p->current);
}

static bool
isExponent
  (
    Parse const* p
  )
{
  return p->current != p->end
      && ('e' == *p->current || 'E' == *p->current);
}

static bool
isPeriod
  (
    Parse const* p
  )
{
  return p->current != p->end
      && ('.' == *p->current);
}

static bool
isDigit
  (
    Parse const* p
  )
{
  return p->current != p->end
      && ('0' <= *p->current && *p->current <= '9');
}

static bool
isUnderscore
  (
    Parse const* p
  )
{
  return p->current != p->end
      && ('_'  == *p->current);
}

static bool
isLetter
  (
    Parse *p
  )
{
  return p->current != p->end
      && (('a' <= *p->current && *p->current <= 'z') || ('A' <= *p->current && *p->current <= 'Z'));
}

static bool
match
  (
    Parse* p,
    char const *current,
    char const *end
  )
{
  char const* old = p->current;
  while (p->current != p->end && current != end) {
    if (*p->current != *current) {
      p->current = old;
      return false;
    }
    p->current++;
    current++;
  }
  if (p->current != p->end || current != end) {
    p->current = old;
    return false;
  }
  return true;
}

static void
parseString
  (
    char const *start,
    char const *end
  )
{
  Parse p;
  p.start = start - 1;
  p.end = end;
  p.current = start - 1;
  // ^
  p.current++;
  //
  if (p.current == p.end || ((*p.current) != '"' && (*p.current) != '\'')) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  char quote = *p.current;
  p.current++;
  bool lastWasSlash = false;
  while (p.current != p.end) {
    if ((*p.current) == '\\') {
      if (lastWasSlash) {
        p.current++;
        lastWasSlash = false;
      } else {
        p.current++;
        lastWasSlash = true;
      }
    } else if ((*p.current) == quote) {
      if (lastWasSlash) {
        p.current++;
        lastWasSlash = false;
      } else {
        break;
      }   
    } else {    
      p.current++;
    }
  }
  if (p.current == p.end || *p.current != quote) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();  
  }
  p.current++;
  // $
  if (p.current != p.end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

static void
parseBoolean
  (
    char const *start,
    char const *end
  )
{
  static const char TRUE[] = "true";
  static const char FALSE[] = "false";
  Parse p;
  p.start = start - 1;
  p.end = end;
  p.current = start - 1;
  // ^
  p.current++;
  // ('true'|'false')
  if (!match(&p, TRUE, TRUE + crt_strlen(TRUE)) && !match(&p, FALSE, FALSE + crt_strlen(FALSE))) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  // $
  if (p.current != p.end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

static void
parseVoid
  (
    char const* start,
    char const* end
  )
{
  static const char VOID[] = "void";
  Parse p;
  p.start = start - 1;
  p.end = end;
  p.current = start - 1;
  // ^
  p.current++;
  // 'void'
  if (!match(&p, VOID, VOID + crt_strlen(VOID))) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  // $
  if (p.current != p.end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}


static void
parseInteger
  (
    char const* start,
    char const* end
  )
{
  Parse p;
  p.start = start - 1;
  p.end = end;
  p.current = start - 1;
  
  // ^
  p.current++;
  // sign?
  if (isPlus(&p)) {
    p.current++;
  } else if (isMinus(&p)) {
    p.current++;
  }
  // digit+
  if (!isDigit(&p)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  p.current++;
  while (isDigit(&p)) {
    p.current++;
  }
  // $
  if (p.current != p.end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

static void
parseReal
  (
    char const* start,
    char const* end
  )
{
  Parse p;
  p.start = start - 1;
  p.end = end;
  p.current = start - 1;

  // ^
  p.current++;
  // sign?
  if (isPlus(&p)) {
    p.current++;
  }
  else if (isMinus(&p)) {
    p.current++;
  }
  // ('.' digit+) | (digit+ ('.' digit*)?)
  if (isPeriod(&p)) {
    p.current++;
    if (!isDigit(&p)) {
      Ring1_Status_set(Ring1_Status_ConversionFailed);
      Ring2_jump();
    }
    do {
      p.current++;
    } while (isDigit(&p));
  } else {
    if (!isDigit(&p)) {
      Ring1_Status_set(Ring1_Status_ConversionFailed);
      Ring2_jump();     
    }
    do {
      p.current++;
    } while (isDigit(&p));
    if (isPeriod(&p)) {
      p.current++;
      while (isDigit(&p)) {
        p.current++;
      }
    }
  }
  if (isExponent(&p)) {
    p.current++;
    // sign?
    if (isPlus(&p)) {
      p.current++;
    }
    else if (isMinus(&p)) {
      p.current++;
    }
    if (!isDigit(&p)) {
      Ring1_Status_set(Ring1_Status_ConversionFailed);
      Ring2_jump();        
    }
    do {
      p.current++;
    } while (isDigit(&p));
  }
  // $
  if (p.current != p.end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

static void
parseName
  (
    char const* start,
    char const* end
  )
{
  Parse p;
  p.start = start - 1;
  p.end = end;
  p.current = start - 1;

  // ^
  p.current++;
  // ('_'|'a'-'z'|'A'-'Z')+
  if (isUnderscore(&p) || isLetter(&p)) {
    do {
      p.current++;
    } while (isUnderscore(&p) || isLetter(&p));
  }
  // ('_'|'a'-'z'|'A'-'Z'|'0'-'9')
  while (isUnderscore(&p) || isLetter(&p) || isDigit(&p)) {
    p.current++;
  }
  // $
  if (p.current != p.end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}
