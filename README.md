# CDocx

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)

C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files.

## Features

- **📄 Document Operations**: Read, write, and edit DOCX files with complete structure support
- **🔄 Template System**: Placeholder replacement with `{{key}}` pattern
- **📑 Document Insertion**: Merge documents at specific positions
- **🔧 XML Parts API**: Direct access to all DOCX internal components
- **🖼️ Media Management**: Add, delete, replace images in `word/media/`
- **🌳 Tree-Based Storage**: Internal tree structure mirrors ZIP organization
- **⚡ Modern C++17**: Iterator-based API with range-based for loop support
- **✅ Cross-Platform**: Linux, Windows (MSVC/MinGW), macOS support

## Quick Start

### Prerequisites

- CMake 3.14+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git

### Build (Linux/macOS)

```bash
git clone https://github.com/lonlng/CDocx.git
cd CDocx
git submodule update --init --recursive

# Using the build script
./scripts/build-linux.sh Release

# Or manually
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
ctest --output-on-failure
```

### Build (Windows)

```cmd
git clone https://github.com/lonlng/CDocx.git
cd CDocx
git submodule update --init --recursive

:: Using the build script (run in Visual Studio Developer Command Prompt)
scripts\build-windows.bat Release x64

:: Or manually
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release --parallel
ctest -C Release --output-on-failure
```

### Example

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    // Read document
    cdocx::Document doc("file.docx");
    doc.open();
    
    for (auto& p : doc.paragraphs()) {
        for (auto& r : p.runs()) {
            std::cout << r.get_text() << std::endl;
        }
    }
    
    // Template replacement
    cdocx::Template tmpl(&doc);
    tmpl.set("name", "John Doe");
    tmpl.replace_all();
    
    doc.save("output.docx");
    return 0;
}
```

## Cross-Platform Build Guide

### Linux

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y cmake g++ git ninja-build
./scripts/build-linux.sh Release
```

**Fedora/RHEL:**
```bash
sudo dnf install cmake gcc-c++ git ninja-build
./scripts/build-linux.sh Release
```

**Arch:**
```bash
sudo pacman -S cmake gcc git ninja
./scripts/build-linux.sh Release
```

### Windows

**Visual Studio 2019/2022:**
```cmd
:: Open "x64 Native Tools Command Prompt for VS"
cd CDocx
scripts\build-windows.bat Release x64
```

**MinGW-w64:**
```cmd
cd CDocx
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
```

### macOS

```bash
brew install cmake ninja
./scripts/build-linux.sh Release
```

## Project Structure

```
cdocx/
├── include/
│   ├── cdocx.h              # Main public API header
│   ├── cdocx/               # Modular headers
│   │   ├── fwd.h            # Forward declarations
│   │   ├── constants.h      # Formatting flags
│   │   ├── iterator.h       # Iterator helpers
│   │   ├── base.h           # Run, Paragraph, Table classes
│   │   ├── document.h       # Document class
│   │   ├── template.h       # Template replacement
│   │   ├── inserter.h       # Document insertion
│   │   └── advanced.h       # Bookmark, DocumentBuilder, Search
│   └── detail/
│       └── impl.h           # Private implementation (PIMPL)
├── src/
│   ├── base_content.cpp     # Content classes implementation
│   ├── document.cpp         # Document class implementation
│   ├── template.cpp         # Template implementation
│   ├── inserter.cpp         # Document inserter implementation
│   ├── tree.cpp             # Tree structure implementation
│   ├── impl.cpp             # DocumentImpl implementation
│   └── advanced.cpp         # Advanced features implementation
├── examples/                # Example programs
├── test/                    # Test suite (Google Test)
├── docs/                    # Documentation
│   └── archive/             # Archived design documents
├── scripts/                 # Build scripts
└── thirdparty/              # Dependencies (pugixml, zip)
```

**Key Design:** Tree-based internal structure completely hidden from public API using PIMPL pattern. All DOCX components (XML parts, media files, relationships) are loaded into memory and preserved on save.

## API Overview

```cpp
// Document operations
cdocx::Document doc("file.docx");
doc.open();
if (doc.is_open()) {
    // Process document
    doc.save();
}

// Paragraph iteration
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    for (auto r = p.runs(); r.has_next(); r.next()) {
        std::string text = r.get_text();
    }
}

// Template processing
cdocx::Template tmpl(&doc);
tmpl.set("key", "value");
tmpl.replace_all();

// Document insertion
cdocx::DocumentInserter inserter(&target);
inserter.insert_document(&source);

// XML Parts access
pugi::xml_document* styles = doc.get_styles();
pugi::xml_document* settings = doc.get_settings();

// Media management
doc.add_media("image.jpg");
doc.export_media("image.jpg", "output/path.jpg");
```

## Documentation

- [AGENTS.md](AGENTS.md) - Complete API documentation, technical details and roadmap
- [docs/OPTIMIZATION_UPGRADE_PLAN.md](docs/OPTIMIZATION_UPGRADE_PLAN.md) - **Optimization and upgrade master plan**
- [docs/ASPOSE_COMPARISON_AND_ROADMAP.md](docs/ASPOSE_COMPARISON_AND_ROADMAP.md) - Feature comparison with Aspose.Words and development roadmap
- [docs/IMPLEMENTATION_PLAN.md](docs/IMPLEMENTATION_PLAN.md) - Detailed implementation plan for new features
- [docs/INSTALL.md](docs/INSTALL.md) - Installation instructions
- [docs/REFACTORING_SUMMARY.md](docs/REFACTORING_SUMMARY.md) - Code structure documentation
- [CONTRIBUTING.md](CONTRIBUTING.md) - Contribution guidelines
- [SECURITY.md](SECURITY.md) - Security policy

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_SHARED_LIBS` | OFF | Build shared library |
| `BUILD_EXAMPLES` | ON | Build example programs |
| `BUILD_TESTING` | ON | Build test suite |
| `BUILD_DOCS` | OFF | Build documentation |
| `ENABLE_COVERAGE` | OFF | Enable code coverage (GCC/Clang) |
| `ENABLE_WERROR` | OFF | Treat warnings as errors |
| `USE_SYSTEM_GTEST` | OFF | Use system Google Test |

## CMake Integration

```cmake
# Method 1: After installation
find_package(cdocx REQUIRED)
target_link_libraries(your_target PRIVATE cdocx::cdocx)

# Method 2: As subdirectory
add_subdirectory(path/to/cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)

# Method 3: FetchContent
include(FetchContent)
FetchContent_Declare(
    cdocx
    GIT_REPOSITORY https://github.com/lonlng/CDocx.git
    GIT_TAG v0.4.0
)
FetchContent_MakeAvailable(cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)
```

## Dependencies

- [pugixml](https://github.com/zeux/pugixml) - XML parsing
- [zip](https://github.com/kuba--/zip) - ZIP archive handling
- [Google Test](https://github.com/google/googletest) - Testing framework (fetched automatically)

## Supported Platforms

| Platform | Compiler | Status |
|----------|----------|--------|
| Linux | GCC 7+ | ✅ Fully Supported |
| Linux | Clang 5+ | ✅ Fully Supported |
| Windows | MSVC 2017+ | ✅ Fully Supported |
| Windows | MinGW-w64 | ✅ Supported |
| macOS | Xcode 10+ | ✅ Supported |

## License

MIT License - see [LICENSE](LICENSE) file.
