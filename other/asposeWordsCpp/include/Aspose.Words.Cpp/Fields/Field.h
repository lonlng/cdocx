//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/Field.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/FieldBundle.h>
#include <Aspose.Words.Cpp/Fields/FieldType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Bidi
{
class IBidiParagraphLevelOverride;
}
namespace Words
{

namespace Fields
{

class FieldChar;

class FieldEnd;

class FieldFormat;

class FieldResultApplier;

class FieldSeparator;

class FieldStart;

class FieldUpdateAction;

enum class FieldUpdateStage;
enum class FieldUpdateStrategy;

class IFieldArgument;

}

class INodeModifier;

class Node;
class NodeRange;

class Section;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerable;
}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents a %Microsoft Word document field.
/// To learn more, visit the  documentation article.
/// 
/// A field in a Word document is a complex structure consisting of multiple nodes that include field start,
/// field code, field separator, field result and field end. Fields can be nested, contain rich content and span
/// multiple paragraphs or sections in a document. The <see cref="Aspose::Words::Fields::Field">Field</see> class is a "facade" object that provides
/// properties and methods that allow to work with a field as a single object.
/// 
/// The <see cref="Aspose::Words::Fields::Field::get_Start">Start</see>, <see cref="Aspose::Words::Fields::Field::get_Separator">Separator</see> and <see cref="Aspose::Words::Fields::Field::get_End">End</see> properties point to the
/// field start, separator and end nodes of the field respectively.
/// 
/// The content between the field start and separator is the field code. The content between the
/// field separator and field end is the field result. The field code typically consists of one or more
/// <see cref="Aspose::Words::Run">Run</see> objects that specify instructions. The processing application is expected to execute
/// the field code to calculate the field result.
/// 
/// The process of calculating field results is called the field update. %Aspose.Words can update field
/// results of most of the field types in exactly the same way as %Microsoft Word does it. Most notably,
/// %Aspose.Words can calculate results of even the most complex formula fields. To calculate the field
/// result of a single field use the <see cref="Aspose::Words::Fields::Field::Update">Update</see> method. To update fields in the whole document
/// use <see cref="Aspose::Words::Document::UpdateFields">UpdateFields</see>.
/// 
/// You can get the plain text version of the field code using the <see cref="Aspose::Words::Fields::Field::GetFieldCode(bool)">GetFieldCode()</see> method.
/// You can get and set the plain text version of the field result using the <see cref="Aspose::Words::Fields::Field::get_Result">Result</see> property.
/// Both the field code and field result can contain complex content, such as nested fields, paragraphs, shapes,
/// tables and in this case you might want to work with the field nodes directly if you need more control.
/// 
/// You do not create instances of the <see cref="Aspose::Words::Fields::Field">Field</see> class directly.
/// To create a new field use the <see cref="Aspose::Words::DocumentBuilder::InsertField(System::String)">InsertField()</see> method.
class ASPOSE_WORDS_SHARED_CLASS Field : public virtual System::Object
{
    typedef Field ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the node that represents the start of the field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() const;
    /// Gets the node that represents the field separator. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldSeparator> get_Separator();
    /// Gets the node that represents the field end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() const;
    /// Gets the node that represents the start of the field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldStart> get_FieldStart() const;
    /// Gets the node that represents the field end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_FieldEnd() const;
    /// Gets the %Microsoft Word field type.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldType get_Type() const;
    /// Gets text that is between the field separator and field end.
    ASPOSE_WORDS_SHARED_API System::String get_Result();
    /// Sets text that is between the field separator and field end.
    ASPOSE_WORDS_SHARED_API void set_Result(const System::String& value);
    /// Gets the text that represents the displayed field result.
    ASPOSE_WORDS_SHARED_API System::String get_DisplayResult();
    /// Gets whether the field is locked (should not recalculate its result).
    ASPOSE_WORDS_SHARED_API bool get_IsLocked();
    /// Sets whether the field is locked (should not recalculate its result).
    ASPOSE_WORDS_SHARED_API void set_IsLocked(bool value);
    /// Gets whether the current result of the field is no longer correct (stale) due to other modifications made to the document.
    ASPOSE_WORDS_SHARED_API bool get_IsDirty();
    /// Sets whether the current result of the field is no longer correct (stale) due to other modifications made to the document.
    ASPOSE_WORDS_SHARED_API void set_IsDirty(bool value);
    /// Gets a <see cref="Aspose::Words::Fields::FieldFormat">FieldFormat</see> object that provides typed access to field's formatting.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldFormat> get_Format();
    /// Gets the LCID of the field.
    /// 
    /// @sa Aspose::Words::Fields::FieldUpdateCultureSource::FieldCode
    ASPOSE_WORDS_SHARED_API int32_t get_LocaleId();
    /// Sets the LCID of the field.
    /// 
    /// @sa Aspose::Words::Fields::FieldUpdateCultureSource::FieldCode
    ASPOSE_WORDS_SHARED_API void set_LocaleId(int32_t value);

    /// Returns text between field start and field separator (or field end if there is no separator).
    /// Both field code and field result of child fields are included.
    ASPOSE_WORDS_SHARED_API System::String GetFieldCode();
    /// Returns text between field start and field separator (or field end if there is no separator).
    /// 
    /// @param includeChildFieldCodes <c>%true</c> if child field codes should be included.
    ASPOSE_WORDS_SHARED_API System::String GetFieldCode(bool includeChildFieldCodes);
    /// Removes the field from the document. Returns a node right after the field. If the field's end is the last child
    /// of its parent node, returns its parent paragraph. If the field is already removed, returns <c>%null</c>.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Remove();
    /// Performs the field update. Throws if the field is being updated already.
    ASPOSE_WORDS_SHARED_API void Update();
    /// Performs a field update. Throws if the field is being updated already.
    /// 
    /// @param ignoreMergeFormat If <c>%true</c> then direct field result formatting is abandoned, regardless of the MERGEFORMAT switch, otherwise normal update is performed.
    ASPOSE_WORDS_SHARED_API void Update(bool ignoreMergeFormat);
    /// Performs the field unlink.
    /// 
    /// Replaces the field with its most recent result.
    /// 
    /// Some fields, such as XE (Index Entry) fields and SEQ (Sequence) fields, cannot be unlinked.
    /// 
    /// @return <c>%true</c> if the field has been unlinked, otherwise <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Unlink();

protected:

    virtual ASPOSE_WORDS_SHARED_API bool get_SupportsConditionalUpdate();

    ASPOSE_WORDS_SHARED_API Field();

    ASPOSE_WORDS_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Field, CODEPORTING_ARGS());

    virtual ASPOSE_WORDS_SHARED_API void Initialize(System::SharedPtr<Aspose::Words::Fields::FieldStart> , System::SharedPtr<Aspose::Words::Fields::FieldSeparator> , System::SharedPtr<Aspose::Words::Fields::FieldEnd> );
    virtual ASPOSE_WORDS_SHARED_API void ParseFieldCode();

    virtual ASPOSE_WORDS_SHARED_API void NotifyChildFieldUpdated(System::SharedPtr<Aspose::Words::Fields::IFieldArgument> );

    virtual ASPOSE_WORDS_SHARED_API void EndUpdate();
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldUpdateStrategy GetChildFieldsUpdateStrategyInArgument(System::SharedPtr<Aspose::Words::Fields::IFieldArgument> );
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldUpdateStage GetUpdateStage();
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore();

    virtual ASPOSE_WORDS_SHARED_API void BeforeUnlink();
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult();

    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Bidi::IBidiParagraphLevelOverride> GetBidiParagraphLevelOverride();

    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> GetPageNumberFormatSection();
    virtual ASPOSE_WORDS_SHARED_API System::String GetDefaultDateTimeFormat();

    virtual ASPOSE_WORDS_SHARED_API bool NeedStoreOldResultNodes();

    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldResultApplier> BuildResultApplier(System::String );

    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::INodeModifier> GetResultModifier();

    virtual ASPOSE_WORDS_SHARED_API ~Field();

private:

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<System::Object> mField1;

    Aspose::Words::Fields::FieldBundle mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::WeakPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;

};

}
}
}
