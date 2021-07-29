#if !defined(MACHINE_VIDEO_H_INCLUDED)
#define MACHINE_VIDEO_H_INCLUDED

#include "_Images.h"
#include "_Math.h"
#include "_Video.h"
#include "./UtilitiesGL.h"
typedef struct Machine_Binding Machine_Binding;
typedef struct Machine_Images_Image Machine_Images_Image;
typedef struct Machine_ShaderProgram Machine_ShaderProgram;

/// @brief Increment the video module by @a 1.
/// FAILS if the reference count is INT_MAX.
/// @return @a 0 on success, a non-zero value on failure.
void Machine_Video_startup();

/// @brief Decrement the video module by @a 1.
/// UNDEFINED if the reference count is @a 0.
void Machine_Video_shutdown();

/// @brief Create a texture from an image.
/// @param image The image.
/// @return The texture.
Machine_Texture* Machine_Video_createTextureFromImage(Machine_Images_Image* image);

/// @brief Create an empty buffer.
/// @return The buffer.
Machine_VideoBuffer * Machine_Video_createBuffer();

/// @brief Create a program.
/// @param vertexProgramText The vertex program text.
/// @param geometryProgramText The geometry program text.
/// @param fragmentProgramText The fragment program text.
/// @return The program.
Machine_ShaderProgram* Machine_Video_createProgram(Machine_String *vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText);

/// @brief Create a binding.
/// @param program The program.
/// @param vertexDescriptor The vertex descriptor.
/// @param buffer The buffer.
/// @return The binding.
Machine_Binding* Machine_Video_createBinding(Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer);

/// @brief Assign a texture unit.
/// @param unit The index of the texture unit.
/// @param texture A pointer to the texture or the null pointer.
void Machine_Video_bindTexture(size_t unit, Machine_Texture* texture);



/// @brief Set the clear color.
/// @param clearColor The clear color.
void Machine_Video_setClearColor(Machine_Math_Vector4 *clearColor);

/// @brief Get the clear color.
/// @return The clear color.
Machine_Math_Vector4* Machine_Video_getClearColor();


/// @brief Set the blend function for the incoming color.
/// @param incomingBlendFunction The blend function for the incoming color.
void Machine_Video_setIncomingBlendFunction(Machine_BlendFunction incomingBlendFunction);

/// @brief Get the blend function for the incoming color.
/// @return The blend function for the incoming color.
Machine_BlendFunction Machine_Video_getIncomingBlendFunction();


/// @brief Set the blend function for the existing color.
/// @param existingBlendFunction The blend function for the existing color.
void Machine_Video_setExistingBlendFunction(Machine_BlendFunction existingBlendFunction);

/// @brief Get the blend function for the existing color.
/// @return The blend function for the existing color.
Machine_BlendFunction Machine_Video_getExistingBlendFunction();


/// @brief Set if depth write is enabled/disabled.
/// @param depthWriteEnabled @a true enables depth write, @a false disables depth write.
void Machine_Video_setDepthWriteEnabled(bool depthWriteEnabled);

/// @brief Get if depth write is enabled/disabled.
/// @return @a true if depth write is enabled, @a false if depth write is disabled.
bool Machine_Video_getDepthWriteEnabled();


/// @brief Set the depth test function.
/// @param depthTestFunction The depth test function.
void Machine_Video_setDepthTestFunction(Machine_DepthTestFunction depthTestFunction);

/// @brief Get the depth test function.
/// @return The depth test function.
Machine_DepthTestFunction Machine_Video_getDepthTestFunction();


/// @brief Set the clear depth.
/// @param clearDepth The clear depth.
void Machine_Video_setClearDepth(Machine_Real clearDepth);

/// @brief Get the clear depth.
/// @return The clear depth.
Machine_Real Machine_Video_getClearDepth();

/// @brief Set the current viewport rectangle.
/// @param left, bottom The lower left corner of the viewport rectangle.
/// @param width, height The width and height of the viewport rectangle.
void Machine_Video_setViewportRectangle(Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height);

/// @brief Get the current viewport rectangle.
/// @param left, bottom Pointers to variables receiving the lower left corner of the viewport rectangle.
/// @param width, height Pointers to variables receiving the width and height of the viewport rectangle.
void Machine_Video_getViewportRectangle(Machine_Real* left, Machine_Real* bottom, Machine_Real* width, Machine_Real* height);

/// @brief Get the maximal number of clip distance coordinates.
/// @return The number of clip distances.
Machine_Integer Machine_Video_getMaximalClipDistanceCount();

/// @brief Set if the clip distance of the specified index is enabled.
/// @param index The index. Must be greater than or equal @a 0 and smaller than Machine_Video_getMaximalClipDistanceCount();
/// @param enabled @a true to enable the clip distance the specified index, @a false to disable it.
void Machine_Video_setClipDistanceEnabled(Machine_Integer index, Machine_Boolean enabled);

/// @brief Get if the clip distance of the specified index is enabled.
/// @param index The index.
/// @return @a true if the clip distance of the specified index is enabled, @a false if it is disabled.
Machine_Boolean Machine_Video_getClipDistanceEnabled(Machine_Integer index);

/// @brief Clear the color buffer.
/// A sub-rectangle of the color buffer is cleared.
/// That sub-rectangle is the current viewport rectangle.
/// The value the color buffer is clear with is the current color clear value.
void Machine_Video_clearColorBuffer();

/// @brief Clear the sub-rectangle of the depth buffer specified by the current viewport using the current clear depth value.
/// A sub-rectangle of the depth buffer is cleared.
/// That sub-rectangle is the current viewport rectangle.
/// The value the color buffer is clear with is the current depth clear value.
void Machine_Video_clearDepthBuffer();

/// @brief Render @a n consecutive vertices starting with the vertex at (zero-based) index @a 0.
void Machine_Video_drawDirect(Machine_Integer i, Machine_Integer n);

/// @brief Render @a n consecutive indices starting with the index at (zero-based) index @a 0.
void Machine_Video_drawIndirect(Machine_Integer i, Machine_Integer n, uint8_t const* indices);

/// @param withMeshColor <code>vec3 mesh_color</code>
/// @param withVertexColor <code>attribute vec3 vertex_color</code>
/// @param withTextureCoordinate <code>attribute vec2 vertex_texture_coordinate</code>
/// @param withTexture <code>uniform sampler2D texture;</code>. @a withTextureCoordinate must be @a true if this is @a true.
Machine_ShaderProgram*
Machine_Video_generateDefaultShader
  (
    bool withMeshColor,
    bool withVertexColor,
    bool withTextureCoordinate,
    bool withTexture
  );

/// @brief Create a shader program for rendering an untextured, colored, rectangle.
/// @return The shader program.
Machine_ShaderProgram*
Machine_Video_generateShape2Shader
  (
  );

/// @brief Create a shader program for rendering 2D text.
/// Provides <code>vec3 mesh_color</code> to colorize the text.
/// @return The shader program.
Machine_ShaderProgram*
Machine_Video_generateText2Shader
  (
    bool highPrecision
  );



#endif // MACHINE_VIDEO_H_INCLUDED
