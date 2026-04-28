//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListLabelUtil.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/NumberStyle.h>
#include <Aspose.Words.Cpp/RevisionsView.h>

namespace Aspose
{
namespace Words
{
namespace Lists
{

class ListNumberGenerator;
class ListNumberState;
}
class Paragraph;
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
namespace Text
{
class StringBuilder;
}
}

namespace Aspose {

namespace Words {

namespace Lists {

/// \cond
class IListLabelBuildBehaviour : public System::Object
{
    typedef IListLabelBuildBehaviour ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual void NotifyListNumberAppended(int32_t listLabelLength) = 0;
    virtual bool ShouldAppendNotListNumberChar(char16_t c) = 0;
    virtual int32_t FinalizeListLabelLength(int32_t listLabelLength) = 0;
    virtual Aspose::Words::NumberStyle NormalizeNumberStyle(Aspose::Words::NumberStyle numberStyle) = 0;

};/// \endcond

/// \cond
class ListLabelUtil
{
    typedef ListLabelUtil ThisType;

private:

    /// ListLabelAction enumeration.
    enum class ListLabelAction
    {
        Undetermined,
        UpdateAndSet,
        UpdateAndClear,
        Clear
    };

private:

public:

    static bool UpdateParagraphListLabel(const System::SharedPtr<Aspose::Words::Paragraph>& para, const System::SharedPtr<Aspose::Words::Lists::ListNumberGenerator>& generator, Aspose::Words::RevisionsView view);
    static bool IsListLabelVisible(const System::SharedPtr<Aspose::Words::Paragraph>& para, Aspose::Words::RevisionsView view);
    static System::String BuildFullListLabel(const System::SharedPtr<Aspose::Words::Lists::ListNumberState>& state, const System::SharedPtr<Aspose::Words::Lists::IListLabelBuildBehaviour>& behaviour, const System::String& separator);
    static System::String BuildFullListLabel(const System::SharedPtr<Aspose::Words::Lists::ListNumberState>& state, int32_t minLevel, const System::SharedPtr<Aspose::Words::Lists::IListLabelBuildBehaviour>& behaviour, const System::String& separator);
    static System::String BuildListLabel(const System::SharedPtr<Aspose::Words::Lists::ListNumberState>& state, const System::SharedPtr<Aspose::Words::Lists::IListLabelBuildBehaviour>& behaviour);
    static bool HasCounter(Aspose::Words::NumberStyle numberStyle);

private:

public:
    ListLabelUtil() = delete;
};/// \endcond

}
}
}
