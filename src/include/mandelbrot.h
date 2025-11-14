#include <CImg.h>
#include <pthread.h>

#include <cmath>
#include <iostream>

#include "consts.h"
#include "thread_data.h"

inline void calc_pixel(ThreadData &data, const int &x, const int &y) {
  int n;
  double cr = C_REAL_MIN + DX * x;
  double ci = C_IMAG_MIN + DY * y;
  double zr = cr;
  double zi = ci;

  for (n = 0; n < N_MAX; ++n) {
    double zr2 = zr * zr;
    double zi2 = zi * zi;

    if (zr2 + zi2 > 4.0)
      break;

    double zri = zr * zi;

    zi = 2.0 * zri + ci;
    zr = zr2 - zi2 + cr;
  }

  unsigned char r, g, b;

  if (n < N_MAX) {
    float hue =
        1 + 30 * (2 * M_PI * (n + 1 - log2(log(zr * zr + zi * zi))) / N_MAX);

    r = 127 * (1 + (cos(hue)));
    g = 127 * (1 + (cos(hue + 2.0 / 3.0 * M_PI)));
    b = 127 * (1 + (cos(hue + 4.0 / 3.0 * M_PI)));
  } else {
    r = g = b = 0;
  }

  (*data.img)(x, y, 0, 0) = r;
  (*data.img)(x, y, 0, 1) = g;
  (*data.img)(x, y, 0, 2) = b;
}

inline void *calc_thread(void *arg) {
  ThreadData *data = static_cast<ThreadData *>(arg);

  int start_x = *data->id * THREAD_COLS;
  int end_x = (*data->id == N_THREADS - 1) ? WIDTH : start_x + THREAD_COLS;

  for (int x = start_x; x < end_x; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      calc_pixel(*data, x, y);
    }
  }

  pthread_exit(nullptr);
}

inline void calc_fractal(cil::CImg<unsigned char> &img) {
  int rc;
  pthread_t threads[N_THREADS];
  ThreadData thread_data[N_THREADS];

  for (long t = 0; t < N_THREADS; t++) {
    thread_data[t] = {&t, &img};
    rc = pthread_create(&threads[t], nullptr, calc_thread,
                        static_cast<void *>(&thread_data[t]));

    if (rc) {
      std::cout << "`pthread_create` error: " << rc << "\n";
      exit(-1);
    }
  }

  for (int t = 0; t < N_THREADS; t++) {
    pthread_join(threads[t], nullptr);
  }
}
