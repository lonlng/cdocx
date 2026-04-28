//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/OleControl.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Ole/Core/IEmbeddedObject.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Ss
{
class MemoryStorage;
}
namespace Words
{
namespace Drawing
{
namespace Core
{
class OleObject;

}

}

class IShapeAttrSource;
namespace RW
{
namespace Ole
{
namespace Ole2
{
class ClipboardFormat;
}
}
}

}
}
namespace System
{
namespace IO
{
class BinaryReader;
class BinaryWriter;
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Ole {

/// Represents OLE ActiveX control.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-ole-objects/">Working with Ole Objects</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS OleControl : public Aspose::Words::Drawing::Ole::Core::IEmbeddedObject
{
    typedef OleControl ThisType;
    typedef Aspose::Words::Drawing::Ole::Core::IEmbeddedObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets name of the ActiveX control.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Sets name of the ActiveX control.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Returns <c>%true</c> if the control is a <see cref="Aspose::Words::Drawing::Ole::Forms2OleControl">Forms2OleControl</see>.
    ASPOSE_WORDS_SHARED_API bool get_IsForms2OleControl();

protected:

    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RW::Ole::Ole2::ClipboardFormat> get_ClipboardFormat();
    virtual ASPOSE_WORDS_SHARED_API System::String get_ClsidVirtual();
    virtual ASPOSE_WORDS_SHARED_API System::String get_UserType();
    virtual ASPOSE_WORDS_SHARED_API System::String get_ProgId();

    virtual ASPOSE_WORDS_SHARED_API void Read(System::SharedPtr<Aspose::Ss::MemoryStorage> );
    virtual ASPOSE_WORDS_SHARED_API void Read(System::SharedPtr<System::IO::BinaryReader> );
    virtual ASPOSE_WORDS_SHARED_API uint32_t Write(System::SharedPtr<System::IO::BinaryWriter> );
    virtual ASPOSE_WORDS_SHARED_API void Write(System::SharedPtr<Aspose::Ss::MemoryStorage> );

private:

    bool get_IsForms2OleControlInternal() override;
    System::String get_ClsidInternal() override;
    int32_t get_Id() override;
    void set_Id(int32_t ) override;
    bool get_IsEmpty() override;

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;

    System::String GetName() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::OleObject> GetOleObject() override;
    System::String GetExtensionForUser(System::String ) override;
    System::String GetFileNameForUser() override;
    void SaveForUser(System::SharedPtr<System::IO::Stream> , System::SharedPtr<Aspose::Words::IShapeAttrSource> ) override;

};

}
}
}
}
