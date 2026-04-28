//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Replacing/ReplacingArgs.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Node;

}
}
namespace System
{
namespace Text
{
namespace RegularExpressions
{
class Match;
}
}
}

namespace Aspose {

namespace Words {

namespace Replacing {

/// Provides data for a custom replace operation.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/find-and-replace/">Find and Replace</a> documentation article.
/// 
/// @sa Aspose::Words::Replacing::IReplacingCallback
/// @sa Aspose::Words::Range
/// @sa Aspose::Words::Range::Replace(System::String, System::String, System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>)
class ASPOSE_WORDS_SHARED_CLASS ReplacingArgs : public System::Object
{
    typedef ReplacingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The <see cref="System::Text::RegularExpressions::Match">Match</see> resulting from a single regular
    /// expression match during a <b>%Replace</b>.
    /// 
    /// <b>%Match.Index"</b>
    /// gets the zero-based starting
    /// position of the match from the start of the find and replace range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Text::RegularExpressions::Match> get_Match() const;
    /// Gets the node that contains the beginning of the match.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Node>& get_MatchNode() const;
    /// Gets the node that contains the end of the match.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Node>& get_MatchEndNode() const;
    /// Gets the zero-based starting position of the match from the start of
    /// the node that contains the beginning of the match.
    ASPOSE_WORDS_SHARED_API int32_t get_MatchOffset() const;
    /// Gets the replacement string.
    ASPOSE_WORDS_SHARED_API System::String get_Replacement() const;
    /// Sets the replacement string.
    ASPOSE_WORDS_SHARED_API void set_Replacement(const System::String& value);
    /// Identifies, by name, a captured group in the <see cref="Aspose::Words::Replacing::ReplacingArgs::get_Match">Match</see>
    /// that is to be replaced with the <see cref="Aspose::Words::Replacing::ReplacingArgs::get_Replacement">Replacement</see> string.
    /// 
    /// When group name is <c>%null</c>, <see cref="Aspose::Words::Replacing::ReplacingArgs::get_GroupIndex">GroupIndex</see> is used to identify the group.
    /// 
    /// Default is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_GroupName() const;
    /// Setter for Aspose::Words::Replacing::ReplacingArgs::get_GroupName
    ASPOSE_WORDS_SHARED_API void set_GroupName(const System::String& value);
    /// Identifies, by index, a captured group in the <see cref="Aspose::Words::Replacing::ReplacingArgs::get_Match">Match</see>
    /// that is to be replaced with the <see cref="Aspose::Words::Replacing::ReplacingArgs::get_Replacement">Replacement</see> string.
    /// 
    /// <see cref="Aspose::Words::Replacing::ReplacingArgs::get_GroupIndex">GroupIndex</see> has effect only when <see cref="Aspose::Words::Replacing::ReplacingArgs::get_GroupName">GroupName</see> is <c>%null</c>.
    /// 
    /// Default is zero.
    ASPOSE_WORDS_SHARED_API int32_t get_GroupIndex() const;
    /// Setter for Aspose::Words::Replacing::ReplacingArgs::get_GroupIndex
    ASPOSE_WORDS_SHARED_API void set_GroupIndex(int32_t value);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::String mField5;
    __TypeStub<4,4,4,4>::type mField6;

};

}
}
}
