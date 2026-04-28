//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartAxisTitle.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
namespace Charts
{

class ChartFormat;

}
}
class Font;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Provides access to the axis title properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with
/// Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartAxisTitle : public System::Object
{
    typedef ChartAxisTitle ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the text of the axis title.
    /// If <c>%null</c> or empty value is specified, auto generated title will be shown.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Sets the text of the axis title.
    /// If <c>%null</c> or empty value is specified, auto generated title will be shown.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);
    /// Determines whether other chart elements shall be allowed to overlap the title.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Overlay();
    /// Determines whether other chart elements shall be allowed to overlap the title.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Overlay(bool value);
    /// Determines whether the title shall be shown for the axis.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Show();
    /// Determines whether the title shall be shown for the axis.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Show(bool value);
    /// Provides access to the font formatting of the axis title.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Provides access to fill and line formatting of the axis title.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
}
