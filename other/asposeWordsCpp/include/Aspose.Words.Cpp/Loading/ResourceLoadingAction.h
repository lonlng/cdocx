//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/ResourceLoadingAction.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Specifies the mode of resource loading.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
enum class ASPOSE_WORDS_SHARED_CLASS ResourceLoadingAction
{
    /// %Aspose.Words will load this resource as usual.
    Default,
    /// %Aspose.Words will skip loading of this resource.
    /// Only link without data will be stored for an image, CSS style sheet will be ignored for HTML format.
    Skip,
    /// %Aspose.Words will use byte array provided by user in <see cref="Aspose::Words::Loading::ResourceLoadingArgs::SetData(System::ArrayPtr<uint8_t>)">SetData()</see> as resource data.
    UserProvided
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::ResourceLoadingAction>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::ResourceLoadingAction, const char_t*>, 3>& values();
};
