//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldHyperlink.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldResultFormatProvider.h>
#include <Aspose.Words.Cpp/Fields/IFieldResultFormatApplier.h>
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
class Inline;

class NodeRange;

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the HYPERLINK field
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldHyperlink : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IFieldResultFormatProvider
{
    typedef FieldHyperlink ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IFieldResultFormatProvider BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the target to which the link should be redirected.
    ASPOSE_WORDS_SHARED_API System::String get_Target();
    /// Sets the target to which the link should be redirected.
    ASPOSE_WORDS_SHARED_API void set_Target(const System::String& value);
    /// Gets a location where this hyperlink jumps.
    ASPOSE_WORDS_SHARED_API System::String get_Address();
    /// Sets a location where this hyperlink jumps.
    ASPOSE_WORDS_SHARED_API void set_Address(const System::String& value);
    /// Gets a location in the file, such as a bookmark, where this hyperlink jumps.
    ASPOSE_WORDS_SHARED_API System::String get_SubAddress();
    /// Sets a location in the file, such as a bookmark, where this hyperlink jumps.
    ASPOSE_WORDS_SHARED_API void set_SubAddress(const System::String& value);
    /// Gets whether to append coordinates to the hyperlink for a server-side image map.
    ASPOSE_WORDS_SHARED_API bool get_IsImageMap();
    /// Sets whether to append coordinates to the hyperlink for a server-side image map.
    ASPOSE_WORDS_SHARED_API void set_IsImageMap(bool value);
    /// Gets whether to open the destination site in a new web browser window.
    ASPOSE_WORDS_SHARED_API bool get_OpenInNewWindow();
    /// Sets whether to open the destination site in a new web browser window.
    ASPOSE_WORDS_SHARED_API void set_OpenInNewWindow(bool value);
    /// Gets the ScreenTip text for the hyperlink.
    ASPOSE_WORDS_SHARED_API System::String get_ScreenTip();
    /// Sets the ScreenTip text for the hyperlink.
    ASPOSE_WORDS_SHARED_API void set_ScreenTip(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;
    ASPOSE_WORDS_SHARED_API void BeforeUnlink() override;
    ASPOSE_WORDS_SHARED_API bool NeedStoreOldResultNodes() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldHyperlink();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;
    System::SharedPtr<Aspose::Words::Inline> GetSourceNode() override;
    System::SharedPtr<Aspose::Words::Fields::IFieldResultFormatApplier> GetFormatApplier() override;

protected:

};

}
}
}
