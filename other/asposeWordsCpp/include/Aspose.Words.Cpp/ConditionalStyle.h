//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ConditionalStyle.h
#pragma once

#include <system/object_ext.h>
#include <cstdint>

#include <Aspose.Words.Cpp/ConditionalStyleType.h>
#include <Aspose.Words.Cpp/IShadingAttrSource.h>
#include <Aspose.Words.Cpp/IRunAttrSource.h>
#include <Aspose.Words.Cpp/IParaAttrSource.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class BorderCollection;
enum class BorderType;

class Font;
class ParagraphFormat;

enum class RevisionsView;

class Shading;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class SortedList;
}
}
}

namespace Aspose {

namespace Words {

/// Represents special formatting applied to some area of a table with assigned table style.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ConditionalStyle final : public Aspose::Words::IBorderAttrSource, public Aspose::Words::IShadingAttrSource, public Aspose::Words::IParaAttrSource, public Aspose::Words::IRunAttrSource
{
    typedef ConditionalStyle ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;
    typedef Aspose::Words::IShadingAttrSource BaseType1;
    typedef Aspose::Words::IParaAttrSource BaseType2;
    typedef Aspose::Words::IRunAttrSource BaseType3;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2, BaseType3> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the paragraph formatting of the conditional style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ParagraphFormat> get_ParagraphFormat();
    /// Gets the character formatting of the conditional style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Gets a <see cref="Aspose::Words::Shading">Shading</see> object that refers to the shading formatting for this conditional style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Shading> get_Shading();
    /// Gets the collection of default cell borders for the conditional style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Gets the amount of space (in points) to add to the left of the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_LeftPadding();
    /// Sets the amount of space (in points) to add to the left of the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_LeftPadding(double value);
    /// Gets the amount of space (in points) to add to the right of the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_RightPadding();
    /// Sets the amount of space (in points) to add to the right of the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_RightPadding(double value);
    /// Gets the amount of space (in points) to add above the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_TopPadding();
    /// Sets the amount of space (in points) to add above the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_TopPadding(double value);
    /// Gets the amount of space (in points) to add below the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_BottomPadding();
    /// Sets the amount of space (in points) to add below the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_BottomPadding(double value);
    /// Gets table area to which this conditional style relates.
    ASPOSE_WORDS_SHARED_API Aspose::Words::ConditionalStyleType get_Type();

    /// Clears formatting of this conditional style.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();
    /// Compares this conditional style with the specified object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    /// Calculates hash code for this object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ConditionalStyle();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::WeakPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;
    System::SharedPtr<System::Object> FetchInheritedShadingAttr(int32_t ) override;
    void SetParaAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveParaAttr(int32_t ) override;
    void ClearParaAttrs() override;
    System::SharedPtr<System::Object> FetchInheritedParaAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectParaAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectParaAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchParaAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedRunAttr(int32_t ) override;
    void SetRunAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveRunAttr(int32_t ) override;
    void ClearRunAttrs() override;

};

}
}
