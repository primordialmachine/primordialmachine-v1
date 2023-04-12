/// @file Ring3/Gui/_Include.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(GUI__INCLUDE_H_INCLUDED)
#define GUI__INCLUDE_H_INCLUDED

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/BorderNode.h"
#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/DefaultRenderContext.h"
#include "Ring3/Gui/RenderContext.h"
#include "Ring3/Gui/GroupNode.h"
#include "Ring3/Gui/TextNode.h"

#include "Ring3/Gui/Reader/Reader.h"

#include "Ring3/Gui/Selectors/IthChildSelector.h"
#include "Ring3/Gui/Selectors/NameSelector.h"
#include "Ring3/Gui/Selectors/UniversalSelector.h"
#undef RING3_GUI_PRIVATE

#endif // GUI__INCLUDE_H_INCLUDED
