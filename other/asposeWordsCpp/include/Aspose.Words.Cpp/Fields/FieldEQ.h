//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldEQ.h
#pragma once

#include <system/shared_ptr.h>
#include <system/idisposable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Math
{
class OfficeMath;
}
class Node;

class NodeRange;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class ICollection;
template <typename> class IList;
template <typename> class List;
}
}
class String;
namespace Text
{

class StringBuilder;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the EQ field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldEQ : public Aspose::Words::Fields::Field
{
    typedef FieldEQ ThisType;
    typedef Aspose::Words::Fields::Field BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns Office Math object corresponded to the EQ field.
    /// 
    /// @return Returns <c>%null</c> if field code is empty or invalid, otherwise an <see cref="Aspose::Words::Math::OfficeMath">OfficeMath</see> instance.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Math::OfficeMath> AsOfficeMath();

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldEQ();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
