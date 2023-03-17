/// @file Ring3/Graphics2/Context.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GRAPHICS2_CONTEXT_H_INCLUDED)
#define RING3_GRAPHICS2_CONTEXT_H_INCLUDED

#if !defined(RING3_GRAPHICS2_PRIVATE)
#error("Do not include `Ring3/Graphics2/Context.h` directly. Include `Ring3/raphics2/_Include.h` instead.")
#endif
#include "Ring3/Math/_Include.h"
#include "Ring3/Visuals/_Include.h"

/// @brief
/// C-level representation of a graphics context for 2D graphics.
/// @extends Machine_Object
MACHINE_DECLARE_CLASSTYPE(Ring3_Graphics2_Context);

struct Ring3_Graphics2_Context_Class {
  Machine_Object_Class parent;
};

struct Ring3_Graphics2_Context {
  Machine_Object parent;

  Ring3_VisualsContext* visualsContext;
  Ring3_ImagesContext* imagesContext;
  Ring3_FontsContext* fontsContext;

  /// @brief The combined model space to projection space transformation matrix.
  Ring3_Math_Matrix4x4f32* modelSpaceToProjectiveSpace;
  /// @brief the combined model space to world space transformation matrix.
  Ring3_Math_Matrix4x4f32* modelSpaceToWorldSpace;

  /// @brief The width, in pixels, of the render target.
  Ring2_Real32 width;
  
  /// @brief The height, in pixels, of the render target.
  Ring2_Real32 height;

  /// @brief The aspect ratio i.e. <code>width / height</code> of the render target.
  /// Mapped to @a 0 if @a height is @a 0.
  Ring2_Real32 aspectRatio;

  /// @brief
  /// If this is true:
  /// - the origin is the left/bottom corner of the render target.
  /// - the positive x-axis points to the right border, the positive y-axis points to the top border.
  /// Otherwise:
  /// - the origin is the left/top corner of the render target.
  /// -  the positive x-axis points to the right border, the positive y-axis points to the bottom border.
  Ring2_Boolean originBottomLeft;

  /// @brief The default shader.
  Ring3_GpuProgram* shader;
  /// @brief A vertex buffer.
  Ring3_GpuBuffer* vertices;
  /// @brief Binding connection shader, vertex buffer, and a constants.
  Ring3_Binding* binding;
};

/// @brief Construct this context with default values.
/// The default width is @a 0, the default height is @a 0, the default aspect ratio is @a 0.
/// The initial model space to world space transformation matrix is the identity matrix.
/// The initial model space to projective space transformation matrix is the identity matrix.
/// the coordinate system is a cartesian coordinate system such that:
/// - <code>(0,0)</code> is at the bottom/left of the canvas,
/// - <code>(0,height)</code> is at the top/left of the canvas, and
/// - <code>(width, 0)</code> is at the bottom/right of the canvas. 
/// @param self This context.
/// @param numberOfArguments, arguments The arguments.
void
Ring3_Graphics2_Context_construct
  (
    Ring3_Graphics2_Context* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a context with default values.
/// @param visualsContext The video context.
/// @return The context.
Ring1_NoDiscardReturn() Ring3_Graphics2_Context*
Ring3_Graphics2_Context_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

/// @brief Set the width and height of the canvas.
/// @param self This context.
/// @param width, height The width and height of the canvas.
void
Ring3_Graphics2_Context_setTargetSize
  (
    Ring3_Graphics2_Context* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  );

/// @brief Get the width of the canvas.
/// @param self This context.
/// @return The width of the canvas.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Graphics2_Context_getTargetWidth
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Get the height of the canvas.
/// @param self This context.
/// @return The height of the canvas.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Graphics2_Context_getTargetHeight
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Get the model space to projective space transformation matrix.
/// @param self This context.
/// @return The model space to projective space transformation matrix.
/// A copy of the matrix is returned.
Ring1_NoDiscardReturn() Ring3_Math_Matrix4x4f32 *
Ring3_Graphics2_Context_getModelSpaceToProjectiveSpaceMatrix
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Get the model space to world space transformation matrix.
/// @param self This context.
/// @return The model space to world space transformation matrix.
/// A copy of the matrix is returned.
Ring1_NoDiscardReturn() Ring3_Math_Matrix4x4f32*
Ring3_Graphics2_Context_getModelSpaceToWorldSpaceMatrix
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Set if the origin of the coordinate system is mapped to the bottom/left corner or the top/left corner of the canvas.
/// @param self This context.
/// @param originBottomLeft
/// @a true maps the origin to the bottom/left corner of the canvas,
/// @a false maps the origin to the top/left corner of the canvas.
void
Ring3_Graphics2_Context_setOriginBottomLeft
  (
    Ring3_Graphics2_Context* self,
    Ring2_Boolean originBottomLeft
  );

/// @brief Get if the origin of the coordinate system is mapped to the bottom/left corner or the top/left corner of the canvas.
/// @param self This context.
/// @return
/// @a true if the origin is mapped to the bottom/left corner of th canvas,
/// @a false if the origin is mapped to the top/left corner of the canvas.
/// @default @a true
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Graphics2_Context_getOriginBottomLeft
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Get the video context.
/// @param self This context.
/// @return The video context.
Ring1_NoDiscardReturn() Ring3_VisualsContext*
Ring3_Graphics2_Context_getVisualsContext
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Get the images context.
/// @param self This context.
/// @return The images context.
Ring1_NoDiscardReturn() Ring3_ImagesContext*
Ring3_Graphics2_Context_getImagesContext
  (
    Ring3_Graphics2_Context const* self
  );

/// @brief Get the fonts context.
/// @param self This context.
/// @return The fonts context.
Ring1_NoDiscardReturn() Ring3_FontsContext*
Ring3_Graphics2_Context_getFontsContext
  (
    Ring3_Graphics2_Context const* self
  );

#endif // RING3_GRAPHICS2_CONTEXT_H_INCLUDED
