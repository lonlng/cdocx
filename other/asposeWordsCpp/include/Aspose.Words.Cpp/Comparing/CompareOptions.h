//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Comparing/CompareOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Comparing/Granularity.h>
#include <Aspose.Words.Cpp/Comparing/ComparisonTargetType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Comparing
{
class AdvancedCompareOptions;

}
}
}

namespace Aspose {

namespace Words {

namespace Comparing {

/// Allows to choose additional options for document comparison operation.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/compare-documents/">Compare Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS CompareOptions : public System::Object
{
    typedef CompareOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether to compare differences   between the two documents.
    ASPOSE_WORDS_SHARED_API bool get_CompareMoves() const;
    /// Specifies whether to compare differences   between the two documents.
    ASPOSE_WORDS_SHARED_API void set_CompareMoves(bool value);
    /// True indicates that documents comparison is case insensitive.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreCaseChanges() const;
    /// True indicates that documents comparison is case insensitive.
    ASPOSE_WORDS_SHARED_API void set_IgnoreCaseChanges(bool value);
    /// Specifies whether to compare the differences in data contained in tables.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreTables() const;
    /// Specifies whether to compare the differences in data contained in tables.
    ASPOSE_WORDS_SHARED_API void set_IgnoreTables(bool value);
    /// Specifies whether to compare differences in fields.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreFields() const;
    /// Specifies whether to compare differences in fields.
    ASPOSE_WORDS_SHARED_API void set_IgnoreFields(bool value);
    /// Specifies whether to compare differences in footnotes and endnotes.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreFootnotes() const;
    /// Specifies whether to compare differences in footnotes and endnotes.
    ASPOSE_WORDS_SHARED_API void set_IgnoreFootnotes(bool value);
    /// Specifies whether to compare differences in comments.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreComments() const;
    /// Specifies whether to compare differences in comments.
    ASPOSE_WORDS_SHARED_API void set_IgnoreComments(bool value);
    /// Specifies whether to compare differences in the data contained within text boxes.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreTextboxes() const;
    /// Specifies whether to compare differences in the data contained within text boxes.
    ASPOSE_WORDS_SHARED_API void set_IgnoreTextboxes(bool value);
    /// True indicates that formatting is ignored.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreFormatting() const;
    /// True indicates that formatting is ignored.
    ASPOSE_WORDS_SHARED_API void set_IgnoreFormatting(bool value);
    /// True indicates that headers and footers content is ignored.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreHeadersAndFooters() const;
    /// True indicates that headers and footers content is ignored.
    ASPOSE_WORDS_SHARED_API void set_IgnoreHeadersAndFooters(bool value);
    /// Specifies which document shall be used as a target during comparison.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Comparing::ComparisonTargetType get_Target() const;
    /// Specifies which document shall be used as a target during comparison.
    ASPOSE_WORDS_SHARED_API void set_Target(Aspose::Words::Comparing::ComparisonTargetType value);
    /// Specifies whether changes are tracked by character or by word.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Comparing::Granularity get_Granularity() const;
    /// Specifies whether changes are tracked by character or by word.
    ASPOSE_WORDS_SHARED_API void set_Granularity(Aspose::Words::Comparing::Granularity value);
    /// Specifies advanced compare options that might help to produce more precise comparison output.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Comparing::AdvancedCompareOptions>& get_AdvancedOptions() const;
    /// Specifies whether to ignore difference in DrawingML unique Id.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreDmlUniqueId();
    /// Specifies whether to ignore difference in DrawingML unique Id.
    ASPOSE_WORDS_SHARED_API void set_IgnoreDmlUniqueId(bool value);

    ASPOSE_WORDS_SHARED_API CompareOptions();

protected:

    __TypeStub<4,4,4,4>::type mField0;

private:

    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    __TypeStub<1,1,1,1>::type mField9;
    __TypeStub<1,1,1,1>::type mField10;
    __TypeStub<4,4,4,4>::type mField11;
    System::SharedPtr<System::Object> mField12;

};

}
}
}
