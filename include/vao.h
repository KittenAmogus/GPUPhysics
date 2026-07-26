#ifndef _VAO_H
#define _VAO_H

#include <glad/gl.h>

GLuint vao_create(void);

GLuint vao_create(void);
void vao_link(GLuint id, GLuint vbo, GLuint layout, GLuint comp_num,
              GLenum type, GLsizeiptr stride, void *offset);
void vao_bind(GLuint id);
void vao_unbind(void);
void vao_delete(GLuint id);

#endif // _VAO_H
