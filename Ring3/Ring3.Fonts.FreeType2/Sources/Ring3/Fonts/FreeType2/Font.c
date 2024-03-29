/// @file Ring3/Fonts/FreeType2/Font.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_FONTS_FREETYPE2_PRIVATE (1)
#include "Ring3/Fonts/FreeType2/Font.h"

#include "Ring3/Fonts/FreeType2/FontsContext.h"
#undef RING3_FONTS_FREETYPE2_PRIVATE

#include "Ring1/All/_Include.h"
#include <inttypes.h>

#include <ft2build.h>
#include FT_FREETYPE_H


typedef struct Node Node;

struct Node {
  Node* next;
  /// @brief Unicode code point.
  uint32_t codepoint;
  /// @brief The texture.
  Ring3_Texture* texture;
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

static void Map_set(Map* self, uint32_t codepoint, float bearingx, float bearingy, float w, float h, float advancex, float advancey, Ring3_Texture* texture) {
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
  Ring3_Font_Class __parent;
};

struct Machine_Fonts_Font {
  Ring3_Font __parent;

  Machine_Fonts_FontsContext* context;
  FT_Face face;
  Map* map;
  float baselineDistance;

  Ring3_GpuProgram* shader;
  Ring3_GpuBuffer* vertices;
  Ring3_Binding* binding;
};

static Ring2_Real32 Machine_Fonts_Font_getBaselineDistance(Machine_Fonts_Font* self) {
  return self->baselineDistance;
}

static Ring2_Boolean Machine_Fonts_Font_getCodePointInfo(Machine_Fonts_Font* self, uint32_t codepoint, Ring3_Math_Rectangle2* bounds, Ring3_Math_Vector2f32* advance, Ring3_Texture** texture) {
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
  Ring3_Math_Vector2f32* v = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(v, node->bearingx, node->bearingy);
  Ring3_Math_Rectangle2_setPosition(bounds, v);
  Ring3_Math_Vector2f32_set(v, node->w, node->h);
  Ring3_Math_Rectangle2_setSize(bounds, v);
  *texture = node->texture;
  Ring3_Math_Vector2f32_set(advance, node->advancex, node->advancey);
  return true;
}

static Ring3_Binding* Machine_Fonts_Font_getVideoBinding(Machine_Fonts_Font* self) {
  return self->binding;
}

static Ring3_GpuProgram* Machine_Fonts_Font_getVideoShaderProgram(Machine_Fonts_Font* self) {
  return self->shader;
}

static Ring3_GpuBuffer* Machine_Fonts_Font_getVideoBuffer(Machine_Fonts_Font* self) {
  return self->vertices;
}

static void Machine_Fonts_Font_constructClass(Machine_Fonts_Font_Class* self) {
  ((Ring3_Font_Class*)self)->getBaselineDistance = (Ring2_Real32(*)(Ring3_Font*)) & Machine_Fonts_Font_getBaselineDistance;
  ((Ring3_Font_Class*)self)->getCodePointInfo = (Ring2_Boolean(*)(Ring3_Font*, uint32_t codepoint, Ring3_Math_Rectangle2* bounds, Ring3_Math_Vector2f32* advance, Ring3_Texture * *texture)) & Machine_Fonts_Font_getCodePointInfo;
  ((Ring3_Font_Class*)self)->getVideoBinding = (Ring3_Binding * (*)(Ring3_Font*)) & Machine_Fonts_Font_getVideoBinding;
  ((Ring3_Font_Class*)self)->getVideoBuffer = (Ring3_GpuBuffer * (*)(Ring3_Font*)) & Machine_Fonts_Font_getVideoBuffer;
  ((Ring3_Font_Class*)self)->getVideoShaderProgram = (Ring3_GpuProgram * (*)(Ring3_Font*)) & Machine_Fonts_Font_getVideoShaderProgram;
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
  Ring3_Font_construct((Ring3_Font*)self, numberOfArguments, arguments);
  Ring2_String *path = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 1);
  Ring2_Integer pointSize = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 2);
  Machine_Fonts_FontsContext* fontsContext = (Machine_Fonts_FontsContext*)Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Machine_Fonts_FontsContext_getType());
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
    self->vertices = Ring3_VisualsContext_createBuffer(fontsContext->videoContext);
    self->shader = Ring3_VisualsContext_generateText2Shader(fontsContext->videoContext, true);

    Ring3_VertexDescriptor* vertexDescriptor = Ring3_VertexDescriptor_create();
    Ring3_VertexDescriptor_append(vertexDescriptor, Ring3_VertexElementSemantics_XfYf);
    Ring3_VertexDescriptor_append(vertexDescriptor, Ring3_VertexElementSemantics_UfVf);

    self->binding = Ring3_VisualsContext_createBinding(fontsContext->videoContext, self->shader, vertexDescriptor, self->vertices);
    Ring3_Binding_setVariableBinding(self->binding, Ring2_String_fromC(true, "vertexPosition"),
                                                    Ring3_GpuProgramLocationType_Vector2Variable,
                                                    0);
    Ring3_Binding_setVariableBinding(self->binding, Ring2_String_fromC(true, "vertexTextureCoordinate1"),
                                                    Ring3_GpuProgramLocationType_Vector2Variable,
                                                    1);

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
      Ring3_Image* image = Ring3_ImagesContext_createImage(
          fontsContext->imageContext, Ring3_PixelFormat_GRAYSCALE,
          self->face->glyph->bitmap.width, self->face->glyph->bitmap.rows, temporary);
      Ring3_Texture* texture = Ring3_VisualsContext_createTextureFromImage(fontsContext->videoContext, image);
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

MACHINE_DEFINE_CLASSTYPE(Machine_Fonts_Font,
                         Ring3_Font,
                         &Machine_Fonts_Font_visit,
                         &Machine_Fonts_Font_construct,
                         &Machine_Fonts_Font_destruct,
                         &Machine_Fonts_Font_constructClass,
                         NULL)

Machine_Fonts_Font* Machine_Fonts_Font_create(Ring3_FontsContext* fontsContext, Ring2_String *path, Ring2_Integer pointSize) {
  Machine_Type* ty = Machine_Fonts_Font_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,fontsContext));
  Ring2_Value_setString(&arguments[1], path);
  Ring2_Value_setInteger(&arguments[2], pointSize);
  Machine_Fonts_Font* self = Ring1_cast(Machine_Fonts_Font*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
