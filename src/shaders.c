#include <stdio.h>
#include <stdlib.h>
#include <shaders.h>

#include <glad/gl.h>

const char *vertex_shader = "./shaders/vertex.vert";
const char *fragment_shader = "./shaders/fragment.frag";

const char *shader_read_src(const char *path) {
  // Open shader file
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "read_shader() error, NULL fopen\r\n");
    return NULL;
  }

  // Get size
  fseek(file, 0, SEEK_END);
  size_t fsize = ftell(file);
  rewind(file);

  // Allocate RAM buffer
  char *buff = (char *)malloc(fsize + 1);
  if (buff == NULL) {
    fprintf(stderr, "read_shader() error, NULL buffer\r\n");
    fclose(file);
    return NULL;
  }

  // Read file with terminating '\0'
  size_t bytes_read = fread(buff, 1, fsize, file);
  buff[bytes_read] = 0;

  // Close file
  fclose(file);
  return buff;
}

GLuint shader_compile(const char *path, GLenum type) {
  if (path == NULL) {
    return SHADER_INVALID;
  }
  printf("SHADER: Compiling shader %s\r\n", path);

  GLuint shader = glCreateShader(type);

  const char *src = shader_read_src(path);
  if (src == NULL)
    return SHADER_INVALID;

  glShaderSource(shader, 1, &src, NULL);
  free((void *)src);

  glCompileShader(shader);
  return shader;
}

void shader_attach(GLuint program, GLuint id) { glAttachShader(program, id); }

void shader_detach(GLuint program, GLuint id) { glDetachShader(program, id); }

GLuint shader_create_program(void) { return glCreateProgram(); }

void shader_link_program(GLuint program) { glLinkProgram(program); }

void shader_delete(GLuint id) { glDeleteShader(id); }

void shader_delete_program(GLuint program) { glDeleteProgram(program); }
