/// @file Ring3/Visuals/_Include.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS__INCLUDE_H_INCLUDED)
#define RING3_VISUALS__INCLUDE_H_INCLUDED

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/BlendFunction.h"
#include "Ring3/Visuals/Canvas.h"
#include "Ring3/Visuals/CanvasSizeChangedEvent.h"
#include "Ring3/Visuals/CullingMode.h"
#include "Ring3/Visuals/DepthTestFunction.h"
#include "Ring3/Visuals/Font.h"
#include "Ring3/Visuals/FontsContext.h"
#include "Ring3/Visuals/GpuBuffer.h"
#include "Ring3/Visuals/GpuProgram.h"
#include "Ring3/Visuals/GpuProgramBinding.h"
#include "Ring3/Visuals/GpuProgramInputDescriptor.h"
#include "Ring3/Visuals/GpuProgramInputKind.h"
#include "Ring3/Visuals/GpuProgramInputType.h"
#include "Ring3/Visuals/GpuProgramKind.h"
#include "Ring3/Visuals/Image.h"
#include "Ring3/Visuals/ImagesContext.h"
#include "Ring3/Visuals/LightType.h"
#include "Ring3/Visuals/Material.h"
#include "Ring3/Visuals/MaterialBuilder.h"
#include "Ring3/Visuals/PixelFormat.h"
#include "Ring3/Visuals/PrimitiveType.h"
#include "Ring3/Visuals/Texture.h"
#include "Ring3/Visuals/WindingMode.h"
#include "Ring3/Visuals/VertexDescriptor.h"
#include "Ring3/Visuals/VertexElementDescriptor.h"
#include "Ring3/Visuals/VertexElementSemantics.h"
#include "Ring3/Visuals/VisualsContext.h"
#undef RING3_VISUALS_PRIVATE

#endif // RING3_VISUALS__INCLUDE_H_INCLUDED
