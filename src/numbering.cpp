/**
 * @file numbering.cpp
 * @brief Numbering (List) system implementation
 */

#include <cdocx/document.h>
#include <cdocx/numbering.h>

#include <cstring>
#include <sstream>

namespace cdocx {

// ============================================================================
// LevelDefinition Implementation
// ============================================================================

LevelDefinition LevelDefinition::make_bullet_level(const std::string& bullet_char, int level) {
    LevelDefinition def;

    // Set up indentation
    ParagraphProperties::Indentation indent;
    indent.special.kind = ParagraphProperties::Indentation::Special::Kind::Hanging;
    indent.special.type = ParagraphProperties::Indentation::Type::Absolute;
    indent.special.value = 360;  // 0.25 inch
    indent.left.type = ParagraphProperties::Indentation::Type::Absolute;
    indent.left.value = 720 + (level * 360);  // 0.5 inch + level offset
    def.indent = indent;

    // Set bullet character
    def.number_style = NumberStyle::Bullet;
    def.number_format = bullet_char;
    def.level_text = bullet_char;

    // Set font for bullet
    def.level_font.ascii = "Symbol";
    def.level_font.h_ansi = "Symbol";

    return def;
}

LevelDefinition LevelDefinition::make_numbered_level(NumberStyle style, int level) {
    LevelDefinition def;

    // Set up indentation
    ParagraphProperties::Indentation indent;
    indent.special.kind = ParagraphProperties::Indentation::Special::Kind::Hanging;
    indent.special.type = ParagraphProperties::Indentation::Type::Absolute;
    indent.special.value = 360;
    indent.left.type = ParagraphProperties::Indentation::Type::Absolute;
    indent.left.value = 720 + (level * 360);
    def.indent = indent;

    // Set numbering style
    def.number_style = style;

    // Set format based on style
    // TODO: Implement distinct formats for Roman and Letter styles.
    def.number_format = "%1.";
    def.level_text = "%1.";

    return def;
}

// ============================================================================
// AbstractNumberingDefinition Implementation
// ============================================================================

AbstractNumberingDefinition AbstractNumberingDefinition::make_bulleted_list() {
    AbstractNumberingDefinition def;
    def.type = NumberingType::MultiLevel;

    // Level 1: Solid circle
    def.levels[0] = LevelDefinition::make_bullet_level(kBulletSolidCircle, 0);

    // Level 2: Hollow circle
    def.levels[1] = LevelDefinition::make_bullet_level(kBulletHollowCircle, 1);
    def.levels[1].level_font.ascii = "Courier New";
    def.levels[1].level_font.h_ansi = "Courier New";

    // Level 3: Solid square
    def.levels[2] = LevelDefinition::make_bullet_level(kBulletSolidSquare, 2);

    // Levels 4-9: Continue pattern
    def.levels[3] = LevelDefinition::make_bullet_level(kBulletSolidCircle, 3);
    def.levels[4] = LevelDefinition::make_bullet_level(kBulletHollowCircle, 4);
    def.levels[5] = LevelDefinition::make_bullet_level(kBulletSolidSquare, 5);
    def.levels[6] = LevelDefinition::make_bullet_level(kBulletSolidCircle, 6);
    def.levels[7] = LevelDefinition::make_bullet_level(kBulletHollowCircle, 7);
    def.levels[8] = LevelDefinition::make_bullet_level(kBulletSolidSquare, 8);

    return def;
}

AbstractNumberingDefinition AbstractNumberingDefinition::make_numbered_list(NumberStyle style) {
    AbstractNumberingDefinition def;
    def.type = NumberingType::MultiLevel;

    // Set up 9 levels with increasing indentation
    for (int i = 0; i < 9; ++i) {
        def.levels[i] = LevelDefinition::make_numbered_level(style, i);

        // Set different styles for different levels in multi-level lists
        if (i == 0) {
            def.levels[i].number_style = style;
        } else if (i == 1) {
            def.levels[i].number_style =
                (style == NumberStyle::Decimal) ? NumberStyle::LowerLetter : NumberStyle::Decimal;
        } else if (i == 2) {
            def.levels[i].number_style = NumberStyle::LowerRoman;
        } else {
            def.levels[i].number_style = NumberStyle::Decimal;
        }

        // Update format based on style
        def.levels[i] = LevelDefinition::make_numbered_level(def.levels[i].number_style, i);
    }

    return def;
}

AbstractNumberingDefinition AbstractNumberingDefinition::make_chinese_numbered_list() {
    AbstractNumberingDefinition def;
    def.type = NumberingType::MultiLevel;

    // Chinese numbering styles for different levels
    const NumberStyle chinese_styles[9] = {
        NumberStyle::ChineseCounting,  // 一、
        NumberStyle::Decimal,          // 1.
        NumberStyle::ChineseCounting,  // (一)
        NumberStyle::LowerRoman,       // a.
        NumberStyle::Decimal,          // 1)
        NumberStyle::ChineseCounting,  // (1)
        NumberStyle::LowerLetter,      // a)
        NumberStyle::Decimal,          // (a)
        NumberStyle::ChineseCounting   // ①
    };

    for (int i = 0; i < 9; ++i) {
        def.levels[i] = LevelDefinition::make_numbered_level(chinese_styles[i], i);
    }

    return def;
}

AbstractNumberingDefinition AbstractNumberingDefinition::make_outline_list() {
    AbstractNumberingDefinition def;
    def.type = NumberingType::HybridMultiLevel;

    // Standard outline format: 1., 1.1, 1.1.1, etc.
    for (int i = 0; i < 9; ++i) {
        def.levels[i] = LevelDefinition::make_numbered_level(NumberStyle::Decimal, i);

        // Build level text
        std::stringstream ss;
        for (int j = 0; j <= i; ++j) {
            if (j > 0) {
                ss << ".";
            }
            ss << "%" << (j + 1);
        }
        def.levels[i].level_text = ss.str();
        def.levels[i].number_format = def.levels[i].level_text;
    }

    return def;
}

// ============================================================================
// NumberingManager Implementation
// ============================================================================

AbstractNumberingId NumberingManager::add_abstract_definition(
    const AbstractNumberingDefinition& def) {
    const AbstractNumberingId id = next_abstract_id_++;
    AbstractNumberingDefinition mutable_def = def;
    mutable_def.id = id;
    abstract_definitions_[id] = mutable_def;
    modified_ = true;
    return id;
}

NumberingId NumberingManager::add_numbering_definition(const NumberingDefinition& def) {
    const NumberingId id = next_num_id_++;
    NumberingDefinition mutable_def = def;
    mutable_def.id = id;
    num_definitions_[id] = mutable_def;
    modified_ = true;
    return id;
}

NumberingId NumberingManager::add_bulleted_list_definition() {
    auto abstract_def = AbstractNumberingDefinition::make_bulleted_list();
    const AbstractNumberingId abstract_id = add_abstract_definition(abstract_def);

    const NumberingDefinition num_def(abstract_id);
    return add_numbering_definition(num_def);
}

NumberingId NumberingManager::add_numbered_list_definition(NumberStyle style) {
    auto abstract_def = AbstractNumberingDefinition::make_numbered_list(style);
    const AbstractNumberingId abstract_id = add_abstract_definition(abstract_def);

    const NumberingDefinition num_def(abstract_id);
    return add_numbering_definition(num_def);
}

NumberingId NumberingManager::add_chinese_numbered_list_definition() {
    auto abstract_def = AbstractNumberingDefinition::make_chinese_numbered_list();
    const AbstractNumberingId abstract_id = add_abstract_definition(abstract_def);

    const NumberingDefinition num_def(abstract_id);
    return add_numbering_definition(num_def);
}

NumberingId NumberingManager::add_outline_list_definition() {
    auto abstract_def = AbstractNumberingDefinition::make_outline_list();
    const AbstractNumberingId abstract_id = add_abstract_definition(abstract_def);

    const NumberingDefinition num_def(abstract_id);
    return add_numbering_definition(num_def);
}

const AbstractNumberingDefinition* NumberingManager::get_abstract_definition(
    AbstractNumberingId id) const {
    auto it = abstract_definitions_.find(id);
    if (it != abstract_definitions_.end()) {
        return &it->second;
    }
    return nullptr;
}

const NumberingDefinition* NumberingManager::get_numbering_definition(NumberingId id) const {
    auto it = num_definitions_.find(id);
    if (it != num_definitions_.end()) {
        return &it->second;
    }
    return nullptr;
}

bool NumberingManager::override_level(NumberingId num_id,
                                      NumberingLevel level,
                                      const LevelDefinition& level_def) {
    auto it = num_definitions_.find(num_id);
    if (it == num_definitions_.end()) {
        return false;
    }

    it->second.level_overrides[level] = level_def;
    modified_ = true;
    return true;
}

void NumberingManager::load_from_xml(pugi::xml_node numbering_root) {
    clear();

    // Parse abstract numbering definitions
    for (const auto& abstract_num : numbering_root.children("w:abstractNum")) {
        AbstractNumberingDefinition def;

        // Parse abstract_numId
        auto id_attr = abstract_num.attribute("w:abstractNumId");
        if (id_attr) {
            def.id = id_attr.as_uint();
            if (def.id >= next_abstract_id_) {
                next_abstract_id_ = def.id + 1;
            }
        }

        // Parse levels
        for (const auto& lvl : abstract_num.children("w:lvl")) {
            auto ilvl = lvl.attribute("w:ilvl");
            if (!ilvl) {
                continue;
            }

            const int level = ilvl.as_int();
            if (level < 0 || level >= 9) {
                continue;
            }

            LevelDefinition level_def;

            // Parse number format
            auto num_fmt = lvl.child("w:numFmt");
            if (num_fmt) {
                const char* val = num_fmt.attribute("w:val").value();
                level_def.number_style = string_to_number_style(val);
            }

            // Parse level text
            auto lvl_text = lvl.child("w:lvlText");
            if (lvl_text) {
                level_def.level_text = lvl_text.attribute("w:val").value();
            }

            // Parse start number
            auto start = lvl.child("w:start");
            if (start) {
                level_def.start_number = start.attribute("w:val").as_uint();
            }

            def.levels[level] = level_def;
        }

        abstract_definitions_[def.id] = def;
    }

    // Parse numbering instances
    for (const auto& num : numbering_root.children("w:num")) {
        NumberingDefinition def;

        auto id_attr = num.attribute("w:numId");
        if (id_attr) {
            def.id = id_attr.as_uint();
            if (def.id >= next_num_id_) {
                next_num_id_ = def.id + 1;
            }
        }

        auto abstract_id = num.child("w:abstractNumId");
        if (abstract_id) {
            def.abstract_id = abstract_id.attribute("w:val").as_uint();
        }

        num_definitions_[def.id] = def;
    }

    modified_ = false;
}

void NumberingManager::save_to_xml(pugi::xml_node numbering_root) {
    // Clear existing content
    for (const auto& child : numbering_root.children()) {
        numbering_root.remove_child(child);
    }

    // Add namespace
    numbering_root.append_attribute("xmlns:w").set_value(
        "http://schemas.openxmlformats.org/wordprocessingml/2006/main");

    // Save abstract numbering definitions
    for (const auto& [id, def] : abstract_definitions_) {
        auto abstract_num = numbering_root.append_child("w:abstractNum");
        abstract_num.append_attribute("w:abstractNumId").set_value(static_cast<unsigned int>(id));

        // Add multi-level type if applicable
        if (def.type == NumberingType::MultiLevel || def.type == NumberingType::HybridMultiLevel) {
            auto multi_level_type = abstract_num.append_child("w:multi_level_type");
            multi_level_type.append_attribute("w:val").set_value(
                def.type == NumberingType::HybridMultiLevel ? "hybridMultilevel" : "multilevel");
        }

        // Save levels
        for (int i = 0; i < 9; ++i) {
            const auto& level = def.levels[i];

            auto lvl = abstract_num.append_child("w:lvl");
            lvl.append_attribute("w:ilvl").set_value(i);

            // Start number
            auto start = lvl.append_child("w:start");
            start.append_attribute("w:val").set_value(static_cast<unsigned int>(level.start_number));

            // Number format
            auto num_fmt = lvl.append_child("w:numFmt");
            num_fmt.append_attribute("w:val").set_value(number_style_to_string(level.number_style));

            // Level text
            auto lvl_text = lvl.append_child("w:lvlText");
            lvl_text.append_attribute("w:val").set_value(level.level_text.c_str());

            // Level justification
            auto lvl_jc = lvl.append_child("w:lvlJc");
            switch (level.number_alignment) {
                case ParagraphProperties::Alignment::Left:
                    lvl_jc.append_attribute("w:val").set_value("left");
                    break;
                case ParagraphProperties::Alignment::Centered:
                    lvl_jc.append_attribute("w:val").set_value("center");
                    break;
                case ParagraphProperties::Alignment::Right:
                    lvl_jc.append_attribute("w:val").set_value("right");
                    break;
                default:
                    lvl_jc.append_attribute("w:val").set_value("left");
            }
        }
    }

    // Save numbering instances
    for (const auto& [id, def] : num_definitions_) {
        auto num = numbering_root.append_child("w:num");
        num.append_attribute("w:numId").set_value(static_cast<unsigned int>(id));

        auto abstract_num_id = num.append_child("w:abstractNumId");
        abstract_num_id.append_attribute("w:val").set_value(
            static_cast<unsigned int>(def.abstract_id));

        // Save level overrides
        for (const auto& [level, level_def] : def.level_overrides) {
            auto lvl_override = num.append_child("w:lvlOverride");
            lvl_override.append_attribute("w:ilvl").set_value(numbering_level_to_int(level));

            auto lvl = lvl_override.append_child("w:lvl");
            lvl.append_attribute("w:ilvl").set_value(numbering_level_to_int(level));

            // Override properties would be saved here
            (void)level_def;  // Avoid unused warning
        }
    }
}

void NumberingManager::clear() {
    abstract_definitions_.clear();
    num_definitions_.clear();
    next_abstract_id_ = 0;
    next_num_id_ = 1;
    modified_ = false;
}

pugi::xml_document* NumberingManager::get_numbering_xml() {
    if (document_) {
        return document_->get_numbering_xml();
    }
    return nullptr;
}

// ============================================================================
// Helper Functions
// ============================================================================

const char* number_style_to_string(NumberStyle style) {
    switch (style) {
        case NumberStyle::Bullet:
            return "bullet";
        case NumberStyle::Decimal:
            return "decimal";
        case NumberStyle::UpperRoman:
            return "upperRoman";
        case NumberStyle::LowerRoman:
            return "lowerRoman";
        case NumberStyle::UpperLetter:
            return "upperLetter";
        case NumberStyle::LowerLetter:
            return "lowerLetter";
        case NumberStyle::OrdinalText:
            return "ordinal";
        case NumberStyle::CardinalText:
            return "cardinalText";
        case NumberStyle::ChineseCounting:
            return "chineseCounting";
        case NumberStyle::IdeographEnchanted:
            return "ideographEnchanted";
        default:
            return "decimal";
    }
}

NumberStyle string_to_number_style(const char* val) {
    if (!val || !*val) {
        return NumberStyle::Decimal;
    }

    if (std::strcmp(val, "bullet") == 0) {
        return NumberStyle::Bullet;
    }
    if (std::strcmp(val, "decimal") == 0) {
        return NumberStyle::Decimal;
    }
    if (std::strcmp(val, "upperRoman") == 0) {
        return NumberStyle::UpperRoman;
    }
    if (std::strcmp(val, "lowerRoman") == 0) {
        return NumberStyle::LowerRoman;
    }
    if (std::strcmp(val, "upperLetter") == 0) {
        return NumberStyle::UpperLetter;
    }
    if (std::strcmp(val, "lowerLetter") == 0) {
        return NumberStyle::LowerLetter;
    }
    if (std::strcmp(val, "ordinal") == 0) {
        return NumberStyle::OrdinalText;
    }
    if (std::strcmp(val, "cardinalText") == 0) {
        return NumberStyle::CardinalText;
    }
    if (std::strcmp(val, "chineseCounting") == 0) {
        return NumberStyle::ChineseCounting;
    }
    if (std::strcmp(val, "ideographEnchanted") == 0) {
        return NumberStyle::IdeographEnchanted;
    }

    return NumberStyle::Decimal;
}

int numbering_level_to_int(NumberingLevel level) {
    return static_cast<int>(level);
}

}  // namespace cdocx
