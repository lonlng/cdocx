//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontInfoCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Fonts
{

class FontInfo;
}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;

}
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Represents a collection of fonts used in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
/// 
/// Items are <see cref="Aspose::Words::Fonts::FontInfo">FontInfo</see> objects.
/// 
/// You do not create instances of this class directly.
/// Use the <see cref="Aspose::Words::DocumentBase::get_FontInfos">FontInfos</see> property to access the collection of fonts
/// defined in the document.
/// 
/// @sa Aspose::Words::Fonts::FontInfo
/// @sa Aspose::Words::DocumentBase::get_FontInfos
class ASPOSE_WORDS_SHARED_CLASS FontInfoCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Fonts::FontInfo>>
{
    typedef FontInfoCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Fonts::FontInfo>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Fonts::FontInfo>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();
    /// Specifies whether or not to embed TrueType fonts in a document when it is saved.
    /// Default value for this property is <c>%false</c>.
    /// 
    /// Embedding TrueType fonts allows others to view the document with the same fonts that were used to create it,
    /// but may substantially increase the document size.
    /// 
    /// This option works for DOC, DOCX and RTF formats only.
    ASPOSE_WORDS_SHARED_API bool get_EmbedTrueTypeFonts() const;
    /// Setter for Aspose::Words::Fonts::FontInfoCollection::get_EmbedTrueTypeFonts
    ASPOSE_WORDS_SHARED_API void set_EmbedTrueTypeFonts(bool value);
    /// Specifies whether or not to embed System fonts into the document.
    /// Default value for this property is <c>%false</c>.
    /// This option works only when <see cref="Aspose::Words::Fonts::FontInfoCollection::get_EmbedTrueTypeFonts">EmbedTrueTypeFonts</see> option is set to <c>%true</c>.
    /// 
    /// Setting this property to <c>%true</c> is useful if the user is on an East Asian system
    /// and wants to create a document that is readable by others who do not have fonts for that
    /// language on their system. For example, a user on a Japanese system could choose to embed the
    /// fonts in a document so that the Japanese document would be readable on all systems.
    /// 
    /// This option works for DOC, DOCX and RTF formats only.
    ASPOSE_WORDS_SHARED_API bool get_EmbedSystemFonts() const;
    /// Setter for Aspose::Words::Fonts::FontInfoCollection::get_EmbedSystemFonts
    ASPOSE_WORDS_SHARED_API void set_EmbedSystemFonts(bool value);
    /// Specifies whether or not to save a subset of the embedded TrueType fonts with the document.
    /// Default value for this property is <c>%false</c>.
    /// This option works only when <see cref="Aspose::Words::Fonts::FontInfoCollection::get_EmbedTrueTypeFonts">EmbedTrueTypeFonts</see> property is set to <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_SaveSubsetFonts() const;
    /// Specifies whether or not to save a subset of the embedded TrueType fonts with the document.
    /// Default value for this property is <c>%false</c>.
    /// This option works only when <see cref="Aspose::Words::Fonts::FontInfoCollection::get_EmbedTrueTypeFonts">EmbedTrueTypeFonts</see> property is set to <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_SaveSubsetFonts(bool value);

    /// Gets a font with the specified name.
    /// 
    /// @param name Case-insensitive name of the font to locate.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontInfo> idx_get(const System::String& name);
    /// Gets a font at the specified index.
    /// 
    /// @param index Zero-based index of the font.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontInfo> idx_get(int32_t index);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Fonts::FontInfo>>> GetEnumerator() override;
    /// Determines whether the collection contains a font with the given name.
    /// 
    /// @param name Case-insensitive name of the font to locate.
    /// 
    /// @return <c>%true</c> if the item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::String& name);

    ASPOSE_WORDS_SHARED_API iterator begin() noexcept;

    ASPOSE_WORDS_SHARED_API iterator end() noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator begin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator end() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cbegin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cend() const noexcept;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginConstIterator() const override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndConstIterator() const override;

protected:

    FontInfoCollection();

    virtual ASPOSE_WORDS_SHARED_API ~FontInfoCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;

};

}
}
}
