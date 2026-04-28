//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/ImageFieldMergingArgs.h
#pragma once

#include <system/io/std_stream_wrappers.h>
#include <iostream>

#include <Aspose.Words.Cpp/MailMerging/FieldMergingArgsBase.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
namespace Drawing
{
class Shape;
}
namespace Fields
{
class FieldMergeField;
class MergeFieldImageDimension;
}

}
}
namespace System
{
namespace Drawing
{
class Image;
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// Provides data for the <see cref="Aspose::Words::MailMerging::IFieldMergingCallback::ImageFieldMerging(System::SharedPtr<Aspose::Words::MailMerging::ImageFieldMergingArgs>)">ImageFieldMerging()</see> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// This event occurs during mail merge when an image mail merge
/// field is encountered in the document. You can respond to this event to return a
/// file name, stream, or an <see cref="System::Drawing::Image">Image</see> object to the mail merge
/// engine so it is inserted into the document.
/// 
/// There are three properties available <see cref="Aspose::Words::MailMerging::ImageFieldMergingArgs::get_ImageFileName">ImageFileName</see>,
/// <see cref="Aspose::Words::MailMerging::ImageFieldMergingArgs::get_ImageStream">ImageStream</see> and <see cref="Aspose::Words::MailMerging::ImageFieldMergingArgs::get_Image">Image</see> to specify where the image must be taken from.
/// Set only one of these properties.
/// 
/// To insert an image mail merge field into a document in Word, select Insert/Field command,
/// then select MergeField and type Image:MyFieldName.
/// 
/// @sa Aspose::Words::MailMerging::IFieldMergingCallback
class ASPOSE_WORDS_SHARED_CLASS ImageFieldMergingArgs : public Aspose::Words::MailMerging::FieldMergingArgsBase
{
    typedef ImageFieldMergingArgs ThisType;
    typedef Aspose::Words::MailMerging::FieldMergingArgsBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Sets the file name of the image that the mail merge engine must insert into the document.
    ASPOSE_WORDS_SHARED_API System::String get_ImageFileName() const;
    /// Sets the file name of the image that the mail merge engine must insert into the document.
    ASPOSE_WORDS_SHARED_API void set_ImageFileName(const System::String& value);
    /// Specifies the stream for the mail merge engine to read an image from.
    /// 
    /// %Aspose.Words closes this stream after it merges the image into the document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::IO::Stream>& get_ImageStream() const;
    /// Specifies the stream for the mail merge engine to read an image from.
    /// 
    /// %Aspose.Words closes this stream after it merges the image into the document.
    ASPOSE_WORDS_SHARED_API void set_ImageStream(const System::SharedPtr<System::IO::Stream>& value);
    /// Specifies the image that the mail merge engine must insert into the document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Drawing::Image>& get_Image() const;
    /// Specifies the image that the mail merge engine must insert into the document.
    ASPOSE_WORDS_SHARED_API void set_Image(const System::SharedPtr<System::Drawing::Image>& value);
    /// Specifies the shape that the mail merge engine must insert into the document.
    /// 
    /// When this property is specified, the mail merge engine ignores all other properties like <see cref="Aspose::Words::MailMerging::ImageFieldMergingArgs::get_ImageFileName">ImageFileName</see> or <see cref="Aspose::Words::MailMerging::ImageFieldMergingArgs::get_ImageStream">ImageStream</see>
    /// and simply inserts the shape into the document.
    /// 
    /// Use this property to fully control the process of merging an image merge field.
    /// For example, you can specify <see cref="Aspose::Words::Drawing::ShapeBase::get_WrapType">WrapType</see> or any other shape property to fine tune the resulting node. However, please note that
    /// you are responsible for providing the content of the shape.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Drawing::Shape>& get_Shape() const;
    /// Setter for Aspose::Words::MailMerging::ImageFieldMergingArgs::get_Shape
    ASPOSE_WORDS_SHARED_API void set_Shape(const System::SharedPtr<Aspose::Words::Drawing::Shape>& value);
    /// Specifies the image width for the image to insert into the document.
    /// 
    /// The value of this property initially comes from the corresponding MERGEFIELD's code, contained in the
    /// template document. To override the initial value, you should assign an instance of
    /// <see cref="Aspose::Words::Fields::MergeFieldImageDimension">MergeFieldImageDimension</see> class to this property or set the properties for the instance
    /// of <see cref="Aspose::Words::Fields::MergeFieldImageDimension">MergeFieldImageDimension</see> class, returned by this property.
    /// 
    /// To indicate that the original value of the image width should be applied, you should assign the <c>%null</c>
    /// value to this property or set the <see cref="Aspose::Words::Fields::MergeFieldImageDimension::get_Value">Value</see> property for the instance
    /// of <see cref="Aspose::Words::Fields::MergeFieldImageDimension">MergeFieldImageDimension</see> class, returned by this property, to a negative value.
    /// 
    /// @sa Aspose::Words::Fields::MergeFieldImageDimension
    /// @sa Aspose::Words::Fields::MergeFieldImageDimensionUnit
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::MergeFieldImageDimension>& get_ImageWidth() const;
    /// Setter for Aspose::Words::MailMerging::ImageFieldMergingArgs::get_ImageWidth
    ASPOSE_WORDS_SHARED_API void set_ImageWidth(const System::SharedPtr<Aspose::Words::Fields::MergeFieldImageDimension>& value);
    /// Specifies the image height for the image to insert into the document.
    /// 
    /// The value of this property initially comes from the corresponding MERGEFIELD's code, contained in the
    /// template document. To override the initial value, you should assign an instance of
    /// <see cref="Aspose::Words::Fields::MergeFieldImageDimension">MergeFieldImageDimension</see> class to this property or set the properties for the instance
    /// of <see cref="Aspose::Words::Fields::MergeFieldImageDimension">MergeFieldImageDimension</see> class, returned by this property.
    /// 
    /// To indicate that the original value of the image height should be applied, you should assign the <c>%null</c>
    /// value to this property or set the <see cref="Aspose::Words::Fields::MergeFieldImageDimension::get_Value">Value</see> property for the instance
    /// of <see cref="Aspose::Words::Fields::MergeFieldImageDimension">MergeFieldImageDimension</see> class, returned by this property, to a negative value.
    /// 
    /// @sa Aspose::Words::Fields::MergeFieldImageDimension
    /// @sa Aspose::Words::Fields::MergeFieldImageDimensionUnit
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::MergeFieldImageDimension>& get_ImageHeight() const;
    /// Setter for Aspose::Words::MailMerging::ImageFieldMergingArgs::get_ImageHeight
    ASPOSE_WORDS_SHARED_API void set_ImageHeight(const System::SharedPtr<Aspose::Words::Fields::MergeFieldImageDimension>& value);

    template <typename CharType, typename Traits>
    void set_ImageStream(std::basic_istream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_ImageStream(valueWrapper);
    }

protected:

private:

    System::String mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
}
