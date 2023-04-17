/// @file Ring3/Audials/Backends/XAudio2/XAudio2.h
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief XAudio2 Backend.
/// See https://docs.microsoft.com/en-us/windows/win32/xaudio2/ for more information on XAudio 2.

#if !defined(RING3_AUDIALS_BACKENDS_XAUDIO2_XAUDIO2_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_XAUDIO2_XAUDIO2_H_INCLUDED

#include "Ring3/Audials/Configuration.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

#include "Ring3/Audials/Backends/PcmDescriptor.h"
#include "Ring3/Audials/Backends/Buffer.h"
#include "Ring3/Audials/Backends/Source.h"
#include "Ring3/Audials/Backends/Backend.h"

#endif

#endif // RING3_AUDIALS_BACKENDS_XAUDIO2_XAUDIO2_H_INCLUDED
