/**
 * @file format.cpp
 * @brief Format attribute implementations
 */

#include <cdocx/format.h>

#include <cstdio>
#include <cstdlib>

namespace cdocx {

Color Color::from_hex(const std::string& hex) {
    std::string h = hex;
    if (!h.empty() && h[0] == '#') {
        h = h.substr(1);
    }
    if (h.length() == 3) {
        std::string expanded;
        for (const char c : h) {
            expanded += c;
            expanded += c;
        }
        h = expanded;
    }
    if (h.length() != 6 && h.length() != 8) {
        return Color::black();
    }

    const auto rgba = static_cast<unsigned int>(std::strtoul(h.c_str(), nullptr, 16));
    if (h.length() == 6) {
        return {static_cast<uint8_t>((rgba >> 16) & 0xFF),
                static_cast<uint8_t>((rgba >> 8) & 0xFF),
                static_cast<uint8_t>(rgba & 0xFF),
                255};
    }
    return {static_cast<uint8_t>((rgba >> 24) & 0xFF),
            static_cast<uint8_t>((rgba >> 16) & 0xFF),
            static_cast<uint8_t>((rgba >> 8) & 0xFF),
            static_cast<uint8_t>(rgba & 0xFF)};
}

Color::Color(const std::string& hex) {
    *this = from_hex(hex);
}

std::string Color::to_hex() const {
    char buf[9];
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, cert-err33-c)
    std::snprintf(buf, sizeof(buf), "%02X%02X%02X%02X", r, g, b, a);
    return {buf};
}

std::string Color::to_hex_rgb() const {
    char buf[7];
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, cert-err33-c)
    std::snprintf(buf, sizeof(buf), "%02X%02X%02X", r, g, b);
    return {buf};
}

}  // namespace cdocx
