# `multithreading-mandelbrot`

A [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) generator utilizing basic multithreading.

Uses the lightweight [`CImg`](https://github.com/GreycLab/CImg) library for image processing, and `pthread.h` for thread manipulation.

## Usage

### Nix users

Use `nix-shell` to install the necessary dependencies into an ephemeral shell:

```bash
nix-shell shell.nix

# or if you don't use bash:
nix-shell shell.nix --command <your-shell>
```

Now, just run the project with [`just`](https://github.com/casey/just)!

```bash
just run
```

You can see the generated fractal in `out/fractal.png`. Playing around with the constants in [`mandelbrot.h`](./src/include/mandelbrot.h) should yield varying results.

### Linux users

Install all the packages listed in [`shell.nix`](./shell.nix) using your distro's package manager, then build and run the project with `just` as shown previously.

### Everyone Else

You can probably figure it out if you really want to.

---

### [License](./LICENSE)
