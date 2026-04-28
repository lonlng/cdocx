//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisScaling.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/Drawing/Core/Dml/IDmlExtensionListSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/AxisScaleType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

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
namespace Charts
{
class AxisBound;

}
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

namespace Charts {

/// Represents the scaling options of the axis.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS AxisScaling : public Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource
{
    typedef AxisScaling ThisType;
    typedef Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets scaling type of the axis.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::AxisScaleType get_Type() const;
    /// Sets scaling type of the axis.
    ASPOSE_WORDS_SHARED_API void set_Type(Aspose::Words::Drawing::Charts::AxisScaleType value);
    /// Gets or sets the logarithmic base for a logarithmic axis.
    /// 
    /// The property is not supported by MS Office 2016 new charts.
    /// 
    /// Valid range of a floating point value is greater than or equal to 2 and less than or
    /// equal to 1000. The property has effect only if <see cref="Aspose::Words::Drawing::Charts::AxisScaling::get_Type">Type</see> is set to
    /// <see cref="Aspose::Words::Drawing::Charts::AxisScaleType::Logarithmic">Logarithmic</see>.
    /// 
    /// Setting this property sets the <see cref="Aspose::Words::Drawing::Charts::AxisScaling::get_Type">Type</see> property to <see cref="Aspose::Words::Drawing::Charts::AxisScaleType::Logarithmic">Logarithmic</see>.
    ASPOSE_WORDS_SHARED_API double get_LogBase() const;
    /// Setter for Aspose::Words::Drawing::Charts::AxisScaling::get_LogBase
    ASPOSE_WORDS_SHARED_API void set_LogBase(double value);
    /// Gets minimum value of the axis.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::AxisBound> get_Minimum();
    /// Sets minimum value of the axis.
    ASPOSE_WORDS_SHARED_API void set_Minimum(const System::SharedPtr<Aspose::Words::Drawing::Charts::AxisBound>& value);
    /// Gets the maximum value of the axis.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::AxisBound> get_Maximum();
    /// Sets the maximum value of the axis.
    ASPOSE_WORDS_SHARED_API void set_Maximum(const System::SharedPtr<Aspose::Words::Drawing::Charts::AxisBound>& value);

    ASPOSE_WORDS_SHARED_API AxisScaling();

protected:

private:

    System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> get_Extensions() override;
    void set_Extensions(System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> ) override;

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<8,8,8,8>::type mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    __TypeStub<4,4,4,4>::type mField5;
    System::SharedPtr<System::Object> mField6;

};

}
}
}
}
