#include <CImg.h>
#include <cmath>
#include <iostream>
#include <pthread.h>

#include "thread_data.h"

#define WIDTH 800
#define HEIGHT 800

#define IMG_NAME "out/fractal.png"

#define C_REAL_MIN -1.5
#define C_REAL_MAX 0.5
#define C_IMAG_MIN -1.4
#define C_IMAG_MAX 1.4

#define N_MAX 1000
#define N_THREADS 10
#define THREAD_ROWS HEIGHT / N_THREADS

inline void calc_pixel(cil::CImg<unsigned char> &img, const int &x,
                       const int &y) {
  double c_r = C_REAL_MIN + ((C_REAL_MAX - C_REAL_MIN) / WIDTH) * x;
  double c_i = C_IMAG_MIN + ((C_IMAG_MAX - C_IMAG_MIN) / HEIGHT) * y;
  double z_r = c_r;
  double z_i = c_i;
  int n;

  for (n = 0; n < N_MAX; n++) {
    double r_tmp = (z_r * z_r) - (z_i * z_i) + c_r;
    double i_tmp = (2.0 * z_r * z_i) + c_i;

    z_r = r_tmp;
    z_i = i_tmp;

    if (z_r * z_r + z_i * z_i > 4) {
      break;
    }
  }

  unsigned char r, g, b;

  if (n < N_MAX) {
    float hue = 1 + 30 * (2 * M_PI *
                          (n + 1 - log2(log(z_r * z_r + z_i * z_i))) / N_MAX);

    r = 127 * (1 + (cos(hue)));
    g = 127 * (1 + (cos(hue + 2.0 / 3.0 * M_PI)));
    b = 127 * (1 + (cos(hue + 4.0 / 3.0 * M_PI)));
  } else {
    r = g = b = 0;
  }

  img(x, y, 0, 0) = r;
  img(x, y, 0, 1) = g;
  img(x, y, 0, 2) = b;
}

inline void *calc_thread(void *arg) {
  ThreadData *data = static_cast<ThreadData *>(arg);

  int y_inicio = data->tid * THREAD_ROWS;
  int y_fin = (data->tid == N_THREADS - 1) ? HEIGHT : y_inicio + THREAD_ROWS;

  for (int y = y_inicio; y < y_fin; y++) {
    for (int x = 0; x < WIDTH; x++) {
      calc_pixel(*data->img, x, y);
    }
  }

  pthread_exit(nullptr);
}

inline void calc_fractal(cil::CImg<unsigned char> &img) {
  int rc;
  pthread_t threads[N_THREADS];
  ThreadData thread_data[N_THREADS];

  for (long t = 0; t < N_THREADS; t++) {
    thread_data[t].tid = t;
    thread_data[t].img = &img;

    rc = pthread_create(&threads[t], nullptr, calc_thread,
                        static_cast<void *>(&thread_data[t]));

    if (rc) {
      std::cout << "ERROR: pthread_create() = " << rc << "\n";
      exit(-1);
    }
  }

  for (int t = 0; t < N_THREADS; t++) {
    pthread_join(threads[t], nullptr);
  }

  img.save_png(IMG_NAME);
}
