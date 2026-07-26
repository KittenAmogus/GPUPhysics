#include <stdio.h>
#include <stdlib.h>
#include <shaders.h>

const char *vertex_shader = "./vertex.vert";
const char *fragment_shader = "./fragment.frag";

const char *read_shader(const char *path) {
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
