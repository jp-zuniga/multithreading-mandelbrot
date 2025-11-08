#include <CImg.h>

#include "include/runtime.h"

int main() {
  cil::CImg<unsigned char> img(WIDTH, HEIGHT, 1, 3);
  measure_runtime(img, 1);
  return 0;
}
