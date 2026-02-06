/**
 * @file cdocxIterator.h
 * @brief Iterator support for C++11 range-based for loops
 * 
 * This header provides iterator functionality that enables C++11
 * range-based for loops to work with CDocx content classes.
 * 
 * @code
 * // Iterate over paragraphs using range-based for
 * for (const auto& para : doc.paragraphs()) {
 *     for (const auto& run : para.runs()) {
 *         std::cout << run.get_text() << std::endl;
 *     }
 * }
 * @endcode
 * 
 * @author Cihan SARI (@CihanSari)
 * @license MIT
 */

#pragma once

namespace pugi {
class xml_node;
}

namespace cdocx {

/**
 * @class Iterator
 * @brief Generic iterator template for CDocx content classes
 * 
 * This template class enables C++11 range-based for loops by
 * implementing the standard iterator interface (operator*, operator++, 
 * operator!=, operator==).
 * 
 * @tparam T The content type (Run, Paragraph, TableCell, TableRow, Table)
 * @tparam P The parent XML node type
 * @tparam C The current XML node type (defaults to P)
 */
template <class T, class P, class C = P>
class Iterator {
  private:
    using ParentType = P;  /**< Type alias for parent node */
    using CurrentType = C; /**< Type alias for current node */
    ParentType parent{0};  /**< Parent XML node */
    CurrentType current{0}; /**< Current XML node */
    mutable T buffer{};    /**< Buffer for the current element */

  public:
    /** @brief Default constructor */
    Iterator() = default;

    /**
     * @brief Construct iterator with parent and current nodes
     * @param parent The parent XML node
     * @param current The current XML node
     */
    Iterator(ParentType parent, CurrentType current)
        : parent(parent), current(current) {}

    /**
     * @brief Inequality comparison
     * @param other The iterator to compare with
     * @return true if iterators point to different positions
     */
    bool operator!=(const Iterator &other) const {
        return parent != other.parent || current != other.current;
    }

    /**
     * @brief Equality comparison
     * @param other The iterator to compare with
     * @return true if iterators point to the same position
     */
    bool operator==(const Iterator &other) const {
        return !this->operator!=(other);
    }

    /**
     * @brief Pre-increment operator
     * @return Reference to this iterator (advanced to next position)
     */
    Iterator &operator++() {
        this->current = this->current.next_sibling();
        return *this;
    }

    /**
     * @brief Dereference operator
     * @return Const reference to the current element
     * 
     * The buffer is updated lazily when dereferenced.
     */
    auto operator*() const -> T const & {
        // Only update the buffer when the user wants to access the data
        buffer.set_parent(parent);
        buffer.set_current(current);
        return buffer;
    }

    /**
     * @brief Arrow operator
     * @return Pointer to the current element
     */
    auto operator-> () const -> T const * { return &(this->operator*()); }
};

/**
 * @class IteratorHelper
 * @brief Helper class for creating begin/end iterators
 * 
 * This class provides static methods to create begin and end iterators
 * for CDocx content classes.
 */
class IteratorHelper {
  private:
    using P = pugi::xml_node; /**< XML node type */
    
    /**
     * @brief Create begin iterator for an object
     * @tparam T The content type
     * @param obj The object to iterate
     * @return Iterator pointing to the first element
     */
    template <class T>
    static auto make_begin(T const &obj) -> Iterator<T, P> {
        return Iterator<T, P>(obj.parent, obj.current);
    }

    /**
     * @brief Create end iterator for an object
     * @tparam T The content type
     * @param obj The object to iterate
     * @return Iterator pointing past the last element
     */
    template <class T>
    static auto make_end(T const &obj) -> Iterator<T, P> {
        return Iterator<T, P>(
            obj.parent, static_cast<decltype(obj.current)>(0));
    }

    template <class T>
    friend auto begin(T const &) -> Iterator<T, P>;
    template <class T>
    friend auto end(T const &) -> Iterator<T, P>;
};

/**
 * @brief Get begin iterator for CDocx content
 * @tparam T The content type
 * @param obj The object to iterate
 * @return Iterator pointing to the first element
 * 
 * This function enables C++11 range-based for loops.
 */
template <class T>
auto begin(T const &obj) -> Iterator<T, pugi::xml_node> {
    return IteratorHelper::make_begin(obj);
}

/**
 * @brief Get end iterator for CDocx content
 * @tparam T The content type
 * @param obj The object to iterate
 * @return Iterator pointing past the last element
 * 
 * This function enables C++11 range-based for loops.
 */
template <class T>
auto end(T const &obj) -> Iterator<T, pugi::xml_node> {
    return IteratorHelper::make_end(obj);
}

} // namespace cdocx
