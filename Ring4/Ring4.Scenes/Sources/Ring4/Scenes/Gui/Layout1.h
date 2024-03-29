#if !defined(RING4_SCENES_GUI_LAYOUT_H_INCLUDED)
#define RING4_SCENES_GUI_LAYOUT_H_INCLUDED

#include "Ring4/Scenes/Scene.h"

MACHINE_DECLARE_CLASSTYPE(Ring4_Scenes_Gui_Layout1)

void
Ring4_Scenes_Gui_Layout1_construct
  (
    Ring4_Scenes_Gui_Layout1* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring4_Scenes_Gui_Layout1*
Ring4_Scenes_Gui_Layout1_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // RING4_SCENES_GUI_LAYOUT_H_INCLUDED
