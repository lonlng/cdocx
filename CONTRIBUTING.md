# Contributing to CDocx

Thank you for your interest in contributing to CDocx! This document provides guidelines and instructions for contributing.

## 🚀 Getting Started

1. Fork the repository on GitHub
2. Clone your fork locally
3. Create a new branch for your feature or bug fix
4. Make your changes
5. Submit a pull request

## 📋 Development Setup

### Prerequisites

- CMake 3.10+
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git

### Building the Project

```bash
# Clone with submodules
git clone --recursive https://github.com/your-username/CDocx.git
cd CDocx

# Create build directory
mkdir build && cd build

# Configure and build
cmake .. -DBUILD_TESTING=ON -DBUILD_EXAMPLES=ON
cmake --build .

# Run tests
ctest --output-on-failure
```

## 📝 Coding Standards

### Code Style

We use `clang-format` to maintain consistent code style. Please format your code before submitting:

```bash
# Format all source files
clang-format -i include/**/*.h src/**/*.cpp
```

The project includes a `.clang-format` file with our style configuration.

### Naming Conventions

- **Classes**: `CamelCase` (`Document`, `Paragraph`)
- **Methods**: `CamelCase` (`GetText()`, `SetBold()`, `IsOpen()`)
- **Member variables**: `snake_case_` (`parent_`, `current_`)
- **Constants**: `kCamelCase` (`kMaxSize`, `kDefaultValue`)
- **Namespaces**: `snake_case` (`cdocx`)

### Documentation

All public APIs must include Doxygen documentation:

```cpp
/**
 * @brief Brief description
 * @details Detailed description
 * @param[in] param Input parameter
 * @return Return value description
 * @since 0.2.0
 */
```

## 🧪 Testing

### Writing Tests

We use Google Test for unit testing. Tests are located in the `test/` directory.

```cpp
#include <gtest/gtest.h>
#include <cdocx.h>

TEST(DocumentTest, DocumentOpening) {
    cdocx::Document doc("test.docx");
    doc.open();
    EXPECT_TRUE(doc.is_open());
}
```

### Running Tests

```bash
cd build
ctest --output-on-failure
```

### Common Assertions

| Assertion | Description |
|-----------|-------------|
| `EXPECT_TRUE(expr)` | Expect expression to be true |
| `EXPECT_FALSE(expr)` | Expect expression to be false |
| `EXPECT_EQ(a, b)` | Expect a equals b |
| `EXPECT_NE(a, b)` | Expect a not equals b |
| `ASSERT_TRUE(expr)` | Assert expression is true (fails test immediately) |
| `ASSERT_EQ(a, b)` | Assert a equals b (fails test immediately) |
| `GTEST_SKIP()` | Skip the current test |

## 🐛 Reporting Bugs

When reporting bugs, please use our [Bug Report Template](.github/ISSUE_TEMPLATE/bug_report.md) and include:

- Clear description of the bug
- Steps to reproduce
- Expected vs actual behavior
- Environment details (OS, compiler, CDocx version)
- Minimal code example

## 💡 Suggesting Features

For feature requests, use our [Feature Request Template](.github/ISSUE_TEMPLATE/feature_request.md) and include:

- Clear description of the feature
- Use case and motivation
- Proposed API design (if applicable)
- Willingness to implement

## 🔀 Pull Request Process

1. **Create a branch**: `git checkout -b feature/my-feature` or `git checkout -b fix/my-bugfix`
2. **Make changes**: Follow coding standards and add tests
3. **Commit**: Write clear, descriptive commit messages
4. **Push**: `git push origin my-branch`
5. **Submit PR**: Use our [Pull Request Template](.github/PULL_REQUEST_TEMPLATE.md)

### PR Checklist

- [ ] Code follows project style guidelines
- [ ] Self-review completed
- [ ] Code is commented where necessary
- [ ] Documentation updated
- [ ] Tests added and passing
- [ ] No new warnings generated
- [ ] PR description is complete

## 📚 Areas for Contribution

### High Priority

- Bug fixes
- Performance improvements
- Test coverage
- Documentation improvements

### Feature Ideas

- [ ] Additional formatting options
- [ ] Better table manipulation
- [ ] Header/footer editing
- [ ] Style management
- [ ] Better image handling

### Documentation

- [ ] API documentation
- [ ] Usage examples
- [ ] Tutorials
- [ ] Translation

## 🤝 Code of Conduct

### Our Standards

- Be respectful and inclusive
- Welcome newcomers
- Accept constructive criticism
- Focus on what's best for the community

### Unacceptable Behavior

- Harassment or discrimination
- Trolling or insulting comments
- Personal or political attacks
- Publishing others' private information

## 📞 Getting Help

- **GitHub Issues**: For bug reports and feature requests
- **GitHub Discussions**: For questions and general discussion
- **Documentation**: See [AGENTS.md](AGENTS.md) for detailed API docs

## 🙏 Recognition

Contributors will be recognized in our README.md file and release notes.

## 📄 License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

Thank you for contributing to CDocx! 🎉
