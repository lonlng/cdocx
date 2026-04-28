//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/MergeFormatMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace LowCode {

/// Specifies how formatting is merged when combining multiple documents.
enum class ASPOSE_WORDS_SHARED_CLASS MergeFormatMode
{
    /// Combine the formatting of the merged documents.
    /// 
    /// By using this option, %Aspose.Words adapts the formatting of the first document to match the structure and
    /// appearance of the second document, but keeps some of the original formatting intact.
    /// This option is useful when you want to maintain the overall look and feel of the destination document
    /// but still retain certain formatting aspects from the original document.
    /// 
    /// This option does not have any affect when the input and the output formats are PDF.
    MergeFormatting = 0,
    /// Means that the source document will retain its original formatting,
    /// such as font styles, sizes, colors, indents, and any other formatting elements applied to its content.
    /// 
    /// By using this option, you ensure that the copied content appears as it did in the original source,
    /// regardless of the formatting settings of the first document in merge queue.
    /// 
    /// This option does not have any affect when the input and the output formats are PDF.
    KeepSourceFormatting = 1,
    /// Preserve the layout of the original documents in the final document.
    /// 
    /// In general, it looks like you print out the original documents and manually adhere them together using glue.
    KeepSourceLayout = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::LowCode::MergeFormatMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LowCode::MergeFormatMode, const char_t*>, 3>& values();
};
