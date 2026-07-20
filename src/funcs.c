#include <stdio.h>

#include <funcs.h>

void error_callback_glfw(int error, const char *description) {
  fprintf(stderr, "GLFW: Error (%d): %s\r\n", error, description);
}
