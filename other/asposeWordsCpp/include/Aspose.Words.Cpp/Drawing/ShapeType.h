//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ShapeType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the type of shape in a %Microsoft Word document.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_ShapeType
enum class ASPOSE_WORDS_SHARED_CLASS ShapeType
{
    /// The shape is an image.
    Image = 75,
    /// The shape is a textbox. Note that shapes of many other types can also have text inside them too.
    /// A shape does not have to have this type to contain text.
    TextBox = 202,
    /// The shape is a group shape.
    Group = -1,
    /// The shape is an OLE object.
    /// You cannot create shapes of this type in the document.
    OleObject = -2,
    /// The shape is an ActiveX control.
    /// You cannot create shapes of this type in the document.
    OleControl = 201,
    /// A shape drawn by user and consisting of multiple segments and/or vertices (curve, freeform or scribble).
    /// You cannot create shapes of this type in the document.
    NonPrimitive = 0,
    /// Rectangle.
    Rectangle = 1,
    /// Round rectangle.
    RoundRectangle = 2,
    /// Ellipse.
    Ellipse = 3,
    /// Diamond.
    Diamond = 4,
    /// Triangle.
    Triangle = 5,
    /// Right triangle.
    RightTriangle = 6,
    /// Parallelogram.
    Parallelogram = 7,
    /// Trapezoid.
    Trapezoid = 8,
    /// Hexagon.
    Hexagon = 9,
    /// Octagon.
    Octagon = 10,
    /// Plus.
    Plus = 11,
    /// Star.
    Star = 12,
    /// Arrow.
    Arrow = 13,
    /// Thick arrow.
    ThickArrow = 14,
    /// Home plate.
    HomePlate = 15,
    /// Cube.
    Cube = 16,
    /// Balloon.
    Balloon = 17,
    /// Seal.
    Seal = 18,
    /// Arc.
    Arc = 19,
    /// Line.
    Line = 20,
    /// Plaque.
    Plaque = 21,
    /// Can.
    Can = 22,
    /// Donut.
    Donut = 23,
    /// Text simple.
    TextSimple = 24,
    /// Text octagon.
    TextOctagon = 25,
    /// Text hexagon.
    TextHexagon = 26,
    /// Text curve.
    TextCurve = 27,
    /// Text wave.
    TextWave = 28,
    /// Text ring.
    TextRing = 29,
    /// Text on curve.
    TextOnCurve = 30,
    /// Text on ring.
    TextOnRing = 31,
    /// A straight connector shape.
    StraightConnector1 = 32,
    /// A bent connector shape with two segments.
    BentConnector2 = 33,
    /// A bent connector shape with three segments.
    BentConnector3 = 34,
    /// A bent connector shape with four segments.
    BentConnector4 = 35,
    /// A bent connector shape with five segments.
    BentConnector5 = 36,
    /// A curved connector shape with two segments.
    CurvedConnector2 = 37,
    /// A curved connector shape with three segments.
    CurvedConnector3 = 38,
    /// A curved connector shape with four segments.
    CurvedConnector4 = 39,
    /// A curved connector shape with five segments.
    CurvedConnector5 = 40,
    /// A callout shape with one arrow.
    Callout1 = 41,
    /// A callout shape with two arrows.
    Callout2 = 42,
    /// A callout shape with three arrows.
    Callout3 = 43,
    /// An accent callout shape with one arrow.
    AccentCallout1 = 44,
    /// An accent callout shape with two arrows.
    AccentCallout2 = 45,
    /// An accent callout shape with three arrows.
    AccentCallout3 = 46,
    /// Border callout 1.
    BorderCallout1 = 47,
    /// Border callout 2.
    BorderCallout2 = 48,
    /// Border callout 3.
    BorderCallout3 = 49,
    /// Accent border callout 1.
    AccentBorderCallout1 = 50,
    /// Accent border callout 2.
    AccentBorderCallout2 = 51,
    /// Accent border callout 3.
    AccentBorderCallout3 = 52,
    /// Ribbon.
    Ribbon = 53,
    /// Ribbon 2.
    Ribbon2 = 54,
    /// Chevron.
    Chevron = 55,
    /// Pentagon.
    Pentagon = 56,
    /// NoSmoking.
    NoSmoking = 57,
    /// Eight-pointed star.
    Seal8 = 58,
    /// 16-pointed star.
    Seal16 = 59,
    /// 32-pointed star.
    Seal32 = 60,
    /// Wedge rect callout.
    WedgeRectCallout = 61,
    /// Wedge R rect callout.
    WedgeRRectCallout = 62,
    /// Wedge ellipse callout.
    WedgeEllipseCallout = 63,
    /// Wave.
    Wave = 64,
    /// Folded corner.
    FoldedCorner = 65,
    /// Left arrow.
    LeftArrow = 66,
    /// Down arrow.
    DownArrow = 67,
    /// Up arrow.
    UpArrow = 68,
    /// Left right arrow.
    LeftRightArrow = 69,
    /// Up down arrow.
    UpDownArrow = 70,
    /// Irregular seal 1.
    IrregularSeal1 = 71,
    /// Irregular seal 2.
    IrregularSeal2 = 72,
    /// Lightning bolt.
    LightningBolt = 73,
    /// Heart.
    Heart = 74,
    /// Quad arrow.
    QuadArrow = 76,
    /// Left arrow callout.
    LeftArrowCallout = 77,
    /// Right arrow callout
    RightArrowCallout = 78,
    /// Up arrow callout.
    UpArrowCallout = 79,
    /// Down arrow callout.
    DownArrowCallout = 80,
    /// Left right arrow callout.
    LeftRightArrowCallout = 81,
    /// Up down arrow callout.
    UpDownArrowCallout = 82,
    /// Quad arrow callout.
    QuadArrowCallout = 83,
    /// Bevel.
    Bevel = 84,
    /// Left bracket.
    LeftBracket = 85,
    /// Right bracket.
    RightBracket = 86,
    /// Left brace.
    LeftBrace = 87,
    /// Right brace.
    RightBrace = 88,
    /// Left up arrow.
    LeftUpArrow = 89,
    /// Bent up arrow.
    BentUpArrow = 90,
    /// Bent arrow.
    BentArrow = 91,
    /// 24-pointed star.
    Seal24 = 92,
    /// Striped right arrow.
    StripedRightArrow = 93,
    /// Notched right arrow.
    NotchedRightArrow = 94,
    /// Block arc.
    BlockArc = 95,
    /// Smiley face.
    SmileyFace = 96,
    /// Vertical scroll.
    VerticalScroll = 97,
    /// Horizontal scroll.
    HorizontalScroll = 98,
    /// Circular arrow.
    CircularArrow = 99,
    /// This shape type seems to be set for shapes that are not part of the standard set of the
    /// auto shapes in %Microsoft Word. For example, if you insert a new auto shape from ClipArt.
    /// You cannot create shapes of this type in the document.
    CustomShape = 100,
    /// Uturn arrow.
    UturnArrow = 101,
    /// Curved right arrow.
    CurvedRightArrow = 102,
    /// Curved left arrow.
    CurvedLeftArrow = 103,
    /// Curved up arrow
    CurvedUpArrow = 104,
    /// Curved down arrow.
    CurvedDownArrow = 105,
    /// Cloud callout.
    CloudCallout = 106,
    /// Ellipse ribbon.
    EllipseRibbon = 107,
    /// Ellipse ribbon 2.
    EllipseRibbon2 = 108,
    /// Flow chart process.
    FlowChartProcess = 109,
    /// Flow chart decision.
    FlowChartDecision = 110,
    /// Flow chart input output.
    FlowChartInputOutput = 111,
    /// Flow chart predefined process
    FlowChartPredefinedProcess = 112,
    /// Flow chart internal storage.
    FlowChartInternalStorage = 113,
    /// Flow chart document.
    FlowChartDocument = 114,
    /// Flow chart multi document.
    FlowChartMultidocument = 115,
    /// Flow chart terminator.
    FlowChartTerminator = 116,
    /// Flow chart preparation.
    FlowChartPreparation = 117,
    /// Flow chart manual input.
    FlowChartManualInput = 118,
    /// Flow chart manual operation.
    FlowChartManualOperation = 119,
    /// Flow chart connector.
    FlowChartConnector = 120,
    /// Flow chart punched card.
    FlowChartPunchedCard = 121,
    /// Flow chart punched tape.
    FlowChartPunchedTape = 122,
    /// Flow chart summing junction.
    FlowChartSummingJunction = 123,
    /// Flow chart or.
    FlowChartOr = 124,
    /// Flow chart collate.
    FlowChartCollate = 125,
    /// Flow chart sort.
    FlowChartSort = 126,
    /// Flow chart extract.
    FlowChartExtract = 127,
    /// Flow chart merge.
    FlowChartMerge = 128,
    /// Flow chart off-line storage.
    FlowChartOfflineStorage = 129,
    /// Flow chart on-line storage.
    FlowChartOnlineStorage = 130,
    /// Flow char magnetic tape.
    FlowChartMagneticTape = 131,
    /// Flow chart magnetic disk.
    FlowChartMagneticDisk = 132,
    /// Flow chart magnetic drum.
    FlowChartMagneticDrum = 133,
    /// Flow chart display.
    FlowChartDisplay = 134,
    /// Flow chart delay.
    FlowChartDelay = 135,
    /// Plain-text, WordArt object.
    TextPlainText = 136,
    /// Stop, WordArt object.
    TextStop = 137,
    /// Triangle, WordArt object.
    TextTriangle = 138,
    /// Triangle inverted, WordArt object.
    TextTriangleInverted = 139,
    /// Chevron, WordArt object.
    TextChevron = 140,
    /// Chevron inverted, WordArt object.
    TextChevronInverted = 141,
    /// Ring inside, WordArt object.
    TextRingInside = 142,
    /// Ring outside, WordArt object.
    TextRingOutside = 143,
    /// Arch up curve, WordArt object.
    TextArchUpCurve = 144,
    /// Arch down curve, WordArt object.
    TextArchDownCurve = 145,
    /// Circle curve, WordArt object.
    TextCircleCurve = 146,
    /// Button curve, WordArt object.
    TextButtonCurve = 147,
    /// Arch up pour, WordArt object.
    TextArchUpPour = 148,
    /// Arch down pour, WordArt object.
    TextArchDownPour = 149,
    /// Circle pour, WordArt object.
    TextCirclePour = 150,
    /// Button pour, WordArt object.
    TextButtonPour = 151,
    /// Curve up, WordArt object.
    TextCurveUp = 152,
    /// Curve down, WordArt object.
    TextCurveDown = 153,
    /// Cascade up, WordArt object.
    TextCascadeUp = 154,
    /// Cascade down, WordArt object.
    TextCascadeDown = 155,
    /// Wave 1, WordArt object.
    TextWave1 = 156,
    /// Wave 2, WordArt object.
    TextWave2 = 157,
    /// Wave 3, WordArt object.
    TextWave3 = 158,
    /// Wave 4, WordArt object.
    TextWave4 = 159,
    /// Inflate, WordArt object.
    TextInflate = 160,
    /// Deflate, WordArt object.
    TextDeflate = 161,
    /// Inflate bottom, WordArt object.
    TextInflateBottom = 162,
    /// Deflate bottom, WordArt object.
    TextDeflateBottom = 163,
    /// Inflate top, WordArt object.
    TextInflateTop = 164,
    /// Deflate top, WordArt object.
    TextDeflateTop = 165,
    /// Deflate inflate, WordArt object.
    TextDeflateInflate = 166,
    /// Deflate inflate deflate, WordArt object.
    TextDeflateInflateDeflate = 167,
    /// Fade right, WordArt object.
    TextFadeRight = 168,
    /// Fade left, WordArt object.
    TextFadeLeft = 169,
    /// Fade up, WordArt object.
    TextFadeUp = 170,
    /// Fade down, WordArt object.
    TextFadeDown = 171,
    /// Slant up, WordArt object.
    TextSlantUp = 172,
    /// Slant down, WordArt object.
    TextSlantDown = 173,
    /// Can up, WordArt object.
    TextCanUp = 174,
    /// Can down, WordArt object.
    TextCanDown = 175,
    /// Flow chart alternate process.
    FlowChartAlternateProcess = 176,
    /// Flow chart off page connector.
    FlowChartOffpageConnector = 177,
    /// Callout 90.
    Callout90 = 178,
    /// Accent callout 90.
    AccentCallout90 = 179,
    /// Border callout 90.
    BorderCallout90 = 180,
    /// Accent border callout 90.
    AccentBorderCallout90 = 181,
    /// Left right up arrow.
    LeftRightUpArrow = 182,
    /// Sun.
    Sun = 183,
    /// Moon.
    Moon = 184,
    /// Bracket pair.
    BracketPair = 185,
    /// Brace pair
    BracePair = 186,
    /// Four-pointed star.
    Seal4 = 187,
    /// Double wave.
    DoubleWave = 188,
    /// Action button blank.
    ActionButtonBlank = 189,
    /// Action button home.
    ActionButtonHome = 190,
    /// Action button help.
    ActionButtonHelp = 191,
    /// Action button information.
    ActionButtonInformation = 192,
    /// Action button forward next.
    ActionButtonForwardNext = 193,
    /// Action button back previous.
    ActionButtonBackPrevious = 194,
    /// Action button end.
    ActionButtonEnd = 195,
    /// Action button beginning.
    ActionButtonBeginning = 196,
    /// Action button return.
    ActionButtonReturn = 197,
    /// Action button document.
    ActionButtonDocument = 198,
    /// Action button sound.
    ActionButtonSound = 199,
    /// Action button movie.
    ActionButtonMovie = 200,
    /// Snip single corner rectangle object.
    SingleCornerSnipped = 203,
    /// Snip same side corner rectangle.
    TopCornersSnipped = 204,
    /// Snip diagonal corner rectangle.
    DiagonalCornersSnipped = 205,
    /// Snip and round single corner rectangle.
    TopCornersOneRoundedOneSnipped = 206,
    /// Round single corner rectangle.
    SingleCornerRounded = 207,
    /// Round same side corner rectangle.
    TopCornersRounded = 208,
    /// Round diagonal corner rectangle.
    DiagonalCornersRounded = 209,
    /// Heptagon.
    Heptagon = 210,
    /// Cloud.
    Cloud = 211,
    /// Six-pointed star.
    Seal6 = 212,
    /// Seven-pointed star.
    Seal7 = 213,
    /// Ten-pointed star.
    Seal10 = 214,
    /// Twelve-pointed star.
    Seal12 = 215,
    /// Swoosh arrow.
    SwooshArrow = 216,
    /// Teardrop.
    Teardrop = 217,
    /// Square tabs.
    SquareTabs = 218,
    /// Plaque tabs.
    PlaqueTabs = 219,
    /// Pie.
    Pie = 220,
    /// Wedge pie.
    WedgePie = 221,
    /// Inverse line.
    InverseLine = 222,
    /// Math plus.
    MathPlus = 223,
    /// Math minus.
    MathMinus = 224,
    /// Math multiply.
    MathMultiply = 225,
    /// Math divide.
    MathDivide = 226,
    /// Math equal.
    MathEqual = 227,
    /// Math not equal.
    MathNotEqual = 228,
    /// Non-isosceles trapezoid.
    NonIsoscelesTrapezoid = 229,
    /// Left-right circular arrow.
    LeftRightCircularArrow = 230,
    /// Left-right ribbon.
    LeftRightRibbon = 231,
    /// Left circular arrow.
    LeftCircularArrow = 232,
    /// Frame.
    Frame = 233,
    /// Half frame.
    HalfFrame = 234,
    /// Funnel.
    Funnel = 235,
    /// Six-tooth gear.
    Gear6 = 236,
    /// Nine-tooth gear.
    Gear9 = 237,
    /// Decagon.
    Decagon = 238,
    /// Dodecagon.
    Dodecagon = 239,
    /// Diagonal stripe.
    DiagonalStripe = 240,
    /// Corner.
    Corner = 241,
    /// Corner tabs.
    CornerTabs = 242,
    /// Chord.
    Chord = 243,
    /// Chart plus.
    ChartPlus = 244,
    /// Chart star.
    ChartStar = 245,
    /// Chart X.
    ChartX = 246,
    /// Reserved for the system use.
    MinValue = static_cast<int32_t>(OleObject)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ShapeType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ShapeType, const char_t*>, 250>& values();
};
