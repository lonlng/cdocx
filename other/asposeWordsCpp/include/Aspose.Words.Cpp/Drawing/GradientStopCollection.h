//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/GradientStopCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{

class GradientStop;
}
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;

}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Contains a collection of <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-graphic-elements/">Working with Graphic Elements</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS GradientStopCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::GradientStop>>
{
    typedef GradientStopCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::GradientStop>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets an integer value indicating the number of items in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or sets a <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> object in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::GradientStop> idx_get(int32_t index);
    /// Gets or sets a <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> object in the collection.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, const System::SharedPtr<Aspose::Words::Drawing::GradientStop>& value);

    /// Inserts a <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> to the collection at a specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::GradientStop> Insert(int32_t index, const System::SharedPtr<Aspose::Words::Drawing::GradientStop>& gradientStop);
    /// Adds a specified <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> to a gradient.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::GradientStop> Add(const System::SharedPtr<Aspose::Words::Drawing::GradientStop>& gradientStop);
    /// Removes a <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> from the collection at a specified index.
    /// 
    /// @return Removed <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::GradientStop> RemoveAt(int32_t index);
    /// Removes a specified <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> from the collection.
    /// 
    /// @return <c>%true</c> if gradient stop was successfully removed, otherwise <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Remove(const System::SharedPtr<Aspose::Words::Drawing::GradientStop>& gradientStop);
    /// Returns an enumerator that iterates through the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Drawing::GradientStop>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~GradientStopCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::WeakPtr<System::Object> mField2;

};

}
}
}
