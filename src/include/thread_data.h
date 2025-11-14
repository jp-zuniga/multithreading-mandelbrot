#include <CImg.h>

struct ThreadData {
  long tid;
  cil::CImg<unsigned char> *img;
};
