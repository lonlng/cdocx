/**
 * @file numbering.h
 * @brief List (Numbering) support for CDocx
 * @details Provides comprehensive list creation and management including
 *          bulleted lists, numbered lists, and multi-level lists.
 * 
 * @author CDocx Team
 * @copyright MIT License
 * @date 2026
 * @version 0.5.0
 * 
 * @par Usage Example:
 * @code
 * cdocx::Document doc("output.docx");
 * doc.open();
 * 
 * // Create a bulleted list
 * auto bullet_list = doc.add_bulleted_list_definition();
 * 
 * // Create a numbered list
 * auto num_list = doc.add_numbered_list_definition();
 * 
 * // Add list items
 * auto para1 = doc.paragraphs().add_paragraph_after("First item");
 * para1.set_numbering(bullet_list, NumberingLevel::Level1);
 * 
 * auto para2 = doc.paragraphs().add_paragraph_after("Second item");
 * para2.set_numbering(bullet_list, NumberingLevel::Level1);
 * 
 * // Add nested item
 * auto para3 = doc.paragraphs().add_paragraph_after("Nested item");
 * para3.set_numbering(bullet_list, NumberingLevel::Level2);
 * 
 * doc.save();
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/properties.h>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <optional>

namespace cdocx {

// ============================================================================
// Type Definitions
// ============================================================================

using NumberingId = size_t;
using AbstractNumberingId = size_t;

/**
 * @brief Numbering level enumeration
 */
enum class NumberingLevel {
    Level1 = 0, Level2, Level3, Level4, Level5,
    Level6, Level7, Level8, Level9
};

// ============================================================================
// List Format (for paragraph-level list formatting)
// ============================================================================

/**
 * @struct ListFormat
 * @brief List formatting for paragraphs
 * @details Links a paragraph to a specific list definition and level
 */
struct ListFormat {
    NumberingId list_id = 0;  ///< 0 = no list
    NumberingLevel level = NumberingLevel::Level1;
    
    bool is_list_item() const { return list_id != 0; }
    void remove_list_format() { list_id = 0; }
};

/**
 * @brief Numbering style enumeration
 */
enum class NumberStyle {
    Bullet,         ///< Project symbols (项目符号)
    Decimal,        ///< 1, 2, 3, etc.
    UpperRoman,     ///< I, II, III, IV, etc.
    LowerRoman,     ///< i, ii, iii, iv, etc.
    UpperLetter,    ///< A, B, C, etc.
    LowerLetter,    ///< a, b, c, etc.
    OrdinalText,    ///< First, Second, Third, etc.
    CardinalText,   ///< One, Two, Three, etc.
    ChineseCounting,///< 一, 二, 三, etc. (中文数字)
    IdeographEnchanted ///< 中文大写数字
};

/**
 * @brief Numbering type enumeration
 */
enum class NumberingType {
    SingleLevel,      ///< Single level list
    MultiLevel,       ///< Multi-level list
    HybridMultiLevel  ///< Hybrid multi-level list
};

// ============================================================================
// Constants
// ============================================================================

// Common bullet characters
constexpr const char* BULLET_SOLID_CIRCLE = "\u2022";    ///< •
constexpr const char* BULLET_HOLLOW_CIRCLE = "\u25CB";   ///< ○
constexpr const char* BULLET_SOLID_SQUARE = "\u25A0";    ///< ■
constexpr const char* BULLET_ARROW = "\u2192";           ///< →
constexpr const char* BULLET_DASH = "\u2013";            ///< –

// ============================================================================
// Level Definition
// ============================================================================

/**
 * @struct LevelDefinition
 * @brief Defines formatting for a specific numbering level
 * @details Combines paragraph and text properties with numbering-specific
 *          settings like start number, format, and alignment.
 */
struct LevelDefinition : public ParagraphProperties, public TextProperties {
    size_t startNumber = 1;          ///< Starting number for this level
    NumberStyle numberStyle = NumberStyle::Decimal;  ///< Numbering style
    std::string numberFormat = "%1."; ///< Format string (%1 = number)
    ParagraphProperties::Alignment numberAlignment = ParagraphProperties::Alignment::Left;
    
    // Level text template (e.g., "%1.", "%1.%2", etc.)
    std::string levelText;
    
    // Font for the numbering symbol
    struct LevelFont {
        std::string ascii = "Arial";
        std::string eastAsia = "SimSun";
        std::string hAnsi = "Arial";
        std::string cs = "Arial";
    } levelFont;
    
    /**
     * @brief Create a default bullet level
     * @param bulletChar Character to use as bullet
     * @param level Level number (0-8)
     * @return Configured LevelDefinition
     */
    static LevelDefinition make_bullet_level(const std::string& bulletChar, int level = 0);
    
    /**
     * @brief Create a default numbered level
     * @param style Numbering style
     * @param level Level number (0-8)
     * @return Configured LevelDefinition
     */
    static LevelDefinition make_numbered_level(NumberStyle style, int level = 0);
};

// ============================================================================
// Abstract Numbering Definition
// ============================================================================

/**
 * @struct AbstractNumberingDefinition
 * @brief Defines the abstract structure of a list
 * @details Contains the definition for all 9 possible levels of a list.
 *          This is the "template" for list formatting.
 */
struct AbstractNumberingDefinition {
    AbstractNumberingId id = 0;      ///< Unique ID
    NumberingType type = NumberingType::HybridMultiLevel;
    std::array<LevelDefinition, 9> levels;
    
    /**
     * @brief Create a default bulleted list definition
     * @return Configured AbstractNumberingDefinition
     */
    static AbstractNumberingDefinition make_bulleted_list();
    
    /**
     * @brief Create a default numbered list definition
     * @param style Numbering style (default: Decimal)
     * @return Configured AbstractNumberingDefinition
     */
    static AbstractNumberingDefinition make_numbered_list(NumberStyle style = NumberStyle::Decimal);
    
    /**
     * @brief Create a Chinese-style numbered list
     * @return Configured AbstractNumberingDefinition
     */
    static AbstractNumberingDefinition make_chinese_numbered_list();
    
    /**
     * @brief Create a multi-level outline list
     * @return Configured AbstractNumberingDefinition
     */
    static AbstractNumberingDefinition make_outline_list();
};

// ============================================================================
// Numbering Definition
// ============================================================================

/**
 * @struct NumberingDefinition
 * @brief Concrete instance of a list definition
 * @details References an abstract definition and can override
 *          specific level properties.
 */
struct NumberingDefinition {
    NumberingId id = 0;              ///< Unique instance ID
    AbstractNumberingId abstractId = 0; ///< Reference to abstract definition
    
    // Level overrides
    std::map<NumberingLevel, LevelDefinition> levelOverrides;
    
    NumberingDefinition() = default;
    explicit NumberingDefinition(AbstractNumberingId abstract_id) 
        : abstractId(abstract_id) {}
};

// ============================================================================
// Numbering Manager
// ============================================================================

/**
 * @class NumberingManager
 * @brief Manages all list definitions in a document
 * @details Handles creation, storage, and serialization of numbering
 *          definitions to the word/numbering.xml part.
 * 
 * @since 0.5.0
 */
class NumberingManager {
private:
    Document* document_ = nullptr;
    
    // Storage
    std::map<AbstractNumberingId, AbstractNumberingDefinition> abstractDefinitions_;
    std::map<NumberingId, NumberingDefinition> numDefinitions_;
    
    // ID counters
    AbstractNumberingId nextAbstractId_ = 0;
    NumberingId nextNumId_ = 1;  // Start from 1 (0 means no numbering)
    
public:
    /**
     * @brief Default constructor
     */
    NumberingManager() = default;
    
    /**
     * @brief Construct with document
     * @param doc Parent document
     */
    explicit NumberingManager(Document* doc) : document_(doc) {}
    
    /**
     * @brief Destructor
     */
    ~NumberingManager() = default;

    // =======================================================================
    // Definition Creation
    // =======================================================================
    
    /**
     * @brief Add abstract numbering definition
     * @param def The abstract definition
     * @return ID of the created definition
     */
    AbstractNumberingId add_abstract_definition(const AbstractNumberingDefinition& def);
    
    /**
     * @brief Add numbering definition instance
     * @param def The numbering definition
     * @return ID of the created definition
     */
    NumberingId add_numbering_definition(const NumberingDefinition& def);
    
    /**
     * @brief Create a bulleted list definition
     * @return NumberingId for the new list
     */
    NumberingId add_bulleted_list_definition();
    
    /**
     * @brief Create a numbered list definition
     * @param style Numbering style
     * @return NumberingId for the new list
     */
    NumberingId add_numbered_list_definition(NumberStyle style = NumberStyle::Decimal);
    
    /**
     * @brief Create a Chinese-style numbered list
     * @return NumberingId for the new list
     */
    NumberingId add_chinese_numbered_list_definition();
    
    /**
     * @brief Create an outline list definition
     * @return NumberingId for the new list
     */
    NumberingId add_outline_list_definition();

    // =======================================================================
    // Definition Retrieval
    // =======================================================================
    
    /**
     * @brief Get abstract definition by ID
     * @param id Abstract numbering ID
     * @return Pointer to definition, nullptr if not found
     */
    const AbstractNumberingDefinition* get_abstract_definition(AbstractNumberingId id) const;
    
    /**
     * @brief Get numbering definition by ID
     * @param id Numbering ID
     * @return Pointer to definition, nullptr if not found
     */
    const NumberingDefinition* get_numbering_definition(NumberingId id) const;

    // =======================================================================
    // Level Override
    // =======================================================================
    
    /**
     * @brief Override level properties for a specific numbering instance
     * @param numId Numbering instance ID
     * @param level Level to override
     * @param levelDef New level definition
     * @return true if successful
     */
    bool override_level(NumberingId numId, NumberingLevel level, 
                        const LevelDefinition& levelDef);

    // =======================================================================
    // Serialization
    // =======================================================================
    
    /**
     * @brief Load definitions from XML
     * @param numbering_root Root node of word/numbering.xml
     */
    void load_from_xml(pugi::xml_node numbering_root);
    
    /**
     * @brief Save definitions to XML
     * @param numbering_root Root node of word/numbering.xml
     */
    void save_to_xml(pugi::xml_node numbering_root);
    
    /**
     * @brief Check if any definitions exist
     * @return true if has definitions
     */
    bool has_definitions() const {
        return !abstractDefinitions_.empty();
    }
    
    /**
     * @brief Clear all definitions
     */
    void clear();

private:
    /**
     * @brief Get or create numbering.xml
     */
    pugi::xml_document* get_numbering_xml();
};

// ============================================================================
// Helper Functions
// ============================================================================

/**
 * @brief Convert NumberStyle to string representation
 * @param style Numbering style
 * @return String representation for XML
 */
const char* number_style_to_string(NumberStyle style);

/**
 * @brief Convert NumberingLevel to integer (0-8)
 * @param level Numbering level
 * @return Integer level value
 */
int numbering_level_to_int(NumberingLevel level);

} // namespace cdocx
