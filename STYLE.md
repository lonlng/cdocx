# CDocx Coding Style

This project uses a **customized Google C++ Style**.

## Customizations from Google Style

| Aspect | Google Standard | Our Customization |
|--------|-----------------|-------------------|
| Indentation | 2 spaces | **4 spaces** |
| Column limit | 80 chars | **100 chars** |
| Header guards | `#ifndef` | **`#pragma once`** (allowed) |

## Naming Conventions (Google Style - Unchanged)

| Type | Convention | Example |
|------|------------|---------|
| Types | `CamelCase` | `Document`, `Paragraph`, `SectionProperties` |
| Functions | `CamelCase` | `Open()`, `GetText()`, `IsOpen()` |
| Variables | `snake_case` | `file_path`, `paragraph_count` |
| Members | `snake_case_` | `impl_`, `filepath_` |
| Constants | `kCamelCase` | `kMaxSize`, `kDefaultValue`, `kBold` |
| Macros | `UPPER_CASE` | `CDOCX_API`, `DISALLOW_COPY_AND_ASSIGN` |
| Files | `snake_case` | `document.h`, `base_content.cpp` |

## Formatting

- **Indentation**: 4 spaces (no tabs)
- **Line length**: 100 characters
- **Braces**: K&R style (opening brace on same line)
- **Header guards**: `#pragma once`

## Example

```cpp
#pragma once

#include <memory>
#include <string>

namespace cdocx {

// Constant: kCamelCase
constexpr int kMaxBufferSize = 1024;

// Type: CamelCase
class Document {
 public:
    // Public method: CamelCase
    void Open();
    bool IsOpen() const;
    std::string GetFilepath() const;

 private:
    // Private member: snake_case_ with trailing underscore
    std::unique_ptr<DocumentImpl> impl_;
    std::string filepath_;
    bool is_open_;
};

}  // namespace cdocx
```

## Tools

### Formatting

```bash
# Format all code
cmake --build build --target format

# Check formatting (for CI)
cmake --build build --target format-check
```

### Static Analysis

```bash
# Run clang-tidy
cmake --build build --target tidy

# Auto-fix issues
cmake --build build --target tidy-fix
```

## References

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [docs/CODE_QUALITY.md](./docs/CODE_QUALITY.md) - Detailed tool configuration
