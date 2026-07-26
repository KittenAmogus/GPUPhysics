#include <glad/gl.h>
#include <vbo.h>

GLuint vbo_create(GLfloat *vertices, GLsizeiptr size) {
  GLuint id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  return id;
}

void vbo_bind(GLuint id) { glBindBuffer(GL_ARRAY_BUFFER, id); }
void vbo_unbind(void) { vbo_bind(0); }

void vbo_delete(GLuint id) { glDeleteBuffers(1, &id); }
