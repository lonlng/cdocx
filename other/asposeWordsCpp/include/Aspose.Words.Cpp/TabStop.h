//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TabStop.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/TabLeader.h>
#include <Aspose.Words.Cpp/TabAlignment.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Represents a single custom tab stop. The <see cref="Aspose::Words::TabStop">TabStop</see> object is a member of the
/// <see cref="Aspose::Words::TabStopCollection">TabStopCollection</see> collection.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// Normally, a tab stop specifies a position where a tab stop exists. But because
/// tab stops can be inherited from parent styles, it might be needed for the child object
/// to define explicitly that there is no tab stop at a given position. To clear
/// an inherited tab stop at a given position, create a <see cref="Aspose::Words::TabStop">TabStop</see> object and set
/// <see cref="Aspose::Words::TabStop::get_Alignment">Alignment</see> to <see cref="Aspose::Words::TabAlignment::Clear">Clear</see>.
/// 
/// For more information see <see cref="Aspose::Words::TabStopCollection">TabStopCollection</see>.
/// 
/// @sa Aspose::Words::ParagraphFormat
/// @sa Aspose::Words::TabStopCollection
/// @sa Aspose::Words::Document::get_DefaultTabStop
class ASPOSE_WORDS_SHARED_CLASS TabStop final : public System::Object
{
    typedef TabStop ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using System::Object::Equals;

public:

    /// Gets the position of the tab stop in points.
    ASPOSE_WORDS_SHARED_API double get_Position();
    /// Gets the alignment of text at this tab stop.
    ASPOSE_WORDS_SHARED_API Aspose::Words::TabAlignment get_Alignment() const;
    /// Sets the alignment of text at this tab stop.
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::TabAlignment value);
    /// Gets the type of the leader line displayed under the tab character.
    ASPOSE_WORDS_SHARED_API Aspose::Words::TabLeader get_Leader() const;
    /// Sets the type of the leader line displayed under the tab character.
    ASPOSE_WORDS_SHARED_API void set_Leader(Aspose::Words::TabLeader value);
    /// Returns <c>%true</c> if this tab stop clears any existing tab stops in this position.
    ASPOSE_WORDS_SHARED_API bool get_IsClear();

    /// Initializes a new instance of this class.
    ASPOSE_WORDS_SHARED_API TabStop(double position);
    /// Initializes a new instance of this class.
    /// 
    /// @param position The position of the tab stop in points.
    /// @param alignment A <see cref="Aspose::Words::TabAlignment">TabAlignment</see> value that
    ///     specifies the alignment of text at this tab stop.
    /// @param leader A <see cref="Aspose::Words::TabLeader">TabLeader</see> value that specifies
    ///     the type of the leader line displayed under the tab character.
    ASPOSE_WORDS_SHARED_API TabStop(double position, Aspose::Words::TabAlignment alignment, Aspose::Words::TabLeader leader);

    /// Compares with the specified <see cref="Aspose::Words::TabStop">TabStop</see>.
    ASPOSE_WORDS_SHARED_API bool Equals(const System::SharedPtr<Aspose::Words::TabStop>& rhs);
    /// Calculates hash code for this object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;

protected:

    TabStop();

private:

    __TypeStub<1,1,1,1>::type mField0;

    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;

};

}
}
