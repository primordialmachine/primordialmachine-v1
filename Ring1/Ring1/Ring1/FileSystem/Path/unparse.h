#if !defined(RING1_FILESYSTEM_PATH_UNPARSE_H_INCLUDED)
#define RING1_FILESYSTEM_PATH_UNPARSE_H_INCLUDED

#include "Ring1/FileSystem/Path/TokenList.h"

Ring1_NoDiscardReturn() Ring1_Result
unparse
  (
    TokenList* tokenList,
    bool zeroTerminated,
    char** p,
    size_t* n
  );

#endif // RING1_FILESYSTEM_PATH_UNPARSE_H_INCLUDED
