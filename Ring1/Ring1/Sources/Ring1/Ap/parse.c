#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/parse.h"
#undef RING1_AP_PRIVATE

static Ring1_NoDiscardReturn() bool
isDigit
  (
    char const *current,
    char const *start,
    char const *end
  )
{
  if (current == end) {
    return false;
  }
  return '0' <= *current && *current <= '9';
}

static Ring1_NoDiscardReturn() bool
isPeriod
  (
    char const *current,
    char const *start,
    char const *end
  )
{
  if (current == end) {
    return false;
  }
  return '.' == *current;
}

static Ring1_NoDiscardReturn() bool
isPlus
  (
    char const *current,
    char const *start,
    char const *end
  )
{
  if (current == end) {
    return false;
  }
  return '+' == *current;
}

static Ring1_NoDiscardReturn() bool
isMinus
  (
    char const *current,
    char const *start,
    char const *end
  )
{
  if (current == end) {
    return false;
  }
  return '-' == *current;
}

static Ring1_NoDiscardReturn() bool
isEnd
  (
    char const *current,
    char const *start,
    char const *end
  )
{
  return current == end;
}

static Ring1_NoDiscardReturn() bool
isStart
  (
    char const *current,
    char const *start,
    char const *end
  )
{
  return current == start - 1;
}

Ring1_NoDiscardReturn() Ring1_Result
parseReal
  (
    char const *start, 
    char const *end,
    Ring1_ApReal *real
  )
{
  Ring1_ApInt ten, integer1;
  if (Ring1_ApInt_initialize_u8(&ten, 10, 0)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_ApInt_initialize_u8(&integer1, 0, 0)) {
    Ring1_ApInt_uninitialize(&ten);
    return Ring1_Result_Failure;
  }
  int64_t exponent1 = 0;

  char const* current = start - 1;
  current++;
  bool negative = false;
  if (isPlus(current, start, end)) {
    current++;
  } else if (isMinus(current, start, end)) {
    current++;
    negative = true;
  }

  if (!isDigit(current, start, end)) {
    if (!isPeriod(current, start, end)) {
      Ring1_ApInt_uninitialize(&integer1);
      Ring1_ApInt_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    current++;
    while (isDigit(current, start, end)) {
      if (Ring1_ApInt_multiply(&integer1, &ten)) {
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApInt digit;
      if (Ring1_ApInt_initialize_u8(&digit, *current - '0', 0)) {
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      if (Ring1_ApInt_add(&integer1, &digit)) {
        Ring1_ApInt_uninitialize(&digit);
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApInt_uninitialize(&digit);
      current++;
      exponent1--;
    }
    // "integer1" contains n digits and "exponent1" is -n.
  } else {
    do {
      if (Ring1_ApInt_multiply(&integer1, &ten)) {
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApInt digit;
      if (Ring1_ApInt_initialize_u8(&digit, *current - '0', 0)) {
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      if (Ring1_ApInt_add(&integer1, &digit)) {
        Ring1_ApInt_uninitialize(&digit);
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApInt_uninitialize(&digit);
      current++;
    } while (isDigit(current, start, end));
    if (isPeriod(current, start, end)) {
      current++;
      while (isDigit(current, start, end)) {
        if (Ring1_ApInt_multiply(&integer1, &ten)) {
          Ring1_ApInt_uninitialize(&integer1);
          Ring1_ApInt_uninitialize(&ten);
          return Ring1_Result_Failure;
        }
        Ring1_ApInt digit;
        if (Ring1_ApInt_initialize_u8(&digit, *current - '0', 0)) {
          Ring1_ApInt_uninitialize(&integer1);
          Ring1_ApInt_uninitialize(&ten);
          return Ring1_Result_Failure;
        }
        if (Ring1_ApInt_add(&integer1, &digit)) {
          Ring1_ApInt_uninitialize(&digit);
          Ring1_ApInt_uninitialize(&integer1);
          Ring1_ApInt_uninitialize(&ten);
          return Ring1_Result_Failure;
        }
        Ring1_ApInt_uninitialize(&digit);
        current++;
        exponent1--;
      }
    }
  }
  Ring1_ApInt_uninitialize(&ten);
  if (negative) {
    if (Ring1_ApInt_negate(&integer1)) {
      Ring1_ApInt_uninitialize(&integer1);
      return Ring1_Result_Failure;
    }
  }
  if (Ring1_ApReal_set(real, &integer1, exponent1)) {
    Ring1_ApInt_uninitialize(&integer1);
    return Ring1_Result_Failure;
  }
  Ring1_ApInt_uninitialize(&integer1);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
parseInteger
  (
    char const* start,
    char const* end,
    Ring1_ApInt* integer
  )
{
  Ring1_ApInt ten, integer1;
  if (Ring1_ApInt_initialize_u8(&ten, 10, 0)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_ApInt_initialize_u8(&integer1, 0, 0)) {
    Ring1_ApInt_uninitialize(&ten);
    return Ring1_Result_Failure;
  }
  char const* current = start - 1;
  current++;
  bool negative = false;
  if (isPlus(current, start, end)) {
    current++;
  } else if (isMinus(current, start, end)) {
    current++;
    negative = true;
  }
  if (!isDigit(current, start, end)) {
    Ring1_ApInt_uninitialize(&integer1);
    Ring1_ApInt_uninitialize(&ten);
    return Ring1_Result_Failure;
  }
  do {
    if (Ring1_ApInt_multiply(&integer1, &ten)) {
      Ring1_ApInt_uninitialize(&integer1);
      Ring1_ApInt_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    Ring1_ApInt digit;
    if (Ring1_ApInt_initialize_u8(&digit, *current - '0', 0)) {
      Ring1_ApInt_uninitialize(&integer1);
      Ring1_ApInt_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    if (Ring1_ApInt_add(&integer1, &digit)) {
      Ring1_ApInt_uninitialize(&digit);
      Ring1_ApInt_uninitialize(&integer1);
      Ring1_ApInt_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    Ring1_ApInt_uninitialize(&digit);
    current++;
  } while (isDigit(current, start, end));
  if (isPeriod(current, start, end)) {
    current++;
    while (isDigit(current, start, end)) {
      if (Ring1_ApInt_multiply(&integer1, &ten)) {
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApInt digit;
      if (Ring1_ApInt_initialize_u8(&digit, *current - '0', 0)) {
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      if (Ring1_ApInt_add(&integer1, &digit)) {
        Ring1_ApInt_uninitialize(&digit);
        Ring1_ApInt_uninitialize(&integer1);
        Ring1_ApInt_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApInt_uninitialize(&digit);
      current++;
    }
  }
  Ring1_ApInt_uninitialize(&ten);
  if (negative) {
    if (Ring1_ApInt_negate(&integer1)) {
      Ring1_ApInt_uninitialize(&integer1);
      return Ring1_Result_Failure;
    }
  }
  if (Ring1_ApInt_assign(integer, &integer1)) {
    Ring1_ApInt_uninitialize(&integer1);
    return Ring1_Result_Failure;
  }
  Ring1_ApInt_uninitialize(&integer1);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
parseNatural
  (
    char const* start,
    char const* end,
    Ring1_ApNat* natural
  )
{
  Ring1_ApNat ten, natural1;
  if (Ring1_ApNat_initialize_u8(&ten, 10, 0)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_ApNat_initialize_u8(&natural1, 0, 0)) {
    Ring1_ApNat_uninitialize(&ten);
    return Ring1_Result_Failure;
  }
  char const* current = start - 1;
  current++;
  if (isPlus(current, start, end)) {
    current++;
  }
  if (!isDigit(current, start, end)) {
    Ring1_ApNat_uninitialize(&natural1);
    Ring1_ApNat_uninitialize(&ten);
    return Ring1_Result_Failure;
  }
  do {
    if (Ring1_ApNat_multiply(&natural1, &ten)) {
      Ring1_ApNat_uninitialize(&natural1);
      Ring1_ApNat_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    Ring1_ApNat digit;
    if (Ring1_ApNat_initialize_u8(&digit, *current - '0', 0)) {
      Ring1_ApNat_uninitialize(&natural1);
      Ring1_ApNat_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    if (Ring1_ApNat_add(&natural1, &digit)) {
      Ring1_ApNat_uninitialize(&digit);
      Ring1_ApNat_uninitialize(&natural1);
      Ring1_ApNat_uninitialize(&ten);
      return Ring1_Result_Failure;
    }
    Ring1_ApNat_uninitialize(&digit);
    current++;
  } while (isDigit(current, start, end));
  if (isPeriod(current, start, end)) {
    current++;
    while (isDigit(current, start, end)) {
      if (Ring1_ApNat_multiply(&natural1, &ten)) {
        Ring1_ApNat_uninitialize(&natural1);
        Ring1_ApNat_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApNat digit;
      if (Ring1_ApNat_initialize_u8(&digit, *current - '0', 0)) {
        Ring1_ApNat_uninitialize(&natural1);
        Ring1_ApNat_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      if (Ring1_ApNat_add(&natural1, &digit)) {
        Ring1_ApNat_uninitialize(&digit);
        Ring1_ApNat_uninitialize(&natural1);
        Ring1_ApNat_uninitialize(&ten);
        return Ring1_Result_Failure;
      }
      Ring1_ApNat_uninitialize(&digit);
      current++;
    }
  }
  Ring1_ApNat_uninitialize(&ten);
  if (Ring1_ApNat_assign(natural, &natural1)) {
    Ring1_ApNat_uninitialize(&natural1);
    return Ring1_Result_Failure;
  }
  Ring1_ApNat_uninitialize(&natural1);
  return Ring1_Result_Success;
}
