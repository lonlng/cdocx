//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/SoftEdgeFormat.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents the soft edge formatting for an object.
/// 
/// Use the <see cref="Aspose::Words::Drawing::ShapeBase::get_SoftEdge">SoftEdge</see> property to access soft edge properties of an object.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::SoftEdgeFormat">SoftEdgeFormat</see> class directly.
class ASPOSE_WORDS_SHARED_CLASS SoftEdgeFormat : public System::Object
{
    typedef SoftEdgeFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a double value that represents the length of the radius for a soft edge effect in points (pt).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Radius();
    /// Sets a double value that represents the length of the radius for a soft edge effect in points (pt).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Radius(double value);

    /// Removes <see cref="Aspose::Words::Drawing::SoftEdgeFormat">SoftEdgeFormat</see> from the parent object.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
