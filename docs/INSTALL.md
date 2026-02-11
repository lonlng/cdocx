# CDocx Installation Guide

This guide explains how to build and install CDocx using CMake.

## Table of Contents

- [Quick Start](#quick-start)
- [Prerequisites](#prerequisites)
- [Basic Installation](#basic-installation)
- [Custom Installation Paths](#custom-installation-paths)
- [Installation Options](#installation-options)
- [Uninstalling](#uninstalling)
- [Using Installed Library](#using-installed-library)
- [Advanced Configuration](#advanced-configuration)

## Quick Start

```bash
# Clone the repository
git clone --recursive https://github.com/lonlng/CDocx.git
cd CDocx

# Build and install
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build .
cmake --install .
```

## Prerequisites

- **CMake** 3.10 or higher
- **C++17** compatible compiler:
  - GCC 7+
  - Clang 5+
  - MSVC 2017+
- **Git** (for cloning submodules)

## Basic Installation

### 1. Clone with Submodules

```bash
git clone --recursive https://github.com/lonlng/CDocx.git
cd CDocx
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

### 2. Configure

```bash
mkdir build && cd build
cmake ..
```

By default, this installs to the build directory's `install` folder.

### 3. Build

```bash
cmake --build . --parallel
```

### 4. Install

```bash
# Default installation (to build/install)
cmake --install .

# Or specify a custom prefix during configuration
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --install .
```

## Custom Installation Paths

### System-wide Installation (Linux/macOS)

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build .
sudo cmake --install .
```

Files will be installed to:
- `/usr/local/lib/libcdocx.a` (or `.so`)
- `/usr/local/include/cdocx/` (headers)
- `/usr/local/lib/cmake/cdocx/` (CMake config)

### User-local Installation

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
cmake --build .
cmake --install .
```

Add to your `~/.bashrc` or `~/.zshrc`:

```bash
export PKG_CONFIG_PATH="$HOME/.local/lib/pkgconfig:$PKG_CONFIG_PATH"
export CMAKE_PREFIX_PATH="$HOME/.local:$CMAKE_PREFIX_PATH"
```

### Windows Installation

```powershell
# Using Visual Studio generator
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX="C:\Program Files\CDocx"
cmake --build . --config Release
cmake --install . --config Release
```

### Project-local Installation

```bash
# Install to a specific directory within your project
cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/your/project/third_party/cdocx
cmake --build .
cmake --install .
```

## Installation Options

### Install Components

```bash
# Install everything (default)
cmake .. -DINSTALL_HEADERS=ON -DINSTALL_CMAKE_CONFIG=ON -DINSTALL_DOCS=ON -DINSTALL_EXAMPLES=ON

# Minimal installation (library only)
cmake .. -DINSTALL_HEADERS=OFF -DINSTALL_CMAKE_CONFIG=OFF

# Full installation with documentation
cmake .. -DINSTALL_DOCS=ON -DBUILD_DOCS=ON
```

| Option | Default | Description |
|--------|---------|-------------|
| `INSTALL_HEADERS` | ON | Install header files |
| `INSTALL_CMAKE_CONFIG` | ON | Install CMake configuration files |
| `INSTALL_DOCS` | OFF | Install documentation |
| `INSTALL_EXAMPLES` | OFF | Install example files |

### Shared vs Static Library

```bash
# Build shared library
cmake .. -DBUILD_SHARED_LIBS=ON

# Build static library (default)
cmake .. -DBUILD_SHARED_LIBS=OFF
```

### Build Type

```bash
# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Release build (optimized)
cmake .. -DCMAKE_BUILD_TYPE=Release

# RelWithDebInfo
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
```

## Uninstalling

### Method 1: Using CMake Uninstall Target

```bash
cd build
sudo cmake --build . --target uninstall
```

### Method 2: Manual Removal

Remove the installed files manually:

```bash
# Remove headers
sudo rm -rf /usr/local/include/cdocx.h
sudo rm -rf /usr/local/include/cdocx

# Remove library
sudo rm -f /usr/local/lib/libcdocx.a
sudo rm -f /usr/local/lib/libcdocx.so*  # if shared

# Remove CMake config
sudo rm -rf /usr/local/lib/cmake/cdocx
```

### Method 3: Using Install Manifest

```bash
cd build
sudo xargs rm < install_manifest.txt
```

## Using Installed Library

### In Your CMake Project

**Method 1: Using find_package**

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Find CDocx
find_package(cdocx REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE cdocx::cdocx)
```

Configure with:

```bash
cmake .. -Dcdocx_DIR=/usr/local/lib/cmake/cdocx
# or if in custom location:
cmake .. -Dcdocx_DIR=/custom/path/lib/cmake/cdocx
```

**Method 2: Using CMAKE_PREFIX_PATH**

```bash
cmake .. -DCMAKE_PREFIX_PATH=/usr/local
```

**Method 3: FetchContent (for embedded builds)**

```cmake
include(FetchContent)
FetchContent_Declare(
    cdocx
    GIT_REPOSITORY https://github.com/lonlng/CDocx.git
    GIT_TAG v0.2.0
)
FetchContent_MakeAvailable(cdocx)

target_link_libraries(my_app PRIVATE cdocx::cdocx)
```

### In Your C++ Code

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc("input.docx");
    doc.open();
    
    // ... your code
    
    return 0;
}
```

### Compile Manually (without CMake)

```bash
# GCC/Clang
g++ -std=c++17 -I/usr/local/include my_app.cpp -L/usr/local/lib -lcdocx -o my_app

# With pugixml (if static)
g++ -std=c++17 -I/usr/local/include my_app.cpp -L/usr/local/lib -lcdocx -lpugixml -o my_app
```

## Advanced Configuration

### Custom Directory Layout

```bash
cmake .. \
    -DCMAKE_INSTALL_BINDIR=bin \
    -DCMAKE_INSTALL_LIBDIR=lib \
    -DCMAKE_INSTALL_INCLUDEDIR=include \
    -DCMAKE_INSTALL_DOCDIR=share/doc/cdocx
```

### Cross-compilation

```bash
# For ARM Linux
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-toolchain.cmake \
    -DCMAKE_INSTALL_PREFIX=/path/to/arm/sysroot
```

### Packaging

```bash
# Create package
cmake --build . --target package

# Specific package types
cpack -G DEB    # Debian/Ubuntu
cpack -G RPM    # RedHat/Fedora
cpack -G NSIS   # Windows installer
cpack -G TGZ    # Tarball
```

### Using with pkg-config

If pkg-config is available:

```bash
# Compile
g++ -std=c++17 my_app.cpp `pkg-config --cflags --libs cdocx` -o my_app
```

### Environment Variables

For development, you can set:

```bash
# In .bashrc or .zshrc
export CDocx_ROOT=/path/to/cdocx/install
export CMAKE_PREFIX_PATH="${CDocx_ROOT}:${CMAKE_PREFIX_PATH}"
export LD_LIBRARY_PATH="${CDocx_ROOT}/lib:${LD_LIBRARY_PATH}"  # For shared libs
```

## Troubleshooting

### "Could not find cdocx package"

Make sure `cdocx_DIR` points to the directory containing `cdocx-config.cmake`:

```bash
cmake .. -Dcdocx_DIR=/usr/local/lib/cmake/cdocx
```

### "Cannot find install manifest"

The uninstall target requires the build directory to exist. Keep your build directory or copy the `install_manifest.txt` file.

### Permission Denied on Install

```bash
# Use sudo for system directories
sudo cmake --install .

# Or install to user directory
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
cmake --install .
```

### Library Not Found at Runtime (Linux)

For shared libraries:

```bash
# Update library cache
sudo ldconfig /usr/local/lib

# Or set LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

## Quick Reference

| Task | Command |
|------|---------|
| Configure | `cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local` |
| Build | `cmake --build . --parallel` |
| Install | `cmake --install .` (or `sudo cmake --install .`) |
| Uninstall | `cmake --build . --target uninstall` |
| Clean | `cmake --build . --target clean` |

## See Also

- [README.md](../README.md) - Project overview
- [CONTRIBUTING.md](../CONTRIBUTING.md) - Contribution guidelines
- [CMake Documentation](https://cmake.org/documentation/)
