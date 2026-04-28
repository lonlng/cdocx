//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ImportFormatMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies how formatting is merged when importing content from another document.
/// 
/// When you copy nodes from one document to another, this option specifies how formatting
/// is resolved when both documents have a style with the same name, but different formatting.
/// 
/// The formatting is resolved as follows:
/// 
/// -# Built-in styles are matched using their locale independent style identifier.
///    User defined styles are matched using case-sensitive style name.
/// -# If a matching style is not found in the destination document, the style
///    (and all styles referenced by it) are copied into the destination document
///    and the imported nodes are updated to reference the new style.
/// -# If a matching style already exists in the destination document, what happens
///    depends on the <c>%importFormatMode</c> parameter passed to
///    <see cref="Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool, Aspose::Words::ImportFormatMode)">ImportNode()</see>
///    as described below.
/// 
/// When using the <see cref="Aspose::Words::ImportFormatMode::UseDestinationStyles">UseDestinationStyles</see> option, if a matching style already exists
/// in the destination document, the style is not copied and the imported nodes are updated
/// to reference the existing style.
/// 
/// The drawback of using <see cref="Aspose::Words::ImportFormatMode::UseDestinationStyles">UseDestinationStyles</see> is that the imported text might
/// look different in the destination document comparing to the source document.
/// For example, the "Heading 1" style in the source document uses Arial 16pt font and
/// the "Heading 1" style in the destination document uses Times New Roman 14pt font.
/// When importing text of "Heading 1" style with no other direct formatting, it will
/// appear as Times New Roman 14pt font in the destination document.
/// 
/// <see cref="Aspose::Words::ImportFormatMode::KeepSourceFormatting">KeepSourceFormatting</see> option allows to make sure the imported content looks the same
/// in the destination document like it looks in the source document.
/// If a matching style already exists in the destination document, the source style formatting is expanded
/// into direct Node attributes and the style is changed to Normal.
/// If the style does not exist in the destination document, then the source style is imported
/// into the destination document and applied to the imported node.
/// Note, that it is not always possible to preserve the source style even if it does not exist in the destination document.
/// In this case formatting of such style will be expanded into direct Node attributes in favor of preserving original Node formatting.
/// 
/// The drawback of using <see cref="Aspose::Words::ImportFormatMode::KeepSourceFormatting">KeepSourceFormatting</see> is that if you perform several imports,
/// you could end up with many styles in the destination document and that could make using
/// consistent style formatting in %Microsoft Word difficult for this document.
/// 
/// Using <see cref="Aspose::Words::ImportFormatMode::KeepDifferentStyles">KeepDifferentStyles</see> option allows to reuse destination styles
/// if the formatting they provide is identical to the styles in the source document.
/// If the style in destination document is different from the source then it is imported.
/// 
/// @sa Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool, Aspose::Words::ImportFormatMode)
enum class ASPOSE_WORDS_SHARED_CLASS ImportFormatMode
{
    /// Use the destination document styles and copy new styles. This is the default option.
    UseDestinationStyles,
    /// Copy all required styles to the destination document, generate unique style names if needed.
    KeepSourceFormatting,
    /// Only copy styles that are different from those in the source document.
    KeepDifferentStyles
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::ImportFormatMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::ImportFormatMode, const char_t*>, 3>& values();
};
