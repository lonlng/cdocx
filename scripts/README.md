# CDocx Scripts

This directory contains helper scripts for CDocx.

## Available Scripts

### install.sh

Bash script for easy installation of CDocx on Linux and macOS.

#### Usage

```bash
./scripts/install.sh [options]
```

#### Options

| Option | Short | Description |
|--------|-------|-------------|
| `--prefix PATH` | `-p` | Installation prefix (default: /usr/local) |
| `--build-type TYPE` | `-b` | Build type: Debug, Release (default: Release) |
| `--shared` | `-s` | Build shared library |
| `--docs` | `-d` | Install documentation |
| `--jobs N` | `-j` | Number of parallel jobs |
| `--uninstall` | `-u` | Uninstall CDocx |
| `--help` | `-h` | Show help message |

#### Examples

```bash
# Install to system (requires sudo)
./scripts/install.sh

# Install to user directory
./scripts/install.sh --prefix $HOME/.local

# Build and install shared library with documentation
./scripts/install.sh --shared --docs --prefix $HOME/.local

# Uninstall
./scripts/install.sh --uninstall
```

#### Prerequisites

- CMake 3.10+
- C++17 compiler
- Git

#### What It Does

1. Checks prerequisites (CMake, Git)
2. Initializes Git submodules
3. Configures CMake with specified options
4. Builds the library
5. Installs to the specified prefix
6. Shows installation summary

## Windows Installation

For Windows, use CMake directly:

```powershell
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX="C:\Program Files\CDocx"
cmake --build . --config Release
cmake --install . --config Release
```

## Adding Scripts to PATH

You can add this directory to your PATH for easier access:

```bash
# Add to ~/.bashrc or ~/.zshrc
export PATH="/path/to/cdocx/scripts:$PATH"
```

Then use:

```bash
cdocx-install --prefix $HOME/.local
```
