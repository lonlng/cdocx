//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/EditorType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the set of possible aliases (or editing groups) which can be used as aliases to
/// determine if the current user shall be allowed to edit a single range
/// defined by an editable range within a document.
enum class ASPOSE_WORDS_SHARED_CLASS EditorType
{
    /// Means that editor type is not specified.
    Unspecified,
    /// Specifies that users associated with the Administrators group shall be allowed to edit editable ranges using
    /// this editing type when document protection is enabled.
    Administrators,
    /// Specifies that users associated with the Contributors group shall be allowed to edit editable ranges using
    /// this editing type when document protection is enabled.
    Contributors,
    /// Specifies that users associated with the Current group shall be allowed to edit editable ranges using this
    /// editing type when document protection is enabled.
    Current,
    /// Specifies that users associated with the Editors group shall be allowed to edit editable ranges using this
    /// editing type when document protection is enabled.
    Editors,
    /// Specifies that all users that open the document shall be allowed to edit editable ranges using this editing
    /// type when document protection is enabled.
    Everyone,
    /// Specifies that none of the users that open the document shall be allowed to edit editable ranges
    /// using this editing type when document protection is enabled.
    None,
    /// Specifies that users associated with the Owners group shall be allowed to edit editable ranges using this
    /// editing type when document protection is enabled.
    Owners,
    /// Same as <see cref="Aspose::Words::EditorType::Unspecified">Unspecified</see>.
    Default = static_cast<int32_t>(Unspecified)
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::EditorType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::EditorType, const char_t*>, 9>& values();
};
