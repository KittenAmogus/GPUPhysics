#include <stdio.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(int argc, char **argv) {
  printf("./Simulator (argc=%d)\n", argc);

  for (int i = 0; i < argc; ++i) {
    printf("(argv[%d]=%s)\n", i, argv[i]);
  }

  return 0;
}
