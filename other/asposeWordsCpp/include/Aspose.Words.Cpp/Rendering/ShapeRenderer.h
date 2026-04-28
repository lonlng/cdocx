//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Rendering/ShapeRenderer.h
#pragma once

#include <Aspose.Words.Cpp/Rendering/NodeRendererBase.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
class ShapeBase;
}

}
}

namespace Aspose {

namespace Words {

namespace Rendering {

/// Provides methods to render an individual <see cref="Aspose::Words::Drawing::Shape">Shape</see> or <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see>
/// to a raster or vector image or to a Graphics object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-shapes/">Working
/// with Shapes</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ShapeRenderer : public Aspose::Words::Rendering::NodeRendererBase
{
    typedef ShapeRenderer ThisType;
    typedef Aspose::Words::Rendering::NodeRendererBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Initializes a new instance of this class.
    /// 
    /// @param shape The DrawinML shape object that you want to render.
    ASPOSE_WORDS_SHARED_API ShapeRenderer(const System::SharedPtr<Aspose::Words::Drawing::ShapeBase>& shape);

private:

};

}
}
}
