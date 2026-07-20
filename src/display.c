#include <stdio.h>
#include <stdlib.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <funcs.h>

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

extern void key_callback_glfw(GLFWwindow *window, int key, int scancode,
                              int action, int mods);

GLFWwindow *create_window(void) {
  // Init GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW: Init failed\r\n");
    return NULL;
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
    return NULL;
  }
  glfwSetKeyCallback(window, key_callback_glfw);
  glfwMakeContextCurrent(window);
  int ver = gladLoadGL(glfwGetProcAddress);
  if (ver == 0) {
    fprintf(stderr, "GLAD: Cannot load OpenGL\r\n");
    glfwTerminate();
    glfwDestroyWindow(window);
    return NULL;
  }

  fprintf(stdout, "GLAD: OpenGL Version:  %d.%d\r\n", GLAD_VERSION_MAJOR(ver),
          GLAD_VERSION_MINOR(ver));
  fprintf(stdout, "GLAD: OpenGL Renderer: %s\r\n", glGetString(GL_RENDERER));

  char *title = malloc(128);
  snprintf(title, 127, "Physics | Renderer %s", glGetString(GL_RENDERER));
  glfwSetWindowTitle(window, title);

  return window;
}
