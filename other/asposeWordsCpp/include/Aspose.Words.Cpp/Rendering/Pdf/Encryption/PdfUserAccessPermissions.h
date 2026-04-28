//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Rendering/Pdf/Encryption/PdfUserAccessPermissions.h
#pragma once

#include <cstdint>

namespace Aspose {

namespace Rendering {

namespace Pdf {

namespace Encryption {

/// \cond
class PdfUserAccessPermissions
{
    typedef PdfUserAccessPermissions ThisType;

public:

    static constexpr int32_t Print = 0x4;

    static constexpr int32_t Modify = 0x8;

    static constexpr int32_t Copy = 0x10;

    static constexpr int32_t ModifyAnnotations = 0x20;

    static constexpr int32_t FillForms = 0x100;

    static constexpr int32_t CopyForAccessibility = 0x200;

    static constexpr int32_t Assemble = 0x400;

    static constexpr int32_t HighQualityPrint = 0x800;

    static constexpr int32_t Reserved1Mask = (int32_t)0xfffff0c0;

    static constexpr int32_t Reserved0MaskInverted = (int32_t)0xfffffffc;

public:
    PdfUserAccessPermissions() = delete;
};/// \endcond

}
}
}
}
