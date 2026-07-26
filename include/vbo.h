#ifndef _VBO_H
#define _VBO_H

#include <glad/gl.h>

GLuint vbo_create(GLfloat *vertices, GLsizeiptr size);
void vbo_bind(GLuint id);
void vbo_unbind(void);
void vbo_delete(GLuint id);

#endif // _VBO_H
