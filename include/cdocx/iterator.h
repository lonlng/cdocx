/**
 * @file iterator.h
 * @brief Iterator classes for CDocx document traversal
 * @details Provides template-based iterator classes for traversing document
 *          elements (paragraphs, runs, tables, etc.) using C++11 range-based
 *          for loops and traditional iterator patterns.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 * 
 * @par Usage Example:
 * @code
 * #include <cdocx/iterator.h>
 * #include <cdocx/base.h>
 * 
 * cdocx::Document doc("file.docx");
 * doc.open();
 * 
 * // Range-based for loop
 * for (const auto& para : doc.paragraphs()) {
 *     for (const auto& run : para.runs()) {
 *         std::cout << run.get_text() << std::endl;
 *     }
 * }
 * 
 * // Traditional iterator style
 * auto para = doc.paragraphs();
 * while (para.has_next()) {
 *     auto run = para.runs();
 *     while (run.has_next()) {
 *         std::cout << run.get_text() << std::endl;
 *         run.next();
 *     }
 *     para.next();
 * }
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>

namespace pugi {
class xml_node;
}

namespace cdocx {

/**
 * @class Iterator
 * @brief Template iterator for traversing CDocx document elements
 * @tparam T The element type (Run, Paragraph, Table, etc.)
 * @tparam P The parent node type (typically pugi::xml_node)
 * @tparam C The current node type (typically pugi::xml_node)
 * 
 * @details This iterator supports C++11 range-based for loops and provides
 *          a standard iterator interface. It wraps pugixml nodes and converts
 *          them to CDocx element types on demand.
 * 
 * @par Iterator Category:
 * - Forward Iterator
 * 
 * @par Requirements:
 * - Type T must provide set_parent() and set_current() methods
 * - Type T must have a default constructor
 * 
 * @since 0.1.0
 * @see IteratorHelper
 */
template <class T, class P, class C>
class Iterator {
private:
    using ParentType = P;   ///< Parent node type alias
    using CurrentType = C;  ///< Current node type alias
    
    ParentType parent_{0};    ///< Parent XML node
    CurrentType current_{0};  ///< Current XML node
    mutable T buffer_{};      ///< Buffer for element conversion

public:
    /**
     * @brief Default constructor
     * @details Creates an empty iterator (end iterator)
     */
    Iterator() = default;

    /**
     * @brief Construct iterator with parent and current nodes
     * @param[in] parent The parent XML node
     * @param[in] current The current XML node
     */
    Iterator(ParentType parent, CurrentType current)
        : parent_(parent), current_(current) {}

    /**
     * @brief Inequality comparison operator
     * @param[in] other The iterator to compare with
     * @return true if iterators point to different positions
     * @return false if iterators point to the same position
     */
    bool operator!=(const Iterator& other) const {
        return parent_ != other.parent_ || current_ != other.current_;
    }

    /**
     * @brief Equality comparison operator
     * @param[in] other The iterator to compare with
     * @return true if iterators point to the same position
     * @return false if iterators point to different positions
     */
    bool operator==(const Iterator& other) const {
        return !this->operator!=(other);
    }

    /**
     * @brief Pre-increment operator
     * @details Advances the iterator to the next sibling element
     * @return Reference to this iterator
     */
    Iterator& operator++() {
        this->current_ = this->current_.next_sibling();
        return *this;
    }

    /**
     * @brief Dereference operator
     * @details Returns a reference to the current element. The buffer is only
     *          updated when this method is called (lazy evaluation).
     * @return const reference to the current element
     */
    auto operator*() const -> T const& {
        // Only update the buffer when the user wants to access the data
        buffer_.set_parent(parent_);
        buffer_.set_current(current_);
        return buffer_;
    }

    /**
     * @brief Arrow operator
     * @return Pointer to the current element
     */
    auto operator->() const -> T const* { return &(this->operator*()); }
};

/**
 * @class IteratorHelper
 * @brief Helper class for creating begin/end iterators
 * @details Provides factory methods for creating begin and end iterators
 *          for CDocx container classes. This class is used internally by
 *          the begin() and end() free functions.
 * 
 * @par Usage Example:
 * @code
 * // Usually no need to use this class directly, use begin() and end() instead
 * for (auto& para : doc.paragraphs()) {
 *     // Iterate paragraphs
 * }
 * @endcode
 * 
 * @since 0.1.0
 * @see begin(), end()
 */
class IteratorHelper {
private:
    using XmlNode = pugi::xml_node;  ///< XML node type alias

    /**
     * @brief Create begin iterator for an object
     * @tparam T The element type
     * @param[in] obj The container object
     * @return Iterator pointing to the first element
     */
    template <class T>
    static auto make_begin(T const& obj) -> Iterator<T, XmlNode> {
        return Iterator<T, XmlNode>(obj.parent_, obj.current_);
    }

    /**
     * @brief Create end iterator for an object
     * @tparam T The element type
     * @param[in] obj The container object
     * @return Iterator pointing past the last element
     */
    template <class T>
    static auto make_end(T const& obj) -> Iterator<T, XmlNode> {
        return Iterator<T, XmlNode>(
            obj.parent_, static_cast<decltype(obj.current_)>(0));
    }

    // Grant friend access to begin() and end() functions
    template <class T>
    friend auto begin(T const&) -> Iterator<T, XmlNode>;
    template <class T>
    friend auto end(T const&) -> Iterator<T, XmlNode>;
};

// ============================================================================
// Range-based for loop support
// ============================================================================

/**
 * @brief Get begin iterator for range-based for loop
 * @tparam T The element type
 * @param[in] obj The container object
 * @return Iterator pointing to the first element
 * @relatesalso IteratorHelper
 * @since 0.1.0
 */
template <class T>
auto begin(T const& obj) -> Iterator<T, pugi::xml_node> {
    return IteratorHelper::make_begin(obj);
}

/**
 * @brief Get end iterator for range-based for loop
 * @tparam T The element type
 * @param[in] obj The container object
 * @return Iterator pointing past the last element
 * @relatesalso IteratorHelper
 * @since 0.1.0
 */
template <class T>
auto end(T const& obj) -> Iterator<T, pugi::xml_node> {
    return IteratorHelper::make_end(obj);
}

} // namespace cdocx
