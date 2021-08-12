/// @file _Video.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE__VIDEO_H_INCLUDED)
#define MACHINE__VIDEO_H_INCLUDED

#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Binding.h"
#include "Video/BlendFunction.h"
#include "Video/Buffer.h"
#include "Video/CanvasSizeChangedEvent.h"
#include "Video/DepthTestFunction.h"
#include "Video/Image.h"
#include "Video/Material.h"
#include "Video/PixelFormat.h"
#include "Video/ProgramKind.h"
#include "Video/ProgramInput.h"
#include "Video/ProgramInputKind.h"
#include "Video/ProgramInputType.h"
#include "Video/ShaderProgram.h"
#include "Video/Texture.h"
#include "Video/VertexDescriptor.h"
#include "Video/VertexElementSemantics.h"
#include "Video/VideoContext.h"
#undef MACHINE_VIDEO_PRIVATE

#endif // MACHINE__VIDEO_H_INCLUDED
