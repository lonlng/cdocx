//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/ITocEntryExtractorOptions.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose
{
namespace Words
{
class Bookmark;
namespace Fields
{
class FieldEnd;
class FieldStart;
class LevelRange;
}
class Paragraph;
class Style;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class ITocEntryExtractorOptions : public System::Object
{
    typedef ITocEntryExtractorOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual bool get_IsBookmarkRangeSpecified() = 0;
    virtual bool get_IncludeTocEntryFields() = 0;
    virtual bool get_IsEntryLevelRangeSpecified() = 0;
    virtual bool get_IsTableOfFigures() = 0;
    virtual bool get_IsHeadingLevelRangeSpecified() = 0;
    virtual bool get_AreCustomStylesSpecified() = 0;
    virtual bool get_UseParagraphOutlineLevel() = 0;
    virtual System::String get_TableOfFiguresLabel() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::LevelRange> get_TocEntryLevelRange() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::LevelRange> get_HeadingLevelRange() = 0;
    virtual System::String get_CaptionlessTableOfFiguresLabel() = 0;
    virtual int32_t get_EntryType() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() = 0;
    virtual bool get_SkipTables() = 0;
    virtual bool get_IncludeRefDocFields() = 0;

    virtual System::SharedPtr<Aspose::Words::Bookmark> GetRangeBookmark() = 0;
    virtual int32_t GetLevelForCustomStyle(System::SharedPtr<Aspose::Words::Paragraph> paragraph, System::SharedPtr<Aspose::Words::Style> style) = 0;

};/// \endcond

}
}
}
