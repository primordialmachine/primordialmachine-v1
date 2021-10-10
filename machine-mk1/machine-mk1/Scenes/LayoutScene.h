#if !defined(MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED)
#define MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED


#include "./../scene.h"


MACHINE_DECLARE_CLASSTYPE(LayoutScene)

void LayoutScene_construct(LayoutScene* self, size_t numberOfArguments, const Machine_Value* arguments);

LayoutScene* LayoutScene_create();

#endif // MACHINE_SCENES_LAYOUTSCENE_H_INCLUDED
