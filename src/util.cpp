#include "util.h"

void readFile(const char *filepath, char *&out) {
  FILE *fp = fopen( filepath , "rb");
  fseek(fp , 0L , SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  out = static_cast<char *>(calloc(1, size + 1));
  fread(out, size, 1 , fp);
  fclose(fp);
}