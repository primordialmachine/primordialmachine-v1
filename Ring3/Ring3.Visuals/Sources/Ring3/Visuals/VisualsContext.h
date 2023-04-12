/// @file Ring3/Visuals/VisualsContext.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_VISUALSCONTEXT_H_INCLUDED)
#define RING3_VISUALS_VISUALSCONTEXT_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/VisualsContext.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"

/// @brief A video context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Ring3_VisualsContext)

struct Ring3_VisualsContext_Class {
  Machine_Object_Class parent;

  void (*setClearColor)(Ring3_VisualsContext*,
                        Ring3_Math_Vector4f32 const*);

  Ring3_Math_Vector4f32 const* (*getClearColor)(Ring3_VisualsContext const*);

  void (*setIncomingBlendFunction)(Ring3_VisualsContext*,
                                   Ring3_BlendFunction);

  Ring3_BlendFunction (*getIncomingBlendFunction)(Ring3_VisualsContext const*);

  void (*setExistingBlendFunction)(Ring3_VisualsContext*,
                                   Ring3_BlendFunction);

  Ring3_BlendFunction (*getExistingBlendFunction)(Ring3_VisualsContext const*);

  void (*setDepthWriteEnabled)(Ring3_VisualsContext*,
                               Ring2_Boolean);

  Ring2_Boolean (*getDepthWriteEnabled)(Ring3_VisualsContext const*);

  void (*setDepthTestFunction)(Ring3_VisualsContext*,
                               Ring3_DepthTestFunction);

  Ring3_DepthTestFunction (*getDepthTestFunction)(Ring3_VisualsContext const* self);

  void (*setClearDepth)(Ring3_VisualsContext* self,
                        Ring2_Real32);

  Ring2_Real32 (*getClearDepth)(Ring3_VisualsContext const*);

  void (*setViewportRectangle)(Ring3_VisualsContext*,
                               Ring2_Real32,
                               Ring2_Real32,
                               Ring2_Real32,
                               Ring2_Real32);

  void (*getViewportRectangle)(Ring3_VisualsContext const*,
                               Ring2_Real32*,
                               Ring2_Real32*,
                               Ring2_Real32*,
                               Ring2_Real32*);

  Ring2_Integer (*getMaximalClipDistanceCount)(Ring3_VisualsContext const*);

  void (*setClipDistanceEnabled)(Ring3_VisualsContext* self,
                                 Ring2_Integer,
                                 Ring2_Boolean);

  Ring2_Boolean (*getClipDistanceEnabled)(Ring3_VisualsContext const*,
                                          Ring2_Integer);

  void (*clearColorBuffer)(Ring3_VisualsContext*);

  void (*clearDepthBuffer)(Ring3_VisualsContext*);

  Ring3_GpuBuffer* (*createBuffer)(Ring3_VisualsContext*);

  Ring3_Texture* (*createTextureFromImage)(Ring3_VisualsContext*,
                                           Ring3_Image*);

  Ring3_GpuProgram* (*createProgram)(Ring3_VisualsContext*,
                                     Ring2_String*,
                                     Ring2_String*,
                                     Ring2_String*);

  Ring3_Binding* (*createBinding)(Ring3_VisualsContext*,
                                  Ring3_GpuProgram*,
                                  Ring3_VertexDescriptor*,
                                  Ring3_GpuBuffer*);

  void (*drawDirect)(Ring3_VisualsContext* self, Ring2_Integer i, Ring2_Integer n);

  void (*drawIndirect)(Ring3_VisualsContext* self, Ring2_Integer i, Ring2_Integer n,
                       uint8_t const* indices);

  void (*bindTexture)(Ring3_VisualsContext* self, size_t unit, Ring3_Texture* texture);

  Ring3_GpuProgram* (*generateDefaultShader)(Ring3_VisualsContext* self,
                                             Ring2_Boolean withMeshColor,
                                             Ring2_Boolean withVertexColor,
                                             Ring2_Boolean withTextureCoordinate,
                                             Ring2_Boolean withTexture);

  Ring3_GpuProgram* (*generateShape2Shader)(Ring3_VisualsContext* self);

  Ring3_GpuProgram* (*generateText2Shader)(Ring3_VisualsContext* self,
                                           Ring2_Boolean highPrecision);
};

struct Ring3_VisualsContext {
  Machine_Object parent;
};

void
Ring3_VisualsContext_construct
  (
    Ring3_VisualsContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Set the clear color.
/// @param self This video context.
/// @param clearColor The clear color.
void
Ring3_VisualsContext_setClearColor
  (
    Ring3_VisualsContext* self,
    Ring3_Math_Vector4f32 const* clearColor
  );

/// @brief Get the clear color.
/// @param self This video context.
/// @return The clear color.
/// @default Default color is opaque black.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32 const*
Ring3_VisualsContext_getClearColor
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set the blend function for the incoming color.
/// @param self This video context.
/// @param incomingBlendFunction The blend function for the incoming color.
void
Ring3_VisualsContext_setIncomingBlendFunction
  (
    Ring3_VisualsContext* self,
    Ring3_BlendFunction incomingBlendFunction
  );

/// @brief Get the blend function for the incoming color.
/// @param self This video context.
/// @return The blend function for the incoming color.
/// @default Default is <code>incoming alpha</code>.
Ring1_NoDiscardReturn() Ring3_BlendFunction
Ring3_VisualsContext_getIncomingBlendFunction
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set the blend function for the existing color.
/// @param self This video context.
/// @param existingBlendFunction The blend function for the existing color.
void
Ring3_VisualsContext_setExistingBlendFunction
  (
    Ring3_VisualsContext* self,
    Ring3_BlendFunction existingBlendFunction
  );

/// @brief Get the blend function for the existing color.
/// @param self This video context.
/// @return The blend function for the existing color.
/// @default Default is <code>one minus incoming alpha</code>.
Ring1_NoDiscardReturn() Ring3_BlendFunction
Ring3_VisualsContext_getExistingBlendFunction
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set if depth write is enabled/disabled.
/// @param self This video context.
/// @param depthWriteEnabled @a true enables depth write, @a false disables depth write.
void
Ring3_VisualsContext_setDepthWriteEnabled
  (
    Ring3_VisualsContext* self,
    Ring2_Boolean depthWriteEnabled
  );

/// @brief Get if depth write is enabled/disabled.
/// @param self This video context.
/// @return @a true if depth write is enabled, @a false if depth write is disabled.
/// @default Default is <code>false</code>.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_VisualsContext_getDepthWriteEnabled
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set the depth test function.
/// @param self This video context.
/// @param depthTestFunction The depth test function.
void
Ring3_VisualsContext_setDepthTestFunction
  (
    Ring3_VisualsContext* self,
    Ring3_DepthTestFunction depthTestFunction
  );

/// @brief Get the depth test function.
/// @param self This video context.
/// @return The depth test function.
/// @default The default depth test function is <code>always/</code>.
Ring1_NoDiscardReturn() Ring3_DepthTestFunction
Ring3_VisualsContext_getDepthTestFunction
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set the clear depth.
/// @param self This video context.
/// @param clearDepth The clear depth.
void
Ring3_VisualsContext_setClearDepth
  (
    Ring3_VisualsContext* self,
    Ring2_Real32 clearDepth
  );

/// @brief Get the clear depth.
/// @param self This video context.
/// @return The clear depth.
/// @default The default clear depth is @a 1.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_VisualsContext_getClearDepth
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set the current viewport rectangle.
/// @param self This video context.
/// @param left, bottom The lower left corner of the viewport rectangle.
/// @param width, height The width and height of the viewport rectangle.
void
Ring3_VisualsContext_setViewportRectangle
  (
    Ring3_VisualsContext* self,
    Ring2_Real32 left,
    Ring2_Real32 bottom,
    Ring2_Real32 width,
    Ring2_Real32 height
  );

/// @brief Get the current viewport rectangle.
/// @param self This video context.
/// @param left, bottom Pointers to variables receiving the lower left corner of the viewport
/// rectangle.
/// @param width, height Pointers to variables receiving the width and height of the viewport
/// rectangle.
/// @default By default @a left and @a bottom are both @a 0 and @a width and @a height are the width
/// and height of the target canvas.
void
Ring3_VisualsContext_getViewportRectangle
  (
    Ring3_VisualsContext const* self,
    Ring2_Real32* left,
    Ring2_Real32* bottom,
    Ring2_Real32* width,
    Ring2_Real32* height
  );

/// @brief Get the maximal number of clip distance coordinates.
/// @param self This video context.
/// @return The number of clip distances.
Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VisualsContext_getMaximalClipDistanceCount
  (
    Ring3_VisualsContext const* self
  );

/// @brief Set if the clip distance of the specified index is enabled.
/// @param self This video context.
/// @param index The index. Must be greater than or equal @a 0 and smaller than
/// Machine_Video_getMaximalClipDistanceCount();
/// @param enabled @a true to enable the clip distance the specified index, @a false to disable it.
void
Ring3_VisualsContext_setClipDistanceEnabled
  (
    Ring3_VisualsContext* self,
    Ring2_Integer index,
    Ring2_Boolean enabled
  );

/// @brief Get if the clip distance of the specified index is enabled.
/// @param self This video context.
/// @param index The index.
/// @return @a true if the clip distance of the specified index is enabled, @a false if it is
/// disabled.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_VisualsContext_getClipDistanceEnabled
  (
    Ring3_VisualsContext const* self,
    Ring2_Integer index
  );

/// @brief Clear the color buffer.
/// A sub-rectangle of the color buffer is cleared.
/// That sub-rectangle is the current viewport rectangle.
/// The value the color buffer is clear with is the current color clear value.
/// @param self This video context.
void
Ring3_VisualsContext_clearColorBuffer
  (
    Ring3_VisualsContext* self
  );

/// @brief Clear the sub-rectangle of the depth buffer specified by the current viewport using the
/// current clear depth value. A sub-rectangle of the depth buffer is cleared. That sub-rectangle is
/// the current viewport rectangle. The value the color buffer is clear with is the current depth
/// clear value.
/// @param self This video context.
void
Ring3_VisualsContext_clearDepthBuffer
  (
    Ring3_VisualsContext* self
  );

/// @brief Create a texture from an image.
/// @param self This video context.
/// @param image The image.
/// @return The texture.
Ring1_NoDiscardReturn() Ring3_Texture*
Ring3_VisualsContext_createTextureFromImage
  (
    Ring3_VisualsContext* self,
    Ring3_Image* image
  );

/// @brief Create an empty buffer.
/// @param self This video context.
/// @return The buffer.
Ring1_NoDiscardReturn() Ring3_GpuBuffer*
Ring3_VisualsContext_createBuffer
  (
    Ring3_VisualsContext* self
  );

/// @brief Create a program.
/// @param self This video context.
/// @param vertexProgramText The vertex program text.
/// @param geometryProgramText The geometry program text.
/// @param fragmentProgramText The fragment program text.
/// @return The program.
Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_createProgram
  (
    Ring3_VisualsContext* self,
    Ring2_String* vertexProgramText,
    Ring2_String* geometryProgramText,
    Ring2_String* fragmentProgramText
  );

/// @brief Create a binding.
/// @param self This video context.
/// @param program The program.
/// @param vertexDescriptor The vertex descriptor.
/// @param buffer The buffer.
/// @return The binding.
Ring1_NoDiscardReturn() Ring3_Binding*
Ring3_VisualsContext_createBinding
  (
    Ring3_VisualsContext* self,
    Ring3_GpuProgram* program,
    Ring3_VertexDescriptor* vertexDescriptor,
    Ring3_GpuBuffer* buffer
  );

/// @brief Render @a n consecutive vertices starting with the vertex at (zero-based) index @a 0.
/// @param self This video context.
/// @param i, n The starting index of the range and its length.
void
Ring3_VisualsContext_drawDirect
  (
    Ring3_VisualsContext* self,
    Ring2_Integer i,
    Ring2_Integer n
  );

/// @brief Render @a n consecutive indices starting with the index at (zero-based) index @a 0.
/// @param self This video context.
/// @param i, n The starting index of the range and its length.
/// @param A pointer to at least <code>i ´+ n</code> indices.
void
Ring3_VisualsContext_drawIndirect
  (
    Ring3_VisualsContext* self,
    Ring2_Integer i,
    Ring2_Integer n,
    uint8_t const* indices
  );

/// @brief Assign a texture unit.
/// @param unit The index of the texture unit.
/// @param texture A pointer to the texture or the null pointer.
void
Ring3_VisualsContext_bindTexture
  (
    Ring3_VisualsContext* self,
    size_t unit,
    Ring3_Texture* texture
  );

/// @param self This video context.
/// @param withMeshColor <code>vec3 meshColor</code>
/// @param withVertexColor <code>attribute vec3 vertexColor</code>
/// @param withTextureCoordinate <code>attribute vec2 vertexTextureCoordinate1</code>
/// @param withTexture <code>uniform sampler2D texture;</code>.
/// @a withTextureCoordinate must be @a true if this is @a true.
Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_generateDefaultShader
  (
    Ring3_VisualsContext* self,
    Ring2_Boolean withMeshColor,
    Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate,
    Ring2_Boolean withTexture
  );

/// @brief Create a shader program for rendering an monochrome shapes in 2D.
/// @param self This video context.
/// @return The shader program.
Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_generateShape2Shader
  (
    Ring3_VisualsContext* self
  );

/// @brief Create a shader program for rendering monochrome 2D text based on texture fonts.
/// Provides <code>vec3 meshColor</code> to colorize the text.
/// @param self This video context.
/// @return The shader program.
Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_generateText2Shader
  (
    Ring3_VisualsContext* self,
    Ring2_Boolean highPrecision
  );

#endif // RING3_VISUALS_VISUALSCONTEXT_H_INCLUDED
