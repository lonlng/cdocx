//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/EditableRange.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/EditorType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class EditableRangeEnd;
class EditableRangeStart;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// Represents a single editable range.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// <see cref="Aspose::Words::EditableRange">EditableRange</see> is a "facade" object that encapsulates two nodes <see cref="Aspose::Words::EditableRange::get_EditableRangeStart">EditableRangeStart</see>
/// and <see cref="Aspose::Words::EditableRange::get_EditableRangeEnd">EditableRangeEnd</see> in a document tree and allows to work with an editable range as a single object.
class ASPOSE_WORDS_SHARED_CLASS EditableRange : public System::Object
{
    typedef EditableRange ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the editable range identifier.
    /// 
    /// The region must be demarcated using the <see cref="Aspose::Words::EditableRange::get_EditableRangeStart">EditableRangeStart</see> and <see cref="Aspose::Words::EditableRange::get_EditableRangeEnd">EditableRangeEnd</see>
    /// 
    /// Editable range identifiers are supposed to be unique across a document and %Aspose.Words automatically
    /// maintains editable range identifiers when loading, saving and combining documents.
    ASPOSE_WORDS_SHARED_API int32_t get_Id();
    /// Returns or sets the single user for editable range.
    /// 
    /// This editor can be stored in one of the following forms:
    /// 
    /// DOMAIN\\Username - for users whose access shall be authenticated using the current user's domain credentials.
    /// 
    /// user\@domain.com - for users whose access shall be authenticated using the user's e-mail address as credentials.
    /// 
    /// user - for users whose access shall be authenticated using the current user's machine credentials.
    /// 
    /// Single user and editor group cannot be set simultaneously for the specific editable range,
    /// if the one is set, the other will be clear.
    ASPOSE_WORDS_SHARED_API System::String get_SingleUser();
    /// Setter for Aspose::Words::EditableRange::get_SingleUser
    ASPOSE_WORDS_SHARED_API void set_SingleUser(const System::String& value);
    /// Returns or sets an alias (or editing group) which shall be used to determine if the current user
    /// shall be allowed to edit this editable range.
    /// 
    /// Single user and editor group cannot be set simultaneously for the specific editable range,
    /// if the one is set, the other will be clear.
    ASPOSE_WORDS_SHARED_API Aspose::Words::EditorType get_EditorGroup();
    /// Setter for Aspose::Words::EditableRange::get_EditorGroup
    ASPOSE_WORDS_SHARED_API void set_EditorGroup(Aspose::Words::EditorType value);
    /// Gets the node that represents the start of the editable range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::EditableRangeStart> get_EditableRangeStart() const;
    /// Gets the node that represents the end of the editable range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::EditableRangeEnd> get_EditableRangeEnd();

    /// Removes the editable range from the document. Does not remove content inside the editable range.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
