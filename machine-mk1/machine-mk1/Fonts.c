/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#include "Fonts.h"



#include "Machine.h"
#include "Texture.h"
#include "ShaderProgram.h"

#include <ft2build.h>
#include FT_FREETYPE_H



static int referenceCount = 0;
static FT_Library library;


typedef struct Node Node;

struct Node {
  Node* next;
  /// @brief Unicode code point.
  uint32_t codepoint;
  /// @brief The texture.
  Machine_Texture* texture;
  /// @brief left, top, width, height in pixels.
  float l, t, w, h;
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

static void Map_visit(Map *self)
{
  for (size_t i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      Machine_visit(node->texture);
      node = node->next;
    }
  }
}

static void Map_finalize(Map* self)
{
  for (size_t i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = node->next;
      free(node);
      self->size--;
    }
  }
  if (self->buckets) {
    free(self->buckets);
    self->buckets = NULL;
  }
}

static Map* Map_create() {
  Map *self = Machine_allocate(sizeof(Map), (Machine_VisitCallback*)&Map_visit, (Machine_FinalizeCallback*)&Map_finalize);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->size = 0;
  self->capacity = 8;
  self->buckets = malloc(sizeof(Node*) * 8);
  if (!self->buckets) {
    self->capacity = 0;
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
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

static void Map_set(Map* self, uint32_t codepoint, float l, float t, float w, float h, float advancex, float advancey, Machine_Texture* texture) {
  size_t hashIndex = codepoint % self->capacity;
  for (Node* node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->codepoint == codepoint) {
      Machine_setStatus(Machine_Status_InvalidOperation);
      Machine_jump();
    }
  }
  
  Node* node = malloc(sizeof(Node));
  if (!node) {
    Machine_setStatus(Machine_Status_InvalidOperation);
    Machine_jump();
  }
  
  node->codepoint = codepoint;
  node->texture = texture;
  node->l = l;
  node->t = t;
  node->w = w;
  node->h = h;
  node->advancex = advancex;
  node->advancey = advancey;

  node->next = self->buckets[hashIndex];
  self->buckets[hashIndex] = node;
  self->size++;
}

struct Machine_Fonts_Font {
  int referenceCount;
  FT_Face face;
  Map* map;
  float baselineDistance;

  Machine_ShaderProgram* shader;
  Machine_FloatBuffer* vertices;
  Machine_Binding* binding;
};


int Machine_Fonts_startup() {
  if (referenceCount == INT_MAX) {
    return 1;
  }
  else if (referenceCount == 0) {
    FT_Error error;
    error = FT_Init_FreeType(&library);
    if (error) {
      Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "FT_Init_FreeType failed\n");
      return 1;
    }
    referenceCount++;
    return 0;
  }
  else {
    referenceCount++;
    return 0;
  }
}

void Machine_Fonts_shutdown() {
  if (0 == --referenceCount) {
    FT_Done_FreeType(library);
  }
}

void Machine_Fonts_Font_visit(Machine_Fonts_Font* self) {
  if (self->map) {
    Machine_visit(self->map);
  }
  if (self->vertices) {
    Machine_visit(self->vertices);
  }
  if (self->shader) {
    Machine_visit(self->shader);
  }
  if (self->binding) {
    Machine_visit(self->binding);
  }
}

void Machine_Fonts_Font_finalize(Machine_Fonts_Font* self) {
  if (self->face) {
    FT_Done_Face(self->face);
    self->face = NULL;
  }
  Machine_Fonts_shutdown();
}

#include <linmath.h>
#include "Texture.h"
#include "VertexDescriptor.h"
#include "Binding.h"

#define X (64.0f)

static const struct {
  float x, y;
  float u, v;
}
vertices[] =
{
  { 0.f, 0.f, 0.f, 0.f }, // left/bottom
  { +X,  0.f, 1.f, 0.f }, // right/bottom
  { 0.f, +X, 0.f, 1.f }, // left/top
  { +X, +X, 1.f, 1.f }, // right/top
};

static const uint8_t indices[] = {
  0, 1, 2,
  2, 1, 3,
};


Machine_Fonts_Font* Machine_Fonts_createFont(const char* path, int pointSize) {
  if (Machine_Fonts_startup()) {
    return NULL;
  }
  Machine_Fonts_Font* font = Machine_allocate(sizeof(Machine_Fonts_Font), (Machine_VisitCallback *)&Machine_Fonts_Font_visit, (Machine_FinalizeCallback *) & Machine_Fonts_Font_finalize);
  if (!font) {
    Machine_Fonts_shutdown();
    return NULL;
  }
  FT_Error error;
  // (1)
  error = FT_New_Face(library, path, 0, &font->face);
  if (error) {
    return NULL;
  }
  // (2)
  error = FT_Set_Pixel_Sizes(font->face, 0, pointSize);
  if (error) {
    FT_Done_Face(font->face);
    font->face = NULL;
    return NULL;
  }

  font->baselineDistance = font->face->size->metrics.height >> 6;

  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    font->map = Map_create();
    font->vertices = Machine_FloatBuffer_create();
    Machine_FloatBuffer_setData(font->vertices, sizeof(vertices) / sizeof(float), vertices);
    font->shader = Machine_ShaderProgram_generateTextShader(true, false, true, true);

    Machine_VertexDescriptor* vertexDescriptor = Machine_VertexDescriptor_create();
    Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_XfYf);
    Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_UfVf);

    font->binding = Machine_Binding_create(font->shader, vertexDescriptor, font->vertices);
    Machine_Binding_set(font->binding, Machine_String_create("vertex_position", strlen("vertex_position") + 1), 0);
    Machine_Binding_set(font->binding, Machine_String_create("vertex_texture_coordinate_1", strlen("vertex_texture_coordinate_1") + 1), 1);

    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
    FT_Done_Face(font->face);
    font->face = NULL;
    return NULL;
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
    's', 'T',
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
  };
  for (size_t i = 0, n = sizeof(codepoints) / sizeof(uint32_t); i < n; ++i) {
    const uint32_t codepoint = codepoints[i];
    if (FT_Load_Char(font->face, codepoint, FT_LOAD_RENDER)) {
      Machine_setStatus(Machine_Status_InvalidOperation);
      Machine_jump();
    }
    Machine_Images_Image* image;
    int result = Machine_Images_createImageDirect(Machine_Images_PixelFormat_GRAYSCALE, font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows, font->face->glyph->bitmap.buffer, &image);
    if (result) {
      Machine_setStatus(result);
      Machine_jump();
    }
    Machine_Texture* texture = Machine_Texture_create(image);
    Map_set(font->map, codepoint,
            font->face->glyph->bitmap_left, font->face->glyph->bitmap_top,
            font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows,
            font->face->glyph->advance.x >> 6, font->face->glyph->advance.y >> 6, texture);
  }
  return font;
}

#include <inttypes.h>

static bool isWhitespace(uint32_t codepoint) {
  return codepoint == ' '
      || codepoint == '\t';
}

static bool isNewline(uint32_t codepoint) {
  return codepoint == '\n';
}

void Machine_Font_getBounds(Machine_Fonts_Font* self, vec2 position, rect2* bounds) {
#define Y_UP
  const char* text = "AgBC X\nY";
  float posx = position[0], posy = position[1];
  bounds->l = posx;
  bounds->w = 0.f;
  bounds->b = posy;
  bounds->h = 0.f;
  for (size_t i = 0, n = strlen(text); i < n; ++i) {
    uint32_t codepoint = text[i];
    if (isWhitespace(codepoint)) {
      codepoint = ' ';
    }
    else if (isNewline(codepoint)) {
      codepoint = ' ';
    }
    Node* node = Map_get(self->map, codepoint);
    if (node == NULL) {
      Machine_log(Machine_LogFlags_ToWarnings, __FILE__, __LINE__, "%"PRIu32" not found\n", text[i]);
      continue;
    }

    float l = 0.f + posx + node->l;
  #if defined(Y_UP)
    float t = 0.f + posy + (node->h - node->t);
  #else
    float t = 0.f + posy - (node->h - node->t);
  #endif

  #if defined(Y_UP)
    const struct {
      float x, y;
    }
    vertices[] =
    {
      { l,            t,            }, // left/bottom
      { l + node->w,  t,            }, // right/bottom
      { l,            t - node->h,  }, // left/top
      { l + node->w,  t - node->h,  }, // right/top
    };
  #else
    const struct {
      float x, y;
    }
    vertices[] =
    {
      { l,            t,            }, // left/bottom
      { l + node->w,  t,            }, // right/bottom
      { l,            t + node->h,  }, // left/top
      { l + node->w,  t + node->h,  }, // right/top
    };
  #endif
    vec2 min = { l,t };
    vec2 max = { l + node->w, t + node->h };
    
    rect2_add_point(bounds, min);
    rect2_add_point(bounds, max);

    posx += (node->advancex);
    posy += (node->advancey);
  }
}

void Machine_Font_draw(Machine_Fonts_Font* self, vec2 position, vec3 color, float width, float height) {
#define Y_UP
  // Set the viewport and clear its color buffer.
  float ratio = width / height;
  Machine_UtilitiesGl_call(glViewport(0, 0, width, height));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));

  // Set the world matrix, view matrix, and projection matrix.
  mat4x4 world, view, projection, wvp;
  mat4x4_identity(world); // world matrix is identity.
  mat4x4_identity(view); // view matrix is identity.
#if defined(Y_UP)
  mat4x4_ortho(projection, 0.f, width, height, 0.f, 1.f, -1.f); // projection matrix
#else
  mat4x4_ortho(projection, 0.f, width, 0.f, height, 1.f, -1.f); // projection matrix
#endif
  // Compute combined world view projection matrix.
  mat4x4_mul(wvp, projection, view);
  mat4x4_mul(wvp, wvp, world);

  Machine_ShaderProgram* shaderProgram = self->shader;
  Machine_Binding* binding = self->binding;

  Machine_Binding_activate(binding);
  Machine_UtilitiesGl_call(glUseProgram(self->shader->programId));
  Machine_Binding_bindVector3(binding, Machine_String_create("mesh_color", strlen("mesh_color") + 1), color);
  Machine_Binding_bindMatrix4x4(binding, Machine_String_create("mvp", strlen("mvp") + 1), wvp);
  GLint texture_location = glGetUniformLocation(self->shader->programId, "texture_1");
  if (texture_location == -1) return;

  const char* text = "AgBC X\nY";
  float posx = position[0], posy = position[1];
  for (size_t i = 0, n = strlen(text); i < n; ++i) {
    uint32_t codepoint = text[i];
    if (isWhitespace(codepoint)) {
      codepoint = ' ';
    } else if (isNewline(codepoint)) {
      codepoint = ' ';
    }
    Node* node = Map_get(self->map, codepoint);
    if (node == NULL) {
      Machine_log(Machine_LogFlags_ToWarnings, __FILE__, __LINE__, "%"PRIu32" not found\n", text[i]);
      continue;
    }

    float l = 0.f + posx + node->l;

    float t;
  #if defined(Y_UP)
    t = 0.f + posy + (node->h - node->t);
  #else
    t = 0.f + posy - (node->h - node->t);
  #endif

  #if defined(Y_UP)
    const struct {
      float x, y;
      float u, v;
    }
    vertices[] =
    {
      { l,            t,            0.f, 1.f }, // left/bottom
      { l + node->w,  t,            1.f, 1.f }, // right/bottom
      { l,            t - node->h,  0.f, 0.f }, // left/top
      { l + node->w,  t - node->h,  1.f, 0.f }, // right/top
    };
  #else
    const struct {
      float x, y;
      float u, v;
  }
    vertices[] =
    {
      { l,            t,            0.f, 1.f }, // left/bottom
      { l + node->w,  t,            1.f, 1.f }, // right/bottom
      { l,            t + node->h,  0.f, 0.f }, // left/top
      { l + node->w,  t + node->h,  1.f, 0.f }, // right/top
    };
  #endif

    Machine_FloatBuffer_setData(self->vertices, sizeof(vertices) / sizeof(float), vertices);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glUniform1i(texture_location, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, node->texture->id);
    Machine_UtilitiesGl_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, &indices));
    posx += (node->advancex);
    posy += (node->advancey);
  }
}

typedef struct Line Line;
struct Line {
  int start;
  int length;
};

Line* Line_create(int start, int length) {
  if (start < 0 || length < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Line *self = Machine_allocate(sizeof(Line), NULL, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->start = start;
  self->length = length;
  return self;
}

Machine_PointerArray* Machine_Text_toLines(const char* text) {
  Machine_PointerArray* lines = Machine_PointerArray_create();
  int lineStart = 0, lineEnd = 0;
  while (text[lineEnd] != '\0') {
    // terminates a line
    if (text[lineEnd] == '\n' || text[lineEnd] == '\r') {
      int old = text[lineEnd];
      lineEnd++;
      if (old != text[lineEnd] && (text[lineEnd] == '\n' || text[lineEnd] == '\r')) {
        lineEnd++;
      }
      Line *line = Line_create(lineStart, lineEnd - lineStart);
      Machine_PointerArray_append(lines, line);
      lineStart = lineEnd;
    }
    lineEnd++;
  }
  if (lineStart != lineEnd) {
    Line *line = Line_create(lineStart, lineEnd - lineStart);
    Machine_PointerArray_append(lines, line);
  }
  return lines;
}
