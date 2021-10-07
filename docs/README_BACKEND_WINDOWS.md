# Backend Instructions for Windows

## Prerequisites

- Visual Studio Code
- MinGW64 (including gcc, gdb, cmake and boost)

## How to setup tools on Windows using MSYS2 (MinGW64)

### install MSYS2

- Get the [MSYS2 64 bit installer](https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20200903.exe)
- install to default location `C:\msys64`
- start msys2 in `C:\msys64\msys2.exe`
- inside the msys2 shell type: `pacman -Syuu` (close the shell when you are asked to)
- type this command `pacman -Syuu` multiple times until there are no updates left ;)

### install gcc, gdb and cmake via MSYS2

- start msys2.exe and type in msys2 shell:

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake
```

- add `C:\msys64\mingw64\bin` to your system PATH
- type `gcc --version` or `g++ --version` to ensure gcc installation is fine
- type `gdb --version` to ensure gdb installation is fine
- type `cmake --version` to ensure gdb installation is fine

### install missing libraries via MSYS2

- start msys2.exe and type in msys2 shell:

```bash
   pacman -Sy mingw-w64-x86_64-boost
```

### configure VisualStudio Code

- add the following lines to `.vscode\settings.json`: (cannot be commited due to platform incompatibility)

```json
  "cmake.generator": "MinGW Makefiles",
  "cmake.cmakePath": "C:/msys64/mingw64/bin/cmake.exe",
  "cmake.mingwSearchDirs": [
      "C:/msys64/mingw64",
  ],
  "cmake.preferredGenerators": [
      "MinGW Makefiles"
  ],
```

- select compiler kit `[GCC 10.2.0]` in the bottom bar
- run `cmake:Configure` again
- run `cmake_Build`
- run `cmake: Run without debugging`

---

## Build the service

- open Command Palette `Ctrl+Shift+P` and run `CMake: Configure`
  - `/build` should be created (contains build system)
- open Command Palette `Ctrl+Shift+P` and run `CMake: Build`

## Run and debug the service

- open Command Palette `Ctrl+Shift+P` and run `CMake: Run without Debugging`
- With Debugger: open Command Palette `Ctrl+Shift+P` and run `CMake: Debug`
