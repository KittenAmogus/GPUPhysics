#include <glad/gl.h>
#include <vbo.h>

GLuint ebo_create(GLuint *indices, GLsizeiptr size) {
  GLuint id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  return id;
}

void ebo_bind(GLuint id) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
void ebo_unbind(void) { ebo_bind(0); }

void ebo_delete(GLuint id) { glDeleteBuffers(1, &id); }
