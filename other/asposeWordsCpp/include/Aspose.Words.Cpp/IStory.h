//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IStory.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/StoryType.h>

namespace Aspose
{
namespace Words
{
class Paragraph;
class ParagraphCollection;
namespace Tables
{
class TableCollection;
}
}
}

namespace Aspose {

namespace Words {

/// \cond
class IStory : public virtual System::Object
{
    typedef IStory ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::StoryType get_StoryType() = 0;
    virtual System::SharedPtr<Aspose::Words::Paragraph> get_FirstParagraph() = 0;
    virtual System::SharedPtr<Aspose::Words::Paragraph> get_LastParagraph() = 0;
    virtual System::SharedPtr<Aspose::Words::ParagraphCollection> get_Paragraphs() = 0;
    virtual System::SharedPtr<Aspose::Words::Tables::TableCollection> get_Tables() = 0;

};/// \endcond

}
}
