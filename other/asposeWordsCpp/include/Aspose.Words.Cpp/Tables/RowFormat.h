//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/RowFormat.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/HeightRule.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class BorderCollection;
enum class BorderType;

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

namespace Tables {

/// Represents all formatting for a table row.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS RowFormat : public Aspose::Words::IBorderAttrSource
{
    typedef RowFormat ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the collection of default cell borders for the row.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Gets the height of the table row in points.
    ASPOSE_WORDS_SHARED_API double get_Height();
    /// Sets the height of the table row in points.
    ASPOSE_WORDS_SHARED_API void set_Height(double value);
    /// Gets the rule for determining the height of the table row.
    ASPOSE_WORDS_SHARED_API Aspose::Words::HeightRule get_HeightRule();
    /// Sets the rule for determining the height of the table row.
    ASPOSE_WORDS_SHARED_API void set_HeightRule(Aspose::Words::HeightRule value);
    /// True if the text in a table row is allowed to split across a page break.
    ASPOSE_WORDS_SHARED_API bool get_AllowBreakAcrossPages();
    /// True if the text in a table row is allowed to split across a page break.
    ASPOSE_WORDS_SHARED_API void set_AllowBreakAcrossPages(bool value);
    /// True if the row is repeated as a table heading on every page when the table spans more than one page.
    ASPOSE_WORDS_SHARED_API bool get_HeadingFormat();
    /// True if the row is repeated as a table heading on every page when the table spans more than one page.
    ASPOSE_WORDS_SHARED_API void set_HeadingFormat(bool value);

    /// Resets to default row formatting.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~RowFormat();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;

};

}
}
}
