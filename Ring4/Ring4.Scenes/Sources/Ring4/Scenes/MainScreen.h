#if !defined(RING4_SCENES_MAINSCREEN_H_INCLUDED)
#define RING4_SCENES_MAINSCREEN_H_INCLUDED

#include "Scene.h"

#define Scene5_withHeader (1)

#define Scene5_withMainMenu (1)

#define Scene5_withFooter (1)

MACHINE_DECLARE_CLASSTYPE(Scene5)

void
Scene5_construct
  (
    Scene5* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Scene5*
Scene5_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // RING4_SCENES_MAINSCREEN_H_INCLUDED
