# GitHub Configuration

This directory contains GitHub-specific configuration files for the CDocx project.

## 📁 Directory Structure

```
.github/
├── ISSUE_TEMPLATE/          # Issue templates
│   ├── bug_report.md        # Bug report template
│   ├── feature_request.md   # Feature request template
│   └── question.md          # Question/help template
├── workflows/               # GitHub Actions workflows
│   ├── cmake.yml            # CMake build and test workflow
│   ├── code-quality.yml     # Code quality checks (clang-format, cppcheck)
│   └── docs.yml             # Documentation generation and deployment
├── FUNDING.yml              # Sponsorship/funding configuration
├── PULL_REQUEST_TEMPLATE.md # PR template
└── dependabot.yml           # Dependabot configuration
```

## 🐛 Issue Templates

We provide three issue templates:

1. **Bug Report** - For reporting bugs and issues
2. **Feature Request** - For suggesting new features
3. **Question** - For asking questions about usage

When creating a new issue, you'll be prompted to choose the appropriate template.

## 🔀 Pull Request Template

The PR template includes:
- Description of changes
- Type of change (bug fix, feature, etc.)
- Testing information
- Checklist for contributors

## 🔄 Workflows

### cmake.yml
- Builds the project on Linux (GCC/Clang), Windows (MSVC), and macOS
- Runs in both Debug and Release modes
- Executes all tests via CTest
- Triggers on push to main/master/develop and pull requests

### code-quality.yml
- Runs `clang-format` to check code formatting
- Runs `cppcheck` for static analysis
- Helps maintain code quality and consistency

### docs.yml
- Generates documentation using Doxygen
- Deploys to GitHub Pages (on main/master branch)
- Updates automatically when source code changes

## 🤖 Dependabot

Configured to automatically:
- Update Git submodules weekly
- Update GitHub Actions weekly
- Create pull requests for updates

## 💰 Funding

The `FUNDING.yml` file configures sponsorship options. Currently supports:
- Custom donation URLs

## 📝 Contributing

See [CONTRIBUTING.md](../CONTRIBUTING.md) for detailed contribution guidelines.

## 🔒 Security

See [SECURITY.md](../SECURITY.md) for security policy and vulnerability reporting.
