//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/PreferredWidth.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Tables/PreferredWidthType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Tables {

/// Represents a value and its unit of measure that is used to specify the preferred width of a table or a cell.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
/// 
/// Preferred width can be specified as a percentage, number of points or a special "none/auto" value.
/// 
/// The instances of this class are immutable.
/// 
/// @sa Aspose::Words::Tables::Table::get_PreferredWidth
/// @sa Aspose::Words::Tables::CellFormat::get_PreferredWidth
class ASPOSE_WORDS_SHARED_CLASS PreferredWidth final : public System::Object
{
    typedef PreferredWidth ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns an instance that represents the "preferred width is not specified" value.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::PreferredWidth>& Auto();

    /// Gets the unit of measure used for this preferred width value.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::PreferredWidthType get_Type() const;
    /// Gets the preferred width value. The unit of measure is specified in the <see cref="Aspose::Words::Tables::PreferredWidth::get_Type">Type</see> property.
    ASPOSE_WORDS_SHARED_API double get_Value() const;

    /// A creation method that returns a new instance that represents a preferred width specified as a percentage.
    /// 
    /// @param percent The value must be from 0 to 100.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::PreferredWidth> FromPercent(double percent);
    /// A creation method that returns a new instance that represents a preferred width specified using a number of points.
    /// 
    /// @param points The value must be from 0 to 22 inches (22 * 72 points).
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::PreferredWidth> FromPoints(double points);
    /// Determines whether the specified <see cref="Aspose::Words::Tables::PreferredWidth">PreferredWidth</see> is equal in value to the current <see cref="Aspose::Words::Tables::PreferredWidth">PreferredWidth</see>.
    ASPOSE_WORDS_SHARED_API bool Equals(const System::SharedPtr<Aspose::Words::Tables::PreferredWidth>& other);
    /// Determines whether the specified object is equal in value to the current object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    /// Serves as a hash function for this type.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;
    /// Returns a user-friendly string that displays the value of this object.
    ASPOSE_WORDS_SHARED_API System::String ToString() const override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~PreferredWidth();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;

protected:

private:

};

}
}
}
