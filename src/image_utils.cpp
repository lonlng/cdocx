/**
 * @file image_utils.cpp
 * @brief Image utilities for size detection and format validation
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.5.0
 */

#include <cdocx/advanced.h>
#include <fstream>
#include <cstring>
#include <algorithm>

namespace cdocx {

// ============================================================================
// PNG Detection
// ============================================================================

static bool detect_png_size(const uint8_t* data, size_t len, ImageFormatInfo& info) {
    // PNG signature: 89 50 4E 47 0D 0A 1A 0A
    if (len < 24 || 
        data[0] != 0x89 || data[1] != 0x50 || data[2] != 0x4E || data[3] != 0x47 ||
        data[4] != 0x0D || data[5] != 0x0A || data[6] != 0x1A || data[7] != 0x0A) {
        return false;
    }
    
    // IHDR chunk starts at offset 16
    // Width: bytes 16-19 (big-endian)
    // Height: bytes 20-23 (big-endian)
    info.width = (data[16] << 24) | (data[17] << 16) | (data[18] << 8) | data[19];
    info.height = (data[20] << 24) | (data[21] << 16) | (data[22] << 8) | data[23];
    info.format = "PNG";
    info.mime_type = "image/png";
    info.is_valid = true;
    
    // Try to extract pHYs chunk for DPI (optional)
    // pHYs chunk contains pixels per unit specifier
    if (len > 33) {
        size_t pos = 33; // After IHDR chunk (8 sig + 4 len + 4 type + 13 data + 4 crc)
        while (pos + 12 <= len) {
            uint32_t chunk_len = (data[pos] << 24) | (data[pos+1] << 16) | 
                                 (data[pos+2] << 8) | data[pos+3];
            const char* chunk_type = reinterpret_cast<const char*>(data + pos + 4);
            
            if (strncmp(chunk_type, "pHYs", 4) == 0 && pos + 21 <= len) {
                uint32_t ppx = (data[pos+8] << 24) | (data[pos+9] << 16) | 
                               (data[pos+10] << 8) | data[pos+11];
                uint32_t ppy = (data[pos+12] << 24) | (data[pos+13] << 16) | 
                               (data[pos+14] << 8) | data[pos+15];
                uint8_t unit = data[pos+16];
                
                if (unit == 1) { // meters
                    info.dpi_x = static_cast<int>(ppx * 0.0254);
                    info.dpi_y = static_cast<int>(ppy * 0.0254);
                }
                break;
            }
            
            if (strncmp(chunk_type, "IEND", 4) == 0) break;
            pos += 12 + chunk_len; // Move to next chunk
        }
    }
    
    return true;
}

// ============================================================================
// JPEG Detection
// ============================================================================

static bool detect_jpeg_size(const uint8_t* data, size_t len, ImageFormatInfo& info) {
    // JPEG starts with FF D8 FF
    if (len < 3 || data[0] != 0xFF || data[1] != 0xD8 || data[2] != 0xFF) {
        return false;
    }
    
    info.format = "JPEG";
    info.mime_type = "image/jpeg";
    
    // Scan for SOF markers
    size_t pos = 2;
    while (pos + 9 < len) {
        if (data[pos] != 0xFF) {
            pos++;
            continue;
        }
        
        uint8_t marker = data[pos + 1];
        
        // Skip padding
        if (marker == 0x00 || marker == 0x01 || 
            (marker >= 0xD0 && marker <= 0xD9) ||
            (marker >= 0xE0 && marker <= 0xEF)) {
            pos += 2;
            continue;
        }
        
        // SOF0, SOF1, SOF2 (baseline, extended, progressive)
        if (marker >= 0xC0 && marker <= 0xCF && marker != 0xC4 && marker != 0xC8 && marker != 0xCC) {
            if (pos + 9 >= len) return false;
            
            // Skip length (2 bytes), precision (1 byte)
            info.height = (data[pos + 5] << 8) | data[pos + 6];
            info.width = (data[pos + 7] << 8) | data[pos + 8];
            info.is_valid = true;
            return true;
        }
        
        // Skip this segment
        if (pos + 3 >= len) break;
        uint16_t segment_len = (data[pos + 2] << 8) | data[pos + 3];
        pos += 2 + segment_len;
    }
    
    return false;
}

// ============================================================================
// BMP Detection
// ============================================================================

static bool detect_bmp_size(const uint8_t* data, size_t len, ImageFormatInfo& info) {
    // BMP starts with "BM"
    if (len < 26 || data[0] != 'B' || data[1] != 'M') {
        return false;
    }
    
    info.format = "BMP";
    info.mime_type = "image/bmp";
    
    // DIB header size at offset 14
    uint32_t dib_size = (data[14] << 0) | (data[15] << 8) | 
                        (data[16] << 16) | (data[17] << 24);
    
    if (dib_size == 12) {
        // BITMAPCOREHEADER (OS/2 BMP)
        if (len < 22) return false;
        info.width = (data[18] << 0) | (data[19] << 8);
        info.height = (data[20] << 0) | (data[21] << 8);
    } else {
        // BITMAPINFOHEADER and later
        if (len < 26) return false;
        info.width = (data[18] << 0) | (data[19] << 8) | 
                     (data[20] << 16) | (data[21] << 24);
        info.height = (data[22] << 0) | (data[23] << 8) | 
                      (data[24] << 16) | (data[25] << 24);
        
        // Pixels per meter to DPI (offset 38 and 42)
        if (len >= 46) {
            int32_t ppm_x = (data[38] << 0) | (data[39] << 8) | 
                            (data[40] << 16) | (data[41] << 24);
            int32_t ppm_y = (data[42] << 0) | (data[43] << 8) | 
                            (data[44] << 16) | (data[45] << 24);
            
            if (ppm_x > 0) info.dpi_x = static_cast<int>(ppm_x * 0.0254);
            if (ppm_y > 0) info.dpi_y = static_cast<int>(ppm_y * 0.0254);
        }
    }
    
    // Handle negative height (top-down BMP)
    if (info.height < 0) info.height = -info.height;
    
    info.is_valid = true;
    return true;
}

// ============================================================================
// GIF Detection
// ============================================================================

static bool detect_gif_size(const uint8_t* data, size_t len, ImageFormatInfo& info) {
    // GIF signature: "GIF87a" or "GIF89a"
    if (len < 10 || data[0] != 'G' || data[1] != 'I' || data[2] != 'F' || 
        data[3] != '8' || (data[4] != '7' && data[4] != '9') || data[5] != 'a') {
        return false;
    }
    
    // Logical Screen Descriptor
    info.width = data[6] | (data[7] << 8);   // Little-endian
    info.height = data[8] | (data[9] << 8);  // Little-endian
    info.format = "GIF";
    info.mime_type = "image/gif";
    info.is_valid = true;
    
    return true;
}

// ============================================================================
// Public API Implementation
// ============================================================================

bool detect_image_size_from_memory(const std::vector<uint8_t>& data, ImageSize& size) {
    if (data.empty()) return false;
    
    ImageFormatInfo info = validate_image_format_from_memory(data);
    if (!info.is_valid || info.width <= 0 || info.height <= 0) {
        return false;
    }
    
    // Convert pixels to points (1 inch = 72 points, 1 inch = DPI pixels)
    size.width_pt = (info.width * 72.0) / info.dpi_x;
    size.height_pt = (info.height * 72.0) / info.dpi_y;
    
    return true;
}

bool detect_image_size(const std::string& image_path, ImageSize& size) {
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        return false;
    }
    
    // Read file header (first 256 bytes should be enough for all formats)
    std::vector<uint8_t> buffer(256);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    size_t bytes_read = static_cast<size_t>(file.gcount());
    buffer.resize(bytes_read);
    
    return detect_image_size_from_memory(buffer, size);
}

ImageFormatInfo validate_image_format_from_memory(const std::vector<uint8_t>& data) {
    ImageFormatInfo info;
    
    if (data.empty()) {
        info.error_message = "Empty data";
        return info;
    }
    
    // Check file size limits
    const size_t MAX_FILE_SIZE = 50 * 1024 * 1024; // 50MB
    if (data.size() > MAX_FILE_SIZE) {
        info.error_message = "File too large (max 50MB)";
        return info;
    }
    
    // Try each format detector
    if (detect_png_size(data.data(), data.size(), info)) {
        return info;
    }
    
    if (detect_jpeg_size(data.data(), data.size(), info)) {
        return info;
    }
    
    if (detect_bmp_size(data.data(), data.size(), info)) {
        return info;
    }
    
    if (detect_gif_size(data.data(), data.size(), info)) {
        return info;
    }
    
    // Unknown format
    info.format = "UNKNOWN";
    info.error_message = "Unknown or unsupported image format";
    return info;
}

ImageFormatInfo validate_image_format_detailed(const std::string& image_path) {
    ImageFormatInfo info;
    
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        info.error_message = "Cannot open file: " + image_path;
        return info;
    }
    
    // Check file size
    file.seekg(0, std::ios::end);
    size_t file_size = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);
    
    const size_t MAX_FILE_SIZE = 50 * 1024 * 1024; // 50MB
    if (file_size > MAX_FILE_SIZE) {
        info.error_message = "File too large (max 50MB): " + std::to_string(file_size) + " bytes";
        return info;
    }
    
    // Read file data
    std::vector<uint8_t> buffer(file_size);
    file.read(reinterpret_cast<char*>(buffer.data()), file_size);
    
    return validate_image_format_from_memory(buffer);
}

} // namespace cdocx
