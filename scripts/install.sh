#!/bin/bash
# CDocx Installation Script
# Usage: ./install.sh [options]

set -e

# Default values
INSTALL_PREFIX="/usr/local"
BUILD_TYPE="Release"
BUILD_SHARED="OFF"
INSTALL_DOCS="OFF"
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Help message
show_help() {
    echo "CDocx Installation Script"
    echo ""
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -p, --prefix PATH       Installation prefix (default: /usr/local)"
    echo "  -b, --build-type TYPE   Build type: Debug, Release, RelWithDebInfo (default: Release)"
    echo "  -s, --shared            Build shared library instead of static"
    echo "  -d, --docs              Install documentation"
    echo "  -j, --jobs N            Number of parallel jobs (default: auto)"
    echo "  -u, --uninstall         Uninstall CDocx"
    echo "  -h, --help              Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                                      # Install to /usr/local"
    echo "  $0 --prefix \$HOME/.local                # Install to user directory"
    echo "  $0 --shared --docs                      # Build shared library with docs"
    echo "  $0 --uninstall                          # Uninstall CDocx"
}

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -p|--prefix)
            INSTALL_PREFIX="$2"
            shift 2
            ;;
        -b|--build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -s|--shared)
            BUILD_SHARED="ON"
            shift
            ;;
        -d|--docs)
            INSTALL_DOCS="ON"
            shift
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        -u|--uninstall)
            UNINSTALL=1
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}CDocx Installation Script${NC}"
echo -e "${GREEN}========================================${NC}"
echo ""

# Uninstall
if [[ -n "$UNINSTALL" ]]; then
    if [[ -d "$BUILD_DIR" ]]; then
        echo -e "${YELLOW}Uninstalling CDocx...${NC}"
        cd "$BUILD_DIR"
        if [[ -f "cmake_uninstall.cmake" ]]; then
            cmake --build . --target uninstall
            echo -e "${GREEN}Uninstallation complete!${NC}"
        else
            echo -e "${RED}Error: Build directory exists but uninstall script not found.${NC}"
            echo "Please remove CDocx files manually or rebuild first."
            exit 1
        fi
    else
        echo -e "${RED}Error: Build directory not found. Cannot uninstall.${NC}"
        exit 1
    fi
    exit 0
fi

# Check prerequisites
echo -e "${YELLOW}Checking prerequisites...${NC}"

if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Error: CMake not found. Please install CMake 3.10 or higher.${NC}"
    exit 1
fi

if ! command -v git &> /dev/null; then
    echo -e "${RED}Error: Git not found. Please install Git.${NC}"
    exit 1
fi

CMAKE_VERSION=$(cmake --version | head -n1 | grep -oE '[0-9]+\.[0-9]+')
REQUIRED_VERSION="3.10"

if [ "$(printf '%s\n' "$REQUIRED_VERSION" "$CMAKE_VERSION" | sort -V | head -n1)" != "$REQUIRED_VERSION" ]; then 
    echo -e "${RED}Error: CMake version $CMAKE_VERSION is too old. Need 3.10 or higher.${NC}"
    exit 1
fi

echo -e "${GREEN}✓ CMake $CMAKE_VERSION found${NC}"
echo ""

# Initialize submodules
echo -e "${YELLOW}Initializing submodules...${NC}"
cd "$PROJECT_ROOT"
if [[ -d ".git" ]]; then
    git submodule update --init --recursive
fi
echo -e "${GREEN}✓ Submodules ready${NC}"
echo ""

# Create build directory
echo -e "${YELLOW}Creating build directory...${NC}"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
echo -e "${GREEN}✓ Build directory: $BUILD_DIR${NC}"
echo ""

# Configure
echo -e "${YELLOW}Configuring with CMake...${NC}"
echo "  Install prefix: $INSTALL_PREFIX"
echo "  Build type: $BUILD_TYPE"
echo "  Shared library: $BUILD_SHARED"
echo "  Install docs: $INSTALL_DOCS"
echo "  Parallel jobs: $JOBS"
echo ""

cmake .. \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DBUILD_SHARED_LIBS="$BUILD_SHARED" \
    -DINSTALL_DOCS="$INSTALL_DOCS" \
    -DBUILD_DOCS="$INSTALL_DOCS" \
    -DBUILD_TESTING=OFF

echo -e "${GREEN}✓ Configuration complete${NC}"
echo ""

# Build
echo -e "${YELLOW}Building CDocx...${NC}"
cmake --build . --parallel "$JOBS"
echo -e "${GREEN}✓ Build complete${NC}"
echo ""

# Install
echo -e "${YELLOW}Installing CDocx to $INSTALL_PREFIX...${NC}"
if [[ "$INSTALL_PREFIX" == "/usr"* ]] && [[ $EUID -ne 0 ]]; then
    echo -e "${YELLOW}Note: Installation to system directory requires sudo.${NC}"
    sudo cmake --install .
else
    cmake --install .
fi
echo -e "${GREEN}✓ Installation complete${NC}"
echo ""

# Summary
echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}CDocx Installation Summary${NC}"
echo -e "${GREEN}========================================${NC}"
echo ""
echo "Installation directory: $INSTALL_PREFIX"
echo "Library: $INSTALL_PREFIX/lib"
echo "Headers: $INSTALL_PREFIX/include/cdocx"
echo "CMake config: $INSTALL_PREFIX/lib/cmake/cdocx"
echo ""
echo "To use CDocx in your project:"
echo ""
echo "  CMake:"
echo "    find_package(cdocx REQUIRED)"
echo "    target_link_libraries(your_target PRIVATE cdocx::cdocx)"
echo ""
echo "  Compile:"
echo "    g++ -std=c++17 your_app.cpp -lcdocx -o your_app"
echo ""
echo -e "${GREEN}Installation successful!${NC}"
echo ""
echo "To uninstall, run: $0 --uninstall"
