// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Event.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_EVENT_H_INCLUDED)
#define RING1_LOG_EVENT_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/Event.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include <stdarg.h>


typedef struct Event {
  /// @brief The log level of the event.
  int level;
  /// @brief The C source file from which the event originates.
  char const*file;
  /// @brief The C source line from which the event originates.
  int line;
  /// @brief The format string of the message of the event.
  char const* format;
  /// qbrief The arguments of the message of the event.
  va_list arguments;
} Event;

static inline void
Event_setData
  (
    Event *event,
    int level,
    char const* file,
    int line,
    char const* format,
    va_list arguments
  )
{
  event->level = level;
  event->file = file;
  event->line = line;
  event->format = format;
  event->arguments = arguments;
}


#endif // RING1_LOG_EVENT_H_INCLUDED
