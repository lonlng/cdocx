//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/StyleCollection.h
#pragma once

#include <system/enum_helpers.h>
#include <system/collections/ienumerable.h>
#include <system/collections/icomparer.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/StyleType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class DocumentBase;

class Font;

class ParagraphFormat;

class Style;
enum class StyleIdentifier;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class IEnumerator;
}
}
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::Style">Style</see> objects that represent both the built-in and user-defined styles in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-styles-and-themes/">Working with Styles and Themes</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS StyleCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Style>>
{
    typedef StyleCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Style>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the owner document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentBase> get_Document() const;
    /// Gets document default text formatting.
    /// 
    /// Note that document-wide defaults were introduced in %Microsoft Word 2007 and are fully supported in OOXML formats (<see cref="Aspose::Words::LoadFormat::Docx">Docx</see>) only.
    /// Earlier document formats have limited support for this feature and only font names can be stored.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_DefaultFont();
    /// Gets document default paragraph formatting.
    /// 
    /// Note that document-wide defaults were introduced in %Microsoft Word 2007 and are fully supported in OOXML formats (<see cref="Aspose::Words::LoadFormat::Docx">Docx</see>) only.
    /// Earlier document formats have no support for document default paragraph formatting.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ParagraphFormat> get_DefaultParagraphFormat();
    /// Gets the number of styles in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Removes all styles from the Quick Style Gallery panel.
    ASPOSE_WORDS_SHARED_API void ClearQuickStyleGallery();

    /// Gets a style by name or alias.
    /// 
    /// Case sensitive, returns <c>%null</c> if the style with the given name is not found.
    /// 
    /// If this is an English name of a built in style that does not yet exist, automatically creates it.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> idx_get(const System::String& name);
    /// Gets a built-in style by its locale independent identifier.
    /// 
    /// When accessing a style that does not yet exist, automatically creates it.
    /// 
    /// @param sti A <see cref="Aspose::Words::StyleIdentifier">StyleIdentifier</see> value that specifies the built in style to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> idx_get(Aspose::Words::StyleIdentifier sti);
    /// Gets a style by index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> idx_get(int32_t index);

    /// Gets an enumerator object that will enumerate styles in the alphabetical order of their names.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Style>>> GetEnumerator() override;
    /// Creates a new user defined style and adds it the collection.
    /// 
    /// You can create character, paragraph or a list style.
    /// 
    /// When creating a list style, the style is created with default numbered list formatting (1 \\ a \\ i).
    /// 
    /// Throws an exception if a style with this name already exists.
    /// 
    /// @param type A <see cref="Aspose::Words::StyleType">StyleType</see> value that specifies the type of the style to create.
    /// @param name Case sensitive name of the style to create.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> Add(Aspose::Words::StyleType type, const System::String& name);
    /// Copies a style into this collection.
    /// 
    /// Style to be copied can belong to the same document as well as to different document.
    /// 
    /// Linked style is copied.
    /// 
    /// This method does doesn't copy base styles.
    /// 
    /// If collection already contains a style with the same name, then new name is
    /// automatically generated by adding "_number" suffix starting from 0 e.g. "Normal_0", "Heading 1_1" etc.
    /// Use <see cref="Aspose::Words::Style::get_Name">Name</see> setter for changing the name of the imported style.
    /// 
    /// @param style Style to be copied.
    /// 
    /// @return Copied style ready for usage.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> AddCopy(const System::SharedPtr<Aspose::Words::Style>& style);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~StyleCollection();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;

    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;

protected:

};

}
}
