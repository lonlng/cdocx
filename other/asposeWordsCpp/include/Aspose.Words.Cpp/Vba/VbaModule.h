//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Vba/VbaModule.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Vba/VbaModuleType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace IO
{
class MemoryStream;
}
namespace Text
{
class Encoding;
}
}

namespace Aspose {

namespace Words {

namespace Vba {

/// Provides access to VBA project module.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-vba-macros/">Working with VBA Macros</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS VbaModule : public System::Object
{
    typedef VbaModule ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets VBA project module name.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Sets VBA project module name.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Gets VBA project module source code.
    ASPOSE_WORDS_SHARED_API System::String get_SourceCode() const;
    /// Sets VBA project module source code.
    ASPOSE_WORDS_SHARED_API void set_SourceCode(const System::String& value);
    /// Specifies whether the module is a procedural module, document module, class module, or designer module.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Vba::VbaModuleType get_Type() const;
    /// Specifies whether the module is a procedural module, document module, class module, or designer module.
    ASPOSE_WORDS_SHARED_API void set_Type(Aspose::Words::Vba::VbaModuleType value);

    /// Creates an empty module.
    ASPOSE_WORDS_SHARED_API VbaModule();

    /// Performs a copy of the <see cref="Aspose::Words::Vba::VbaModule">VbaModule</see>.
    /// 
    /// @return The cloned <see cref="Aspose::Words::Vba::VbaModule">VbaModule</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Vba::VbaModule> Clone();

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::SharedPtr<System::Object> mField5;
    System::WeakPtr<System::Object> mField6;

};

}
}
}
