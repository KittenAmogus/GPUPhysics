#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vbo.h>
#include <ebo.h>
#include <vao.h>
#include <shaders.h>

int main(void) {

  // Create GLFW instance
  if (!glfwInit()) {
    fprintf(stderr, "GLFW Init error\r\n");
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create GLFW window
  GLFWwindow *window = glfwCreateWindow(1280, 720, "Window name", NULL, NULL);
  if (!window) {
    fprintf(stderr, "GLFW Window error\r\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Load OpenGL
  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "GLAD Error\r\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  // Create triangle
  GLfloat vertices[] = {
      -0.5f,  -0.5f, 0.0f, // A
      0.5f,   -0.5f, 0.0f, // B
      0.0f,   0.5f,  0.0f, // C
      -0.25f, 0.0f,  0.0f, // AB/2
      0.25f,  0.0f,  0.0f, // BC/2
      0.0f,   -0.5f, 0.0f, // CA/2
  };

  const int vert_count = sizeof(vertices) / sizeof(GLfloat) / 3;
  // const int point_count = sizeof(vertices) / sizeof(GLfloat);

  GLuint indices[] = {
      0, 3, 5, // First
      3, 2, 4, // Second
      5, 4, 1, // Third
  };
  const int ind_count = sizeof(indices) / sizeof(GLuint);

  printf("Vertices count: %d\r\n", vert_count);
  printf("Indices count: %d\r\n", ind_count);

  GLuint vao, vbo, ebo;

  vao = vao_create();
  vao_bind(vao);

  vbo = vbo_create(vertices, sizeof(vertices));
  ebo = ebo_create(indices, sizeof(indices));

  vao_link(vao, vbo, 0);
  vao_unbind();
  vbo_unbind();
  ebo_unbind();

  // Compile shaders
  GLuint vs, fs, shader_program;

  vs = shader_compile(vertex_shader, GL_VERTEX_SHADER);
  fs = shader_compile(fragment_shader, GL_FRAGMENT_SHADER);

  shader_program = shader_create_program();
  shader_attach(shader_program, vs);
  shader_attach(shader_program, fs);
  shader_link_program(shader_program);

  shader_detach(shader_program, vs);
  shader_detach(shader_program, fs);
  shader_delete(vs);
  shader_delete(fs);

  // Mainloop
  int width, height;
  while (!glfwWindowShouldClose(window)) {
    // Create viewport and get size
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Clear
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Prepare drawing
    glUseProgram(shader_program);
    vao_bind(vao);

    // Draw triangle
    glDrawElements(GL_TRIANGLES, ind_count, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, vert_count);

    // Update
    glfwSwapBuffers(window);
    glfwPollEvents();
    usleep(8000);
  }

  vao_delete(vao);
  vbo_delete(vbo);
  ebo_delete(ebo);
  shader_delete_program(shader_program);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
