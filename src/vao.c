#include <glad/gl.h>
#include <vao.h>

GLuint vao_create(void) {
  GLuint id;
  glGenVertexArrays(1, &id);
  return id;
}

void vao_bind(GLuint id) { glBindVertexArray(id); }

void vao_unbind(void) { vao_bind(0); }

void vao_link(GLuint id, GLuint vbo, GLuint layout) {
  vao_bind(id);
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(layout);
  vao_unbind();
}

void vao_delete(GLuint id) { glDeleteVertexArrays(1, &id); }
