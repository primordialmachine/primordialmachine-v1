#include "Buffer.h"



#include <malloc.h>
#include <string.h>



struct Machine_Uint8Buffer {
  size_t n;
  uint8_t* p;
  GLuint id;
};

static void Machine_Uint8Buffer_finalize(Machine_Uint8Buffer* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
}

Machine_Uint8Buffer* Machine_Uint8Buffer_create() {
  Machine_Uint8Buffer* self = Machine_allocate(sizeof(Machine_Uint8Buffer), NULL, &Machine_Uint8Buffer_finalize);
  if (!self) {
    return NULL;
  }
  self->p = malloc(sizeof(uint8_t));
  if (!self->p) {
    free(self);
    return NULL;
  }
  self->n = 0;

  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(uint8_t), self->p, GL_STATIC_DRAW);

  return self;
}

void Machine_Uint8Buffer_setData(Machine_Uint8Buffer* self, size_t n, uint8_t* p) {
  uint8_t* t = realloc(self->p, n * sizeof(uint8_t));
  if (!t) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->p = t;
  memcpy(self->p, p, n * sizeof(uint8_t));
  self->n = n;

  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, self->n * sizeof(uint8_t), self->p, GL_STATIC_DRAW);
}

uint8_t* Machine_Uint8Buffer_getData(Machine_Uint8Buffer* self) {
  return self->p;
}

size_t Machine_Uint8Buffer_getSize(Machine_Uint8Buffer* self) {
  return self->n;
}

GLuint Machine_Uint8Buffer_getId(Machine_Uint8Buffer* self) {
  return self->id;
}



struct Machine_FloatBuffer {
  size_t n;
  float* p;
  GLuint id;
};

static void Machine_FloatBuffer_finalize(Machine_FloatBuffer* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
}

Machine_FloatBuffer* Machine_FloatBuffer_create() {
  Machine_FloatBuffer* self = Machine_allocate(sizeof(Machine_FloatBuffer), NULL, &Machine_FloatBuffer_finalize);
  if (!self) {
    return NULL;
  }
  self->p = malloc(sizeof(float));
  if (!self->p) {
    free(self);
    return NULL;
  }
  self->n = 0;

  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(float), self->p, GL_STATIC_DRAW);

  return self;
}

void Machine_FloatBuffer_setData(Machine_FloatBuffer* self, size_t n, float* p) {
  float *t = realloc(self->p, n * sizeof(float));
  if (!t) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->p = t;
  memcpy(self->p, p, n * sizeof(float));
  self->n = n;

  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, self->n * sizeof(float), self->p, GL_STATIC_DRAW);
}

float* Machine_FloatBuffer_getData(Machine_FloatBuffer* self) {
  return self->p;
}

size_t Machine_Floatbuffer_getSize(Machine_FloatBuffer* self) {
  return self->n;
}

GLuint Machine_FloatBuffer_getId(Machine_FloatBuffer* self) {
  return self->id;
}
