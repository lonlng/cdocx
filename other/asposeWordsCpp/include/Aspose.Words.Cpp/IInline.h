//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IInline.h
#pragma once

#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/RunPrExpandFlags.h>
#include <Aspose.Words.Cpp/IRunAttrSource.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class Paragraph;
class RunPr;
}
}

namespace Aspose {

namespace Words {

/// \cond
class IInline : public Aspose::Words::IRunAttrSource
{
    typedef IInline ThisType;
    typedef Aspose::Words::IRunAttrSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Paragraph> get_ParentParagraph_IInline() = 0;
    virtual System::SharedPtr<Aspose::Words::DocumentBase> get_Document_IInline() = 0;
    virtual System::SharedPtr<Aspose::Words::RunPr> get_RunPr_IInline() = 0;
    virtual void set_RunPr_IInline(System::SharedPtr<Aspose::Words::RunPr> value) = 0;

    virtual System::SharedPtr<Aspose::Words::RunPr> GetExpandedRunPr_IInline(Aspose::Words::RunPrExpandFlags flags) = 0;

};/// \endcond

}
}
