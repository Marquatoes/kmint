{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  buildInputs = [
    cmake
    ninja
    SDL2
    SDL2_image
    pkgconfig
    pandoc
  ];
}
