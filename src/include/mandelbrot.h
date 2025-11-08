#include <CImg.h>
#include <cmath>

#define WIDTH 800
#define HEIGHT 800

#define IMG_NAME "out/fractal.png"

#define C_REAL_MIN -1.5
#define C_REAL_MAX 0.5
#define C_IMAG_MIN -1.4
#define C_IMAG_MAX 1.4

#define N_MAX 1000

inline void calc_pixel(cil::CImg<unsigned char> &img, int x, int y) {
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

inline void calc_fractal(cil::CImg<unsigned char> &img) {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      calc_pixel(img, x, y);
    }
  }

  img.save_png(IMG_NAME);
}
