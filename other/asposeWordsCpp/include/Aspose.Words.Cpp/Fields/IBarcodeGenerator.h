//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IBarcodeGenerator.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class BarcodeParameters;
}
}
}
namespace System
{
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IBarcodeGenerator
/// Public interface for barcode custom generator. Implementation should be provided by user.
class ASPOSE_WORDS_SHARED_CLASS IBarcodeGenerator : public virtual System::Object
{
    typedef IBarcodeGenerator ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Generate barcode image using the set of parameters (for DisplayBarcode field).
    /// 
    /// @param parameters The set of parameters
    /// 
    /// @return Stream with image data representing generated barcode.
    virtual System::SharedPtr<System::IO::Stream> GetBarcodeImage(System::SharedPtr<Aspose::Words::Fields::BarcodeParameters> parameters) = 0;
    /// Generate barcode image using the set of parameters (for old-fashioned Barcode field).
    /// 
    /// @param parameters The set of parameters
    /// 
    /// @return Stream with image data representing generated barcode.
    virtual System::SharedPtr<System::IO::Stream> GetOldBarcodeImage(System::SharedPtr<Aspose::Words::Fields::BarcodeParameters> parameters) = 0;

};

}
}
}
