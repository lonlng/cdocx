//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WarningInfo.h
#pragma once

#include <system/string.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/WarningType.h>
#include <Aspose.Words.Cpp/WarningSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Contains information about a warning that %Aspose.Words issued during document loading or saving.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
/// 
/// You do not create instances of this class. Objects of this class are created
/// and passed by %Aspose.Words to the <see cref="Aspose::Words::IWarningCallback::Warning(System::SharedPtr<Aspose::Words::WarningInfo>)">Warning()</see> method.
/// 
/// @sa Aspose::Words::IWarningCallback
class ASPOSE_WORDS_SHARED_CLASS WarningInfo : public System::Object
{
    typedef WarningInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the type of the warning.
    ASPOSE_WORDS_SHARED_API Aspose::Words::WarningType get_WarningType() const;
    /// Returns the description of the warning.
    ASPOSE_WORDS_SHARED_API System::String get_Description() const;
    /// Returns the source of the warning.
    ASPOSE_WORDS_SHARED_API Aspose::Words::WarningSource get_Source() const;

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::String mField2;

};

}
}
