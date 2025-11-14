#include <CImg.h>

struct ThreadData {
  long *id;
  cil::CImg<unsigned char> *img;
};
