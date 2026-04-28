//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LocaleDefaults.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace System
{
namespace Drawing
{
class Size;
}
}

namespace Aspose {

namespace Words {

/// \cond
class LocaleDefaults
{
    typedef LocaleDefaults ThisType;

public:

    class Margins : public System::Object
    {
        typedef Margins ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        int32_t get_Left() const;
        int32_t get_Right() const;
        int32_t get_Top() const;
        int32_t get_Bottom() const;

        Margins(int32_t left, int32_t right, int32_t top, int32_t bottom);

    private:

        __TypeStub<4,4,4,4>::type mField0;
        __TypeStub<4,4,4,4>::type mField1;
        __TypeStub<4,4,4,4>::type mField2;
        __TypeStub<4,4,4,4>::type mField3;

    };

public:

    static System::SharedPtr<Aspose::Words::LocaleDefaults::Margins> GetPageMargins(int32_t lcid);
    static int32_t GetHeaderFooterDistance(int32_t lcid);
    static int32_t GetSpaceBetweenColumns(int32_t lcid);
    static System::Drawing::Size GetPageSize(int32_t lcid);

private:

private:

public:
    LocaleDefaults() = delete;
};/// \endcond

}
}
