#include "scene1.h"

#include <stddef.h>
#include <malloc.h>

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath.h>

#include "Fonts.h"

static const struct
{
  float x, y;
  float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
  "#version 110\n"
  "uniform mat4 mvp;\n"
  "attribute vec3 vertex_color;\n"
  "attribute vec2 vertex_position;\n"
  "varying vec3 color;\n"
  "void main()\n"
  "{\n"
  "    gl_Position = mvp * vec4(vertex_position, 0.0, 1.0);\n"
  "    color = vertex_color;\n"
  "}\n";

static const char* fragment_shader_text =
  "#version 110\n"
  "varying vec3 color;\n"
  "void main()\n"
  "{\n"
  "    gl_FragColor = vec4(color, 1.0);\n"
  "}\n";

typedef struct Scene1 {
  Scene parent;

  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  GLint mvp_location, vpos_location, vcol_location;
  Machine_Fonts_Font* font;
} Scene1;

static int Scene1_startup(Scene1* scene) {

  scene->font = Machine_Fonts_createFont("RobotoSlab-Regular.ttf", 12);
  if (!scene->font) {
    return 1;
  }


  glGenBuffers(1, &scene->vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, scene->vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  scene->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(scene->vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(scene->vertex_shader);

  scene->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(scene->fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(scene->fragment_shader);

  scene->program = glCreateProgram();
  glAttachShader(scene->program, scene->vertex_shader);
  glAttachShader(scene->program, scene->fragment_shader);
  glLinkProgram(scene->program);

  scene->mvp_location = glGetUniformLocation(scene->program, "mvp");
  scene->vpos_location = glGetAttribLocation(scene->program, "vertex_position");
  scene->vcol_location = glGetAttribLocation(scene->program, "vertex_color");

  glEnableVertexAttribArray(scene->vpos_location);
  glVertexAttribPointer(scene->vpos_location, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertices[0]), (void*)0);
  glEnableVertexAttribArray(scene->vcol_location);
  glVertexAttribPointer(scene->vcol_location, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertices[0]), (void*)(sizeof(float) * 2));

  return 0;
}

static int Scene1_update(Scene1* scene, float width, float height) {
  float ratio;
  mat4x4 m, p, mvp;

  ratio = width / height;

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);

  mat4x4_identity(m);
  mat4x4_rotate_Z(m, m, (float)glfwGetTime());
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);

  glUseProgram(scene->program);
  glUniformMatrix4fv(scene->mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  return 0;
}

static void Scene1_shutdown(Scene1* scene) {
  if (scene->font) {
    Machine_Fonts_Font_destroy(scene->font);
    scene->font = NULL;
  }
  if (scene->program) {
    glDeleteProgram(scene->program);
    scene->program = 0;
  }
  if (scene->vertex_shader) {
    glDeleteShader(scene->vertex_shader);
    scene->vertex_shader = 0;
  }
  if (scene->fragment_shader) {
    glDeleteShader(scene->fragment_shader);
    scene->fragment_shader = 0;
  }
}

int Scene1_construct(Scene1* self) {
  self->font = NULL;
  ((Scene*)self)->startup = (Scene_StartupCallback*)&Scene1_startup;
  ((Scene*)self)->update = (Scene_UpdateCallback*)&Scene1_update;
  ((Scene*)self)->shutdown = (Scene_ShutdownCallback*)&Scene1_shutdown;
  return 0;
}

void Scene1_destruct(Scene1* self) {
}

Scene* Scene1_create() {
  Scene1* scene = malloc(sizeof(Scene1));
  if (!scene) {
    return NULL;
  }
  if (Scene1_construct(scene)) {
    free(scene);
    return NULL;
  }
#if 0
  scene->startup = (Scene_StartupCallback *)&Scene1_startup;
  scene->update = (Scene_UpdateCallback *)&Scene1_update;
  scene->shutdown = (Scene_ShutdownCallback *)&Scene1_shutdown;
#endif
  return scene;
}
