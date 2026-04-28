//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldFileSize.h
#pragma once

#include <Aspose.Words.Cpp/Fields/IFieldInfoResultProvider.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
namespace Fields
{
namespace Expressions
{
class Constant;

}

enum class FieldSwitchType;
class FieldUpdateAction;
class IFieldCode;
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

/// Implements the FILESIZE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// Retrieves the size of the current document's file or 0 if the size cannot be determined.
/// 
/// In the current implementation, uses the <see cref="Aspose::Words::Document::get_OriginalFileName">OriginalFileName</see> property to retrieve
/// the file name used to determine the file size.
class ASPOSE_WORDS_SHARED_CLASS FieldFileSize : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldFileSize ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets whether to display the file size in kilobytes.
    ASPOSE_WORDS_SHARED_API bool get_IsInKilobytes();
    /// Sets whether to display the file size in kilobytes.
    ASPOSE_WORDS_SHARED_API void set_IsInKilobytes(bool value);
    /// Gets whether to display the file size in megabytes.
    ASPOSE_WORDS_SHARED_API bool get_IsInMegabytes();
    /// Sets whether to display the file size in megabytes.
    ASPOSE_WORDS_SHARED_API void set_IsInMegabytes(bool value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldFileSize();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
