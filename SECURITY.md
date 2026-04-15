# Security Policy

## Supported Versions

| Version | Supported |
|---------|-----------|
| 0.7.x   | ✅         |
| < 0.7.0 | ❌         |

## Reporting a Vulnerability

Please do not report security vulnerabilities through public GitHub issues.

Instead, please report them via:
- [GitHub Security Advisories](https://github.com/lonlng/CDocx/security/advisories), or
- Open a private security issue with the "security" label

## Security Best Practices

### Input Validation

- Validate all file paths before opening documents
- Check file sizes to prevent memory exhaustion
- Verify file formats before processing

```cpp
// Good practice
if (!std::filesystem::exists(filepath)) {
    // Handle error
    return;
}
cdocx::Document doc(filepath);
```

### Memory Management

- Be cautious with very large DOCX files
- Check available memory before processing large batches

### XML Security

CDocx uses pugixml for XML parsing:

- XXE attacks are mitigated by pugixml defaults
- Billion Laughs attacks are prevented by pugixml's default limits

## Known Limitations

- No built-in file size limits (implement your own checks)
- No encryption/decryption support yet
- No digital signature verification

## Dependencies

- **pugixml**: Follows [pugixml security practices](https://pugixml.org/docs/manual.html#xml_security)
- **zip library**: Uses standard ZIP parsing

Keep these dependencies updated to their latest versions.
