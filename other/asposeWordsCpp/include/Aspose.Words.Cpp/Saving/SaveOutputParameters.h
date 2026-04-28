//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/SaveOutputParameters.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// This object is returned to the caller after a document is saved and contains additional information that
/// has been generated or calculated during the save operation. The caller can use or ignore this object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SaveOutputParameters : public System::Object
{
    typedef SaveOutputParameters ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the Content-Type string (Internet Media Type) that identifies the type of the saved document.
    ASPOSE_WORDS_SHARED_API System::String get_ContentType() const;

protected:

private:

    System::String mField0;

};

}
}
}
