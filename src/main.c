#include <stdio.h>
#include <unistd.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vbo.h>
#include <ebo.h>
#include <vao.h>
#include <shaders.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct {
  float x, y, z;
} vec3_t;

typedef struct {
  float r, g, b;
} col3_t;

typedef struct {
  vec3_t pos;
  col3_t col;
} vertex_t;

vertex_t vertices[] = {
    {{-0.75f, -0.75f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // A (RED)
    {{0.75f, -0.75f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // B (GREEN)
    {{0.75f, 0.75f, 0.0f}, {1.0f, 0.0f, 0.0f}},   // C (RED)
    {{-0.75f, 0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}},  // D (BLUE)
};

GLuint indices[] = {
    0, 1, 3, // ABD
    3, 1, 2, // DBC
}; // Square
const int ind_count = sizeof(indices) / sizeof(GLuint);

int main(void) {

  // Create GLFW instance
  if (!glfwInit()) {
    fprintf(stderr, "GLFW Init error\r\n");
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  puts("GLFW: Initialized");

  // Create GLFW window
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Window name", NULL, NULL);
  if (!window) {
    fprintf(stderr, "GLFW Window error\r\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  puts("GLFW: Created window");

  // Load OpenGL
  int ver = gladLoadGL(glfwGetProcAddress);
  if (!ver) {
    fprintf(stderr, "GLAD Error\r\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  printf("GLAD: OpenGL Version:  %d.%d\r\n", GLAD_VERSION_MAJOR(ver),
         GLAD_VERSION_MINOR(ver));
  printf("GLAD: OpenGL Renderer: %s\r\n", glGetString(GL_RENDERER));

  GLuint vao, vbo, ebo;
  vao = vao_create();
  vao_bind(vao);

  vbo = vbo_create((GLfloat *)vertices, sizeof(vertices));
  ebo = ebo_create(indices, sizeof(indices));

  vao_link(vao, vbo, 0, 3, GL_FLOAT, sizeof(vertex_t),
           (void *)offsetof(vertex_t, pos));
  vao_link(vao, vbo, 1, 3, GL_FLOAT, sizeof(vertex_t),
           (void *)offsetof(vertex_t, col));
  vao_unbind();
  vbo_unbind();
  ebo_unbind();

  puts("MAIN: Created buffers and arrays");

  // Compile shaders
  GLuint vs, fs, shader_program;

  puts("MAIN: Compiling shaders");
  vs = shader_compile(vertex_shader, GL_VERTEX_SHADER);
  fs = shader_compile(fragment_shader, GL_FRAGMENT_SHADER);

  puts("MAIN: Linking shader program");
  shader_program = shader_create_program();
  shader_attach(shader_program, vs);
  shader_attach(shader_program, fs);
  shader_link_program(shader_program);

  puts("MAIN: Removing compiled shaders");
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

    // Update
    glfwSwapBuffers(window);
    glfwPollEvents();
    usleep(8000);
  }
  puts("MAIN: Window closed");

  puts("MAIN: Deleting buffers and arrays");
  vao_delete(vao);
  vbo_delete(vbo);
  ebo_delete(ebo);

  puts("MAIN: Deleting shader program");
  shader_delete_program(shader_program);

  puts("MAIN: Destroying window and GLFW instance");
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
