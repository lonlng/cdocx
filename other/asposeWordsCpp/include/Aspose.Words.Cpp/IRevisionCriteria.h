//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IRevisionCriteria.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Revision;
}
}

namespace Aspose {

namespace Words {

/// \interface IRevisionCriteria
/// Implement this interface if you want to control when certain <see cref="Aspose::Words::Revision">Revision</see> should be accepted/rejected
/// or not by the <see cref="Aspose::Words::RevisionCollection::Accept(System::SharedPtr<Aspose::Words::IRevisionCriteria>)">Accept()</see>/<see cref="Aspose::Words::RevisionCollection::Reject(System::SharedPtr<Aspose::Words::IRevisionCriteria>)">Reject()</see> methods.
class ASPOSE_WORDS_SHARED_CLASS IRevisionCriteria : public virtual System::Object
{
    typedef IRevisionCriteria ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Checks whether or not specified @a revision matches criteria.
    /// 
    /// @param revision The <see cref="Aspose::Words::Revision">Revision</see> instance to match criteria.
    /// 
    /// @return <c>%True</c> if the @a revision matches criteria, otherwise <c>%False</c>.
    virtual bool IsMatch(System::SharedPtr<Aspose::Words::Revision> revision) = 0;

};

}
}
