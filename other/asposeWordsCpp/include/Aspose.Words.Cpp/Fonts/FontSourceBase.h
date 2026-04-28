//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontSourceBase.h
#pragma once

#include <system/shared_ptr.h>
#include <Aspose.Words.Cpp/Fonts/IFontSource.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fonts/FontSourceType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Fonts
{
class IFontData;
}
namespace Words
{
namespace Fonts
{

class PhysicalFontInfo;

}
class IWarningCallback;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerable;
template <typename> class IList;
}
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// This is an abstract base class for the classes that allow the user to specify various font sources.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FontSourceBase : public Aspose::Fonts::IFontSource
{
    typedef FontSourceBase ThisType;
    typedef Aspose::Fonts::IFontSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the type of the font source.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontSourceType get_Type() = 0;
    /// Returns the font source priority.
    /// 
    /// This value is used when there are fonts with the same family name and style in different font sources.
    /// In this case %Aspose.Words selects the font from the source with the higher priority value.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_Priority() const;
    /// Called during processing of font source when an issue is detected that might result in formatting fidelity loss.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::IWarningCallback> get_WarningCallback() const;
    /// Called during processing of font source when an issue is detected that might result in formatting fidelity loss.
    ASPOSE_WORDS_SHARED_API void set_WarningCallback(const System::SharedPtr<Aspose::Words::IWarningCallback>& value);

    /// Returns list of fonts available via this source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::Fonts::PhysicalFontInfo>>> GetAvailableFonts();

protected:

    ASPOSE_WORDS_SHARED_API FontSourceBase();

    virtual ASPOSE_WORDS_SHARED_API ~FontSourceBase();

private:

    ASPOSE_WORDS_SHARED_API int32_t get_PriorityInternal() override;

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Fonts::IFontData>>> GetFontDataInternal() override;

};

}
}
}
