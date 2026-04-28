//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/IFootnoteOptions.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Notes/FootnoteLocation.h>
#include <Aspose.Words.Cpp/NumberStyle.h>
#include <Aspose.Words.Cpp/Notes/FootnoteNumberingRule.h>

namespace Aspose {

namespace Words {

namespace Notes {

/// \cond
class IFootnoteOptions : public System::Object
{
    typedef IFootnoteOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::NumberStyle get_NumberStyle() = 0;
    virtual void set_NumberStyle(Aspose::Words::NumberStyle value) = 0;
    virtual Aspose::Words::Notes::FootnoteNumberingRule get_RestartRule() = 0;
    virtual void set_RestartRule(Aspose::Words::Notes::FootnoteNumberingRule value) = 0;
    virtual int32_t get_StartNumber() = 0;
    virtual void set_StartNumber(int32_t value) = 0;
    virtual Aspose::Words::Notes::FootnoteLocation get_Location() = 0;
    virtual void set_Location(Aspose::Words::Notes::FootnoteLocation value) = 0;

};/// \endcond

}
}
}
