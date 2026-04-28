//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/XmlMapping.h
#pragma once

#include <system/array.h>
#include <mutex>
#include <memory>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Markup
{
class CustomXmlPart;

}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IList;
}
}

}

namespace Aspose {

namespace Words {

namespace Markup {

/// Specifies the information that is used to establish a mapping between the parent
/// structured document tag and an XML element stored within a custom XML data part in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS XmlMapping : public System::Object
{
    typedef XmlMapping ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns XML namespace prefix mappings to evaluate the <see cref="Aspose::Words::Markup::XmlMapping::get_XPath">XPath</see>.
    ASPOSE_WORDS_SHARED_API System::String get_PrefixMappings() const;
    /// Returns the XPath expression, which is evaluated to find the custom XML node
    /// that is mapped to the parent structured document tag.
    ASPOSE_WORDS_SHARED_API System::String get_XPath() const;
    /// Returns the custom XML data part to which the parent structured document tag is mapped.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPart> get_CustomXmlPart();
    /// Returns <c>%true</c> if the parent structured document tag is successfully mapped to XML data.
    ASPOSE_WORDS_SHARED_API bool get_IsMapped();
    /// Specifies the custom XML data identifier for the custom XML data part which
    /// shall be used to evaluate the <see cref="Aspose::Words::Markup::XmlMapping::get_XPath">XPath</see> expression.
    ASPOSE_WORDS_SHARED_API System::String get_StoreItemId();

    /// Sets a mapping between the parent structured document tag and an XML node of a custom XML data part.
    /// 
    /// @param customXmlPart A custom XML data part to map to.
    /// @param xPath An XPath expression to find the XML node.
    /// @param prefixMapping XML namespace prefix mappings to evaluate the XPath.
    /// 
    /// @return A flag indicating whether the parent structured document tag is successfully mapped to
    ///     the XML node.
    ASPOSE_WORDS_SHARED_API bool SetMapping(const System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>& customXmlPart, const System::String& xPath, const System::String& prefixMapping);
    /// Deletes mapping of the parent structured document to XML data.
    ASPOSE_WORDS_SHARED_API void Delete();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~XmlMapping();

private:

    System::String mField0;

    System::String mField1;
    System::String mField2;
    System::String mField3;
    System::SharedPtr<System::Object> mField4;
    System::WeakPtr<System::Object> mField5;

};

}
}
}
