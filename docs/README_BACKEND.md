# Backend Instructions

## Prerequisites

- Visual Studio Code
- CMake
- C++ Compiler
  - GCC (Linux, Windows) or Clang (Mac)
- C++ Debugger
  - GDB (Linux, Windows) or lldb (Mac)
- Boost > 1.55

**CMake, C++ Compiler and C++ Debugger need to be in PATH**

## Build the service

- open Command Palette `Ctrl+Shift+P` and run `CMake: Configure`
  - `/build` should be created (contains build system)
- open Command Palette `Ctrl+Shift+P` and run `CMake: Build`

## Run and debug the service

- open Command Palette `Ctrl+Shift+P` and run `CMake: Run without Debugging`
- With Debugger: open Command Palette `Ctrl+Shift+P` and run `CMake: Debug`

---

## Troubleshooting

### GDB

- source files of stl not found:
  - add a sourceFileMap entry to `launch.json` files

### Cmake Tools

- no compiler kit found:
  - open Command Palette `Ctrl+Shift+P` and run the `CMake: Edit User-Local CMake Kits` command
  - specify your correct compiler path in `cmake-tools-kits.json` file

### Application Exceptions

- Boost system error: bind: Address already in use:
  - Kill application running on port 8080: `kill \$(lsof -t -i:8080)`
