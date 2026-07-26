#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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

  // Load shaders
  const char *vs_src;
  const char *fs_src;
  vs_src = read_shader(vertex_shader);
  if (vs_src == NULL) {
    fprintf(stderr, "MAIN: VS error\r\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }
  fs_src = read_shader(fragment_shader);
  if (fs_src == NULL) {
    fprintf(stderr, "MAIN: FS error\r\n");
    free((void *)vs_src);
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

  // Compile shaders
  GLuint vs, fs;

  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vs_src, NULL);
  glCompileShader(vs);
  free((void *)vs_src);

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fs_src, NULL);
  free((void *)fs_src);
  glCompileShader(fs);

  // Link shader program
  GLuint shader_program;
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  glAttachShader(shader_program, fs);
  glLinkProgram(shader_program);

  // Clean shaders
  glDetachShader(shader_program, vs);
  glDetachShader(shader_program, fs);
  glDeleteShader(vs);
  glDeleteShader(fs);

  // Allocate arrays and buffers
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind VAO
  glBindVertexArray(VAO);

  // Bind buffer and copy data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Create attribute pointer
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, NULL);

  // Enable VAO
  glEnableVertexAttribArray(0);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
    glBindVertexArray(VAO);

    // Draw triangle
    glDrawElements(GL_TRIANGLES, ind_count, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, vert_count);

    // Update
    glfwSwapBuffers(window);
    glfwPollEvents();
    usleep(8000);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shader_program);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
