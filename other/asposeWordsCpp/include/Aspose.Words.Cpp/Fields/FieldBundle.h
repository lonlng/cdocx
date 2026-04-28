//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldBundle.h
#pragma once

#include <system/object.h>
#include <system/exceptions.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/FieldType.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class Field;
class FieldChar;
class FieldEnd;
class FieldSeparator;
class FieldStart;
}
}
}
namespace System
{
class Details_InvalidOperationException; using InvalidOperationException = System::ExceptionWrapper<Details_InvalidOperationException>;
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class FieldBundle : public System::Object, public System::Details::BoxableObjectBase
{
    typedef FieldBundle ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

private:

public:

    System::SharedPtr<Aspose::Words::Fields::FieldChar> get_FieldCodeEnd();
    Aspose::Words::Fields::FieldType get_FieldType();
    void set_FieldType(Aspose::Words::Fields::FieldType value);
    const System::SharedPtr<Aspose::Words::Fields::FieldStart>& get_Start() const;
    void set_Start(const System::SharedPtr<Aspose::Words::Fields::FieldStart>& value);
    const System::SharedPtr<Aspose::Words::Fields::FieldSeparator>& get_Separator() const;
    void set_Separator(const System::SharedPtr<Aspose::Words::Fields::FieldSeparator>& value);
    bool get_HasSeparator();
    const System::SharedPtr<Aspose::Words::Fields::FieldEnd>& get_End() const;
    void set_End(const System::SharedPtr<Aspose::Words::Fields::FieldEnd>& value);
    bool get_IsLocked();
    void set_IsLocked(bool value);
    bool get_IsDirty();
    void set_IsDirty(bool value);

    FieldBundle(const System::SharedPtr<Aspose::Words::Fields::FieldStart>& start, const System::SharedPtr<Aspose::Words::Fields::FieldSeparator>& separator, const System::SharedPtr<Aspose::Words::Fields::FieldEnd>& end);

    System::String GetFieldCode();
    System::String GetFieldCode(bool includeChildFieldCodes);
    System::SharedPtr<Aspose::Words::Fields::Field> GetField();
    Aspose::Words::Fields::FieldType ParseFieldType();
    void DetermineFieldType();
    void RemoveFieldNodes();
    void UpdateDirtyLocked();
    static Aspose::Words::Fields::FieldBundle GetFieldBundle(const System::SharedPtr<Aspose::Words::Fields::FieldChar>& fieldChar);
    static Aspose::Words::Fields::FieldBundle GetFieldBundleNoSeparatorCheck(const System::SharedPtr<Aspose::Words::Fields::FieldChar>& fieldChar);
    void FillFieldBundleOneWay(const System::SharedPtr<Aspose::Words::Fields::FieldChar>& fieldChar, bool isForward);

    FieldBundle();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

};/// \endcond

}
}
}
