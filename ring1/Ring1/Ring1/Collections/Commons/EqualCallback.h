// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Collections/Commons/EqualCallback.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_COLLECTIONS_COMMONS_EQUALCALLBACK_H_INCLUDED)
#define MKX_COLLECTIONS_COMMONS_EQUALCALLBACK_H_INCLUDED


#include "Ring1/Intrinsic.h"
#include "Ring1/Status.h"
#include <stdbool.h>

// https://documentation.primordialmachine.com/utility-libraries/collections-commons-library#mkx_collection_equalcallback
typedef Ring1_Status(Mkx_Collection_EqualCallback)(bool* result, void* first, void *second);

#endif // MKX_COLLECTIONS_COMMONS_EQUALCALLBACK_H_INCLUDED
