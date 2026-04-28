//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Vba/VbaReference.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Vba/VbaReferenceType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Vba
{

class VbaRecordReader;
class VbaRecordWriter;

}
}
}

namespace Aspose {

namespace Words {

namespace Vba {

/// Implements a reference to an Automation type library or VBA project.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-vba-macros/">Working with VBA Macros</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS VbaReference : public System::Object
{
    typedef VbaReference ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets <see cref="Aspose::Words::Vba::VbaReferenceType">VbaReferenceType</see> object that indicates the type of reference that a <see cref="Aspose::Words::Vba::VbaReference">VbaReference</see> object represents.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Vba::VbaReferenceType get_Type() = 0;
    /// Gets a string value containing the identifier of an Automation type library.
    /// 
    /// Depending on reference type, the value of this property can be:
    /// 
    /// - a LibidReference specified at 2.1.1.8 LibidReference of [MS-OVBA]:
    ///   https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-ovba/3737ef6e-d819-4186-a5f2-6e258ddf66a5
    /// - a ProjectReference specified at 2.1.1.12 ProjectReference of [MS-OVBA]:
    ///   https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-ovba/9a45ac1a-f1ff-4ebd-958e-537701aa8131
    virtual ASPOSE_WORDS_SHARED_API System::String get_LibId() const = 0;

protected:

    virtual void Write(System::SharedPtr<Aspose::Words::Vba::VbaRecordWriter> ) = 0;

    virtual void ReadCore(System::SharedPtr<Aspose::Words::Vba::VbaRecordReader> ) = 0;

private:

    System::String mField0;

    virtual ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const = 0;

};

}
}
}
