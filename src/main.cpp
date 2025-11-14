#include <CImg.h>

#include <chrono>

#include "include/consts.h"
#include "include/mandelbrot.h"

using namespace std::chrono;

int main() {
  cil::CImg<unsigned char> img(WIDTH, HEIGHT, 1, 3);

  for (int i = 0; i < N_RUNS; i++) {
    steady_clock::time_point begin = steady_clock::now();
    calc_fractal(img);
    steady_clock::time_point end = steady_clock::now();

    std::cout << "Execution time: "
              << duration_cast<milliseconds>(end - begin).count() << "ms\n";
  }

  img.save_png(IMG_NAME);

  return 0;
}
