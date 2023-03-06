/// @file Ring3/Gui/TextNode.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/TextNode.h"

#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/Widget.h"
#include "Ring3/Gui/RenderContext.h"
#undef RING3_GUI_PRIVATE

#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Text/_Include.h"
#include "Ring3/Visuals/_Include.h"


struct Machine_Gui_TextNode_Class {
  Machine_Gui_Widget_Class __parent;
};

struct Machine_Gui_TextNode {
  Machine_Gui_Widget __parent;

  /// @brief The layout for rendering the text.
  Machine_Text_Layout* foreground;

  /// @brief The shape for rendering the background.
  Ring3_Rectangle2* background;

  bool childDirty;
};

static void
Machine_Gui_TextNode_visit
  (
    Machine_Gui_TextNode* self
  )
{
  if (self->foreground) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->foreground);
  }
  if (self->background) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->background);
  }
}

static Ring3_Math_Vector2f32*
Machine_Gui_TextNode_getPreferredSize
  (
    Machine_Gui_TextNode const* self
  );

static void
Machine_Gui_TextNode_render
  (
    Machine_Gui_TextNode* self,
    Ring3_Gui_RenderContext* renderContext
  );

static void
boundsChangedCallback
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_assertNotNull(result);
  Ring2_assert(2 == numberOfArguments, Ring1_Status_InvalidNumberOfArguments);
  Machine_Gui_TextNode* self = (Machine_Gui_TextNode*)Ring2_Value_getObject(&arguments[0]);
  self->childDirty = true;
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void
Machine_Gui_TextNode_constructClass
  (
    Machine_Gui_TextNode_Class* self
  )
{
  ((Machine_Gui_Widget_Class*)self)->render
      = (void (*)(Machine_Gui_Widget*, Ring3_Gui_RenderContext*)) & Machine_Gui_TextNode_render;
  ((Machine_Gui_Widget_Class*)self)->getPreferredSize
      = (Ring3_Math_Vector2f32* (*)(Machine_Gui_Widget const*))
        & Machine_Gui_TextNode_getPreferredSize;
}

void
Machine_Gui_TextNode_construct
  (
    Machine_Gui_TextNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Gui_Widget_construct((Machine_Gui_Widget*)self, numberOfArguments, arguments);
  Machine_Gui_Context* guiContext = (Machine_Gui_Context*)Ring2_CallArguments_getObjectArgument(
      numberOfArguments, arguments, 0, Machine_Gui_Context_getType());
  Ring3_FontsContext* fontsContext = Ring3_Context2_getFontsContext(guiContext->context2);
  Ring3_Font* font = Ring3_FontsContext_createFont(fontsContext, guiContext->defaultFontFile, guiContext->defaultFontSize);
  self->foreground = Machine_Text_Layout_create(Ring2_String_fromC(false, ""), font);
  self->background = Ring3_Rectangle2_create();
  self->childDirty = true;
  Machine_Gui_Widget_subscribe((Machine_Gui_Widget*)self,
                               ((Machine_Gui_Widget*)self)->context->signalsContext->PositionChanged,
                               (Machine_Object*)self,
                               &boundsChangedCallback);
  Machine_Gui_Widget_subscribe((Machine_Gui_Widget*)self,
                               ((Machine_Gui_Widget*)self)->context->signalsContext->SizeChanged,
                               (Machine_Object*)self,
                               &boundsChangedCallback);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_TextNode_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_TextNode,
                         Machine_Gui_Widget,
                         &Machine_Gui_TextNode_visit,
                         &Machine_Gui_TextNode_construct,
                         NULL,
                         &Machine_Gui_TextNode_constructClass,
                         NULL)

Ring1_NoDiscardReturn() Machine_Gui_TextNode*
Machine_Gui_TextNode_create
  (
    Machine_Gui_Context* context
  )
{
  Machine_ClassType* ty = Machine_Gui_TextNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_Gui_TextNode* self
      = (Machine_Gui_TextNode*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring3_Math_Vector2f32*
Machine_Gui_TextNode_getPreferredSize
  (
    Machine_Gui_TextNode const* self
  )
{ return Ring3_Math_Rectangle2_getSize(Machine_Text_Layout_getBounds(self->foreground)); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_TextNode_setText
  (
    Machine_Gui_TextNode* self,
    Ring2_String* text
  )
{
  Machine_Text_Layout_setText(self->foreground, text);
  Machine_Gui_Widget_emitPositionChangedSignal((Machine_Gui_Widget*)self);
  Machine_Gui_Widget_emitSizeChangedSignal((Machine_Gui_Widget*)self);
}

Ring1_NoDiscardReturn() Ring2_String*
Machine_Gui_TextNode_getText
  (
    Machine_Gui_TextNode const* self
  )
{ return Machine_Text_Layout_getText(self->foreground); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_TextNode_setBackgroundColor
  (
    Machine_Gui_TextNode* self,
    Ring3_Math_Vector4f32 const* backgroundColor
  )
{
  Ring3_Rectangle2_setColor(self->background, backgroundColor);
  Machine_Gui_Widget_emitPositionChangedSignal((Machine_Gui_Widget*)self);
  Machine_Gui_Widget_emitSizeChangedSignal((Machine_Gui_Widget*)self);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_TextNode_getBackgroundColor
  (
    Machine_Gui_TextNode const* self
  )
{ return Ring3_Rectangle2_getColor(self->background); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_TextNode_setForegroundColor
  (
    Machine_Gui_TextNode* self,
    Ring3_Math_Vector3f32 const* foregroundColor
  )
{
  Machine_Text_Layout_setColor(self->foreground, foregroundColor);
  Machine_Gui_Widget_emitPositionChangedSignal((Machine_Gui_Widget*)self);
  Machine_Gui_Widget_emitSizeChangedSignal((Machine_Gui_Widget*)self);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Machine_Gui_TextNode_getForegroundColor
  (
    Machine_Gui_TextNode const* self
  )
{ return Machine_Text_Layout_getColor(self->foreground); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Machine_Gui_TextNode_render2
  (
    Machine_Gui_TextNode* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  Ring3_Context2* ctx2 = ((Machine_Gui_Widget*)self)->context->context2;
  Ring3_Context2_setTargetSize(ctx2, width, height);
  if (self->childDirty) {
    Machine_Gui_Context* ctx = ((Machine_Gui_Widget*)self)->context;
    Ring3_Rectangle2_setRectangle(self->background, ((Machine_Gui_Widget*)self)->rectangle);
    // TODO: Only do this layouting if necessary.
    Ring3_Math_Rectangle2* clipRect = Ring3_Rectangle2_getRectangle(self->background);
    Ring3_Math_Vector2f32 const* widgetCenter
        = Ring3_Math_Rectangle2_getCenter(Ring3_Rectangle2_getRectangle(self->background));

    Ring3_Math_Rectangle2 const* textBounds = Machine_Text_Layout_getBounds(self->foreground);
    Ring3_Math_Vector2f32 const* textCenter = Ring3_Math_Rectangle2_getCenter(textBounds);
    Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_difference(widgetCenter, textCenter);
    Ring3_Math_Vector2f32 const* oldPosition = Machine_Text_Layout_getPosition(self->foreground);
    Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_sum(oldPosition, delta);
    Machine_Text_Layout_setPosition(self->foreground, newPosition);
    Machine_Text_Layout_setClipRectangle(self->foreground, clipRect);

    self->childDirty = false;
  }
  Ring3_Shape2_render((Ring3_Shape2*)self->background, ctx2);
  Machine_Text_Layout_render(self->foreground, ctx2);
}

static void
Machine_Gui_TextNode_render
  (
    Machine_Gui_TextNode* self,
    Ring3_Gui_RenderContext* renderContext
  )
{
  Machine_Gui_TextNode_render2(self, Ring3_Gui_RenderContext_getCanvasWidth(renderContext),
                                     Ring3_Gui_RenderContext_getCanvasHeight(renderContext));
}
