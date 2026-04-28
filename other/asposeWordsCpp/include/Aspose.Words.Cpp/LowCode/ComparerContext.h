//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/ComparerContext.h
#pragma once

#include <system/string.h>
#include <system/date_time.h>

#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Comparing
{
class CompareOptions;
}

}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Document comparer context
class ASPOSE_WORDS_SHARED_CLASS ComparerContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef ComparerContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The author to be assigned to revisions created during document comparison.
    ASPOSE_WORDS_SHARED_API System::String get_Author() const;
    /// The author to be assigned to revisions created during document comparison.
    ASPOSE_WORDS_SHARED_API void set_Author(const System::String& value);
    /// The date and time assigned to revisions created during document comparison.
    ASPOSE_WORDS_SHARED_API System::DateTime get_DateTime() const;
    /// The date and time assigned to revisions created during document comparison.
    ASPOSE_WORDS_SHARED_API void set_DateTime(System::DateTime value);
    /// Indicates whether to accept revisions in the documents before comparing them.
    /// If the compared documents contain revisions and this flag is set to false, the processor will reject revisions.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_AcceptRevisions() const;
    /// Indicates whether to accept revisions in the documents before comparing them.
    /// If the compared documents contain revisions and this flag is set to false, the processor will reject revisions.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_AcceptRevisions(bool value);
    /// Options used upon comparing documents.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& get_CompareOptions() const;

    ASPOSE_WORDS_SHARED_API ComparerContext();

protected:

private:

    System::String mField0;
    System::DateTime mField1;
    __TypeStub<1,1,1,1>::type mField2;
    System::SharedPtr<System::Object> mField3;

};

}
}
}
