//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFormattableMergeField.h
#pragma once

#include <system/array.h>

namespace Aspose
{
namespace Collections
{
template <typename> class StringToObjDictionary;
}
namespace Words
{
class Document;
namespace Fields
{
class IMergeFormatContext;
class MergeFormatPlaceholder;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFormattableMergeField : public virtual System::Object
{
    typedef IFormattableMergeField ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::String get_MergeFormat() = 0;
    virtual System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::String>> get_PlaceholdersToFieldsMap() = 0;

    virtual System::SharedPtr<Aspose::Words::Document> IFormattableMergeField_FetchDocument() = 0;
    virtual System::String GetPlaceholderValue(System::SharedPtr<Aspose::Words::Fields::IMergeFormatContext> context, System::SharedPtr<Aspose::Words::Fields::MergeFormatPlaceholder> placeholder) = 0;
    virtual System::ArrayPtr<System::String> GetFieldNames() = 0;

};/// \endcond

}
}
}
