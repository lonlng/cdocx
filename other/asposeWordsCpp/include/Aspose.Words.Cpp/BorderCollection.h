//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BorderCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/LineStyle.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
class Border;
enum class BorderType;

}
}
namespace System
{
namespace Drawing
{
class Color;
}
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::Border">Border</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS BorderCollection final : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Border>>
{
    typedef BorderCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Border>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using System::Object::Equals;

private:

public:

    /// Gets the left border.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Left();
    /// Gets the right border.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Right();
    /// Gets the top border.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Top();
    /// Gets the bottom border.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Bottom();
    /// Gets the horizontal border that is used between cells or conforming paragraphs.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Horizontal();
    /// Gets the vertical border that is used between cells.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Vertical();
    /// Gets the number of borders in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();
    /// Gets or sets the border width in points.
    /// 
    /// Returns the width of the first border in the collection.
    /// 
    /// Sets the width of all borders in the collection excluding diagonal borders.
    ASPOSE_WORDS_SHARED_API double get_LineWidth();
    /// Setter for Aspose::Words::BorderCollection::get_LineWidth
    ASPOSE_WORDS_SHARED_API void set_LineWidth(double value);
    /// Gets or sets the border style.
    /// 
    /// Returns the style of the first border in the collection.
    /// 
    /// Sets the style of all borders in the collection excluding diagonal borders.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LineStyle get_LineStyle();
    /// Setter for Aspose::Words::BorderCollection::get_LineStyle
    ASPOSE_WORDS_SHARED_API void set_LineStyle(Aspose::Words::LineStyle value);
    /// Gets or sets the border color.
    /// 
    /// Returns the color of the first border in the collection.
    /// 
    /// Sets the color of all borders in the collection excluding diagonal borders.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Setter for Aspose::Words::BorderCollection::get_Color
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets or sets distance of the border from text in points.
    /// 
    /// Gets the distance from text for the first border.
    /// 
    /// Sets the distance from text for all borders in the collection excluding diagonal borders.
    /// 
    /// Has no effect and will be automatically reset to zero for borders of table cells.
    ASPOSE_WORDS_SHARED_API double get_DistanceFromText();
    /// Setter for Aspose::Words::BorderCollection::get_DistanceFromText
    ASPOSE_WORDS_SHARED_API void set_DistanceFromText(double value);
    /// Gets or sets a value indicating whether the border has a shadow.
    /// 
    /// Gets the value from the first border in the collection.
    /// 
    /// Sets the value for all borders in the collection excluding diagonal borders.
    ASPOSE_WORDS_SHARED_API bool get_Shadow();
    /// Setter for Aspose::Words::BorderCollection::get_Shadow
    ASPOSE_WORDS_SHARED_API void set_Shadow(bool value);

    /// Compares collections of borders.
    ASPOSE_WORDS_SHARED_API bool Equals(const System::SharedPtr<Aspose::Words::BorderCollection>& brColl);

    /// Retrieves a <see cref="Aspose::Words::Border">Border</see> object by border type.
    /// 
    /// Note that not all borders are present for different document elements.
    /// This method throws an exception if you request a border not applicable to the current object.
    /// 
    /// @param borderType A <see cref="Aspose::Words::BorderType">BorderType</see> value
    ///     that specifies the type of the border to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> idx_get(Aspose::Words::BorderType borderType);
    /// Retrieves a <see cref="Aspose::Words::Border">Border</see> object by index.
    /// 
    /// @param index Zero-based index of the border to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> idx_get(int32_t index);

    /// Removes all borders of an object.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();
    /// Returns an enumerator object that can be used to iterate over all borders in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Border>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~BorderCollection();

private:

    System::WeakPtr<System::Object> mField0;

};

}
}
