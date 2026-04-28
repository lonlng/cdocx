//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/ITocEntry.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose
{
namespace Words
{
class NodeRange;
class Paragraph;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class ITocEntry : public virtual System::Object
{
    typedef ITocEntry ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual int32_t get_Level() = 0;
    virtual bool get_OmitPageNumber() = 0;
    virtual System::SharedPtr<Aspose::Words::Paragraph> get_Paragraph() = 0;
    virtual bool get_IsInFieldCode() = 0;
    virtual bool get_HasBookmark() = 0;
    virtual bool get_IsLinkedStyleTocEntry() = 0;

    virtual System::SharedPtr<Aspose::Words::NodeRange> InsertBookmark(System::String bookmarkName) = 0;
    virtual System::String GetDocumentOutlineTitle() = 0;
    virtual System::SharedPtr<Aspose::Words::NodeRange> GetLabelRange() = 0;
    virtual int32_t GetSequenceValue(System::String sequenceIdentifier) = 0;
    virtual int32_t GetPageNumber() = 0;

};/// \endcond

}
}
}
