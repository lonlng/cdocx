//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListFormat.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Lists
{
class List;

class ListLevel;

}

}
}

namespace Aspose {

namespace Words {

namespace Lists {

/// Allows to control what list formatting is applied to a paragraph.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-lists/">Working with Lists</a> documentation article.
/// 
/// A paragraph in a %Microsoft Word document can be bulleted or numbered.
/// When a paragraph is bulleted or numbered, it is said that list formatting
/// is applied to the paragraph.
/// 
/// You do not create objects of the <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see> class directly.
/// You access <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see> as a property of another object that can
/// have list formatting associated with it. At the moment the objects that can
/// have list formatting are: <see cref="Aspose::Words::Paragraph">Paragraph</see>,
/// <see cref="Aspose::Words::Style">Style</see> and <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>.
/// 
/// <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see> of a <see cref="Aspose::Words::Paragraph">Paragraph</see> specifies
/// what list formatting and list level is applied to that particular paragraph.
/// 
/// <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see> of a <see cref="Aspose::Words::Style">Style</see> (applicable
/// to paragraph styles only) allows to specify what list formatting and list level
/// is applied to all paragraphs of that particular style.
/// 
/// <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see> of a <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>
/// provides access to the list formatting at the current cursor position
/// inside the <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>.
/// 
/// The list formatting itself is stored inside a <see cref="Aspose::Words::Lists::List">List</see>
/// object that is stored separately from the paragraphs. The list objects
/// are stored inside a <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see> collection. There is a single
/// <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see> collection per <see cref="Aspose::Words::Document">Document</see>.
/// 
/// The paragraphs do not physically belong to a list. The paragraphs just
/// reference a particular list object via the <see cref="Aspose::Words::Lists::ListFormat::get_List">List</see> property
/// and a particular level in the list via the <see cref="Aspose::Words::Lists::ListFormat::get_ListLevelNumber">ListLevelNumber</see> property.
/// By setting these two properties you control what bullets and numbering is
/// applied to a paragraph.
class ASPOSE_WORDS_SHARED_CLASS ListFormat : public System::Object
{
    typedef ListFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the list level number (0 to 8) for the paragraph.
    /// 
    /// In Word documents, lists may consist of 1 or 9 levels, numbered 0 to 8.
    /// 
    /// Has effect only when the <see cref="Aspose::Words::Lists::ListFormat::get_List">List</see> property is set to reference a valid list.
    /// 
    /// @sa Aspose::Words::Lists::ListFormat::get_List
    ASPOSE_WORDS_SHARED_API int32_t get_ListLevelNumber();
    /// Setter for Aspose::Words::Lists::ListFormat::get_ListLevelNumber
    ASPOSE_WORDS_SHARED_API void set_ListLevelNumber(int32_t value);
    /// True when the paragraph has bulleted or numbered formatting applied to it.
    ASPOSE_WORDS_SHARED_API bool get_IsListItem();
    /// Gets or sets the list this paragraph is a member of.
    /// 
    /// The list that is being assigned to this property must belong to the current document.
    /// 
    /// The list that is being assigned to this property must not be a list style definition.
    /// 
    /// Setting this property to <c>%null</c> removes bullets and numbering from the paragraph
    /// and sets the list level number to zero. Setting this property to <c>%null</c> is equivalent
    /// to calling <see cref="Aspose::Words::Lists::ListFormat::RemoveNumbers">RemoveNumbers</see>.
    /// 
    /// @sa Aspose::Words::Lists::ListFormat::get_ListLevelNumber
    /// @sa Aspose::Words::Lists::ListFormat::RemoveNumbers
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> get_List();
    /// Setter for Aspose::Words::Lists::ListFormat::get_List
    ASPOSE_WORDS_SHARED_API void set_List(const System::SharedPtr<Aspose::Words::Lists::List>& value);
    /// Returns the list level formatting plus any formatting overrides applied to the current paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::ListLevel> get_ListLevel();

    /// Starts a new default bulleted list and applies it to the paragraph.
    /// 
    /// This is a shortcut method that creates a new list using the default bulleted
    /// template, applies it to the paragraph and selects the 1st list level.
    /// 
    /// @sa Aspose::Words::Lists::ListFormat::get_List
    /// @sa Aspose::Words::Lists::ListFormat::RemoveNumbers
    /// @sa Aspose::Words::Lists::ListFormat::get_ListLevelNumber
    ASPOSE_WORDS_SHARED_API void ApplyBulletDefault();
    /// Starts a new default numbered list and applies it to the paragraph.
    /// 
    /// This is a shortcut method that creates a new list using the default numbered
    /// template, applies it to the paragraph and selects the 1st list level.
    /// 
    /// @sa Aspose::Words::Lists::ListFormat::get_List
    /// @sa Aspose::Words::Lists::ListFormat::RemoveNumbers
    /// @sa Aspose::Words::Lists::ListFormat::get_ListLevelNumber
    ASPOSE_WORDS_SHARED_API void ApplyNumberDefault();
    /// Removes numbers or bullets from the current paragraph and sets list level to zero.
    /// 
    /// Calling this method is equivalent to setting the <see cref="Aspose::Words::Lists::ListFormat::get_List">List</see> property to <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void RemoveNumbers();
    /// Increases the list level of the current paragraph by one level.
    /// 
    /// This method changes the list level and applies formatting properties of the new level.
    /// 
    /// In Word documents, lists may consist of up to nine levels. List formatting
    /// for each level specifies what bullet or number is used, left indent, space between
    /// the bullet and text etc.
    ASPOSE_WORDS_SHARED_API void ListIndent();
    /// Decreases the list level of the current paragraph by one level.
    /// 
    /// This method changes the list level and applies formatting properties of the new level.
    /// 
    /// In Word documents, lists may consist of up to nine levels. List formatting
    /// for each level specifies what bullet or number is used, left indent, space between
    /// the bullet and text etc.
    ASPOSE_WORDS_SHARED_API void ListOutdent();

protected:

private:

    System::WeakPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
