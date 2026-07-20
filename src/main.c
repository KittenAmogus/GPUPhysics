#include <stdio.h>
#include <stdlib.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <funcs.h>

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

const char *vertex_shader = ("#version 410 core\n"
                             "in vec3 vp;"
                             "void main() {"
                             "  gl_Position = vec4(vp, 1.0);"
                             "}");

const char *fragment_shader = ("#version 410 core\n"
                               "out vec4 frag_colour;"
                               "void main() {"
                               "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
                               "}");

static const float vertices[] = {
    0.0f,  0.5f,  0.0f, // XYZ of first point
    0.5f,  -0.5f, 0.0f, // XYZ of second point
    -0.5f, -0.5f, 0.0f, // XYZ of third point
};

static void key_callback_glfw(GLFWwindow *window, int key, int scancode,
                              int action, int mods) {
  switch (key) {
  case GLFW_KEY_ESCAPE: {
    glfwSetWindowShouldClose(window, 1);
  }
  }
}

int main(int argc, char **argv) {
  // Init GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW: Init failed\r\n");
    return -1;
  }
  glfwSetErrorCallback(error_callback_glfw);

  // Setup window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  GLFWwindow *window =
      glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Physics", NULL, NULL);
  if (!window) {
    fprintf(stderr, "GLFW: Window creating failed\r\n");
    glfwTerminate();
    return -1;
  }
  glfwSetKeyCallback(window, key_callback_glfw);
  glfwMakeContextCurrent(window);
  int ver = gladLoadGL(glfwGetProcAddress);
  if (ver == 0) {
    fprintf(stderr, "GLAD: Cannot load OpenGL\r\n");
    glfwTerminate();
    glfwDestroyWindow(window);
    return -1;
  }

  fprintf(stdout, "GLAD: OpenGL Version:  %d.%d\r\n", GLAD_VERSION_MAJOR(ver),
          GLAD_VERSION_MINOR(ver));
  fprintf(stdout, "GLAD: OpenGL Renderer: %s\r\n", glGetString(GL_RENDERER));

  char *title = malloc(128);
  snprintf(title, 127, "Physics | Renderer %s", glGetString(GL_RENDERER));
  glfwSetWindowTitle(window, title);

  // Init buffer
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Init array
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

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

  // Mainloop
  int width, height;
  while (!glfwWindowShouldClose(window)) {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    /* Draw */
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
