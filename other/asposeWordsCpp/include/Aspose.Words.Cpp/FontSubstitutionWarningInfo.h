//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/FontSubstitutionWarningInfo.h
#pragma once

#include <system/string.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/WarningInfo.h>
#include <Aspose.Words.Cpp/FontSubstitutionReason.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fonts
{

class PhysicalFontInfo;
}
}
}

namespace Aspose {

namespace Words {

/// Contains information about a font substitution warning that %Aspose.Words issued during document loading or saving.
class ASPOSE_WORDS_SHARED_CLASS FontSubstitutionWarningInfo : public Aspose::Words::WarningInfo
{
    typedef FontSubstitutionWarningInfo ThisType;
    typedef Aspose::Words::WarningInfo BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Font substitution reason.
    ASPOSE_WORDS_SHARED_API Aspose::Words::FontSubstitutionReason get_Reason() const;
    /// Requested font family name.
    ASPOSE_WORDS_SHARED_API System::String get_RequestedFamilyName() const;
    /// Indicates whether bold style was requested.
    ASPOSE_WORDS_SHARED_API bool get_RequestedBold() const;
    /// Indicates whether italic style was requested.
    ASPOSE_WORDS_SHARED_API bool get_RequestedItalic() const;
    /// Resolved font.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::PhysicalFontInfo>& get_ResolvedFont() const;

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
