/// @file Font.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_FONTS_PRIVATE (1)
#include "Font.h"


#include "Ring1/Intrinsic.h"
#include "Ring1/Status.h"
#include "FontsContext.h"
#include <inttypes.h>
#include <ft2build.h>
#include FT_FREETYPE_H


typedef struct Node Node;

struct Node {
  Node* next;
  /// @brief Unicode code point.
  uint32_t codepoint;
  /// @brief The texture.
  Machine_Texture* texture;
  /// @brief Add bearingx to the cursor position before rendering.
  float bearingx;
  /// @brief Add h - bearingy to the cursor position before rendering.
  float bearingy;
  /// @brief left, top, width, height in pixels.
  /// @remark Left and top are usually 0.
  float w, h;
  /// @brief Advance in pixels.
  float advancex;
  /// @brief Advance in pixels.
  float advancey;
};

typedef struct Map Map;

struct Map {
  Node** buckets;
  size_t size, capacity;
};

static void Map_visit(void *gc, Map* self) {
  for (size_t i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      Ring2_Gc_visit(Ring2_Gc_get(), node->texture);
      node = node->next;
    }
  }
}

static void Map_finalize(void *gc, Map* self) {
  for (size_t i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = node->next;
      Ring1_Memory_deallocate(node);
      self->size--;
    }
  }
  if (self->buckets) {
    Ring1_Memory_deallocate(self->buckets);
    self->buckets = NULL;
  }
  Ring1_Memory_deallocate(self);
}

static Map* Map_create() {
  Map* self;
  if (Ring1_Memory_allocate(&self, sizeof(Map))) {
    Ring2_jump();
  }
  self->size = 0;
  self->capacity = 8;
  self->buckets = NULL;
  if (Ring1_Memory_allocateArray((void **) & self->buckets, 8, sizeof(Node*))) {
    self->capacity = 0;
    Ring1_Memory_deallocate(self);
    Ring2_jump();
  }
  for (size_t i = 0; i < 8; ++i) {
    self->buckets[i] = NULL;
  }
  return self;
}

static Node* Map_get(Map* self, uint32_t codepoint) {
  size_t hashIndex = codepoint % self->capacity;
  for (Node* node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->codepoint == codepoint) {
      return node;
    }
  }
  return NULL;
}

static void Map_set(Map* self, uint32_t codepoint, float bearingx, float bearingy, float w, float h, float advancex, float advancey, Machine_Texture* texture) {
  size_t hashIndex = codepoint % self->capacity;
  for (Node* node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->codepoint == codepoint) {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
  }

  Node* node = NULL;
  if (Ring1_Memory_allocate(&node, sizeof(Node))) {
    Ring2_jump();
  }

  node->codepoint = codepoint;
  node->texture = texture;
  node->w = w;
  node->h = h;
  node->bearingx = bearingx;
  node->bearingy = bearingy;
  node->advancex = advancex;
  node->advancey = advancey;

  node->next = self->buckets[hashIndex];
  self->buckets[hashIndex] = node;
  self->size++;
}

static Ring2_Boolean isWhitespace(uint32_t codepoint) {
  return codepoint == ' '
    || codepoint == '\t';
}

static Ring2_Boolean isNewline(uint32_t codepoint) {
  return codepoint == '\n';
}

struct Machine_Fonts_Font_Class {
  Machine_Font_Class __parent;
};

struct Machine_Fonts_Font {
  Machine_Font __parent;

  Machine_Fonts_FontsContext* context;
  FT_Face face;
  Map* map;
  float baselineDistance;

  Machine_ShaderProgram* shader;
  Machine_VideoBuffer* vertices;
  Machine_Binding* binding;
};

static Ring2_Real32 Machine_Fonts_Font_getBaselineDistance(Machine_Fonts_Font* self) {
  return self->baselineDistance;
}

static Ring2_Boolean Machine_Fonts_Font_getCodePointInfo(Machine_Fonts_Font* self, uint32_t codepoint, Ring3_Math_Rectangle2* bounds, Ring3_Math_Vector2* advance, Machine_Texture** texture) {
  if (isWhitespace(codepoint)) {
    codepoint = ' ';
  }
  else if (isNewline(codepoint)) {
    return false;
  }
  Node* node = Map_get(self->map, codepoint);
  if (node == NULL) {
    Ring2_log(Ring2_LogFlags_ToWarnings, __FILE__, __LINE__, "%"PRIu32" not found\n", codepoint);
    return false;
  }
  Ring3_Math_Vector2* v = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(v, node->bearingx, node->bearingy);
  Ring3_Math_Rectangle2_setPosition(bounds, v);
  Ring3_Math_Vector2_set(v, node->w, node->h);
  Ring3_Math_Rectangle2_setSize(bounds, v);
  *texture = node->texture;
  Ring3_Math_Vector2_set(advance, node->advancex, node->advancey);
  return true;
}

static Machine_Binding* Machine_Fonts_Font_getVideoBinding(Machine_Fonts_Font* self) {
  return self->binding;
}

static Machine_ShaderProgram* Machine_Fonts_Font_getVideoShaderProgram(Machine_Fonts_Font* self) {
  return self->shader;
}

static Machine_VideoBuffer* Machine_Fonts_Font_getVideoBuffer(Machine_Fonts_Font* self) {
  return self->vertices;
}

static void Machine_Fonts_Font_constructClass(Machine_Fonts_Font_Class* self) {
  ((Machine_Font_Class*)self)->getBaselineDistance = (Ring2_Real32(*)(Machine_Font*)) & Machine_Fonts_Font_getBaselineDistance;
  ((Machine_Font_Class*)self)->getCodePointInfo = (Ring2_Boolean(*)(Machine_Font*, uint32_t codepoint, Ring3_Math_Rectangle2 * bounds, Ring3_Math_Vector2 * advance, Machine_Texture * *texture)) & Machine_Fonts_Font_getCodePointInfo;
  ((Machine_Font_Class*)self)->getVideoBinding = (Machine_Binding * (*)(Machine_Font*)) & Machine_Fonts_Font_getVideoBinding;
  ((Machine_Font_Class*)self)->getVideoBuffer = (Machine_VideoBuffer * (*)(Machine_Font*)) & Machine_Fonts_Font_getVideoBuffer;
  ((Machine_Font_Class*)self)->getVideoShaderProgram = (Machine_ShaderProgram * (*)(Machine_Font*)) & Machine_Fonts_Font_getVideoShaderProgram;
}

static void Machine_Fonts_Font_visit(Machine_Fonts_Font* self) {
  if (self->map) {
    Map_visit(Ring2_Gc_get(), self->map);
  }
  if (self->vertices) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->vertices);
  }
  if (self->shader) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->shader);
  }
  if (self->binding) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->binding);
  }
  if (self->context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->context);
  }
  if (self->map) {
    Map_visit(Ring2_Gc_get(), self->map);
  }
}

static void Machine_Fonts_Font_destruct(Machine_Fonts_Font* self) {
  if (self->face) {
    FT_Done_Face(self->face);
    self->face = NULL;
  }
  if (self->map) {
    Map_finalize(Ring2_Gc_get(), self->map);
    self->map = NULL;
  }
  Ring2_Gc_unlock(self->context);
  self->context = NULL;
}

void Machine_Fonts_Font_construct(Machine_Fonts_Font* self, size_t numberOfArguments, Ring2_Value const *arguments) {
  Machine_Font_construct((Machine_Font*)self, numberOfArguments, arguments);
  Ring2_String *path = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 1);
  Ring2_Integer pointSize = Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 2);
  Machine_Fonts_FontsContext* fontsContext = (Machine_Fonts_FontsContext *)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0, Machine_Fonts_FontsContext_getType());
  if (pointSize < 0 || pointSize > INT_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (NULL == path) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->context = fontsContext;
  Ring2_Gc_lock(self->context);
  //
  FT_Error error;
  // (1) Ensure string is zero terminated.
  path = Ring2_String_concatenate(Ring2_Context_get(), path, Ring2_String_create("", 1));
  // (2)
  error = FT_New_Face(*fontsContext->library, Ring2_String_getBytes(path), 0, &self->face);
  if (error) {
    Ring2_Gc_unlock(self->context);
    self->context = NULL;

    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  // (3)
  error = FT_Set_Pixel_Sizes(self->face, 0, pointSize);
  if (error) {
    FT_Done_Face(self->face);
    self->face = NULL;

    Ring2_Gc_unlock(self->context);
    self->context = NULL;

    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  self->baselineDistance = self->face->size->metrics.height >> 6;

  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    self->map = Map_create();
    self->vertices = Machine_VideoContext_createBuffer(fontsContext->videoContext);
    self->shader = Machine_VideoContext_generateText2Shader(fontsContext->videoContext, true);

    Machine_VertexDescriptor* vertexDescriptor = Machine_VertexDescriptor_create();
    Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_XfYf);
    Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_UfVf);

    self->binding = Machine_VideoContext_createBinding(fontsContext->videoContext, self->shader, vertexDescriptor, self->vertices);
    Machine_Binding_setVariableBinding(self->binding, Ring2_String_create("vertex_position", crt_strlen("vertex_position") + 1), 0);
    Machine_Binding_setVariableBinding(self->binding, Ring2_String_create("vertex_texture_coordinate_1", crt_strlen("vertex_texture_coordinate_1") + 1), 1);

    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();

    FT_Done_Face(self->face);
    self->face = NULL;

    Ring2_Gc_unlock(self->context);
    self->context = NULL;
    
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  const uint32_t codepoints[] = {
    'a', 'A',
    'b', 'B',
    'c', 'C',
    'd', 'D',
    'e', 'E',
    'f', 'F',
    'g', 'G',
    'h', 'H',
    'i', 'I',
    'j', 'J',
    'k', 'K',
    'l', 'L',
    'm', 'M',
    'n', 'N',
    'o', 'O',
    'p', 'P',
    'q', 'Q',
    'r', 'R',
    's', 'S',
    't', 'T',
    'u', 'U',
    'v', 'V',
    'w', 'W',
    'x', 'X',
    'y', 'Y',
    'z', 'Z',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '.',
    ',',
    '!',
    ' ',
    '+',
    '-',
  };
  Ring2_ByteBuffer* temporary = Ring2_ByteBuffer_create();
  for (size_t i = 0, n = sizeof(codepoints) / sizeof(uint32_t); i < n; ++i) {
    const uint32_t codepoint = codepoints[i];
    if (FT_Load_Char(self->face, codepoint, FT_LOAD_RENDER)) {

      FT_Done_Face(self->face);
      self->face = NULL;

      Ring2_Gc_unlock(self->context);
      self->context = NULL;

      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_JumpTarget jt;
    Ring2_pushJumpTarget(&jt);
    if (!setjmp(jt.environment)) {
      Ring2_ByteBuffer_clear(temporary);
      if (self->face->glyph->bitmap.buffer) {
        Ring2_ByteBuffer_appendBytes(temporary, self->face->glyph->bitmap.buffer,
                                     (size_t)self->face->glyph->bitmap.width * (size_t)self->face->glyph->bitmap.rows);
      }
      Machine_Image* image = Machine_ImagesContext_createDirect(
          fontsContext->imageContext, Ring3_PixelFormat_GRAYSCALE,
          self->face->glyph->bitmap.width, self->face->glyph->bitmap.rows, temporary);
      Machine_Texture* texture = Machine_VideoContext_createTextureFromImage(fontsContext->videoContext, image);
      Map_set(self->map, codepoint,
              self->face->glyph->bitmap_left, self->face->glyph->bitmap_top,
              self->face->glyph->bitmap.width, self->face->glyph->bitmap.rows,
              self->face->glyph->advance.x >> 6, self->face->glyph->advance.y >> 6, texture);
      Ring2_popJumpTarget();
    } else {
      FT_Done_Face(self->face);
      self->face = NULL;
      
      Ring2_Gc_unlock(self->context);
      self->context = NULL;

      Ring2_popJumpTarget();
      Ring2_jump();
    }
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Fonts_Font_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Fonts_Font, Machine_Font, &Machine_Fonts_Font_visit,
                         &Machine_Fonts_Font_construct, &Machine_Fonts_Font_destruct,
                         &Machine_Fonts_Font_constructClass, NULL)

Machine_Fonts_Font* Machine_Fonts_Font_create(Machine_FontsContext* fontsContext, Ring2_String *path, Ring2_Integer pointSize) {
  Machine_ClassType* ty = Machine_Fonts_Font_getType();
  size_t numberOfArguments = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&arguments[0], (Machine_Object *)fontsContext);
  Ring2_Value_setString(&arguments[1], path);
  Ring2_Value_setInteger(&arguments[2], pointSize);
  Machine_Fonts_Font* self = (Machine_Fonts_Font*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}
