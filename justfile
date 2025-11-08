compile:
    clang++ -std=c++20 src/main.cpp \
            -Iinclude \
            -Dcimg_display=0 -Dcimg_use_png \
            -lpng -lpthread \
            -o out/mandelbrot
