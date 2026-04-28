//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/GeneralFormatCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/GeneralFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents a typed collection of general formats.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS GeneralFormatCollection : public System::Collections::Generic::IEnumerable<Aspose::Words::Fields::GeneralFormat>
{
    typedef GeneralFormatCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<Aspose::Words::Fields::GeneralFormat> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the total number of the items in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Adds a general format to the collection.
    /// 
    /// @param item A general format.
    ASPOSE_WORDS_SHARED_API void Add(Aspose::Words::Fields::GeneralFormat item);
    /// Removes all occurrences of the specified general format from the collection.
    /// 
    /// @param item A general format.
    ASPOSE_WORDS_SHARED_API void Remove(Aspose::Words::Fields::GeneralFormat item);
    /// Removes a general format occurrence at the specified index.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);

    /// Gets a general format at the specified index.
    /// 
    /// @param index The index of a general format.
    /// 
    /// @return A general format.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::GeneralFormat idx_get(int32_t index);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<Aspose::Words::Fields::GeneralFormat>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~GeneralFormatCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
