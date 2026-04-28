//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SpecialChar.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Inline.h>
#include <Aspose.Words.Cpp/NodeType.h>
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

/// Base class for special characters in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// A %Microsoft Word document can include a number of special characters
/// that represent fields, form fields, shapes, OLE objects, footnotes etc. For the list
/// of special characters see <see cref="Aspose::Words::ControlChar">ControlChar</see>.
/// 
/// <see cref="Aspose::Words::SpecialChar">SpecialChar</see> is an inline-node and can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// <see cref="Aspose::Words::SpecialChar">SpecialChar</see> char is used as a base class for more specific classes
/// that represent special characters that %Aspose.Words provides programmatic access for.
/// The <see cref="Aspose::Words::SpecialChar">SpecialChar</see> class is also used itself to represent special character for which
/// %Aspose.Words does not provide detailed programmatic access.
class ASPOSE_WORDS_SHARED_CLASS SpecialChar : public Aspose::Words::Inline
{
    typedef SpecialChar ThisType;
    typedef Aspose::Words::Inline BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::SpecialChar">SpecialChar</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitSpecialChar(System::SharedPtr<Aspose::Words::SpecialChar>)">VisitSpecialChar()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Gets the special character that this node represents.
    /// 
    /// @return The string that contains the character that this node represents.
    ASPOSE_WORDS_SHARED_API System::String GetText() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~SpecialChar();

private:

    __TypeStub<2,2,2,2>::type mField0;
    System::String mField1;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
