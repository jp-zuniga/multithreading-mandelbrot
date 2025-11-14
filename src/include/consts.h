#define IMG_NAME "out/fractal.png"
#define WIDTH 800
#define HEIGHT 800

#define C_REAL_MIN -1.5
#define C_REAL_MAX 0.5
#define C_IMAG_MIN -1.4
#define C_IMAG_MAX 1.4

#define DX (C_REAL_MAX - C_REAL_MIN) / WIDTH
#define DY (C_IMAG_MAX - C_IMAG_MIN) / HEIGHT

#define N_MAX 1000
#define N_RUNS 5
#define N_THREADS 12
#define THREAD_COLS WIDTH / N_THREADS
