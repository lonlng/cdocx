//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ConditionalStyleCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
class ConditionalStyle;
enum class ConditionalStyleType;

}
}

namespace Aspose {

namespace Words {

/// Represents a collection of <see cref="Aspose::Words::ConditionalStyle">ConditionalStyle</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ConditionalStyleCollection final : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::ConditionalStyle>>
{
    typedef ConditionalStyleCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::ConditionalStyle>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the number of conditional styles in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count() const;
    /// Gets the first row style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_FirstRow();
    /// Gets the first column style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_FirstColumn();
    /// Gets the last row style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_LastRow();
    /// Gets the last column style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_LastColumn();
    /// Gets the odd row banding style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_OddRowBanding();
    /// Gets the odd column banding style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_OddColumnBanding();
    /// Gets the even row banding style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_EvenRowBanding();
    /// Gets the even column banding style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_EvenColumnBanding();
    /// Gets the top left cell style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_TopLeftCell();
    /// Gets the top right cell style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_TopRightCell();
    /// Gets the bottom left cell style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_BottomLeftCell();
    /// Gets the bottom right cell style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> get_BottomRightCell();

    /// Clears all conditional styles of the table style.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();
    /// Returns an enumerator object that can be used to iterate over all conditional styles in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::ConditionalStyle>>> GetEnumerator() override;

    /// Retrieves a <see cref="Aspose::Words::ConditionalStyle">ConditionalStyle</see> object by conditional style type.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> idx_get(Aspose::Words::ConditionalStyleType conditionalStyleType);
    /// Retrieves a <see cref="Aspose::Words::ConditionalStyle">ConditionalStyle</see> object by index.
    /// 
    /// @param index Zero-based index of the conditional style to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyle> idx_get(int32_t index);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ConditionalStyleCollection();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
