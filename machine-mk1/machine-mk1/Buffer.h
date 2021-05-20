#if !defined(MACHINE_BUFFER_H_INCLUDED)
#define MACHINE_BUFFER_H_INCLUDED


#include "UtilitiesGL.h"


MACHINE_DECLARE_CLASSTYPE(Machine_Uint8Buffer)

/**
 * @brief Create a managed mesh.
 * @return The mesh.
 */
Machine_Uint8Buffer* Machine_Uint8Buffer_create();

/**
 * @brief Set the uint8_t values.
 * @param n The number of uint8_t values.
 * @param p The uint8_t values.
 */
void Machine_Uint8Buffer_setData(Machine_Uint8Buffer* self, size_t n, uint8_t* p);

/**
 * @brief Get the floats.
 * @return The floats.
 */
uint8_t* Machine_Uint8Buffer_getData(Machine_Uint8Buffer* self);

/**
 * @brief Get the number of floats.
 * @return The number of floats.
 */
size_t Machine_Uint8Buffer_getSize(Machine_Uint8Buffer* self);

GLuint Machine_Uint8Buffer_getId(Machine_Uint8Buffer* self);



typedef struct Machine_FloatBuffer Machine_FloatBuffer;

/**
 * @brief Create a managed mesh.
 * @return The mesh.
 */
Machine_FloatBuffer* Machine_FloatBuffer_create();

/**
 * @brief Set the float values.
 * @param n The number of float values.
 * @param p The float values.
 */
void Machine_FloatBuffer_setData(Machine_FloatBuffer* self, size_t n, const float* p);

/**
 * @brief Get the floats.
 * @return The floats.
 */
float* Machine_FloatBuffer_getData(Machine_FloatBuffer* self);

/**
 * @brief Get the number of floats.
 * @return The number of floats.
 */
size_t Machine_Floatbuffer_getSize(Machine_FloatBuffer* self);

GLuint Machine_FloatBuffer_getId(Machine_FloatBuffer* self);



#endif // MACHINE_BUFFER_H_INCLUDED
