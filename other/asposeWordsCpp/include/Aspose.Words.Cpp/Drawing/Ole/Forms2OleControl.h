//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/Forms2OleControl.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>

#include <Aspose.Words.Cpp/Drawing/Ole/OleControl.h>
#include <Aspose.Words.Cpp/Drawing/Ole/Forms2OleControlType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Ss
{
class MemoryStorage;
}
namespace Words
{

namespace Drawing
{
namespace Ole
{

class Forms2OleControlCollection;

}

}
namespace Forms2
{

enum class ClsidCacheIndex;

}
namespace RW
{
namespace Ole
{
namespace Ole2
{
class ClipboardFormat;
}
}
}
}
}
namespace System
{
namespace Drawing
{
class Color;
}
class Guid;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Ole {

/// Represents %Microsoft Forms 2.0 OLE control.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-ole-objects/">Working with Ole Objects</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Forms2OleControl : public Aspose::Words::Drawing::Ole::OleControl
{
    typedef Forms2OleControl ThisType;
    typedef Aspose::Words::Drawing::Ole::OleControl BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

protected:

protected:

public:

    /// Gets a Caption property of the control.
    /// Default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Caption();
    /// Sets a Caption property of the control.
    /// Default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_Caption(const System::String& value);
    /// Gets underlying Value property which often represents control state.
    /// For example checked option button has '1' value while unchecked has '0'.
    /// Default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Value();
    /// Returns <c>%true</c> if control is in enabled state.
    ASPOSE_WORDS_SHARED_API bool get_Enabled();
    /// Gets collection of immediate child controls.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Ole::Forms2OleControlCollection> get_ChildNodes();
    /// Gets type of Forms 2.0 control.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Ole::Forms2OleControlType get_Type() = 0;
    /// Gets a string that specifies a group of mutually exclusive controls.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_GroupName();
    /// Sets a string that specifies a group of mutually exclusive controls.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_GroupName(const System::String& value);
    /// Gets a foreground color of the control.
    /// The default value depends on a type of the control.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_ForeColor();
    /// Sets a foreground color of the control.
    /// The default value depends on a type of the control.
    ASPOSE_WORDS_SHARED_API void set_ForeColor(System::Drawing::Color value);
    /// Gets a background color of the control.
    /// The default value depends on a type of the control.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BackColor();
    /// Sets a background color of the control.
    /// The default value depends on a type of the control.
    ASPOSE_WORDS_SHARED_API void set_BackColor(System::Drawing::Color value);
    /// Gets a width of the control in points.
    ASPOSE_WORDS_SHARED_API double get_Width();
    /// Sets a width of the control in points.
    ASPOSE_WORDS_SHARED_API void set_Width(double value);
    /// Gets a height of the control in points.
    ASPOSE_WORDS_SHARED_API double get_Height();
    /// Sets a height of the control in points.
    ASPOSE_WORDS_SHARED_API void set_Height(double value);

protected:

    virtual Aspose::Words::Forms2::ClsidCacheIndex get_ClsidCacheIndex() = 0;
    virtual ASPOSE_WORDS_SHARED_API bool get_IsComposite();
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RW::Ole::Ole2::ClipboardFormat> get_ClipboardFormat() override;

    ASPOSE_WORDS_SHARED_API System::String get_UserType() override;
    ASPOSE_WORDS_SHARED_API System::String get_ProgId() override;

    System::SharedPtr<System::Object> mField0;

    ASPOSE_WORDS_SHARED_API void Read(System::SharedPtr<Aspose::Ss::MemoryStorage> ) override;
    ASPOSE_WORDS_SHARED_API void Write(System::SharedPtr<Aspose::Ss::MemoryStorage> ) override;

private:

};

}
}
}
}
