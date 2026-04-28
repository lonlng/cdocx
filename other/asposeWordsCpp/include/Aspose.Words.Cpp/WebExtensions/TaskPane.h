//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/TaskPane.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/WebExtensions/TaskPaneDockState.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace WebExtensions
{
class WebExtension;
}
}
}

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Represents an add-in task pane object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-office-add-ins/">Work with Office Add-ins</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS TaskPane : public System::Object
{
    typedef TaskPane ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the index, enumerating from the outside to the inside, of this task pane among other persisted
    /// task panes docked in the same default location.
    ASPOSE_WORDS_SHARED_API int32_t get_Row() const;
    /// Specifies the index, enumerating from the outside to the inside, of this task pane among other persisted
    /// task panes docked in the same default location.
    ASPOSE_WORDS_SHARED_API void set_Row(int32_t value);
    /// Specifies the default width value for this task pane instance.
    ASPOSE_WORDS_SHARED_API double get_Width() const;
    /// Specifies the default width value for this task pane instance.
    ASPOSE_WORDS_SHARED_API void set_Width(double value);
    /// Specifies whether the task pane is locked to the document in the UI and cannot be closed by the user.
    ASPOSE_WORDS_SHARED_API bool get_IsLocked() const;
    /// Specifies whether the task pane is locked to the document in the UI and cannot be closed by the user.
    ASPOSE_WORDS_SHARED_API void set_IsLocked(bool value);
    /// Specifies whether the task pane shows as visible by default when the document opens.
    ASPOSE_WORDS_SHARED_API bool get_IsVisible() const;
    /// Specifies whether the task pane shows as visible by default when the document opens.
    ASPOSE_WORDS_SHARED_API void set_IsVisible(bool value);
    /// Specifies the last-docked location of this task pane object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::WebExtensions::TaskPaneDockState get_DockState() const;
    /// Specifies the last-docked location of this task pane object.
    ASPOSE_WORDS_SHARED_API void set_DockState(Aspose::Words::WebExtensions::TaskPaneDockState value);
    /// Represents an web extension object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::WebExtensions::WebExtension> get_WebExtension() const;

    ASPOSE_WORDS_SHARED_API TaskPane();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<8,8,8,8>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
}
