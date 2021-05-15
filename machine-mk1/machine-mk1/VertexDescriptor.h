#if !defined(MACHINE_VERTEXDESCRIPTOR_H_INCLUDED)
#define MACHINE_VERTEXDESCRIPTOR_H_INCLUDED



#include "_Runtime.h"
#include "UtilitiesGL.h"



/**
 * @brief Semantics of a vertex element.
 */
typedef enum Machine_VertexElementSemantics Machine_VertexElementSemantics;

enum Machine_VertexElementSemantics {
  /**
   * @brief Vertex element consists of sub-elements "x" and "y" in that order.
   * All sub-elements are of type float.
   */
  Machine_VertexElementSemantics_XfYf,

  /**
   * @brief Vertex element consists of sub-elements "r", "g", and "b" in that order.
   * All sub-elements are of type float and within the bounds of 0 (inclusive) and 1 (inclusive).
   */
   Machine_VertexElementSemantics_RfGfBf,

   /**
    * @brief Vertex element consists of sub-elements "u" and "v" in that order.
    * All sub-elements are of type float.
    */
    Machine_VertexElementSemantics_UfVf,
};

typedef struct Machine_VertexDescriptor Machine_VertexDescriptor;

/**
 * @brief Create a vertex descriptor.
 * @return The vertex descriptor.
 */
Machine_VertexDescriptor* Machine_VertexDescriptor_create();

/**
 * @brief Get the size, in Bytes, of the vertex.
 * @param self The vertex descriptor.
 * @return The size, in Bytes, of the vertex.
 */
size_t Machine_VertexDescriptor_getVertexSize(Machine_VertexDescriptor* self);

/**
 * Get the number of vertex elements.
 * @param self This vertex descriptor.
 * @return The number of vertex elements.
 */
size_t Machine_VertexDescriptor_getNumberOfElements(Machine_VertexDescriptor* self);

/**
 * @brief Get the semantics of a vertex element.
 * @param index The index of the vertex element.
 * @return The semantics.
 */
Machine_VertexElementSemantics Machine_VertexDescriptor_getElementSemantics(Machine_VertexDescriptor* self, size_t index);

/**
 * @brief Get the offset of a vertex element.
 * @param index The index of the vertex element.
 * @return The offset.
 */
size_t Machine_VertexDescriptor_getElementOffset(Machine_VertexDescriptor* self, size_t index);

void Machine_VertexDescriptor_insert(Machine_VertexDescriptor* self, size_t index, Machine_VertexElementSemantics semantics);

void Machine_VertexDescriptor_append(Machine_VertexDescriptor* self, Machine_VertexElementSemantics semantics);

void Machine_VertexDescriptor_prepend(Machine_VertexDescriptor* self, Machine_VertexElementSemantics semantics);


#endif // MACHINE_VERTEXDESCRIPTOR_H_INCLUDED
