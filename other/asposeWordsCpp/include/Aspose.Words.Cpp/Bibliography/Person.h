//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/Person.h
#pragma once

#include <system/object_ext.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Bibliography {

/// Represents individual (a person) bibliography source contributor.
class ASPOSE_WORDS_SHARED_CLASS Person final : public System::Object
{
    typedef Person ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the last name of a person.
    ASPOSE_WORDS_SHARED_API System::String get_Last() const;
    /// Sets the last name of a person.
    ASPOSE_WORDS_SHARED_API void set_Last(const System::String& value);
    /// Gets the first name of a person.
    ASPOSE_WORDS_SHARED_API System::String get_First() const;
    /// Sets the first name of a person.
    ASPOSE_WORDS_SHARED_API void set_First(const System::String& value);
    /// Gets the middle name of a person.
    ASPOSE_WORDS_SHARED_API System::String get_Middle() const;
    /// Sets the middle name of a person.
    ASPOSE_WORDS_SHARED_API void set_Middle(const System::String& value);

    /// Initialize a new instance of the <see cref="Aspose::Words::Bibliography::Person">Person</see> class.
    /// 
    /// @param last The last name.
    /// @param first The last name.
    /// @param middle The last name.
    ASPOSE_WORDS_SHARED_API Person(const System::String& last, const System::String& first, const System::String& middle);

    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Person();

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;

};

}
}
}
