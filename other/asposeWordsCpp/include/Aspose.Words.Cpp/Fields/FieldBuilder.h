//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldBuilder.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/FieldType.h>
#include <Aspose.Words.Cpp/Fields/IFieldBuildingBlock.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBuilder;
namespace Fields
{
class Field;
class FieldArgumentBuilder;

}
class Inline;

class Paragraph;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Builds a field from field code tokens (arguments and switches).
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldBuilder : public Aspose::Words::Fields::IFieldBuildingBlock
{
    typedef FieldBuilder ThisType;
    typedef Aspose::Words::Fields::IFieldBuildingBlock BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Initializes an instance of the <see cref="Aspose::Words::Fields::FieldBuilder">FieldBuilder</see> class.
    /// 
    /// @param fieldType The type of the field to build.
    ASPOSE_WORDS_SHARED_API FieldBuilder(Aspose::Words::Fields::FieldType fieldType);

    /// Adds a field's argument.
    /// 
    /// @param argument The argument value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddArgument(const System::String& argument);
    /// Adds a field's argument.
    /// 
    /// @param argument The argument value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddArgument(int32_t argument);
    /// Adds a field's argument.
    /// 
    /// @param argument The argument value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddArgument(double argument);
    /// Adds a child field represented by another <see cref="Aspose::Words::Fields::FieldBuilder">FieldBuilder</see> to the field's code.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddArgument(const System::SharedPtr<Aspose::Words::Fields::FieldBuilder>& argument);
    /// Adds a field's argument represented by <see cref="Aspose::Words::Fields::FieldArgumentBuilder">FieldArgumentBuilder</see> to the field's code.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddArgument(const System::SharedPtr<Aspose::Words::Fields::FieldArgumentBuilder>& argument);
    /// Adds a field's switch.
    /// 
    /// @param switchName The switch name.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddSwitch(const System::String& switchName);
    /// Adds a field's switch.
    /// 
    /// @param switchName The switch name.
    /// @param switchArgument The switch value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddSwitch(const System::String& switchName, const System::String& switchArgument);
    /// Adds a field's switch.
    /// 
    /// @param switchName The switch name.
    /// @param switchArgument The switch value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddSwitch(const System::String& switchName, int32_t switchArgument);
    /// Adds a field's switch.
    /// 
    /// @param switchName The switch name.
    /// @param switchArgument The switch value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldBuilder> AddSwitch(const System::String& switchName, double switchArgument);
    /// Builds and inserts a field into the document before the specified inline node.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the inserted field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> BuildAndInsert(const System::SharedPtr<Aspose::Words::Inline>& refNode);
    /// Builds and inserts a field into the document to the end of the specified paragraph.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the inserted field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> BuildAndInsert(const System::SharedPtr<Aspose::Words::Paragraph>& refNode);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FieldBuilder();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

    void BuildBlock(System::SharedPtr<Aspose::Words::DocumentBuilder> ) override;

};

}
}
}
