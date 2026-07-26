#ifndef _SHADERS_H
#define _SHADERS_H

#include <stddef.h>
#include <glad/gl.h>

#define SHADER_INVALID 0xFFFFFFFF

extern const char *vertex_shader;
extern const char *fragment_shader;

const char *shader_read_src(const char *path);
GLuint shader_compile(const char *path, GLenum type);
GLuint shader_create_program(void);

void shader_attach(GLuint program, GLuint id);
void shader_detach(GLuint program, GLuint id);
void shader_link_program(GLuint program);
void shader_delete(GLuint id);
void shader_delete_program(GLuint program);

#endif // _SHADERS_H
