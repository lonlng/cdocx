//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/ContributorCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerable.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Bibliography
{
class Contributor;

}
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

namespace Bibliography {

/// Represents bibliography source contributors.
class ASPOSE_WORDS_SHARED_CLASS ContributorCollection final : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bibliography::Contributor>>
{
    typedef ContributorCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bibliography::Contributor>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the artist of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Artist();
    /// Sets the artist of a source.
    ASPOSE_WORDS_SHARED_API void set_Artist(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the author of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Author();
    /// Sets the author of a source.
    ASPOSE_WORDS_SHARED_API void set_Author(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the book author of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_BookAuthor();
    /// Sets the book author of a source.
    ASPOSE_WORDS_SHARED_API void set_BookAuthor(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the compiler of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Compiler();
    /// Sets the compiler of a source.
    ASPOSE_WORDS_SHARED_API void set_Compiler(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the composer of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Composer();
    /// Sets the composer of a source.
    ASPOSE_WORDS_SHARED_API void set_Composer(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the conductor of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Conductor();
    /// Sets the conductor of a source.
    ASPOSE_WORDS_SHARED_API void set_Conductor(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the counsel of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Counsel();
    /// Sets the counsel of a source.
    ASPOSE_WORDS_SHARED_API void set_Counsel(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the director of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Director();
    /// Sets the director of a source.
    ASPOSE_WORDS_SHARED_API void set_Director(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the editor of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Editor();
    /// Sets the editor of a source.
    ASPOSE_WORDS_SHARED_API void set_Editor(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the interviewee of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Interviewee();
    /// Sets the interviewee of a source.
    ASPOSE_WORDS_SHARED_API void set_Interviewee(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the interviewer of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Interviewer();
    /// Sets the interviewer of a source.
    ASPOSE_WORDS_SHARED_API void set_Interviewer(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the inventor of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Inventor();
    /// Sets the inventor of a source.
    ASPOSE_WORDS_SHARED_API void set_Inventor(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the performer of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Performer();
    /// Sets the performer of a source.
    ASPOSE_WORDS_SHARED_API void set_Performer(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the producer of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Producer();
    /// Sets the producer of a source.
    ASPOSE_WORDS_SHARED_API void set_Producer(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the translator of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Translator();
    /// Sets the translator of a source.
    ASPOSE_WORDS_SHARED_API void set_Translator(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);
    /// Gets the writer of a source.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> get_Writer();
    /// Sets the writer of a source.
    ASPOSE_WORDS_SHARED_API void set_Writer(const System::SharedPtr<Aspose::Words::Bibliography::Contributor>& value);

protected:

    ContributorCollection();

    virtual ASPOSE_WORDS_SHARED_API ~ContributorCollection();

private:

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Bibliography::Contributor>>> GetEnumerator() override;

};

}
}
}
