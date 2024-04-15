#include "util.h"

void readFile(const char *filepath, char *&out, long *fileSize) {
  FILE *fp = fopen( filepath, "rb");
  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  if (fileSize != nullptr) {
    *fileSize = size;
  }
  rewind(fp);

  out = static_cast<char *>(calloc(1, size + 1));
  fread(out, size, 1, fp);
  fclose(fp);
}