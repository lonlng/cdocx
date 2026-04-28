//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Vba/VbaReferenceType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Vba {

/// Allows to specify the type of a <see cref="Aspose::Words::Vba::VbaReference">VbaReference</see> object.
enum class ASPOSE_WORDS_SHARED_CLASS VbaReferenceType
{
    /// Specifies an Automation type library reference type.
    Registered = 0x0d,
    /// Specified an external VBA project reference type.
    Project = 0x0e,
    /// Specifies an original Automation type library reference type.
    Original = 0x33,
    /// Specifies a twiddled type library reference type.
    Control = 0x2f
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Vba::VbaReferenceType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Vba::VbaReferenceType, const char_t*>, 4>& values();
};
