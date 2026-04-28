//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/RevisionCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/IRevisionCriteria.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class Revision;

class RevisionGroupCollection;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class List;
}
}
class String;
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::Revision">Revision</see> objects that represent revisions in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/track-changes-in-a-document/">Track Changes in a Document</a> documentation article.
/// 
/// You do not create instances of this class directly. Use the <see cref="Aspose::Words::Document::get_Revisions">Revisions</see> property to get revisions present in a document.
class ASPOSE_WORDS_SHARED_CLASS RevisionCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Revision>>
{
    typedef RevisionCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Revision>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of revisions in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();
    /// Collection of revision groups.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RevisionGroupCollection> get_Groups();

    /// Accepts all revisions in this collection.
    ASPOSE_WORDS_SHARED_API void AcceptAll();
    /// Rejects all revisions in this collection.
    ASPOSE_WORDS_SHARED_API void RejectAll();
    /// Accepts revisions that match specified criteria.
    /// 
    /// @param criteria The <see cref="Aspose::Words::IRevisionCriteria">IRevisionCriteria</see> implementation.
    /// 
    /// @return The count of accepted revisions.
    ASPOSE_WORDS_SHARED_API int32_t Accept(const System::SharedPtr<Aspose::Words::IRevisionCriteria>& criteria);
    /// Rejects revisions that match specified criteria.
    /// 
    /// @param criteria The <see cref="Aspose::Words::IRevisionCriteria">IRevisionCriteria</see> implementation.
    /// 
    /// @return The count of rejected revisions.
    ASPOSE_WORDS_SHARED_API int32_t Reject(const System::SharedPtr<Aspose::Words::IRevisionCriteria>& criteria);

    /// Returns a <see cref="Aspose::Words::Revision">Revision</see> at the specified index.
    /// 
    /// The index is zero-based.
    /// 
    /// Negative indexes are allowed and indicate access from the back of the collection.
    /// For example -1 means the last item, -2 means the second before last and so on.
    /// 
    /// If index is greater than or equal to the number of items in the list, this returns a null reference.
    /// 
    /// If index is negative and its absolute value is greater than the number of items in the list, this returns a null reference.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Revision> idx_get(int32_t index);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Revision>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~RevisionCollection();

private:

    __TypeStub<4,4,4,4>::type mField0;

    __TypeStub<4,4,4,4>::type mField1;
    System::WeakPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;

};

}
}
