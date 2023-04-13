#if !defined(RING1_FILESYSTEM_PATH_PARSE_H_INCLUDED)
#define RING1_FILESYSTEM_PATH_PARSE_H_INCLUDED

#include "Ring1/FileSystem/Path/TokenList.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Path_parse
  (
    TokenList **result,
    const char* s,
    size_t sn
  );

#endif // RING1_FILESYSTEM_PATH_PARSE_H_INCLUDED
