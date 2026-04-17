/**
 * @file format_context.cpp
 * @brief Implementation of TextFormatContext class
 * @details Provides unified text formatting operations for XML run elements.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 */

#include <cdocx/format_context.h>

namespace cdocx {

// ============================================================================
// Private Helper Methods
// ============================================================================

pugi::xml_node TextFormatContext::get_or_create_rPr(pugi::xml_node run) {
    pugi::xml_node rPr = run.child("w:rPr");
    if (!rPr) {
        // Prepend to ensure rPr comes before w:t
        rPr = run.prepend_child("w:rPr");
    }
    return rPr;
}

// ============================================================================
// Public API Methods
// ============================================================================

bool TextFormatContext::apply_color(pugi::xml_node run, const std::string& color_hex) {
    if (!run) {
        return false;
    }

    // Get or create run properties
    pugi::xml_node rPr = get_or_create_rPr(run);

    // Get or create color element
    pugi::xml_node color = rPr.child("w:color");
    if (!color) {
        color = rPr.append_child("w:color");
    }

    // Set color value (hex without #)
    color.append_attribute("w:val").set_value(color_hex.c_str());
    return true;
}

bool TextFormatContext::apply_font_size(pugi::xml_node run, int size) {
    if (!run) {
        return false;
    }

    pugi::xml_node rPr = get_or_create_rPr(run);

    // Set sz (size) element
    pugi::xml_node sz = rPr.child("w:sz");
    if (!sz) {
        sz = rPr.append_child("w:sz");
    }
    sz.append_attribute("w:val").set_value(size);

    // Set szCs (complex script size) element
    pugi::xml_node szCs = rPr.child("w:szCs");
    if (!szCs) {
        szCs = rPr.append_child("w:szCs");
    }
    szCs.append_attribute("w:val").set_value(size);

    return true;
}

bool TextFormatContext::apply_font_name(pugi::xml_node run, const std::string& font_name) {
    if (!run) {
        return false;
    }

    pugi::xml_node rPr = get_or_create_rPr(run);

    // Get or create rFonts element
    pugi::xml_node rFonts = rPr.child("w:rFonts");
    if (!rFonts) {
        rFonts = rPr.append_child("w:rFonts");
    }

    // Set font attributes for different character sets
    rFonts.append_attribute("w:ascii").set_value(font_name.c_str());
    rFonts.append_attribute("w:hAnsi").set_value(font_name.c_str());
    rFonts.append_attribute("w:cs").set_value(font_name.c_str());

    return true;
}

bool TextFormatContext::apply_bold(pugi::xml_node run, bool bold) {
    if (!run) {
        return false;
    }

    pugi::xml_node rPr = get_or_create_rPr(run);

    if (bold) {
        // Add bold element if not present
        if (!rPr.child("w:b")) {
            rPr.append_child("w:b");
        }
    } else {
        // Remove bold element
        rPr.remove_child("w:b");
    }
    return true;
}

bool TextFormatContext::apply_italic(pugi::xml_node run, bool italic) {
    if (!run) {
        return false;
    }

    pugi::xml_node rPr = get_or_create_rPr(run);

    if (italic) {
        if (!rPr.child("w:i")) {
            rPr.append_child("w:i");
        }
    } else {
        rPr.remove_child("w:i");
    }
    return true;
}

bool TextFormatContext::apply_underline(pugi::xml_node run, bool underline) {
    if (!run) {
        return false;
    }

    pugi::xml_node rPr = get_or_create_rPr(run);

    if (underline) {
        pugi::xml_node u = rPr.child("w:u");
        if (!u) {
            u = rPr.append_child("w:u");
        }
        u.append_attribute("w:val").set_value("single");
    } else {
        rPr.remove_child("w:u");
    }
    return true;
}

}  // namespace cdocx
