#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <shaders.h>
#include <display.h>

static float *vertices;
static int vertices_count = 0;

void key_callback_glfw(GLFWwindow *window, int key, int scancode, int action,
                       int mods) {
  switch (key) {
  case GLFW_KEY_ESCAPE: {
    glfwSetWindowShouldClose(window, 1);
  }
  }
}

int main(int argc, char **argv) {
  GLFWwindow *window = create_window();
  if (!window) {
    return -1;
  }

  GLuint shader_program = link_shader_program();
  if (!shader_program) {
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  // Create vertices
  vertices = malloc(sizeof(float) * 128);
  if (vertices == NULL) {
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }
  memset(vertices, 0, 128 * sizeof(float));
  int sz = 128;

  float a = 512.f;
  for (int i = 0; i < a; i += 2) {
    float x = (2.0f / a * (float)i) - 1.0f;

    if (vertices_count * 2 * sizeof(float) >= sz) {
      sz <<= 1;
      vertices = reallocarray(vertices, vertices_count * 2, sz);
    }

    vertices[(i * 2) + 0] = x;
    vertices[(i * 2) + 1] = -1.0f;

    vertices[(i * 2) + 2] = x;
    vertices[(i * 2) + 3] = 1.0f;
    vertices_count += 2;
  }

  // Init buffer
  printf("OpenGL: Creating buffers and arrays\r\n");
  GLuint vbo = 0;
  GLuint vao = 0;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices_count * 2 * sizeof(float), vertices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
  glEnableVertexAttribArray(0);

  // Mainloop
  int width, height;
  while (!glfwWindowShouldClose(window)) {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    /* Draw */
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, vertices_count << 1);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
