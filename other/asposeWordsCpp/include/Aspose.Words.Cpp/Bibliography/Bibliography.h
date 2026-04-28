//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/Bibliography.h
#pragma once

#include <system/string.h>
#include <mutex>
#include <memory>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Bibliography
{
class Bibliography;

class Source;
}

}

}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class IList;
}
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Bibliography {

/// Represents the list of bibliography sources available in the document.
class ASPOSE_WORDS_SHARED_CLASS Bibliography final : public System::Object
{
    typedef Bibliography ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets a string that represents the name of the active style to use for a bibliography.
    ASPOSE_WORDS_SHARED_API System::String get_BibliographyStyle() const;
    /// Sets a string that represents the name of the active style to use for a bibliography.
    ASPOSE_WORDS_SHARED_API void set_BibliographyStyle(const System::String& value);
    /// Gets a collection that represents all the sources contained in a bibliography.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::Bibliography::Source>>>& get_Sources() const;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Bibliography();

private:

    System::String mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<1,1,1,1>::type mField4;
    System::SharedPtr<System::Object> mField5;
    System::String mField6;
    __TypeStub<4,4,4,4>::type mField7;
    System::SharedPtr<System::Object> mField8;

};

}
}
}
