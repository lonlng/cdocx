//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ReflectionFormat.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents the reflection formatting for an object.
/// 
/// Use the <see cref="Aspose::Words::Drawing::ShapeBase::get_Reflection">Reflection</see> property to access reflection properties of an object.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::ReflectionFormat">ReflectionFormat</see> class directly.
class ASPOSE_WORDS_SHARED_CLASS ReflectionFormat : public System::Object
{
    typedef ReflectionFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a double value that specifies the degree of blur effect applied to the reflection effect in points.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Blur();
    /// Sets a double value that specifies the degree of blur effect applied to the reflection effect in points.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Blur(double value);
    /// Gets a double value that specifies the amount of separation of the reflected image from the object in points.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Distance();
    /// Sets a double value that specifies the amount of separation of the reflected image from the object in points.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Distance(double value);
    /// Gets a double value between 0.0 and 1.0 representing the size of the reflection
    /// as a percentage of the reflected object.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Size();
    /// Sets a double value between 0.0 and 1.0 representing the size of the reflection
    /// as a percentage of the reflected object.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Size(double value);
    /// Gets a double value between 0.0 (opaque) and 1.0 (clear) representing the degree
    /// of transparency for the reflection effect.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Transparency();
    /// Sets a double value between 0.0 (opaque) and 1.0 (clear) representing the degree
    /// of transparency for the reflection effect.
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Transparency(double value);

    /// Removes <see cref="Aspose::Words::Drawing::ReflectionFormat">ReflectionFormat</see> from the parent object.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
