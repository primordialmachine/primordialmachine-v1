/// @file Video/VideoContext.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_VIDEOCONTEXT_H_INCLUDED)
#define MACHINE_VIDEO_VIDEOCONTEXT_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif
#include "_Math.h"
#include "Binding.h"
#include "Buffer.h"
#include "BlendFunction.h"
#include "DepthTestFunction.h"
#include "Image.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexDescriptor.h"



/// @brief A video context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_VideoContext)

struct Machine_VideoContext_Class {
  Machine_Object_Class parent;



  void (*setClearColor)(Machine_VideoContext* self, Machine_Math_Vector4 const* clearColor);

  Machine_Math_Vector4 const* (*getClearColor)(Machine_VideoContext const* self);



  void (*setIncomingBlendFunction)(Machine_VideoContext* self, Machine_BlendFunction incomingBlendFunction);

  Machine_BlendFunction(*getIncomingBlendFunction)(Machine_VideoContext const* self);



  void (*setExistingBlendFunction)(Machine_VideoContext* self, Machine_BlendFunction existingBlendFunction);

  Machine_BlendFunction(*getExistingBlendFunction)(Machine_VideoContext const* self);



  void (*setDepthWriteEnabled)(Machine_VideoContext* self, Machine_Boolean depthWriteEnabled);

  Machine_Boolean(*getDepthWriteEnabled)(Machine_VideoContext const* self);



  void (*setDepthTestFunction)(Machine_VideoContext* self, Machine_DepthTestFunction depthTestFunction);

  Machine_DepthTestFunction(*getDepthTestFunction)(Machine_VideoContext const* self);



  void (*setClearDepth)(Machine_VideoContext* self, Machine_Real clearDepth);

  Machine_Real(*getClearDepth)(Machine_VideoContext const* self);



  void (*setViewportRectangle)(Machine_VideoContext* self, Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height);

  void (*getViewportRectangle)(Machine_VideoContext const* self, Machine_Real* left, Machine_Real* bottom, Machine_Real* width, Machine_Real* height);



  Machine_Integer(*getMaximalClipDistanceCount)(Machine_VideoContext const* self);

  void (*setClipDistanceEnabled)(Machine_VideoContext* self, Machine_Integer index, Machine_Boolean enabled);

  Machine_Boolean(*getClipDistanceEnabled)(Machine_VideoContext const* self, Machine_Integer index);



  void (*clearColorBuffer)(Machine_VideoContext* self);

  void (*clearDepthBuffer)(Machine_VideoContext* self);

  Machine_VideoBuffer* (*createBuffer)(Machine_VideoContext* self);

  Machine_Texture* (*createTextureFromImage)(Machine_VideoContext* self, Machine_Image* image);

  Machine_ShaderProgram* (*createProgram)(Machine_VideoContext* self, Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText);

  Machine_Binding* (*createBinding)(Machine_VideoContext* self, Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer);

  void (*drawDirect)(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n);

  void (*drawIndirect)(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n, uint8_t const* indices);



  void (*bindTexture)(Machine_VideoContext* self, size_t unit, Machine_Texture* texture);



  Machine_ShaderProgram*
    (*generateDefaultShader)
      (
        Machine_VideoContext* self,
        Machine_Boolean withMeshColor,
        Machine_Boolean withVertexColor,
        Machine_Boolean withTextureCoordinate,
        Machine_Boolean withTexture
      );

  Machine_ShaderProgram*
    (*generateShape2Shader)
      (
        Machine_VideoContext* self
      );

  Machine_ShaderProgram*
    (*generateText2Shader)
      (
        Machine_VideoContext* self,
        Machine_Boolean highPrecision
      );
};

struct Machine_VideoContext {
  Machine_Object parent;
};



void Machine_VideoContext_construct(Machine_VideoContext* self, size_t numberOfArguments, Machine_Value const* arguments);



/// @brief Set the clear color.
/// @param self This video context.
/// @param clearColor The clear color.
void Machine_VideoContext_setClearColor(Machine_VideoContext* self, Machine_Math_Vector4 const* clearColor);

/// @brief Get the clear color.
/// @param self This video context.
/// @return The clear color.
/// @default Default color is opaque black.
Machine_Math_Vector4 const* Machine_VideoContext_getClearColor(Machine_VideoContext const* self);



/// @brief Set the blend function for the incoming color.
/// @param self This video context.
/// @param incomingBlendFunction The blend function for the incoming color.
void Machine_VideoContext_setIncomingBlendFunction(Machine_VideoContext* self, Machine_BlendFunction incomingBlendFunction);

/// @brief Get the blend function for the incoming color.
/// @param self This video context.
/// @return The blend function for the incoming color.
/// @default Default is <code>incoming alpha</code>.
Machine_BlendFunction Machine_VideoContext_getIncomingBlendFunction(Machine_VideoContext const* self);



/// @brief Set the blend function for the existing color.
/// @param self This video context.
/// @param existingBlendFunction The blend function for the existing color.
void Machine_VideoContext_setExistingBlendFunction(Machine_VideoContext* self, Machine_BlendFunction existingBlendFunction);

/// @brief Get the blend function for the existing color.
/// @param self This video context.
/// @return The blend function for the existing color.
/// @default Default is <code>one minus incoming alpha</code>.
Machine_BlendFunction Machine_VideoContext_getExistingBlendFunction(Machine_VideoContext const* self);



/// @brief Set if depth write is enabled/disabled.
/// @param self This video context.
/// @param depthWriteEnabled @a true enables depth write, @a false disables depth write.
void Machine_VideoContext_setDepthWriteEnabled(Machine_VideoContext* self, Machine_Boolean depthWriteEnabled);

/// @brief Get if depth write is enabled/disabled.
/// @param self This video context.
/// @return @a true if depth write is enabled, @a false if depth write is disabled.
/// @default Default is <code>false</code>.
Machine_Boolean Machine_VideoContext_getDepthWriteEnabled(Machine_VideoContext const* self);



/// @brief Set the depth test function.
/// @param self This video context.
/// @param depthTestFunction The depth test function.
void Machine_VideoContext_setDepthTestFunction(Machine_VideoContext* self, Machine_DepthTestFunction depthTestFunction);

/// @brief Get the depth test function.
/// @param self This video context.
/// @return The depth test function.
/// @default The default depth test function is <code>always/</code>.
Machine_DepthTestFunction Machine_VideoContext_getDepthTestFunction(Machine_VideoContext const* self);



/// @brief Set the clear depth.
/// @param self This video context.
/// @param clearDepth The clear depth.
void Machine_VideoContext_setClearDepth(Machine_VideoContext* self, Machine_Real clearDepth);

/// @brief Get the clear depth.
/// @param self This video context.
/// @return The clear depth.
/// @default The default clear depth is @a 1.
Machine_Real Machine_VideoContext_getClearDepth(Machine_VideoContext const* self);



/// @brief Set the current viewport rectangle.
/// @param self This video context.
/// @param left, bottom The lower left corner of the viewport rectangle.
/// @param width, height The width and height of the viewport rectangle.
void Machine_VideoContext_setViewportRectangle(Machine_VideoContext* self, Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height);

/// @brief Get the current viewport rectangle.
/// @param self This video context.
/// @param left, bottom Pointers to variables receiving the lower left corner of the viewport rectangle.
/// @param width, height Pointers to variables receiving the width and height of the viewport rectangle.
/// @default By default @a left and @a bottom are both @a 0 and @a width and @a height are the width and height of the target canvas.
void Machine_VideoContext_getViewportRectangle(Machine_VideoContext const* self, Machine_Real* left, Machine_Real* bottom, Machine_Real* width, Machine_Real* height);



/// @brief Get the maximal number of clip distance coordinates.
/// @param self This video context.
/// @return The number of clip distances.
Machine_Integer Machine_VideoContext_getMaximalClipDistanceCount(Machine_VideoContext const* self);

/// @brief Set if the clip distance of the specified index is enabled.
/// @param self This video context.
/// @param index The index. Must be greater than or equal @a 0 and smaller than Machine_Video_getMaximalClipDistanceCount();
/// @param enabled @a true to enable the clip distance the specified index, @a false to disable it.
void Machine_VideoContext_setClipDistanceEnabled(Machine_VideoContext* self, Machine_Integer index, Machine_Boolean enabled);

/// @brief Get if the clip distance of the specified index is enabled.
/// @param self This video context.
/// @param index The index.
/// @return @a true if the clip distance of the specified index is enabled, @a false if it is disabled.
Machine_Boolean Machine_VideoContext_getClipDistanceEnabled(Machine_VideoContext const* self, Machine_Integer index);



/// @brief Clear the color buffer.
/// A sub-rectangle of the color buffer is cleared.
/// That sub-rectangle is the current viewport rectangle.
/// The value the color buffer is clear with is the current color clear value.
/// @param self This video context.
void Machine_VideoContext_clearColorBuffer(Machine_VideoContext* self);

/// @brief Clear the sub-rectangle of the depth buffer specified by the current viewport using the current clear depth value.
/// A sub-rectangle of the depth buffer is cleared.
/// That sub-rectangle is the current viewport rectangle.
/// The value the color buffer is clear with is the current depth clear value.
/// @param self This video context.
void Machine_VideoContext_clearDepthBuffer(Machine_VideoContext* self);

/// @brief Create a texture from an image.
/// @param self This video context.
/// @param image The image.
/// @return The texture.
Machine_Texture* Machine_VideoContext_createTextureFromImage(Machine_VideoContext* self, Machine_Image* image);

/// @brief Create an empty buffer.
/// @param self This video context.
/// @return The buffer.
Machine_VideoBuffer* Machine_VideoContext_createBuffer(Machine_VideoContext* self);

/// @brief Create a program.
/// @param self This video context.
/// @param vertexProgramText The vertex program text.
/// @param geometryProgramText The geometry program text.
/// @param fragmentProgramText The fragment program text.
/// @return The program.
Machine_ShaderProgram* Machine_VideoContext_createProgram(Machine_VideoContext* self, Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText);

/// @brief Create a binding.
/// @param self This video context.
/// @param program The program.
/// @param vertexDescriptor The vertex descriptor.
/// @param buffer The buffer.
/// @return The binding.
Machine_Binding* Machine_VideoContext_createBinding(Machine_VideoContext* self, Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer);

/// @brief Render @a n consecutive vertices starting with the vertex at (zero-based) index @a 0.
/// @param self This video context.
/// @param i, n The starting index of the range and its length.
void Machine_VideoContext_drawDirect(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n);

/// @brief Render @a n consecutive indices starting with the index at (zero-based) index @a 0.
/// @param self This video context.
/// @param i, n The starting index of the range and its length.
/// @param A pointer to at least <code>i ´+ n</code> indices.
void Machine_VideoContext_drawIndirect(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n, uint8_t const* indices);



/// @brief Assign a texture unit.
/// @param unit The index of the texture unit.
/// @param texture A pointer to the texture or the null pointer.
void Machine_VideoContext_bindTexture(Machine_VideoContext* self, size_t unit, Machine_Texture* texture);



/// @param self This video context.
/// @param withMeshColor <code>vec3 mesh_color</code>
/// @param withVertexColor <code>attribute vec3 vertex_color</code>
/// @param withTextureCoordinate <code>attribute vec2 vertex_texture_coordinate</code>
/// @param withTexture <code>uniform sampler2D texture;</code>. @a withTextureCoordinate must be @a true if this is @a true.
Machine_ShaderProgram*
Machine_VideoContext_generateDefaultShader
  (
    Machine_VideoContext* self,
    Machine_Boolean withMeshColor,
    Machine_Boolean withVertexColor,
    Machine_Boolean withTextureCoordinate,
    Machine_Boolean withTexture
  );

/// @brief Create a shader program for rendering an untextured, colored, rectangle.
/// @param self This video context.
/// @return The shader program.
Machine_ShaderProgram*
Machine_VideoContext_generateShape2Shader
  (
    Machine_VideoContext* self
  );

/// @brief Create a shader program for rendering 2D text.
/// Provides <code>vec3 mesh_color</code> to colorize the text.
/// @param self This video context.
/// @return The shader program.
Machine_ShaderProgram*
Machine_VideoContext_generateText2Shader
  (
    Machine_VideoContext* self,
    Machine_Boolean highPrecision
  );



#endif // MACHINE_VIDEO_VIDEOCONTEXT_H_INCLUDED
