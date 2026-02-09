# Security Policy

## Supported Versions

We release security updates for the following versions:

| Version | Supported          |
| ------- | ------------------ |
| 0.2.x   | :white_check_mark: |
| < 0.2.0 | :x:                |

## Reporting a Vulnerability

We take security seriously. If you discover a security vulnerability, please report it to us responsibly.

### How to Report

**Please do not report security vulnerabilities through public GitHub issues.**

Instead, please report them via email to:

📧 **amir.mohamadi@example.com** (replace with actual contact)

Please include the following information:

- Description of the vulnerability
- Steps to reproduce (if applicable)
- Potential impact
- Suggested fix (if any)

### Response Process

1. **Acknowledgment**: We will acknowledge receipt of your report within 48 hours
2. **Assessment**: We will assess the vulnerability and determine its impact
3. **Fix Development**: We will work on a fix for confirmed vulnerabilities
4. **Disclosure**: We will coordinate with you on the disclosure timeline

### Disclosure Policy

- We follow responsible disclosure practices
- We aim to fix vulnerabilities within 90 days of report
- We will credit you in the security advisory (unless you prefer to remain anonymous)

## Security Best Practices

When using CDocx in your applications:

### Input Validation

- Validate all file paths before opening documents
- Check file sizes to prevent memory exhaustion
- Verify file formats before processing

```cpp
// Good practice
cdocx::Document doc;
if (!std::filesystem::exists(filepath)) {
    // Handle error
    return;
}
```

### Memory Management

- Be cautious with large DOCX files
- Check available memory before processing
- Use streaming for large files when possible

### XML Security

CDocx uses pugixml for XML parsing. Be aware that:

- XML External Entity (XXE) attacks are mitigated by pugixml defaults
- Billion Laughs attacks are prevented by pugixml's default limits
- Always use the latest version of pugixml

## Known Security Considerations

### Current Limitations

- No built-in file size limits (implement your own checks)
- No encryption/decryption support yet
- No digital signature verification

### Dependencies

CDocx depends on:
- **pugixml**: Follows [pugixml security practices](https://pugixml.org/docs/manual.html#xml_security)
- **zip library**: Uses standard ZIP parsing

Keep these dependencies updated to their latest versions.

## Security Updates

Security updates will be announced through:

- GitHub Security Advisories
- Release notes
- Project README

---

Thank you for helping keep CDocx and its users secure!
