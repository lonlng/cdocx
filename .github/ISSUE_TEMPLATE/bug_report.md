---
name: 🐛 Bug report
about: Create a report to help us improve CDocx
title: '[BUG] '
labels: bug
assignees: ''

---

## 🐛 Bug Description

A clear and concise description of what the bug is.

## 📝 Steps to Reproduce

Steps to reproduce the behavior:
1. Open file '...'
2. Call function '...'
3. Pass parameters '...'
4. See error

## 💻 Minimal Code Example

```cpp
// Provide a minimal, complete, verifiable example
#include <cdocx.h>

int main() {
    cdocx::Document doc("test.docx");
    doc.open();
    // ... your code that triggers the bug
    return 0;
}
```

## ✅ Expected Behavior

A clear and concise description of what you expected to happen.

## ❌ Actual Behavior

A clear and concise description of what actually happened.

Include any error messages:
```
Error message here
```

## 🖥️ Environment

Please complete the following information:

- **OS**: [e.g. Windows 11, Ubuntu 22.04, macOS 14]
- **Compiler**: [e.g. MSVC 2022, GCC 12, Clang 15]
- **CMake Version**: [e.g. 3.25]
- **CDocx Version**: [e.g. 0.2.0, or commit hash]
- **Build Type**: [e.g. Debug, Release]

## 📄 Test File

If applicable, attach the DOCX file that causes the issue (or a minimal version of it).

## 📋 Additional Context

Add any other context about the problem here, such as:
- Does it work with other DOCX files?
- Is this a regression (did it work in previous versions)?
- Any workarounds you've found?
