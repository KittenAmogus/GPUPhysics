#ifndef _EBO_H
#define _EBO_H

#include <glad/gl.h>

GLuint ebo_create(GLuint *indices, GLsizeiptr size);
void ebo_bind(GLuint id);
void ebo_unbind(void);
void ebo_delete(GLuint id);

#endif // _EBO_H
