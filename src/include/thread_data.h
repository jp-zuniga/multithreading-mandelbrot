#include <CImg.h>

struct ThreadData {
  int id;
  cil::CImg<unsigned char> *img;
};
