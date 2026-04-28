//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartShapeType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the shape type of chart elements.
/// 
/// @sa Aspose::Words::Drawing::Charts::ChartFormat::get_ShapeType
enum class ASPOSE_WORDS_SHARED_CLASS ChartShapeType
{
    /// Indicates that a shape is not defined for the chart element.
    Default,
    /// Rectangle.
    Rectangle,
    /// Rounded rectangle.
    RoundRectangle,
    /// Ellipse.
    Ellipse,
    /// Diamond.
    Diamond,
    /// Triangle.
    Triangle,
    /// Right triangle.
    RightTriangle,
    /// Parallelogram.
    Parallelogram,
    /// Trapezoid.
    Trapezoid,
    /// Hexagon.
    Hexagon,
    /// Octagon.
    Octagon,
    /// Plus.
    Plus,
    /// Star.
    Star,
    /// Arrow.
    Arrow,
    /// Home plate.
    HomePlate,
    /// Cube.
    Cube,
    /// Arc.
    Arc,
    /// Line.
    Line,
    /// Plaque.
    Plaque,
    /// Can.
    Can,
    /// Donut.
    Donut,
    /// Straight connector 1.
    StraightConnector1,
    /// Bent connector 2.
    BentConnector2,
    /// Bent connector 3.
    BentConnector3,
    /// Bent connector 4.
    BentConnector4,
    /// Bent connector 5.
    BentConnector5,
    /// Curved connector 2.
    CurvedConnector2,
    /// Curved connector 3.
    CurvedConnector3,
    /// Curved connector 4.
    CurvedConnector4,
    /// Curved connector 5.
    CurvedConnector5,
    /// Callout 1.
    Callout1,
    /// Callout 2.
    Callout2,
    /// Callout 3.
    Callout3,
    /// Accent callout 1.
    AccentCallout1,
    /// Accent callout 2.
    AccentCallout2,
    /// Accent callout 3.
    AccentCallout3,
    /// Callout with border 1.
    BorderCallout1,
    /// Callout with border 2.
    BorderCallout2,
    /// Callout with border 3.
    BorderCallout3,
    /// Accent callout with border 1.
    AccentBorderCallout1,
    /// Accent callout with border 2.
    AccentBorderCallout2,
    /// Accent callout with border 3.
    AccentBorderCallout3,
    /// Ribbon.
    Ribbon,
    /// Ribbon 2.
    Ribbon2,
    /// Chevron.
    Chevron,
    /// Pentagon.
    Pentagon,
    /// No smoking.
    NoSmoking,
    /// Four pointed star.
    Seal4,
    /// Six pointed star.
    Seal6,
    /// Seven pointed star.
    Seal7,
    /// Eight pointed star.
    Seal8,
    /// Ten pointed star.
    Seal10,
    /// Twelve pointed star.
    Seal12,
    /// Sixteen pointed star.
    Seal16,
    /// Twenty-four pointed star.
    Seal24,
    /// Thirty-two pointed star.
    Seal32,
    /// Callout wedge rectangle.
    WedgeRectCallout,
    /// Callout wedge round rectangle.
    WedgeRRectCallout,
    /// Callout wedge ellipse.
    WedgeEllipseCallout,
    /// Wave.
    Wave,
    /// Folded corner.
    FoldedCorner,
    /// Left arrow.
    LeftArrow,
    /// Down arrow.
    DownArrow,
    /// Up  arrow.
    UpArrow,
    /// Left and right arrow.
    LeftRightArrow,
    /// Up and down arrow.
    UpDownArrow,
    /// Irregular seal 1.
    IrregularSeal1,
    /// Irregular seal 2.
    IrregularSeal2,
    /// Lightning bolt.
    LightningBolt,
    /// Heart.
    Heart,
    /// Quad arrow.
    QuadArrow,
    /// Callout left arrow.
    LeftArrowCallout,
    /// Callout right arrow.
    RightArrowCallout,
    /// Callout up arrow.
    UpArrowCallout,
    /// Callout down arrow.
    DownArrowCallout,
    /// Callout left and right arrow.
    LeftRightArrowCallout,
    /// Callout up and down arrow.
    UpDownArrowCallout,
    /// Callout quad arrow.
    QuadArrowCallout,
    /// Bevel.
    Bevel,
    /// Left bracket.
    LeftBracket,
    /// Right bracket.
    RightBracket,
    /// Left brace.
    LeftBrace,
    /// Right brace.
    RightBrace,
    /// Left up arrow.
    LeftUpArrow,
    /// Bent up arrow.
    BentUpArrow,
    /// Bent arrow.
    BentArrow,
    /// Striped right arrow.
    StripedRightArrow,
    /// Notched right arrow.
    NotchedRightArrow,
    /// Block arc.
    BlockArc,
    /// Smiley face.
    SmileyFace,
    /// Vertical scroll.
    VerticalScroll,
    /// Horizontal scroll.
    HorizontalScroll,
    /// Circular arrow.
    CircularArrow,
    /// U-turn arrow.
    UturnArrow,
    /// Curved right arrow.
    CurvedRightArrow,
    /// Curved left arrow.
    CurvedLeftArrow,
    /// Curved up arrow.
    CurvedUpArrow,
    /// Curved down arrow.
    CurvedDownArrow,
    /// Callout cloud.
    CloudCallout,
    /// Ellipse ribbon.
    EllipseRibbon,
    /// Ellipse ribbon 2.
    EllipseRibbon2,
    /// Process flow.
    FlowChartProcess,
    /// Decision flow.
    FlowChartDecision,
    /// Input output flow.
    FlowChartInputOutput,
    /// Predefined process flow.
    FlowChartPredefinedProcess,
    /// Internal storage flow.
    FlowChartInternalStorage,
    /// Document flow.
    FlowChartDocument,
    /// Multi-document flow.
    FlowChartMultidocument,
    /// Terminator flow.
    FlowChartTerminator,
    /// Preparation flow.
    FlowChartPreparation,
    /// Manual input flow.
    FlowChartManualInput,
    /// Manual operation flow.
    FlowChartManualOperation,
    /// Connector flow.
    FlowChartConnector,
    /// Punched card flow.
    FlowChartPunchedCard,
    /// Punched tape flow.
    FlowChartPunchedTape,
    /// Summing junction flow.
    FlowChartSummingJunction,
    /// Or flow.
    FlowChartOr,
    /// Collate flow.
    FlowChartCollate,
    /// Sort flow.
    FlowChartSort,
    /// Extract flow.
    FlowChartExtract,
    /// Merge flow.
    FlowChartMerge,
    /// Offline storage flow.
    FlowChartOfflineStorage,
    /// Online storage flow.
    FlowChartOnlineStorage,
    /// Magnetic tape flow.
    FlowChartMagneticTape,
    /// Magnetic disk flow.
    FlowChartMagneticDisk,
    /// Magnetic drum flow.
    FlowChartMagneticDrum,
    /// Display flow.
    FlowChartDisplay,
    /// Delay flow.
    FlowChartDelay,
    /// Alternate process flow.
    FlowChartAlternateProcess,
    /// Off-page connector flow.
    FlowChartOffpageConnector,
    /// Left right up arrow.
    LeftRightUpArrow,
    /// Sun.
    Sun,
    /// Moon.
    Moon,
    /// Bracket pair.
    BracketPair,
    /// Brace pair.
    BracePair,
    /// Double wave.
    DoubleWave,
    /// Blank button.
    ActionButtonBlank,
    /// Home button.
    ActionButtonHome,
    /// Help button.
    ActionButtonHelp,
    /// Information button.
    ActionButtonInformation,
    /// Forward or next button.
    ActionButtonForwardNext,
    /// Back or previous button.
    ActionButtonBackPrevious,
    /// End button.
    ActionButtonEnd,
    /// Beginning button.
    ActionButtonBeginning,
    /// Return button.
    ActionButtonReturn,
    /// Document button.
    ActionButtonDocument,
    /// Sound button.
    ActionButtonSound,
    /// Movie button.
    ActionButtonMovie,
    /// Snip single corner rectangle object.
    SingleCornerSnipped,
    /// Snip same side corner rectangle.
    TopCornersSnipped,
    /// Snip diagonal corner rectangle.
    DiagonalCornersSnipped,
    /// Snip and round single corner rectangle.
    TopCornersOneRoundedOneSnipped,
    /// Rounded single corner rectangle.
    SingleCornerRounded,
    /// Rounded same side corner rectangle.
    TopCornersRounded,
    /// Rounded diagonal corner rectangle.
    DiagonalCornersRounded,
    /// Heptagon.
    Heptagon,
    /// Cloud.
    Cloud,
    /// Swoosh arrow.
    SwooshArrow,
    /// Teardrop.
    Teardrop,
    /// Square tabs.
    SquareTabs,
    /// Plaque tabs.
    PlaqueTabs,
    /// Pie.
    Pie,
    /// Wedge pie.
    WedgePie,
    /// Inverse line.
    InverseLine,
    /// Math plus.
    MathPlus,
    /// Math minus.
    MathMinus,
    /// Math multiply.
    MathMultiply,
    /// Math divide.
    MathDivide,
    /// Math equal.
    MathEqual,
    /// Math not equal.
    MathNotEqual,
    /// Non-isosceles trapezoid.
    NonIsoscelesTrapezoid,
    /// Left-right circular arrow.
    LeftRightCircularArrow,
    /// Left-right ribbon.
    LeftRightRibbon,
    /// Left circular arrow.
    LeftCircularArrow,
    /// Frame.
    Frame,
    /// Half frame.
    HalfFrame,
    /// Funnel.
    Funnel,
    /// Six-tooth gear.
    Gear6,
    /// Nine-tooth gear.
    Gear9,
    /// Decagon.
    Decagon,
    /// Dodecagon.
    Dodecagon,
    /// Diagonal stripe.
    DiagonalStripe,
    /// Corner.
    Corner,
    /// Corner tabs.
    CornerTabs,
    /// Chord.
    Chord,
    /// Chart plus.
    ChartPlus,
    /// Chart star.
    ChartStar,
    /// Chart X.
    ChartX
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartShapeType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartShapeType, const char_t*>, 188>& values();
};
