//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IBibliographyStylesProvider.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IBibliographyStylesProvider
/// Implement this interface to provide bibliography style for
/// the  <see cref="Aspose::Words::Fields::FieldBibliography">FieldBibliography</see> and <see cref="Aspose::Words::Fields::FieldCitation">FieldCitation</see> fields when they're updated.
class ASPOSE_WORDS_SHARED_CLASS IBibliographyStylesProvider : public virtual System::Object
{
    typedef IBibliographyStylesProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns bibliography style.
    /// 
    /// @param styleFileName The bibliography style file name.
    /// 
    /// @return The <see cref="System::IO::Stream">Stream</see> with bibliography style XSLT stylesheet.
    virtual System::SharedPtr<System::IO::Stream> GetStyle(System::String styleFileName) = 0;

};

}
}
}
