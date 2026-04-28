//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/OleFormat.h
#pragma once

#include <system/io/std_stream_wrappers.h>
#include <system/array.h>
#include <iostream>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Drawing
{

namespace Ole
{

class OleControl;
}
class OlePackage;
}

}
}
namespace System
{
class Guid;
namespace IO
{
class MemoryStream;
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Provides access to the data of an OLE object or ActiveX control.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-ole-objects/">Working with Ole Objects</a> documentation article.
/// 
/// Use the <see cref="Aspose::Words::Drawing::Shape::get_OleFormat">OleFormat</see> property to access the data of an OLE object.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::OleFormat">OleFormat</see> class directly.
/// 
/// @sa Aspose::Words::Drawing::Shape::get_OleFormat
class ASPOSE_WORDS_SHARED_CLASS OleFormat : public System::Object
{
    typedef OleFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets icon caption of OLE object.
    /// In case if the OLE object does not have an icon or a caption cannot be retrieved, returns an empty
    /// string.
    ASPOSE_WORDS_SHARED_API System::String get_IconCaption();
    /// Gets the file extension suggested for the current embedded object if you want to save it into a file.
    ASPOSE_WORDS_SHARED_API System::String get_SuggestedExtension();
    /// Gets the file name suggested for the current embedded object if you want to save it into a file.
    ASPOSE_WORDS_SHARED_API System::String get_SuggestedFileName();
    /// Gets or sets the ProgID of the OLE object.
    /// 
    /// The ProgID property is not always present in %Microsoft Word documents and cannot be relied upon.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_ProgId();
    /// Setter for Aspose::Words::Drawing::OleFormat::get_ProgId
    ASPOSE_WORDS_SHARED_API void set_ProgId(const System::String& value);
    /// Returns <c>%true</c> if the OLE object is linked (when <see cref="Aspose::Words::Drawing::OleFormat::get_SourceFullName">SourceFullName</see> is specified).
    ASPOSE_WORDS_SHARED_API bool get_IsLink();
    /// Gets or sets the path and name of the source file for the linked OLE object.
    /// 
    /// The default value is an empty string.
    /// 
    /// If <see cref="Aspose::Words::Drawing::OleFormat::get_SourceFullName">SourceFullName</see> is not an empty string, the OLE object is linked.
    ASPOSE_WORDS_SHARED_API System::String get_SourceFullName();
    /// Setter for Aspose::Words::Drawing::OleFormat::get_SourceFullName
    ASPOSE_WORDS_SHARED_API void set_SourceFullName(const System::String& value);
    /// Gets or sets a string that is used to identify the portion of the source file that is being linked.
    /// 
    /// The default value is an empty string.
    /// 
    /// For example, if the source file is a %Microsoft Excel workbook, the <see cref="Aspose::Words::Drawing::OleFormat::get_SourceItem">SourceItem</see>
    /// property might return "Workbook1!R3C1:R4C2" if the OLE object contains only a few cells from
    /// the worksheet.
    ASPOSE_WORDS_SHARED_API System::String get_SourceItem();
    /// Setter for Aspose::Words::Drawing::OleFormat::get_SourceItem
    ASPOSE_WORDS_SHARED_API void set_SourceItem(const System::String& value);
    /// Specifies whether the link to the OLE object is automatically updated or not in %Microsoft Word.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_AutoUpdate();
    /// Specifies whether the link to the OLE object is automatically updated or not in %Microsoft Word.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_AutoUpdate(bool value);
    /// Gets the draw aspect of the OLE object. When <c>%true</c>, the OLE object is displayed as an icon.
    /// When <c>%false</c>, the OLE object is displayed as content.
    /// 
    /// %Aspose.Words does not allow to set this property to avoid confusion. If you were able to change
    /// the draw aspect in %Aspose.Words, %Microsoft Word would still display the OLE object in its original
    /// draw aspect until you edit or update the OLE object in %Microsoft Word.
    ASPOSE_WORDS_SHARED_API bool get_OleIcon();
    /// Specifies whether the link to the OLE object is locked from updates.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsLocked();
    /// Specifies whether the link to the OLE object is locked from updates.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IsLocked(bool value);
    /// Gets the CLSID of the OLE object.
    ASPOSE_WORDS_SHARED_API System::Guid get_Clsid();
    /// Provide access to <see cref="Aspose::Words::Drawing::OlePackage">OlePackage</see> if OLE object is an OLE Package.
    /// Returns <c>%null</c> otherwise.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::OlePackage> get_OlePackage();
    /// Gets <see cref="Aspose::Words::Drawing::OleFormat::get_OleControl">OleControl</see> objects if this OLE object is an ActiveX control. Otherwise this property is null.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Ole::OleControl> get_OleControl();

    /// Saves the data of the embedded object into the specified stream.
    /// 
    /// It is the responsibility of the caller to dispose the stream.
    /// 
    /// @param stream Where to save the object data.
    /// 
    /// @exception System::InvalidOperationException Throws if you attempt to save a linked object.
    ASPOSE_WORDS_SHARED_API void Save(const System::SharedPtr<System::IO::Stream>& stream);
    /// Saves the data of the embedded object into a file with the specified name.
    /// 
    /// @param fileName Name of the file to save the OLE object data.
    /// 
    /// @exception System::InvalidOperationException Throws if you attempt to save a linked object.
    ASPOSE_WORDS_SHARED_API void Save(const System::String& fileName);
    /// Gets OLE object data entry.
    /// 
    /// @param oleEntryName Case-sensitive name of the OLE data stream.
    /// 
    /// @return An OLE data stream or <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::MemoryStream> GetOleEntry(const System::String& oleEntryName);
    /// Gets OLE object raw data.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> GetRawData();

    template <typename CharType, typename Traits>
    void Save(std::basic_ostream<CharType, Traits>& stream)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        Save(streamWrapper);
    }

protected:

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
}
