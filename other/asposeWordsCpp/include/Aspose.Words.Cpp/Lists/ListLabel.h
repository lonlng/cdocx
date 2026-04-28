//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListLabel.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/IRunAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class Font;

enum class RevisionsView;

}
}

namespace Aspose {

namespace Words {

namespace Lists {

/// Defines properties specific to a list label.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-lists/">Working with Lists</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ListLabel : public Aspose::Words::IRunAttrSource
{
    typedef ListLabel ThisType;
    typedef Aspose::Words::IRunAttrSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the list label font.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Gets a string representation of list label.
    ASPOSE_WORDS_SHARED_API System::String get_LabelString();
    /// Gets a numeric value for this label.
    ASPOSE_WORDS_SHARED_API int32_t get_LabelValue();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ListLabel();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;

    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedRunAttr(int32_t ) override;
    void SetRunAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveRunAttr(int32_t ) override;
    void ClearRunAttrs() override;

};

}
}
}
