#if !defined(RING1_FILESYSTEM_PATH_NORMALIZE_H_INCLUDED)
#define RING1_FILESYSTEM_PATH_NORMALIZE_H_INCLUDED

#include "Ring1/FileSystem/Path/TokenList.h"

Ring1_NoDiscardReturn() Ring1_Result
normalize
  (
    TokenList *tokens
  );

#endif // RING1_FILESYSTEM_PATH_NORMALIZE_H_INCLUDED
