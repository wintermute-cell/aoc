{ pkgs ? import (fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/nixos-24.05.tar.gz";
  }) {}
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    libgcc
    clang-tools
    pkg-config
    cmake
    gdb
    libgcc
    pkgs.glibc.static # useful for static linking (but that shouldnt be relevant since we time inside the program)
  ];

  shellHook = '''';
}

