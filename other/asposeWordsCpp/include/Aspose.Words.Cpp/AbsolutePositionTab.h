//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AbsolutePositionTab.h
#pragma once

#include <Aspose.Words.Cpp/SpecialChar.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class DocumentBase;
class DocumentVisitor;

class RunPr;

}
}

namespace Aspose {

namespace Words {

/// An absolute position tab is a character which is used to advance the position on
/// the current line of text when displaying this WordprocessingML content.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS AbsolutePositionTab : public Aspose::Words::SpecialChar
{
    typedef AbsolutePositionTab ThisType;
    typedef Aspose::Words::SpecialChar BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitAbsolutePositionTab(System::SharedPtr<Aspose::Words::AbsolutePositionTab>)">VisitAbsolutePositionTab()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~AbsolutePositionTab();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
