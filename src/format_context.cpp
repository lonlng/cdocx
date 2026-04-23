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

pugi::xml_node TextFormatContext::get_or_create_r_pr(pugi::xml_node run) {
    pugi::xml_node r_pr = run.child("w:rPr");
    if (!r_pr) {
        // Prepend to ensure r_pr comes before w:t
        r_pr = run.prepend_child("w:rPr");
    }
    return r_pr;
}

// ============================================================================
// Public API Methods
// ============================================================================

bool TextFormatContext::apply_color(pugi::xml_node run, const std::string& color_hex) {
    if (!run) {
        return false;
    }

    // Get or create run properties
    pugi::xml_node r_pr = get_or_create_r_pr(run);

    // Get or create color element
    pugi::xml_node color = r_pr.child("w:color");
    if (!color) {
        color = r_pr.append_child("w:color");
    }

    // Set color value (hex without #)
    color.append_attribute("w:val").set_value(color_hex.c_str());
    return true;
}

bool TextFormatContext::apply_font_size(pugi::xml_node run, int size) {
    if (!run) {
        return false;
    }

    pugi::xml_node r_pr = get_or_create_r_pr(run);

    // Set sz (size) element
    pugi::xml_node sz = r_pr.child("w:sz");
    if (!sz) {
        sz = r_pr.append_child("w:sz");
    }
    sz.append_attribute("w:val").set_value(size);

    // Set sz_cs (complex script size) element
    pugi::xml_node sz_cs = r_pr.child("w:szCs");
    if (!sz_cs) {
        sz_cs = r_pr.append_child("w:szCs");
    }
    sz_cs.append_attribute("w:val").set_value(size);

    return true;
}

bool TextFormatContext::apply_font_name(pugi::xml_node run, const std::string& font_name) {
    if (!run) {
        return false;
    }

    pugi::xml_node r_pr = get_or_create_r_pr(run);

    // Get or create r_fonts element
    pugi::xml_node r_fonts = r_pr.child("w:rFonts");
    if (!r_fonts) {
        r_fonts = r_pr.append_child("w:rFonts");
    }

    // Set font attributes for different character sets
    r_fonts.append_attribute("w:ascii").set_value(font_name.c_str());
    r_fonts.append_attribute("w:hAnsi").set_value(font_name.c_str());
    r_fonts.append_attribute("w:cs").set_value(font_name.c_str());

    return true;
}

bool TextFormatContext::apply_bold(pugi::xml_node run, bool bold) {
    if (!run) {
        return false;
    }

    pugi::xml_node r_pr = get_or_create_r_pr(run);

    if (bold) {
        // Add bold element if not present
        if (!r_pr.child("w:b")) {
            r_pr.append_child("w:b");
        }
    } else {
        // Remove bold element
        r_pr.remove_child("w:b");
    }
    return true;
}

bool TextFormatContext::apply_italic(pugi::xml_node run, bool italic) {
    if (!run) {
        return false;
    }

    pugi::xml_node r_pr = get_or_create_r_pr(run);

    if (italic) {
        if (!r_pr.child("w:i")) {
            r_pr.append_child("w:i");
        }
    } else {
        r_pr.remove_child("w:i");
    }
    return true;
}

bool TextFormatContext::apply_underline(pugi::xml_node run, bool underline) {
    if (!run) {
        return false;
    }

    pugi::xml_node r_pr = get_or_create_r_pr(run);

    if (underline) {
        pugi::xml_node u = r_pr.child("w:u");
        if (!u) {
            u = r_pr.append_child("w:u");
        }
        u.append_attribute("w:val").set_value("single");
    } else {
        r_pr.remove_child("w:u");
    }
    return true;
}

}  // namespace cdocx
