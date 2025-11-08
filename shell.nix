{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  buildInputs = with pkgs; [
    cimg
    clang-tools
    clang
    just
    libclang
    libcxx
    libpng
    xorg.libX11
    zlib
  ];
}
