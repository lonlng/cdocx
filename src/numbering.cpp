/**
 * @file numbering.cpp
 * @brief Numbering (List) system implementation
 */

#include <cdocx/numbering.h>
#include <cdocx/document.h>
#include <sstream>

namespace cdocx {

// ============================================================================
// LevelDefinition Implementation
// ============================================================================

LevelDefinition LevelDefinition::make_bullet_level(const std::string& bulletChar, int level) {
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
    def.numberStyle = NumberStyle::Bullet;
    def.numberFormat = bulletChar;
    def.levelText = bulletChar;
    
    // Set font for bullet
    def.levelFont.ascii = "Symbol";
    def.levelFont.hAnsi = "Symbol";
    
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
    def.numberStyle = style;
    
    // Set format based on style
    switch (style) {
        case NumberStyle::Decimal:
            def.numberFormat = "%1.";
            def.levelText = "%1.";
            break;
        case NumberStyle::UpperRoman:
        case NumberStyle::LowerRoman:
            def.numberFormat = "%1.";
            def.levelText = "%1.";
            break;
        case NumberStyle::UpperLetter:
        case NumberStyle::LowerLetter:
            def.numberFormat = "%1.";
            def.levelText = "%1.";
            break;
        default:
            def.numberFormat = "%1.";
            def.levelText = "%1.";
    }
    
    return def;
}

// ============================================================================
// AbstractNumberingDefinition Implementation
// ============================================================================

AbstractNumberingDefinition AbstractNumberingDefinition::make_bulleted_list() {
    AbstractNumberingDefinition def;
    def.type = NumberingType::MultiLevel;
    
    // Level 1: Solid circle
    def.levels[0] = LevelDefinition::make_bullet_level(BULLET_SOLID_CIRCLE, 0);
    
    // Level 2: Hollow circle
    def.levels[1] = LevelDefinition::make_bullet_level(BULLET_HOLLOW_CIRCLE, 1);
    def.levels[1].levelFont.ascii = "Courier New";
    def.levels[1].levelFont.hAnsi = "Courier New";
    
    // Level 3: Solid square
    def.levels[2] = LevelDefinition::make_bullet_level(BULLET_SOLID_SQUARE, 2);
    
    // Levels 4-9: Continue pattern
    def.levels[3] = LevelDefinition::make_bullet_level(BULLET_SOLID_CIRCLE, 3);
    def.levels[4] = LevelDefinition::make_bullet_level(BULLET_HOLLOW_CIRCLE, 4);
    def.levels[5] = LevelDefinition::make_bullet_level(BULLET_SOLID_SQUARE, 5);
    def.levels[6] = LevelDefinition::make_bullet_level(BULLET_SOLID_CIRCLE, 6);
    def.levels[7] = LevelDefinition::make_bullet_level(BULLET_HOLLOW_CIRCLE, 7);
    def.levels[8] = LevelDefinition::make_bullet_level(BULLET_SOLID_SQUARE, 8);
    
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
            def.levels[i].numberStyle = style;
        } else if (i == 1) {
            def.levels[i].numberStyle = (style == NumberStyle::Decimal) 
                ? NumberStyle::LowerLetter : NumberStyle::Decimal;
        } else if (i == 2) {
            def.levels[i].numberStyle = NumberStyle::LowerRoman;
        } else {
            def.levels[i].numberStyle = NumberStyle::Decimal;
        }
        
        // Update format based on style
        def.levels[i] = LevelDefinition::make_numbered_level(def.levels[i].numberStyle, i);
    }
    
    return def;
}

AbstractNumberingDefinition AbstractNumberingDefinition::make_chinese_numbered_list() {
    AbstractNumberingDefinition def;
    def.type = NumberingType::MultiLevel;
    
    // Chinese numbering styles for different levels
    NumberStyle chineseStyles[9] = {
        NumberStyle::ChineseCounting,   // 一、
        NumberStyle::Decimal,            // 1.
        NumberStyle::ChineseCounting,    // (一)
        NumberStyle::LowerRoman,         // a.
        NumberStyle::Decimal,            // 1)
        NumberStyle::ChineseCounting,    // (1)
        NumberStyle::LowerLetter,        // a)
        NumberStyle::Decimal,            // (a)
        NumberStyle::ChineseCounting     // ①
    };
    
    for (int i = 0; i < 9; ++i) {
        def.levels[i] = LevelDefinition::make_numbered_level(chineseStyles[i], i);
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
            if (j > 0) ss << ".";
            ss << "%" << (j + 1);
        }
        def.levels[i].levelText = ss.str();
        def.levels[i].numberFormat = def.levels[i].levelText;
    }
    
    return def;
}

// ============================================================================
// NumberingManager Implementation
// ============================================================================

AbstractNumberingId NumberingManager::add_abstract_definition(const AbstractNumberingDefinition& def) {
    AbstractNumberingId id = nextAbstractId_++;
    AbstractNumberingDefinition mutableDef = def;
    mutableDef.id = id;
    abstractDefinitions_[id] = mutableDef;
    return id;
}

NumberingId NumberingManager::add_numbering_definition(const NumberingDefinition& def) {
    NumberingId id = nextNumId_++;
    NumberingDefinition mutableDef = def;
    mutableDef.id = id;
    numDefinitions_[id] = mutableDef;
    return id;
}

NumberingId NumberingManager::add_bulleted_list_definition() {
    auto abstractDef = AbstractNumberingDefinition::make_bulleted_list();
    AbstractNumberingId abstractId = add_abstract_definition(abstractDef);
    
    NumberingDefinition numDef(abstractId);
    return add_numbering_definition(numDef);
}

NumberingId NumberingManager::add_numbered_list_definition(NumberStyle style) {
    auto abstractDef = AbstractNumberingDefinition::make_numbered_list(style);
    AbstractNumberingId abstractId = add_abstract_definition(abstractDef);
    
    NumberingDefinition numDef(abstractId);
    return add_numbering_definition(numDef);
}

NumberingId NumberingManager::add_chinese_numbered_list_definition() {
    auto abstractDef = AbstractNumberingDefinition::make_chinese_numbered_list();
    AbstractNumberingId abstractId = add_abstract_definition(abstractDef);
    
    NumberingDefinition numDef(abstractId);
    return add_numbering_definition(numDef);
}

NumberingId NumberingManager::add_outline_list_definition() {
    auto abstractDef = AbstractNumberingDefinition::make_outline_list();
    AbstractNumberingId abstractId = add_abstract_definition(abstractDef);
    
    NumberingDefinition numDef(abstractId);
    return add_numbering_definition(numDef);
}

const AbstractNumberingDefinition* NumberingManager::get_abstract_definition(AbstractNumberingId id) const {
    auto it = abstractDefinitions_.find(id);
    if (it != abstractDefinitions_.end()) {
        return &it->second;
    }
    return nullptr;
}

const NumberingDefinition* NumberingManager::get_numbering_definition(NumberingId id) const {
    auto it = numDefinitions_.find(id);
    if (it != numDefinitions_.end()) {
        return &it->second;
    }
    return nullptr;
}

bool NumberingManager::override_level(NumberingId numId, NumberingLevel level, 
                                      const LevelDefinition& levelDef) {
    auto it = numDefinitions_.find(numId);
    if (it == numDefinitions_.end()) {
        return false;
    }
    
    it->second.levelOverrides[level] = levelDef;
    return true;
}

void NumberingManager::load_from_xml(pugi::xml_node numbering_root) {
    clear();
    
    // Parse abstract numbering definitions
    for (auto abstractNum : numbering_root.children("w:abstractNum")) {
        AbstractNumberingDefinition def;
        
        // Parse abstractNumId
        auto id_attr = abstractNum.attribute("w:abstractNumId");
        if (id_attr) {
            def.id = id_attr.as_uint();
            if (def.id >= nextAbstractId_) {
                nextAbstractId_ = def.id + 1;
            }
        }
        
        // Parse levels
        for (auto lvl : abstractNum.children("w:lvl")) {
            auto ilvl = lvl.attribute("w:ilvl");
            if (!ilvl) continue;
            
            int level = ilvl.as_int();
            if (level < 0 || level >= 9) continue;
            
            LevelDefinition levelDef;
            
            // Parse number format
            auto numFmt = lvl.child("w:numFmt");
            if (numFmt) {
                const char* val = numFmt.attribute("w:val").value();
                // Convert string to NumberStyle
                // (simplified - would need full mapping)
            }
            
            // Parse level text
            auto lvlText = lvl.child("w:lvlText");
            if (lvlText) {
                levelDef.levelText = lvlText.attribute("w:val").value();
            }
            
            // Parse start number
            auto start = lvl.child("w:start");
            if (start) {
                levelDef.startNumber = start.attribute("w:val").as_uint();
            }
            
            def.levels[level] = levelDef;
        }
        
        abstractDefinitions_[def.id] = def;
    }
    
    // Parse numbering instances
    for (auto num : numbering_root.children("w:num")) {
        NumberingDefinition def;
        
        auto id_attr = num.attribute("w:numId");
        if (id_attr) {
            def.id = id_attr.as_uint();
            if (def.id >= nextNumId_) {
                nextNumId_ = def.id + 1;
            }
        }
        
        auto abstractId = num.child("w:abstractNumId");
        if (abstractId) {
            def.abstractId = abstractId.attribute("w:val").as_uint();
        }
        
        numDefinitions_[def.id] = def;
    }
}

void NumberingManager::save_to_xml(pugi::xml_node numbering_root) {
    // Clear existing content
    for (auto child : numbering_root.children()) {
        numbering_root.remove_child(child);
    }
    
    // Add namespace
    numbering_root.append_attribute("xmlns:w").set_value(
        "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    
    // Save abstract numbering definitions
    for (const auto& [id, def] : abstractDefinitions_) {
        auto abstractNum = numbering_root.append_child("w:abstractNum");
        abstractNum.append_attribute("w:abstractNumId").set_value(
            static_cast<unsigned int>(id));
        
        // Add multi-level type if applicable
        if (def.type == NumberingType::MultiLevel || 
            def.type == NumberingType::HybridMultiLevel) {
            auto multiLevelType = abstractNum.append_child("w:multiLevelType");
            multiLevelType.append_attribute("w:val").set_value(
                def.type == NumberingType::HybridMultiLevel ? "hybridMultilevel" : "multilevel");
        }
        
        // Save levels
        for (int i = 0; i < 9; ++i) {
            const auto& level = def.levels[i];
            
            auto lvl = abstractNum.append_child("w:lvl");
            lvl.append_attribute("w:ilvl").set_value(i);
            
            // Start number
            auto start = lvl.append_child("w:start");
            start.append_attribute("w:val").set_value(
                static_cast<unsigned int>(level.startNumber));
            
            // Number format
            auto numFmt = lvl.append_child("w:numFmt");
            numFmt.append_attribute("w:val").set_value(number_style_to_string(level.numberStyle));
            
            // Level text
            auto lvlText = lvl.append_child("w:lvlText");
            lvlText.append_attribute("w:val").set_value(level.levelText.c_str());
            
            // Level justification
            auto lvlJc = lvl.append_child("w:lvlJc");
            switch (level.numberAlignment) {
                case ParagraphProperties::Alignment::Left:
                    lvlJc.append_attribute("w:val").set_value("left");
                    break;
                case ParagraphProperties::Alignment::Centered:
                    lvlJc.append_attribute("w:val").set_value("center");
                    break;
                case ParagraphProperties::Alignment::Right:
                    lvlJc.append_attribute("w:val").set_value("right");
                    break;
                default:
                    lvlJc.append_attribute("w:val").set_value("left");
            }
        }
    }
    
    // Save numbering instances
    for (const auto& [id, def] : numDefinitions_) {
        auto num = numbering_root.append_child("w:num");
        num.append_attribute("w:numId").set_value(static_cast<unsigned int>(id));
        
        auto abstractNumId = num.append_child("w:abstractNumId");
        abstractNumId.append_attribute("w:val").set_value(
            static_cast<unsigned int>(def.abstractId));
        
        // Save level overrides
        for (const auto& [level, levelDef] : def.levelOverrides) {
            auto lvlOverride = num.append_child("w:lvlOverride");
            lvlOverride.append_attribute("w:ilvl").set_value(numbering_level_to_int(level));
            
            auto lvl = lvlOverride.append_child("w:lvl");
            lvl.append_attribute("w:ilvl").set_value(numbering_level_to_int(level));
            
            // Override properties would be saved here
            (void)levelDef;  // Avoid unused warning
        }
    }
}

void NumberingManager::clear() {
    abstractDefinitions_.clear();
    numDefinitions_.clear();
    nextAbstractId_ = 0;
    nextNumId_ = 1;
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
        case NumberStyle::Bullet: return "bullet";
        case NumberStyle::Decimal: return "decimal";
        case NumberStyle::UpperRoman: return "upperRoman";
        case NumberStyle::LowerRoman: return "lowerRoman";
        case NumberStyle::UpperLetter: return "upperLetter";
        case NumberStyle::LowerLetter: return "lowerLetter";
        case NumberStyle::OrdinalText: return "ordinal";
        case NumberStyle::CardinalText: return "cardinalText";
        case NumberStyle::ChineseCounting: return "chineseCounting";
        case NumberStyle::IdeographEnchanted: return "ideographEnchanted";
        default: return "decimal";
    }
}

int numbering_level_to_int(NumberingLevel level) {
    return static_cast<int>(level);
}

} // namespace cdocx
