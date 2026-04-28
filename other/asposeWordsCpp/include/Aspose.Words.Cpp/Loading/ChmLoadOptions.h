//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/ChmLoadOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Loading/LoadOptions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify additional options when loading CHM document into a <see cref="Aspose::Words::Document">Document</see> object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChmLoadOptions : public Aspose::Words::Loading::LoadOptions
{
    typedef ChmLoadOptions ThisType;
    typedef Aspose::Words::Loading::LoadOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The name of the CHM file.
    /// Default value is <c>%null</c>.
    /// 
    /// CHM documents may contain links that reference the same document by file name. %Aspose.Words supports such links
    /// and normally uses <see cref="Aspose::Words::Document::get_OriginalFileName">OriginalFileName</see> to check whether the file referenced by a link
    /// is the file that is being loaded. If a document is loaded from a stream, its original file name should be specified
    /// explicitly via this property, since it cannot be determined automatically.
    /// 
    /// If a CHM document is loaded from a file and a non-null value for this property is specified, the value will take
    /// priority over the actual name of the file stored in <see cref="Aspose::Words::Document::get_OriginalFileName">OriginalFileName</see>.
    ASPOSE_WORDS_SHARED_API System::String get_OriginalFileName() const;
    /// Setter for Aspose::Words::Loading::ChmLoadOptions::get_OriginalFileName
    ASPOSE_WORDS_SHARED_API void set_OriginalFileName(const System::String& value);

    /// Initializes a new instance of this class with default values.
    ASPOSE_WORDS_SHARED_API ChmLoadOptions();

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::LoadOptions> Clone() override;

    virtual ASPOSE_WORDS_SHARED_API ~ChmLoadOptions();

private:

    System::String mField0;

};

}
}
}
