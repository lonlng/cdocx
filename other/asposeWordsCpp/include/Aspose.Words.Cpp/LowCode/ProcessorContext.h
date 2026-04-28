//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/ProcessorContext.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fonts
{
class FontSettings;
}
class IWarningCallback;
namespace Layout
{
class LayoutOptions;
}

}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Base class for processor contexts. Provides properties and options used by the processor to execute processing.
class ASPOSE_WORDS_SHARED_CLASS ProcessorContext : public System::Object
{
    typedef ProcessorContext ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Warning callback used by the processor.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::IWarningCallback>& get_WarningCallback() const;
    /// Warning callback used by the processor.
    ASPOSE_WORDS_SHARED_API void set_WarningCallback(const System::SharedPtr<Aspose::Words::IWarningCallback>& value);
    /// Font settings used by the processor.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::FontSettings>& get_FontSettings() const;
    /// Font settings used by the processor.
    ASPOSE_WORDS_SHARED_API void set_FontSettings(const System::SharedPtr<Aspose::Words::Fonts::FontSettings>& value);
    /// Document layout options used by the processor.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Layout::LayoutOptions>& get_LayoutOptions() const;

    ASPOSE_WORDS_SHARED_API ProcessorContext();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
}
