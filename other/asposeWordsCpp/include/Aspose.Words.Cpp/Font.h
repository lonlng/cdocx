//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Font.h
#pragma once

#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/Themes/ThemeFont.h>
#include <Aspose.Words.Cpp/Themes/ThemeColor.h>
#include <Aspose.Words.Cpp/Underline.h>
#include <Aspose.Words.Cpp/TextEffect.h>
#include <Aspose.Words.Cpp/TextDmlEffect.h>
#include <Aspose.Words.Cpp/NumSpacing.h>
#include <Aspose.Words.Cpp/EmphasisMark.h>
#include <Aspose.Words.Cpp/StyleIdentifier.h>
#include <Aspose.Words.Cpp/IShadingAttrSource.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/Drawing/Core/IFillable.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class Border;
enum class BorderType;

namespace Drawing
{

namespace Core
{
namespace Dml
{
namespace Colors
{
class DmlColor;
}

namespace Themes
{
class IThemeProvider;
}
}
enum class FillTypeCore;
class IFill;
}
class Fill;
class GradientStopCollection;
enum class GradientStyle;
enum class GradientVariant;
enum class PatternType;
enum class PresetTexture;

enum class TextureAlignment;
}

class Shading;
class Style;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class SortedList;
}
}
namespace Drawing
{
class Color;

}
}

namespace Aspose {

namespace Words {

/// Contains font attributes (font name, font size, color, and so on) for an object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
/// 
/// You do not create instances of the <see cref="Aspose::Words::Font">Font</see> class directly. You just use
/// <see cref="Aspose::Words::Font">Font</see> to access the font properties of the various objects such as <see cref="Aspose::Words::Run">Run</see>,
/// <see cref="Aspose::Words::Paragraph">Paragraph</see>, <see cref="Aspose::Words::Style">Style</see>, <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>.
class ASPOSE_WORDS_SHARED_CLASS Font : public Aspose::Words::IBorderAttrSource, public Aspose::Words::IShadingAttrSource, public Aspose::Words::Drawing::Core::IFillable
{
    typedef Font ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;
    typedef Aspose::Words::IShadingAttrSource BaseType1;
    typedef Aspose::Words::Drawing::Core::IFillable BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the name of the font.
    /// 
    /// When getting, returns <see cref="Aspose::Words::Font::get_NameAscii">NameAscii</see>.
    /// 
    /// When setting, sets <see cref="Aspose::Words::Font::get_NameAscii">NameAscii</see>, <see cref="Aspose::Words::Font::get_NameBi">NameBi</see>, <see cref="Aspose::Words::Font::get_NameFarEast">NameFarEast</see>
    /// and <see cref="Aspose::Words::Font::get_NameOther">NameOther</see> to the specified value.
    ASPOSE_WORDS_SHARED_API System::String get_Name();
    /// Setter for Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Returns the font used for Latin text (characters with character codes from 0 (zero) through 127).
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API System::String get_NameAscii();
    /// Sets the font used for Latin text (characters with character codes from 0 (zero) through 127).
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API void set_NameAscii(const System::String& value);
    /// Returns the name of the font in a right-to-left language document.
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API System::String get_NameBi();
    /// Sets the name of the font in a right-to-left language document.
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API void set_NameBi(const System::String& value);
    /// Returns an East Asian font name.
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API System::String get_NameFarEast();
    /// Sets an East Asian font name.
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API void set_NameFarEast(const System::String& value);
    /// Returns the font used for characters with character codes from 128 through 255.
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API System::String get_NameOther();
    /// Sets the font used for characters with character codes from 128 through 255.
    /// 
    /// @sa Aspose::Words::Font::get_Name
    ASPOSE_WORDS_SHARED_API void set_NameOther(const System::String& value);
    /// Gets the theme font in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeFont get_ThemeFont();
    /// Sets the theme font in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API void set_ThemeFont(Aspose::Words::Themes::ThemeFont value);
    /// Gets the theme font used for Latin text (characters with character codes from 0 (zero) through 127)
    /// in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeFont get_ThemeFontAscii();
    /// Sets the theme font used for Latin text (characters with character codes from 0 (zero) through 127)
    /// in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API void set_ThemeFontAscii(Aspose::Words::Themes::ThemeFont value);
    /// Gets the East Asian theme font in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeFont get_ThemeFontFarEast();
    /// Sets the East Asian theme font in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API void set_ThemeFontFarEast(Aspose::Words::Themes::ThemeFont value);
    /// Gets the theme font used for characters with character codes from 128 through 255
    /// in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeFont get_ThemeFontOther();
    /// Sets the theme font used for characters with character codes from 128 through 255
    /// in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API void set_ThemeFontOther(Aspose::Words::Themes::ThemeFont value);
    /// Gets the theme font in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object
    /// in a right-to-left language document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeFont get_ThemeFontBi();
    /// Sets the theme font in the applied font scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object
    /// in a right-to-left language document.
    ASPOSE_WORDS_SHARED_API void set_ThemeFontBi(Aspose::Words::Themes::ThemeFont value);
    /// Gets the font size in points.
    ASPOSE_WORDS_SHARED_API double get_Size();
    /// Sets the font size in points.
    ASPOSE_WORDS_SHARED_API void set_Size(double value);
    /// Gets the font size in points used in a right-to-left document.
    ASPOSE_WORDS_SHARED_API double get_SizeBi();
    /// Sets the font size in points used in a right-to-left document.
    ASPOSE_WORDS_SHARED_API void set_SizeBi(double value);
    /// True if the font is formatted as bold.
    ASPOSE_WORDS_SHARED_API bool get_Bold();
    /// True if the font is formatted as bold.
    ASPOSE_WORDS_SHARED_API void set_Bold(bool value);
    /// True if the right-to-left text is formatted as bold.
    ASPOSE_WORDS_SHARED_API bool get_BoldBi();
    /// True if the right-to-left text is formatted as bold.
    ASPOSE_WORDS_SHARED_API void set_BoldBi(bool value);
    /// True if the font is formatted as italic.
    ASPOSE_WORDS_SHARED_API bool get_Italic();
    /// True if the font is formatted as italic.
    ASPOSE_WORDS_SHARED_API void set_Italic(bool value);
    /// True if the right-to-left text is formatted as italic.
    ASPOSE_WORDS_SHARED_API bool get_ItalicBi();
    /// True if the right-to-left text is formatted as italic.
    ASPOSE_WORDS_SHARED_API void set_ItalicBi(bool value);
    /// Gets the color of the font.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Sets the color of the font.
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets the theme color in the applied color scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeColor get_ThemeColor();
    /// Sets the theme color in the applied color scheme that is associated with this <see cref="Aspose::Words::Font">Font</see> object.
    ASPOSE_WORDS_SHARED_API void set_ThemeColor(Aspose::Words::Themes::ThemeColor value);
    /// Gets or sets a double value that lightens or darkens a color.
    /// 
    /// The allowed values are in range from -1 (darkest) to 1 (lightest) for this property.
    /// 
    /// Zero (0) is neutral.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throw if set this property to a value less than -1 or more than 1.
    /// @exception System::InvalidOperationException Throw if set this property for <see cref="Aspose::Words::Font">Font</see> object with non-theme colors.
    ASPOSE_WORDS_SHARED_API double get_TintAndShade();
    /// Setter for Aspose::Words::Font::get_TintAndShade
    ASPOSE_WORDS_SHARED_API void set_TintAndShade(double value);
    /// Returns the present calculated color of the text (black or white) to be used for 'auto color'.
    /// If the color is not 'auto' then returns <see cref="Aspose::Words::Font::get_Color">Color</see>.
    /// 
    /// When text has 'automatic color', the actual color of text is calculated automatically
    /// so that it is readable against the background color. As you change the background color,
    /// the text color will automatically switch to black or white in MS Word to maximize legibility.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_AutoColor();
    /// True if the font is formatted as strikethrough text.
    ASPOSE_WORDS_SHARED_API bool get_StrikeThrough();
    /// True if the font is formatted as strikethrough text.
    ASPOSE_WORDS_SHARED_API void set_StrikeThrough(bool value);
    /// True if the font is formatted as double strikethrough text.
    ASPOSE_WORDS_SHARED_API bool get_DoubleStrikeThrough();
    /// True if the font is formatted as double strikethrough text.
    ASPOSE_WORDS_SHARED_API void set_DoubleStrikeThrough(bool value);
    /// True if the font is formatted as shadowed.
    ASPOSE_WORDS_SHARED_API bool get_Shadow();
    /// True if the font is formatted as shadowed.
    ASPOSE_WORDS_SHARED_API void set_Shadow(bool value);
    /// True if the font is formatted as outline.
    ASPOSE_WORDS_SHARED_API bool get_Outline();
    /// True if the font is formatted as outline.
    ASPOSE_WORDS_SHARED_API void set_Outline(bool value);
    /// True if the font is formatted as embossed.
    ASPOSE_WORDS_SHARED_API bool get_Emboss();
    /// True if the font is formatted as embossed.
    ASPOSE_WORDS_SHARED_API void set_Emboss(bool value);
    /// True if the font is formatted as engraved.
    ASPOSE_WORDS_SHARED_API bool get_Engrave();
    /// True if the font is formatted as engraved.
    ASPOSE_WORDS_SHARED_API void set_Engrave(bool value);
    /// True if the font is formatted as superscript.
    ASPOSE_WORDS_SHARED_API bool get_Superscript();
    /// True if the font is formatted as superscript.
    ASPOSE_WORDS_SHARED_API void set_Superscript(bool value);
    /// True if the font is formatted as subscript.
    ASPOSE_WORDS_SHARED_API bool get_Subscript();
    /// True if the font is formatted as subscript.
    ASPOSE_WORDS_SHARED_API void set_Subscript(bool value);
    /// True if the font is formatted as small capital letters.
    ASPOSE_WORDS_SHARED_API bool get_SmallCaps();
    /// True if the font is formatted as small capital letters.
    ASPOSE_WORDS_SHARED_API void set_SmallCaps(bool value);
    /// True if the font is formatted as all capital letters.
    ASPOSE_WORDS_SHARED_API bool get_AllCaps();
    /// True if the font is formatted as all capital letters.
    ASPOSE_WORDS_SHARED_API void set_AllCaps(bool value);
    /// True if the font is formatted as hidden text.
    ASPOSE_WORDS_SHARED_API bool get_Hidden();
    /// True if the font is formatted as hidden text.
    ASPOSE_WORDS_SHARED_API void set_Hidden(bool value);
    /// Gets the type of underline applied to the font.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Underline get_Underline();
    /// Sets the type of underline applied to the font.
    ASPOSE_WORDS_SHARED_API void set_Underline(Aspose::Words::Underline value);
    /// Gets the color of the underline applied to the font.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_UnderlineColor();
    /// Sets the color of the underline applied to the font.
    ASPOSE_WORDS_SHARED_API void set_UnderlineColor(System::Drawing::Color value);
    /// Gets the spacing type of the numeral being displayed.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NumSpacing get_NumberSpacing();
    /// Sets the spacing type of the numeral being displayed.
    ASPOSE_WORDS_SHARED_API void set_NumberSpacing(Aspose::Words::NumSpacing value);
    /// Gets character width scaling in percent.
    ASPOSE_WORDS_SHARED_API int32_t get_Scaling();
    /// Sets character width scaling in percent.
    ASPOSE_WORDS_SHARED_API void set_Scaling(int32_t value);
    /// Returns the spacing (in points) between characters .
    ASPOSE_WORDS_SHARED_API double get_Spacing();
    /// Sets the spacing (in points) between characters .
    ASPOSE_WORDS_SHARED_API void set_Spacing(double value);
    /// Returns line spacing of this font (in points).
    ASPOSE_WORDS_SHARED_API double get_LineSpacing();
    /// Gets the position of text (in points) relative to the base line.
    /// A positive number raises the text, and a negative number lowers it.
    ASPOSE_WORDS_SHARED_API double get_Position();
    /// Sets the position of text (in points) relative to the base line.
    /// A positive number raises the text, and a negative number lowers it.
    ASPOSE_WORDS_SHARED_API void set_Position(double value);
    /// Gets the font size at which kerning starts.
    ASPOSE_WORDS_SHARED_API double get_Kerning();
    /// Sets the font size at which kerning starts.
    ASPOSE_WORDS_SHARED_API void set_Kerning(double value);
    /// Gets the highlight (marker) color.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_HighlightColor();
    /// Sets the highlight (marker) color.
    ASPOSE_WORDS_SHARED_API void set_HighlightColor(System::Drawing::Color value);
    /// Gets the font animation effect.
    ASPOSE_WORDS_SHARED_API Aspose::Words::TextEffect get_TextEffect();
    /// Sets the font animation effect.
    ASPOSE_WORDS_SHARED_API void set_TextEffect(Aspose::Words::TextEffect value);
    /// Gets fill formatting for the <see cref="Aspose::Words::Font">Font</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Fill> get_Fill();
    /// Specifies whether the contents of this run shall have right-to-left characteristics.
    /// 
    /// This property, when on, shall not be used with strongly left-to-right text. Any behavior under that condition is unspecified.
    /// This property, when off, shall not be used with strong right-to-left text. Any behavior under that condition is unspecified.
    /// 
    /// When the contents of this run are displayed, all characters shall be treated as complex script characters for formatting
    /// purposes. This means that <see cref="Aspose::Words::Font::get_BoldBi">BoldBi</see>, <see cref="Aspose::Words::Font::get_ItalicBi">ItalicBi</see>, <see cref="Aspose::Words::Font::get_SizeBi">SizeBi</see> and a corresponding font name
    /// will be used when rendering this run.
    /// 
    /// Also, when the contents of this run are displayed, this property acts as a right-to-left override for characters
    /// which are classified as "weak types" and "neutral types".
    ASPOSE_WORDS_SHARED_API bool get_Bidi();
    /// Setter for Aspose::Words::Font::get_Bidi
    ASPOSE_WORDS_SHARED_API void set_Bidi(bool value);
    /// Specifies whether the contents of this run shall be treated as complex script text regardless
    /// of their Unicode character values when determining the formatting for this run.
    ASPOSE_WORDS_SHARED_API bool get_ComplexScript();
    /// Specifies whether the contents of this run shall be treated as complex script text regardless
    /// of their Unicode character values when determining the formatting for this run.
    ASPOSE_WORDS_SHARED_API void set_ComplexScript(bool value);
    /// True when the formatted characters are not to be spell checked.
    ASPOSE_WORDS_SHARED_API bool get_NoProofing();
    /// True when the formatted characters are not to be spell checked.
    ASPOSE_WORDS_SHARED_API void set_NoProofing(bool value);
    /// Gets the locale identifier (language) of the formatted characters.
    ASPOSE_WORDS_SHARED_API int32_t get_LocaleId();
    /// Sets the locale identifier (language) of the formatted characters.
    ASPOSE_WORDS_SHARED_API void set_LocaleId(int32_t value);
    /// Gets the locale identifier (language) of the formatted right-to-left characters.
    ASPOSE_WORDS_SHARED_API int32_t get_LocaleIdBi();
    /// Sets the locale identifier (language) of the formatted right-to-left characters.
    ASPOSE_WORDS_SHARED_API void set_LocaleIdBi(int32_t value);
    /// Gets the locale identifier (language) of the formatted Asian characters.
    ASPOSE_WORDS_SHARED_API int32_t get_LocaleIdFarEast();
    /// Sets the locale identifier (language) of the formatted Asian characters.
    ASPOSE_WORDS_SHARED_API void set_LocaleIdFarEast(int32_t value);
    /// Returns a <see cref="Aspose::Words::Border">Border</see> object that specifies border for the font.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Border> get_Border();
    /// Returns a <see cref="Aspose::Words::Shading">Shading</see> object that refers to the shading formatting for the font.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Shading> get_Shading();
    /// Gets the character style applied to this formatting.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> get_Style();
    /// Sets the character style applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_Style(const System::SharedPtr<Aspose::Words::Style>& value);
    /// Gets the name of the character style applied to this formatting.
    ASPOSE_WORDS_SHARED_API System::String get_StyleName();
    /// Sets the name of the character style applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_StyleName(const System::String& value);
    /// Gets the locale independent style identifier of the character style applied to this formatting.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StyleIdentifier get_StyleIdentifier();
    /// Sets the locale independent style identifier of the character style applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_StyleIdentifier(Aspose::Words::StyleIdentifier value);
    /// Specifies whether the current font should use the document grid characters per line settings
    /// when laying out.
    ASPOSE_WORDS_SHARED_API bool get_SnapToGrid();
    /// Specifies whether the current font should use the document grid characters per line settings
    /// when laying out.
    ASPOSE_WORDS_SHARED_API void set_SnapToGrid(bool value);
    /// Gets the emphasis mark applied to this formatting.
    ASPOSE_WORDS_SHARED_API Aspose::Words::EmphasisMark get_EmphasisMark();
    /// Sets the emphasis mark applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_EmphasisMark(Aspose::Words::EmphasisMark value);

    /// Resets to default font formatting.
    /// 
    /// Removes all font formatting specified explicitly on the object from which
    /// <see cref="Aspose::Words::Font">Font</see> was obtained so the font formatting will be inherited from
    /// the appropriate parent.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();
    /// Checks if particular DrawingML text effect is applied.
    /// 
    /// @param dmlEffectType DrawingML text effect type.
    /// 
    /// @return <c>%true</c> if particular DrawingML text effect is applied.
    ASPOSE_WORDS_SHARED_API bool HasDmlEffect(Aspose::Words::TextDmlEffect dmlEffectType);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Font();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;
    System::Drawing::Color get_FilledColor() override;
    void set_FilledColor(System::Drawing::Color ) override;
    bool get_OldOn() override;
    void set_OldOn(bool ) override;
    double get_OldOpacity() override;
    void set_OldOpacity(double ) override;
    System::ArrayPtr<uint8_t> get_FillableImageBytes() override;
    Aspose::Words::Drawing::TextureAlignment get_TextureAlignment() override;
    void set_TextureAlignment(Aspose::Words::Drawing::TextureAlignment ) override;
    double get_GradientAngle() override;
    void set_GradientAngle(double ) override;
    Aspose::Words::Drawing::GradientVariant get_GradientVariant() override;
    Aspose::Words::Drawing::GradientStyle get_GradientStyle() override;
    System::SharedPtr<Aspose::Words::Drawing::GradientStopCollection> get_GradientStops() override;
    System::Drawing::Color get_FillableForeColor() override;
    void set_FillableForeColor(System::Drawing::Color ) override;
    System::Drawing::Color get_FillableBaseForeColor() override;
    System::Drawing::Color get_FillableBackColor() override;
    void set_FillableBackColor(System::Drawing::Color ) override;
    Aspose::Words::Themes::ThemeColor get_FillableForeThemeColor() override;
    void set_FillableForeThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    Aspose::Words::Themes::ThemeColor get_FillableBackThemeColor() override;
    void set_FillableBackThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    double get_FillableForeTintAndShade() override;
    void set_FillableForeTintAndShade(double ) override;
    double get_FillableBackTintAndShade() override;
    void set_FillableBackTintAndShade(double ) override;
    bool get_FillableVisible() override;
    void set_FillableVisible(bool ) override;
    double get_FillableTransparency() override;
    void set_FillableTransparency(double ) override;
    bool get_RotateWithObject() override;
    void set_RotateWithObject(bool ) override;
    Aspose::Words::Drawing::Core::FillTypeCore get_FillType() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_FillableThemeProvider() override;

    System::WeakPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;
    System::SharedPtr<System::Object> FetchInheritedShadingAttr(int32_t ) override;
    void Solid() override;
    Aspose::Words::Drawing::PresetTexture GetPresetTexture() override;
    Aspose::Words::Drawing::PatternType GetPatternType() override;
    void PresetTextured(Aspose::Words::Drawing::PresetTexture ) override;
    void Patterned(Aspose::Words::Drawing::PatternType ) override;
    void TwoColorGradient(Aspose::Words::Drawing::GradientStyle , Aspose::Words::Drawing::GradientVariant ) override;
    void OneColorGradient(Aspose::Words::Drawing::GradientStyle , Aspose::Words::Drawing::GradientVariant , double ) override;
    void SetImage(System::ArrayPtr<uint8_t> ) override;
    void SetFill(System::SharedPtr<Aspose::Words::Drawing::Core::IFill> ) override;
    double GetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> ) override;
    void SetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> , double ) override;

};

}
}
