#if !defined(RING4_SCENES_GRAPHICS2_RECTANGLES1_H_INCLUDED)
#define RING4_SCENES_GRAPHICS2_RECTANGLES1_H_INCLUDED

#include "Ring4/Scenes/Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scenes_Graphics2_Rectangles1)

void
Scenes_Graphics2_Rectangles1_construct
  (
    Scenes_Graphics2_Rectangles1* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Scenes_Graphics2_Rectangles1*
Scenes_Graphics2_Rectangles1_create
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // RING4_SCENES_GRAPHICS2_RECTANGLES1_H_INCLUDED
