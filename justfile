[private]
default:
  just --list

compile:
  mkdir -p out
  clang++ src/main.cpp \
          -std=c++20 \
          -Iinclude \
          -lpng \
          -lpthread \
          -Dcimg_display=0 \
          -Dcimg_use_png \
          -o out/mandelbrot

run: compile
  ./out/mandelbrot
