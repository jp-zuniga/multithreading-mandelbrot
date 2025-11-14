#include <CImg.h>
#include <chrono>
#include <iostream>

#include "mandelbrot.h"

using namespace std::chrono;

inline void measure_runtime(cil::CImg<unsigned char> &img, int n) {
  for (int i = 0; i < n; i++) {
    steady_clock::time_point begin = steady_clock::now();
    calc_fractal(img);
    steady_clock::time_point end = steady_clock::now();

    std::cout << "\n\nExecution time: "
              << duration_cast<milliseconds>(end - begin).count() << "ms"
              << std::endl;
  }
}
