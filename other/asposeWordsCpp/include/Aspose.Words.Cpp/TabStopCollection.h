//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TabStopCollection.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/TabLeader.h>
#include <Aspose.Words.Cpp/TabAlignment.h>
#include <Aspose.Words.Cpp/InternableComplexAttr.h>
#include <Aspose.Words.Cpp/IExpandableAttr.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class IComplexAttr;

class TabStop;
}
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::TabStop">TabStop</see> objects that represent custom tabs for a paragraph or a style.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// In %Microsoft Word documents, a tab stop can be defined in the properties of a paragraph
/// style or directly in the properties of a paragraph. A style can be based on another style.
/// Therefore, the complete set of tab stops for a given object is a combination of tab stops
/// defined directly on this object and tab stops inherited from the parent styles.
/// 
/// In %Aspose.Words, when you obtain a <see cref="Aspose::Words::TabStopCollection">TabStopCollection</see> for a paragraph or a style,
/// it contains only the custom tab stops defined directly for this paragraph or style.
/// The collection does not include tab stops defined in the parent styles or default tab stops.
/// 
/// @sa Aspose::Words::ParagraphFormat
/// @sa Aspose::Words::TabStop
/// @sa Aspose::Words::Document::get_DefaultTabStop
class ASPOSE_WORDS_SHARED_CLASS TabStopCollection : public Aspose::Words::InternableComplexAttr, public Aspose::Words::IExpandableAttr
{
    typedef TabStopCollection ThisType;
    typedef Aspose::Words::InternableComplexAttr BaseType;
    typedef Aspose::Words::IExpandableAttr BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of tab stops in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Determines whether the specified <see cref="Aspose::Words::TabStopCollection">TabStopCollection</see> is equal in value to the current <see cref="Aspose::Words::TabStopCollection">TabStopCollection</see>.
    ASPOSE_WORDS_SHARED_API bool Equals(const System::SharedPtr<Aspose::Words::TabStopCollection>& rhs);
    /// Determines whether the specified object is equal in value to the current object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    /// Serves as a hash function for this type.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;

    /// Gets a tab stop at the given index.
    /// 
    /// @param index An index into the collection of tab stops.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TabStop> idx_get(int32_t index);
    /// Gets a tab stop at the specified position.
    /// 
    /// @param position The position (in points) of the tab stop.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TabStop> idx_get(double position);

    /// Deletes all tab stop positions.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Gets the position (in points) of the tab stop at the specified index.
    /// 
    /// @param index An index into the collection of tab stops.
    /// 
    /// @return The position of the tab stop.
    ASPOSE_WORDS_SHARED_API double GetPositionByIndex(int32_t index);
    /// Gets the index of a tab stop with the specified position in points.
    ASPOSE_WORDS_SHARED_API int32_t GetIndexByPosition(double position);
    /// Adds or replaces a tab stop in the collection.
    /// 
    /// If a tab stop already exists at the specified position, it is replaced.
    /// 
    /// @param tabStop A tab stop object to add.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::TabStop>& tabStop);
    /// Adds or replaces a tab stop in the collection.
    /// 
    /// If a tab stop already exists at the specified position, it is replaced.
    /// 
    /// @param position A position (in points) where to add the tab stop.
    /// @param alignment A <see cref="Aspose::Words::TabAlignment">TabAlignment</see> value that
    ///     specifies the alignment of text at the tab stop.
    /// @param leader A <see cref="Aspose::Words::TabLeader">TabLeader</see> value that
    ///     specifies the type of the leader line displayed under the tab character.
    ASPOSE_WORDS_SHARED_API void Add(double position, Aspose::Words::TabAlignment alignment, Aspose::Words::TabLeader leader);
    /// Removes a tab stop at the specified position from the collection.
    /// 
    /// @param position The position (in points) of the tab stop to remove.
    ASPOSE_WORDS_SHARED_API void RemoveByPosition(double position);
    /// Removes a tab stop at the specified index from the collection.
    /// 
    /// @param index An index into the collection of tab stops.
    ASPOSE_WORDS_SHARED_API void RemoveByIndex(int32_t index);
    /// Gets a first tab stop to the right of the specified position.
    /// 
    /// Skips tab stops with <see cref="Aspose::Words::TabStop::get_Alignment">Alignment</see> set to <see cref="Aspose::Words::TabAlignment::Bar">Bar</see>.
    /// 
    /// @param position The reference position (in points).
    /// 
    /// @return A tab stop object or <c>%null</c> if a suitable tab stop was not found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TabStop> After(double position);
    /// Gets a first tab stop to the left of the specified position.
    /// 
    /// Skips tab stops with <see cref="Aspose::Words::TabStop::get_Alignment">Alignment</see> set to <see cref="Aspose::Words::TabAlignment::Bar">Bar</see>.
    /// 
    /// @param position The reference position (in points).
    /// 
    /// @return A tab stop object or <c>%null</c> if a suitable tab stop was not found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TabStop> Before(double position);

protected:

    TabStopCollection();

    virtual ASPOSE_WORDS_SHARED_API ~TabStopCollection();

private:

    bool get_IsInheritedComplexAttr() override;

    System::SharedPtr<System::Object> mField0;
    __TypeStub<1,1,1,1>::type mField1;

    System::SharedPtr<Aspose::Words::IComplexAttr> DeepCloneComplexAttr() override;
    System::SharedPtr<Aspose::Words::IExpandableAttr> Expand(System::SharedPtr<Aspose::Words::IExpandableAttr> ) override;
    void Collapse(System::SharedPtr<Aspose::Words::IExpandableAttr> ) override;

};

}
}
