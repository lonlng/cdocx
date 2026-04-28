//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/List.h
#pragma once

#include <system/shared_ptr.h>
#include <system/icomparable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class DocumentBase;

namespace Lists
{

class ListLevelCollection;

}

class Style;

}
}

namespace Aspose {

namespace Words {

namespace Lists {

/// Represents formatting of a list.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-lists/">Working with Lists</a> documentation article.
/// 
/// A list in a %Microsoft Word document is a set of list formatting properties.
/// Each list can have up to 9 levels and formatting properties, such as number style, start value,
/// indent, tab position etc are defined separately for each level.
/// 
/// A <see cref="Aspose::Words::Lists::List">List</see> object always belongs to the <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see> collection.
/// 
/// To create a new list, use the Add methods of the <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see> collection.
/// 
/// To modify formatting of a list, use <see cref="Aspose::Words::Lists::ListLevel">ListLevel</see> objects found in
/// the <see cref="Aspose::Words::Lists::List::get_ListLevels">ListLevels</see> collection.
/// 
/// To apply or remove list formatting from a paragraph, use <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see>.
/// 
/// @sa Aspose::Words::Lists::ListCollection
/// @sa Aspose::Words::Lists::ListLevel
/// @sa Aspose::Words::Lists::ListFormat
class ASPOSE_WORDS_SHARED_CLASS List : public System::IComparable<System::SharedPtr<Aspose::Words::Lists::List>>
{
    typedef List ThisType;
    typedef System::IComparable<System::SharedPtr<Aspose::Words::Lists::List>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the unique identifier of the list.
    /// 
    /// You do not normally need to use this property. But if you use it, you normally do so
    /// in conjunction with the <see cref="Aspose::Words::Lists::ListCollection::GetListByListId(int32_t)">GetListByListId()</see> method to find a
    /// list by its identifier.
    ASPOSE_WORDS_SHARED_API int32_t get_ListId() const;
    /// Gets the owner document.
    /// 
    /// A list always has a parent document and is valid only in the context of that document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentBase> get_Document() const;
    /// Returns <c>%true</c> when the list contains 9 levels; <c>%false</c> when 1 level.
    /// 
    /// The lists that you create with %Aspose.Words are always multi-level lists and contain 9 levels.
    /// 
    /// %Microsoft Word 2003 and later always create multi-level lists with 9 levels.
    /// But in some documents, created with earlier versions of %Microsoft Word you might encounter
    /// lists that have 1 level only.
    ASPOSE_WORDS_SHARED_API bool get_IsMultiLevel();
    /// Gets the collection of list levels for this list.
    /// 
    /// Use this property to access and modify formatting individual to each level of the list.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::ListLevelCollection> get_ListLevels();
    /// Specifies whether list should be restarted at each section.
    /// Default value is <c>%false</c>.
    /// 
    /// This option is supported only in RTF, DOC and DOCX document formats.
    /// 
    /// This option will be written to DOCX only if <see cref="Aspose::Words::Saving::OoxmlCompliance">OoxmlCompliance</see> is higher then <see cref="Aspose::Words::Saving::OoxmlCompliance::Ecma376_2006">Ecma376_2006</see>.
    ASPOSE_WORDS_SHARED_API bool get_IsRestartAtEachSection();
    /// Setter for Aspose::Words::Lists::List::get_IsRestartAtEachSection
    ASPOSE_WORDS_SHARED_API void set_IsRestartAtEachSection(bool value);
    /// Returns <c>%true</c> if this list is a definition of a list style.
    /// 
    /// When this property is <c>%true</c>, the <see cref="Aspose::Words::Lists::List::get_Style">Style</see> property returns the list style that
    /// this list defines.
    /// 
    /// By modifying properties of a list that defines a list style, you modify the properties
    /// of the list style.
    /// 
    /// A list that is a definition of a list style cannot be applied directly to paragraphs
    /// to make them numbered.
    /// 
    /// @sa Aspose::Words::Lists::List::get_Style
    /// @sa Aspose::Words::Lists::List::get_IsListStyleReference
    ASPOSE_WORDS_SHARED_API bool get_IsListStyleDefinition();
    /// Returns <c>%true</c> if this list is a reference to a list style.
    /// 
    /// Note, modifying properties of a list that is a reference to list style has no effect.
    /// The list formatting specified in the list style itself always takes precedence.
    /// 
    /// @sa Aspose::Words::Lists::List::get_Style
    /// @sa Aspose::Words::Lists::List::get_IsListStyleDefinition
    ASPOSE_WORDS_SHARED_API bool get_IsListStyleReference();
    /// Gets the list style that this list references or defines.
    /// 
    /// If this list is not associated with a list style, the property will return <c>%null</c>.
    /// 
    /// A list could be a reference to a list style, in this case <see cref="Aspose::Words::Lists::List::get_IsListStyleReference">IsListStyleReference</see>
    /// will be <c>%true</c>.
    /// 
    /// A list could be a definition of a list style, in this case <see cref="Aspose::Words::Lists::List::get_IsListStyleDefinition">IsListStyleDefinition</see>
    /// will be <c>%true</c>. Such a list cannot be applied to paragraphs in the document directly.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> get_Style();

    /// Compares with the specified list.
    ASPOSE_WORDS_SHARED_API bool Equals(const System::SharedPtr<Aspose::Words::Lists::List>& list);
    /// Determines whether the specified object is equal in value to the current object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    /// Calculates hash code for this list object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;
    /// Compares the specified list to the current list.
    ASPOSE_WORDS_SHARED_API int32_t CompareTo(System::SharedPtr<Aspose::Words::Lists::List> other) override;
    /// Returns true if the current list and the given list are created from the same template.
    ASPOSE_WORDS_SHARED_API bool HasSameTemplate(const System::SharedPtr<Aspose::Words::Lists::List>& other);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~List();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::WeakPtr<System::Object> mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    mutable System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
}
