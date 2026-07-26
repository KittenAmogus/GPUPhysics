#include <glad/gl.h>
#include <vao.h>

GLuint vao_create(void) {
  GLuint id;
  glGenVertexArrays(1, &id);
  return id;
}

void vao_bind(GLuint id) { glBindVertexArray(id); }

void vao_unbind(void) { vao_bind(0); }

void vao_link(GLuint id, GLuint vbo, GLuint layout, GLuint comp_num,
              GLenum type, GLsizeiptr stride, void *offset) {
  vao_bind(id);
  glVertexAttribPointer(layout, comp_num, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  vao_unbind();
}

void vao_delete(GLuint id) { glDeleteVertexArrays(1, &id); }
