#include <stdio.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <shaders.h>

static const char *vertex_shader =
    ("#version 430 core\n"
     "layout (location = 0) in vec2 aPos;"
     "void main() {"
     "  gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);"
     "}");

static const char *fragment_shader =
    ("#version 430 core\n"
     "out vec4 frag_colour;"
     "void main() {"
     "  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
     "}");

GLuint link_shader_program(void) {
  // Create shaders
  printf("OpenGL: Compiling shaders\r\n");
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  printf("OpenGL: Linking shader program\r\n");
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  glAttachShader(shader_program, fs);
  glLinkProgram(shader_program);

  // Remove linked shaders
  glDeleteShader(vs);
  glDeleteShader(fs);

  return shader_program;
}
