/// @file Graphics2/Context2.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GRAPHICS2_CONTEXT2_H_INCLUDED)
#define MACHINE_GRAPHICS2_CONTEXT2_H_INCLUDED



#if !defined(MACHINE_GRAPHICS2_PRIVATE)
#error("Do not include `Graphics2/Context2.h` directly, include `_Graphics2.h` instead.")
#endif
#include "_Math.h"
#include "_Video.h"



/// C-level representation of a graphics context for 2D graphics.
/// @extends Machine_Object
MACHINE_DECLARE_CLASSTYPE(Machine_Context2);

struct Machine_Context2_Class {
  Machine_Object_Class parent;
};

struct Machine_Context2 {
  Machine_Object parent;

  Machine_VideoContext* videoContext;

  /// @brief The combined model space to projection space transformation matrix.
  Machine_Math_Matrix4* modelSpaceToProjectiveSpace;
  /// @brief the combined model space to world space transformation matrix.
  Machine_Math_Matrix4* modelSpaceToWorldSpace;

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
  Machine_ShaderProgram* shader;
  /// @brief A vertex buffer.
  Machine_VideoBuffer* vertices;
  /// @brief Binding connection shader, vertex buffer, and a constants.
  Machine_Binding* binding;
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
void Machine_Context2_construct(Machine_Context2* self, size_t numberOfArguments, Ring2_Value const* arguments);

/// @brief Create a context with default values.
/// @param videoContext The video context.
/// @return The context.
Machine_Context2* Machine_Context2_create(Machine_VideoContext* videoContext);

/// @brief Set the width and height of the canvas.
/// @param self This context.
/// @param width, height The width and height of the canvas.
void Machine_Context2_setTargetSize(Machine_Context2* self, Ring2_Real32 width, Ring2_Real32 height);

/// @brief Get the width of the canvas.
/// @param self This context.
/// @return The width of the canvas.
Ring2_Real32 Machine_Context2_getTargetWidth(Machine_Context2 const* self);

/// @brief Get the height of the canvas.
/// @param self This context.
/// @return The height of the canvas.
Ring2_Real32 Machine_Context2_getTargetHeight(Machine_Context2 const* self);

/// @brief Get the model space to projective space transformation matrix.
/// @param self This context.
/// @return The model space to projective space transformation matrix.
Machine_Math_Matrix4 const *Machine_Context2_getModelSpaceToProjectiveSpaceMatrix(Machine_Context2 const* self);

/// @brief Get the model space to world space transformation matrix.
/// @param self This context.
/// @return The model space to world space transformation matrix.
Machine_Math_Matrix4 const* Machine_Context2_getModelSpaceToWorldSpaceMatrix(Machine_Context2 const* self);

/// @brief Set if the origin of the coordinate system is mapped to the bottom/left corner or the top/left corner of the canvas.
/// @param self This context.
/// @param originBottomLeft
/// @a true maps the origin to the bottom/left corner of the canvas,
/// @a false maps the origin to the top/left corner of the canvas.
void Machine_Context2_setOriginBottomLeft(Machine_Context2* self, Ring2_Boolean originBottomLeft);

/// @brief Get if the origin of the coordinate system is mapped to the bottom/left corner or the top/left corner of the canvas.
/// @param self This context.
/// @return
/// @a true if the origin is mapped to the bottom/left corner of th canvas,
/// @a false if the origin is mapped to the top/left corner of the canvas.
/// @default @a true
Ring2_Boolean Machine_Context2_getOriginBottomLeft(Machine_Context2 const* self);



#endif // MACHINE_GRAPHICS2_CONTEXT2_H_INCLUDED
