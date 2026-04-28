//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldUpdateCultureProvider.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class Field;
}
}
}
namespace System
{
namespace Globalization
{
class CultureInfo;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IFieldUpdateCultureProvider
/// When implemented, provides a <see cref="System::Globalization::CultureInfo">CultureInfo</see> object that should be used during the update of a particular field.
class ASPOSE_WORDS_SHARED_CLASS IFieldUpdateCultureProvider : public virtual System::Object
{
    typedef IFieldUpdateCultureProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns a <see cref="System::Globalization::CultureInfo">CultureInfo</see> object to be used during the field's update.
    /// 
    /// @param culture The name of the culture requested for the field being updated.
    /// @param field The field being updated.
    /// 
    /// @return The culture object that should be used for the field's update.
    virtual System::SharedPtr<System::Globalization::CultureInfo> GetCulture(System::String culture, System::SharedPtr<Aspose::Words::Fields::Field> field) = 0;

};

}
}
}
