//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/Dml/IDmlExtensionListSource.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Collections
{
template <typename> class StringToObjDictionary;
}
namespace Words
{
namespace Drawing
{
namespace Core
{
namespace Dml
{
class DmlExtension;
}
}
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

namespace Dml {

/// \cond
class IDmlExtensionListSource : public virtual System::Object
{
    typedef IDmlExtensionListSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> get_Extensions() = 0;
    virtual void set_Extensions(System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> value) = 0;

};/// \endcond

}
}
}
}
}
