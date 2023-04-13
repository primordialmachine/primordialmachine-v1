#if !defined(MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED)
#define MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED

#include "Ring4/Scenes/Scene.h"

MACHINE_DECLARE_CLASSTYPE(LayoutScene)

void
LayoutScene_construct
  (
    LayoutScene* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

LayoutScene*
LayoutScene_create
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED
