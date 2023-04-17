/// @file Ring3/Audials/_Include.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_AUDIALS__INCLUDE_H_INCLUDED)
#define RING3_AUDIALS__INCLUDE_H_INCLUDED

#define RING3_AUDIALS_PRIVATE (1)
#include "Ring3/Audials/PcmBuffer.h"
#include "Ring3/Audials/PcmDescriptor.h"

#include "Ring3/Audials/Configuration.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2
#include "Ring3/Audials/Backends/XAudio2/XAudio2.h"
#endif
#if Ring3_Audials_Backend == Ring3_Audials_Backend_OpenAL
#include "Ring3/Audials/Backends/OpenAL/OpenAL.h"
#endif

#undef RING3_AUDIALS_PRIVATE

#endif // RING3_AUDIALS__INCLUDE_H_INCLUDED
