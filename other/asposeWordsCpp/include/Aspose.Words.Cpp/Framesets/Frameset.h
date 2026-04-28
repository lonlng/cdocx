//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Framesets/Frameset.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Framesets
{

class FramesetCollection;
}

}
}

namespace Aspose {

namespace Words {

namespace Framesets {

/// Represents a frames page or a single frame on a frames page.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Frameset : public System::Object
{
    typedef Frameset ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the web page URL or document file name to display in this frame.
    ASPOSE_WORDS_SHARED_API System::String get_FrameDefaultUrl();
    /// Sets the web page URL or document file name to display in this frame.
    ASPOSE_WORDS_SHARED_API void set_FrameDefaultUrl(const System::String& value);
    /// Gets a value indicating whether the web page or document file name specified in the
    /// <see cref="Aspose::Words::Framesets::Frameset::get_FrameDefaultUrl">FrameDefaultUrl</see> property is an external resource the frame is linked with.
    ASPOSE_WORDS_SHARED_API bool get_IsFrameLinkToFile();
    /// Sets a value indicating whether the web page or document file name specified in the
    /// <see cref="Aspose::Words::Framesets::Frameset::get_FrameDefaultUrl">FrameDefaultUrl</see> property is an external resource the frame is linked with.
    ASPOSE_WORDS_SHARED_API void set_IsFrameLinkToFile(bool value);
    /// Gets the collection of child frames and frames pages.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Framesets::FramesetCollection> get_ChildFramesets() const;

    ASPOSE_WORDS_SHARED_API Frameset();

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    __TypeStub<1,1,1,1>::type mField9;
    __TypeStub<4,4,4,4>::type mField10;
    __TypeStub<4,4,4,4>::type mField11;
    System::SharedPtr<System::Object> mField12;
    System::SharedPtr<System::Object> mField13;
    __TypeStub<4,4,4,4>::type mField14;
    __TypeStub<4,4,4,4>::type mField15;

};

}
}
}
