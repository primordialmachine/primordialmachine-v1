#if !defined(MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED)
#define MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED

#include "Scenes/Scene.h"

MACHINE_DECLARE_CLASSTYPE(LayoutScene)

void LayoutScene_construct(LayoutScene* self, size_t numberOfArguments,
                           Machine_Value const* arguments);

LayoutScene* LayoutScene_create(Machine_VideoContext *videoContext);

#endif // MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED
