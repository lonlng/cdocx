//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TextColumnCollection.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class TextColumn;

}
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::TextColumn">TextColumn</see> objects that represent all the columns of text in a section of a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-sections/">Working with Sections</a> documentation article.
/// 
/// Use <see cref="Aspose::Words::TextColumnCollection::SetCount(int32_t)">SetCount()</see> to set the number of text columns.
/// 
/// To make all columns equal width and spaced evenly, set <see cref="Aspose::Words::TextColumnCollection::get_EvenlySpaced">EvenlySpaced</see> to <c>%true</c>
/// and specify the amount of space between the columns in <see cref="Aspose::Words::TextColumnCollection::get_Spacing">Spacing</see>. MS Word will
/// automatically calculate column widths.
/// 
/// If you have <see cref="Aspose::Words::TextColumnCollection::get_EvenlySpaced">EvenlySpaced</see> set to <c>%false</c>, you need to specify width and spacing for each
/// column individually. Use the indexer to access individual <see cref="Aspose::Words::TextColumn">TextColumn</see> objects.
/// 
/// When using custom column widths, make sure the sum of all column widths and spacings between them
/// equals page width minus left and right page margins.
/// 
/// @sa Aspose::Words::PageSetup
/// @sa Aspose::Words::Section
class ASPOSE_WORDS_SHARED_CLASS TextColumnCollection : public System::Object
{
    typedef TextColumnCollection ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// True if text columns are of equal width and evenly spaced.
    ASPOSE_WORDS_SHARED_API bool get_EvenlySpaced();
    /// True if text columns are of equal width and evenly spaced.
    ASPOSE_WORDS_SHARED_API void set_EvenlySpaced(bool value);
    /// When columns are evenly spaced, gets or sets the amount of space between each column in points.
    ASPOSE_WORDS_SHARED_API double get_Spacing();
    /// When columns are evenly spaced, gets or sets the amount of space between each column in points.
    ASPOSE_WORDS_SHARED_API void set_Spacing(double value);
    /// When columns are evenly spaced, gets the width of the columns.
    /// 
    /// Has effect only when <see cref="Aspose::Words::TextColumnCollection::get_EvenlySpaced">EvenlySpaced</see> is set to <c>%true</c>.
    ASPOSE_WORDS_SHARED_API double get_Width();
    /// When <c>%true</c>, adds a vertical line between columns.
    ASPOSE_WORDS_SHARED_API bool get_LineBetween();
    /// When <c>%true</c>, adds a vertical line between columns.
    ASPOSE_WORDS_SHARED_API void set_LineBetween(bool value);
    /// Gets the number of columns in the section of a document.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Arranges text into the specified number of text columns.
    /// 
    /// When <see cref="Aspose::Words::TextColumnCollection::get_EvenlySpaced">EvenlySpaced</see> is <c>%false</c> and you increase the number of columns,
    /// new <see cref="Aspose::Words::TextColumn">TextColumn</see> objects are created with zero width and spacing.
    /// You need to set width and spacing for the new columns.
    /// 
    /// @param newCount The number of columns the text is to be arranged into.
    ASPOSE_WORDS_SHARED_API void SetCount(int32_t newCount);

    /// Returns a text column at the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TextColumn> idx_get(int32_t index);

protected:

private:

    System::WeakPtr<System::Object> mField0;

};

}
}
