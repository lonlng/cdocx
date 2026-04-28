//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/OlePackage.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Allows to access OLE Package properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-ole-objects/">Working with Ole Objects</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS OlePackage : public System::Object
{
    typedef OlePackage ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets OLE Package file name.
    ASPOSE_WORDS_SHARED_API System::String get_FileName() const;
    /// Sets OLE Package file name.
    ASPOSE_WORDS_SHARED_API void set_FileName(System::String value);
    /// Gets OLE Package display name.
    ASPOSE_WORDS_SHARED_API System::String get_DisplayName() const;
    /// Sets OLE Package display name.
    ASPOSE_WORDS_SHARED_API void set_DisplayName(System::String value);

protected:

    System::String mField0;
    System::SharedPtr<System::Object> mField1;

    OlePackage();

private:

    System::String mField2;
    System::String mField3;
    System::SharedPtr<System::Object> mField4;

protected:

};

}
}
}
