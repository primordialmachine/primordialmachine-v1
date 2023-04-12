/// @file Ring3/Gui/TextNode.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/TextNode.h"

#include "Ring3/Gui/Context.h"
#include "Ring3/Gui/WidgetBase.h"
#include "Ring3/Gui/RenderContext.h"
#undef RING3_GUI_PRIVATE

#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Text/_Include.h"
#include "Ring3/Visuals/_Include.h"


struct Machine_Gui_TextNode_Class {
  Ring3_Gui_WidgetBase_Class __parent;
};

struct Machine_Gui_TextNode {
  Ring3_Gui_WidgetBase __parent;

  /// @brief The layout for rendering the text.
  Machine_Text_Layout* foreground;

  /// @brief The shape for rendering the background.
  Ring3_Graphics2_Rectangle* background;

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

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Gui_TextNode_getPreferredSizeImpl
  (
    Machine_Gui_TextNode const* self
  );

static void
Machine_Gui_TextNode_renderImpl
  (
    Machine_Gui_TextNode* self,
    Ring3_Gui_RenderContext* renderContext
  );

static Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gui_TextNode_getChildrenImpl
  (
    Machine_Gui_TextNode const* self
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
{ }

void
Machine_Gui_TextNode_construct
  (
    Machine_Gui_TextNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Gui_WidgetBase_construct((Ring3_Gui_WidgetBase*)self, numberOfArguments, arguments);
  Machine_Gui_Context* guiContext = (Machine_Gui_Context*)Ring2_CallArguments_getObjectArgument(
      numberOfArguments, arguments, 0, Machine_Gui_Context_getType());
  Ring3_FontsContext* fontsContext = Ring3_Graphics2_Context_getFontsContext(guiContext->graphics2Context);
  Ring3_Font* font = Ring3_FontsContext_createFont(fontsContext, guiContext->defaultFontFile, guiContext->defaultFontSize);
  self->foreground = Machine_Text_Layout_create(Ring2_String_fromC(false, ""), font);
  self->background = Ring3_Graphics2_Rectangle_create();
  self->childDirty = true;
  Ring3_Gui_Widget_subscribe((Ring3_Gui_Widget*)self,
                             ((Ring3_Gui_WidgetBase*)self)->context->signalsContext->PositionChanged,
                             (Machine_Object*)self,
                             &boundsChangedCallback);
  Ring3_Gui_Widget_subscribe((Ring3_Gui_Widget*)self,
                             ((Ring3_Gui_WidgetBase*)self)->context->signalsContext->SizeChanged,
                             (Machine_Object*)self,
                             &boundsChangedCallback);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_TextNode_getType());
}

static void
Machine_Gui_TextNode_implement_Ring3_Gui_Widget
  (
    Ring3_Gui_Widget_Dispatch* self
  )
{
  self->render = (void (*)(Ring3_Gui_Widget*, Ring3_Gui_RenderContext*)) & Machine_Gui_TextNode_renderImpl;
  self->getPreferredSize = (Ring3_Math_Vector2f32 * (*)(Ring3_Gui_Widget const*)) & Machine_Gui_TextNode_getPreferredSizeImpl;
  self->getChildren = (Ring2_Collections_List * (*)(Ring3_Gui_Widget const*)) & Machine_Gui_TextNode_getChildrenImpl;
}

static void
Machine_Gui_TextNode_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement
    (
      self,
      Ring3_Gui_Widget_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_Gui_TextNode_implement_Ring3_Gui_Widget
    );
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_TextNode,
                         Ring3_Gui_WidgetBase,
                         &Machine_Gui_TextNode_visit,
                         &Machine_Gui_TextNode_construct,
                         NULL,
                         &Machine_Gui_TextNode_constructClass,
                         &Machine_Gui_TextNode_implementInterfaces)

Ring1_NoDiscardReturn() Machine_Gui_TextNode*
Machine_Gui_TextNode_create
  (
    Machine_Gui_Context* context
  )
{
  Machine_Type* ty = Machine_Gui_TextNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)context);
  Machine_Gui_TextNode* self = Ring1_cast(Machine_Gui_TextNode*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Gui_TextNode_getPreferredSizeImpl
  (
    Machine_Gui_TextNode const* self
  )
{ return Ring3_Math_Rectangle2_getSize(Machine_Text_Layout_getBounds(self->foreground)); }

static Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gui_TextNode_getChildrenImpl
  (
    Machine_Gui_TextNode const* self
  )
{ return (Ring2_Collections_List*)Ring2_Collections_ArrayList_create(); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_TextNode_setText
  (
    Machine_Gui_TextNode* self,
    Ring2_String* text
  )
{
  Machine_Text_Layout_setText(self->foreground, text);
  Ring3_Gui_WidgetBase_emitPositionChangedSignal((Ring3_Gui_WidgetBase*)self);
  Ring3_Gui_WidgetBase_emitSizeChangedSignal((Ring3_Gui_WidgetBase*)self);
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
  Ring3_Graphics2_Rectangle_setColor(self->background, backgroundColor);
  Ring3_Gui_WidgetBase_emitPositionChangedSignal((Ring3_Gui_WidgetBase*)self);
  Ring3_Gui_WidgetBase_emitSizeChangedSignal((Ring3_Gui_WidgetBase*)self);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_TextNode_getBackgroundColor
  (
    Machine_Gui_TextNode const* self
  )
{ return Ring3_Graphics2_Rectangle_getColor(self->background); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_TextNode_setForegroundColor
  (
    Machine_Gui_TextNode* self,
    Ring3_Math_Vector3f32 const* foregroundColor
  )
{
  Machine_Text_Layout_setColor(self->foreground, foregroundColor);
  Ring3_Gui_WidgetBase_emitPositionChangedSignal((Ring3_Gui_WidgetBase*)self);
  Ring3_Gui_WidgetBase_emitSizeChangedSignal((Ring3_Gui_WidgetBase*)self);
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
  Ring3_Graphics2_Context* ctx2 = ((Ring3_Gui_WidgetBase*)self)->context->graphics2Context;
  Ring3_Graphics2_Context_setTargetSize(ctx2, width, height);
  if (self->childDirty) {
    Machine_Gui_Context* ctx = ((Ring3_Gui_WidgetBase*)self)->context;
    Ring3_Graphics2_Rectangle_setRectangle(self->background, Ring3_Gui_Widget_getAbsoluteRectangle((Ring3_Gui_Widget*)self));
    // TODO: Only do this layouting if necessary.
    Ring3_Math_Rectangle2* clipRect = Ring3_Graphics2_Rectangle_getRectangle(self->background);
    Ring3_Math_Vector2f32 const* widgetCenter = Ring3_Math_Rectangle2_getCenter(Ring3_Graphics2_Rectangle_getRectangle(self->background));

    Ring3_Math_Rectangle2 const* textBounds = Machine_Text_Layout_getBounds(self->foreground);
    Ring3_Math_Vector2f32 const* textCenter = Ring3_Math_Rectangle2_getCenter(textBounds);
    Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_difference(widgetCenter, textCenter);
    Ring3_Math_Vector2f32 const* oldPosition = Machine_Text_Layout_getPosition(self->foreground);
    Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_sum(oldPosition, delta);
    Machine_Text_Layout_setPosition(self->foreground, newPosition);
    Machine_Text_Layout_setClipRectangle(self->foreground, clipRect);

    self->childDirty = false;
  }
  Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->background, ctx2);
  Machine_Text_Layout_render(self->foreground, ctx2);
}

static void
Machine_Gui_TextNode_renderImpl
  (
    Machine_Gui_TextNode* self,
    Ring3_Gui_RenderContext* renderContext
  )
{
  Machine_Gui_TextNode_render2(self, Ring3_Gui_RenderContext_getCanvasWidth(renderContext),
                                     Ring3_Gui_RenderContext_getCanvasHeight(renderContext));
}
