/// @file system/collections/base_enumerator.h
#pragma once

#include "system/collections/ienumerator.h"

namespace System { namespace Collections { namespace Generic {

/// Enumerator definition to wrap STL-styled types for C#-styled usage.
/// Makes no assertions on container structure except for existance of sequental iterator.
/// Uses begin() and end() functions.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam Container STL-styled container type.
/// @tparam Element Element type.
template <typename Container, typename Element>
class ASPOSECPP_SHARED_CLASS BaseEnumerator : public IEnumerator<Element>
{
protected:
    /// Pointer to owner container object to make sure it is not deleted before enumerator is.
    Object::ptr m_owner;
    /// Container inner data structure reference.
    Container& m_data;
    /// Actual STL iterator.
    typename Container::iterator m_it;
    /// Whether MoveNext() was ever called.
    bool m_inited;

public:

    /// Initializes iterator.
    /// @param owner Pointer to owner container.
    /// @param cont Actual container implementation reference.
    BaseEnumerator(const Object::ptr& owner, Container& cont) : m_owner(owner), m_data(cont), m_inited(false) {}
    // There no need to define an empty virtual dtor, virtual dtor for inheritance already defined in the Object class

    /// Checks whether MoveNext() was called and end was not reached.
    /// @return false if MoveNext() was not called at all or container end is hit; true otherwise.
    bool IsValid() const
    {
        return m_inited && m_it != m_data.end();
    }
    /// Enumerator-style increment.
    /// @return true if enumerator points to valid element, false if container end is hit.
    bool MoveNext() override
    {
        if (!m_inited)
        {
            m_it = m_data.begin();
            m_inited = true;
        }
        else if (m_it != m_data.end())
        {
            ++m_it;
        }

        return m_it != m_data.end();
    }
    /// Resets enumerator to allow re-enumerating elements.
    void Reset() override { m_inited = false; }

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Implements loop reference lookup for enumerator object.
    virtual void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        Object::GetSharedMembers(result);
        result.Add("System::Collections::Generic::BaseEnumerator<Container,Element>::m_owner", m_owner);
    }
#endif

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to collection and its elements.
    /// @param visitor Visitor to apply.
    void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
    {
        System::Object::DBG_for_each_member(visitor);

        visitor.add_self(this);
        visitor.add_member(this, m_owner, "m_owner");
    }

    /// Gets class name.
    /// @return Current class name.
    const char* DBG_class_name() const override { return "BaseEnumerator<T>"; }
#endif
};

/// Iterator class for simple containers holding elements directly using rbegin() and rend() functions.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam Container Container type to iterate through.
/// @tparam Element Element type.
template <typename Container, typename Element = typename Container::value_type>
class SimpleEnumerator : public BaseEnumerator<Container, Element>
{
public:
    /// Creates simple iterator.
    /// @param owner Owner object to hold while iterator lives.
    /// @param cont Container reference.
    SimpleEnumerator(Object::ptr owner, Container& cont) : BaseEnumerator<Container, Element>(owner, cont) {}

    /// Gets 'current' element.
    /// @return Current element (if any) or default-constructed item otherwise.
    MakeConstRef_t<Element> get_Current() const override
    {
        return this->IsValid() ? *(this->m_it) : System::Default<Element>();
    }

    /// Clones current iterator.
    /// @return Copy of the current iterator.
    System::Details::VirtualizedIteratorBase<Element>* CloneIterator() const override
    {
        return new SimpleEnumerator(*this);
    }
};


/// Adapting iterator, wraps std::pair into KVPair expected from Dictionary
/// @tparam KVPair Required return type
/// @tparam Container wrapped container type
template <typename KVPair, typename Container>
class KVPairIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = KVPair;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type * ;
    using reference = value_type & ;

    KVPairIterator(typename Container::const_iterator current) : mCurrent(std::move(current)) {}

    friend bool operator==(const KVPairIterator& lhs, const KVPairIterator& rhs)
    {
        return lhs.mCurrent == rhs.mCurrent;
    }

    friend bool operator!=(const KVPairIterator& lhs, const KVPairIterator& rhs)
    {
        return lhs.mCurrent != rhs.mCurrent;
    }

    KVPair operator*() const
    {
        return KVPair(*mCurrent);
    }

    KVPairIterator& operator++()
    {
        ++mCurrent;
        return *this;
    }

    KVPairIterator operator++(int)
    {
        KVPairIterator tmp = KVPairIterator(mCurrent);
        ++mCurrent;
        return tmp;
    }

    KVPairIterator& operator--()
    {
        --mCurrent;
        return *this;
    }

    KVPairIterator operator--(int)
    {
        KVPairIterator tmp = KVPairIterator(mCurrent);
        --mCurrent;
        return tmp;
    }
private:
    typename Container::const_iterator mCurrent;
};


/// Enumerator that reverse-iterates through container.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam Container Container to iterate through.
/// @tparam Element Element type.
template <typename Container, typename Element = typename Container::value_type>
class ReverseEnumerator : public IEnumerator<Element>
{
protected:
    /// Pointer to owner container object to make sure it is not deleted before enumerator is.
    Object::ptr m_owner;
    /// Container inner data structure reference.
    Container& m_data;
    /// Actual STL iterator.
    typename Container::reverse_iterator m_it;
    /// Whether MoveNext() was ever called.
    bool m_inited;

public:

    /// Initializes iterator.
    /// @param owner Pointer to owner container.
    /// @param cont Actual container implementation reference.
    ReverseEnumerator(const Object::ptr& owner, Container& cont) : m_owner(owner), m_data(cont), m_inited(false) {}
    /// Destructor.
    virtual ~ReverseEnumerator() {}

    /// Checks whether MoveNext() was called and end was not reached.
    /// @return false if MoveNext() was not called at all or container end is hit; true otherwise.
    bool IsValid() const
    {
        return m_inited && m_it != m_data.rend();
    }
    /// Enumerator-style increment.
    /// @return true if enumerator points to valid element, false if container end is hit.
    bool MoveNext() override
    {
        if (!m_inited)
        {
            m_it = m_data.rbegin();
            m_inited = true;
        }
        else if (m_it != m_data.rend())
        {
            ++m_it;
        }

        return m_it != m_data.rend();
    }
    /// Gets 'current' element.
    /// @return Current element (if any) or default-constructed item otherwise.
    virtual MakeConstRef_t<Element> get_Current() const override
    {
        return this->IsValid() ? *(this->m_it) : System::Default<Element>();
    }
    /// Resets enumerator to allow re-enumerating elements.
    void Reset() override { m_inited = false; }

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Implements loop reference lookup for enumerator object.
    virtual void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        Object::GetSharedMembers(result);
        result.Add("System::Collections::Generic::ReverseEnumerator<Container,Element>::m_owner", m_owner);
    }
#endif

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to collection and its elements.
    /// @param visitor Visitor to apply.
    void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
    {
        System::Object::DBG_for_each_member(visitor);

        visitor.add_self(this);
        visitor.add_member(this, m_owner, "m_owner");
    }

    /// Gets class name.
    /// @return Current class name.
    const char* DBG_class_name() const override { return "ReverseEnumerator<T>"; }
#endif
};

}}} // namespace System::Collections::Generic
