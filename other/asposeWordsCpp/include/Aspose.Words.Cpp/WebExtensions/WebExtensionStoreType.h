//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/WebExtensionStoreType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Enumerates available types of a web extension store.
enum class ASPOSE_WORDS_SHARED_CLASS WebExtensionStoreType
{
    /// Specifies that the store type is SharePoint corporate catalog.
    SPCatalog,
    /// Specifies that the store type is Office.com.
    OMEX,
    /// Specifies that the store type is a SharePoint web application.
    SPApp,
    /// Specifies that the store type is an Exchange server.
    Exchange,
    /// Specifies that the store type is a file system share.
    FileSystem,
    /// Specifies that the store type is the system registry.
    Registry,
    /// Specifies that the store type is Centralized Deployment via Exchange.
    ExCatalog,
    /// Default value.
    Default = static_cast<int32_t>(SPCatalog)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::WebExtensions::WebExtensionStoreType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::WebExtensions::WebExtensionStoreType, const char_t*>, 8>& values();
};
