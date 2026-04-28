//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Vba/VbaModuleType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Vba {

/// Specifies the type of a model in a VBA project.
enum class ASPOSE_WORDS_SHARED_CLASS VbaModuleType
{
    /// A type of VBA project item that specifies a module for embedded macros and programmatic access operations
    /// that are associated with a document.
    DocumentModule,
    /// A collection of subroutines and functions.
    ProceduralModule,
    /// A module that contains the definition for a new object. Each instance of a class creates a new object,
    /// and procedures that are defined in the module become properties and methods of the object.
    ClassModule,
    /// A VBA module that extends the methods and properties of an ActiveX control that has been registered with the project.
    DesignerModule
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Vba::VbaModuleType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Vba::VbaModuleType, const char_t*>, 4>& values();
};
