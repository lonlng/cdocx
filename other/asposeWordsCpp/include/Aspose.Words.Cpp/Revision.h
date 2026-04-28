//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Revision.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/RevisionType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class Node;

class RevisionGroup;

class Style;
}
}
namespace System
{
class DateTime;
class String;
}

namespace Aspose {

namespace Words {

/// Represents a revision (tracked change) in a document node or style.
/// Use <see cref="Aspose::Words::Revision::get_RevisionType">RevisionType</see> to check the type of this revision.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/track-changes-in-a-document/">Track Changes in a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Revision : public System::Object
{
    typedef Revision ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the author of this revision. Can not be empty string or <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Author();
    /// Sets the author of this revision. Can not be empty string or <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Author(const System::String& value);
    /// Gets the date/time of this revision.
    ASPOSE_WORDS_SHARED_API System::DateTime get_DateTime();
    /// Sets the date/time of this revision.
    ASPOSE_WORDS_SHARED_API void set_DateTime(System::DateTime value);
    /// Gets the type of this revision.
    ASPOSE_WORDS_SHARED_API Aspose::Words::RevisionType get_RevisionType() const;
    /// Gets the immediate parent node (owner) of this revision.
    /// This property will work for any revision type other than <see cref="Aspose::Words::RevisionType::StyleDefinitionChange">StyleDefinitionChange</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_ParentNode();
    /// Gets the immediate parent style (owner) of this revision.
    /// This property will work for only for the <see cref="Aspose::Words::RevisionType::StyleDefinitionChange">StyleDefinitionChange</see> revision type.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> get_ParentStyle();
    /// Gets the revision group. Returns <c>%null</c> if the revision does not belong to any group.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RevisionGroup> get_Group();

    /// Accepts this revision.
    ASPOSE_WORDS_SHARED_API void Accept();
    /// Reject this revision.
    ASPOSE_WORDS_SHARED_API void Reject();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Revision();

private:

    __TypeStub<4,4,4,4>::type mField0;

    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<1,1,1,1>::type mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
