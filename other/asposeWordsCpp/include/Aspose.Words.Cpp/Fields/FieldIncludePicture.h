//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldIncludePicture.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldIncludePictureCode.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
enum class FieldSwitchType;
class FieldUpdateAction;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the INCLUDEPICTURE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldIncludePicture : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IFieldIncludePictureCode
{
    typedef FieldIncludePicture ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IFieldIncludePictureCode BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the location of the picture using an IRI.
    ASPOSE_WORDS_SHARED_API System::String get_SourceFullName() override;
    /// Sets the location of the picture using an IRI.
    ASPOSE_WORDS_SHARED_API void set_SourceFullName(const System::String& value);
    /// Gets the name of the filter for the format of the graphic that is to be inserted.
    ASPOSE_WORDS_SHARED_API System::String get_GraphicFilter();
    /// Sets the name of the filter for the format of the graphic that is to be inserted.
    ASPOSE_WORDS_SHARED_API void set_GraphicFilter(const System::String& value);
    /// Gets whether to reduce the file size by not storing graphics data with the document.
    ASPOSE_WORDS_SHARED_API bool get_IsLinked() override;
    /// Sets whether to reduce the file size by not storing graphics data with the document.
    ASPOSE_WORDS_SHARED_API void set_IsLinked(bool value);
    /// Gets whether to resize the picture horizontally from the source.
    ASPOSE_WORDS_SHARED_API bool get_ResizeHorizontally();
    /// Sets whether to resize the picture horizontally from the source.
    ASPOSE_WORDS_SHARED_API void set_ResizeHorizontally(bool value);
    /// Gets whether to resize the picture vertically from the source.
    ASPOSE_WORDS_SHARED_API bool get_ResizeVertically();
    /// Sets whether to resize the picture vertically from the source.
    ASPOSE_WORDS_SHARED_API void set_ResizeVertically(bool value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;
    ASPOSE_WORDS_SHARED_API void BeforeUnlink() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldIncludePicture();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
