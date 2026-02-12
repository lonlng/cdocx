#!/bin/bash
# ============================================================================
# CDocx Code Quality Check Script (Linux/macOS)
# ============================================================================
# Usage:
#   ./scripts/code-quality.sh format       - Format all code
#   ./scripts/code-quality.sh format-check - Check formatting without changes
#   ./scripts/code-quality.sh tidy         - Run static analysis
#   ./scripts/code-quality.sh tidy-fix     - Run static analysis with auto-fix
#   ./scripts/code-quality.sh all          - Run all checks
# ============================================================================

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="${PROJECT_DIR}/build"

# Help message
usage() {
    cat << EOF
CDocx Code Quality Tools
========================

Usage: $0 [command]

Commands:
  format       - Format all code with clang-format
  format-check - Check formatting without making changes
  tidy         - Run clang-tidy static analysis
  tidy-fix     - Run clang-tidy with automatic fixes
  all          - Run format-check and tidy

Examples:
  $0 format
  $0 tidy-fix
  $0 all

EOF
    exit 1
}

# Check build directory exists
check_build_dir() {
    if [ ! -d "$BUILD_DIR" ]; then
        echo -e "${RED}[ERROR]${NC} Build directory not found: $BUILD_DIR"
        echo "Please run: mkdir build && cd build && cmake .."
        exit 1
    fi
}

# Run formatting
run_format() {
    echo -e "${GREEN}[Code Quality]${NC} Formatting code with clang-format..."
    cmake --build "$BUILD_DIR" --target format
}

# Run format check
run_format_check() {
    echo -e "${GREEN}[Code Quality]${NC} Checking code formatting..."
    cmake --build "$BUILD_DIR" --target format-check
}

# Run clang-tidy
run_tidy() {
    echo -e "${GREEN}[Code Quality]${NC} Running clang-tidy analysis..."
    cmake --build "$BUILD_DIR" --target tidy
}

# Run clang-tidy with fixes
run_tidy_fix() {
    echo -e "${GREEN}[Code Quality]${NC} Running clang-tidy with auto-fix..."
    cmake --build "$BUILD_DIR" --target tidy-fix
}

# Run all checks
run_all() {
    echo -e "${GREEN}[Code Quality]${NC} Running all checks..."
    echo ""
    echo "=== Format Check ==="
    cmake --build "$BUILD_DIR" --target format-check || true
    echo ""
    echo "=== Static Analysis ==="
    cmake --build "$BUILD_DIR" --target tidy || true
}

# Main
if [ $# -eq 0 ]; then
    usage
fi

check_build_dir

case "$1" in
    format)
        run_format
        ;;
    format-check)
        run_format_check
        ;;
    tidy)
        run_tidy
        ;;
    tidy-fix)
        run_tidy_fix
        ;;
    all)
        run_all
        ;;
    -h|--help|help)
        usage
        ;;
    *)
        echo -e "${RED}[ERROR]${NC} Unknown command: $1"
        usage
        ;;
esac

echo ""
echo -e "${GREEN}[Code Quality]${NC} Done!"
