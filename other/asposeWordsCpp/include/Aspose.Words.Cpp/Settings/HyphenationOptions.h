//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/HyphenationOptions.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Allows to configure document hyphenation options.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-hyphenation/">Working with Hyphenation</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS HyphenationOptions : public System::Object
{
    typedef HyphenationOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets value determining whether automatic hyphenation is turned on for the document.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_AutoHyphenation() const;
    /// Sets value determining whether automatic hyphenation is turned on for the document.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_AutoHyphenation(bool value);
    /// Gets or sets the maximum number of consecutive lines that can end with hyphens.
    /// Default value for this property is 0.
    /// 
    /// If value of this property is set to 0, any number of consecutive lines can end with hyphens.
    /// 
    /// The property does not have effect when saving to fixed page formats e.g. PDF.
    ASPOSE_WORDS_SHARED_API int32_t get_ConsecutiveHyphenLimit() const;
    /// Setter for Aspose::Words::Settings::HyphenationOptions::get_ConsecutiveHyphenLimit
    ASPOSE_WORDS_SHARED_API void set_ConsecutiveHyphenLimit(int32_t value);
    /// Gets the distance in 1/20 of a point from the right margin within which you do not want
    /// to hyphenate words.
    /// Default value for this property is 360 (0.25 inch).
    ASPOSE_WORDS_SHARED_API int32_t get_HyphenationZone() const;
    /// Sets the distance in 1/20 of a point from the right margin within which you do not want
    /// to hyphenate words.
    /// Default value for this property is 360 (0.25 inch).
    ASPOSE_WORDS_SHARED_API void set_HyphenationZone(int32_t value);
    /// Gets value determining whether words written in all capital letters are hyphenated.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_HyphenateCaps() const;
    /// Sets value determining whether words written in all capital letters are hyphenated.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_HyphenateCaps(bool value);

    ASPOSE_WORDS_SHARED_API HyphenationOptions();

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;

protected:

};

}
}
}
