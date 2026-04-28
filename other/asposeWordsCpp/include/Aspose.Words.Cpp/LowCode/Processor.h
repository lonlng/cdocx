//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Processor.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Loading
{
class LoadOptions;
}
namespace LowCode
{

class OutputDocument;

}
namespace Saving
{
class SaveOptions;
}
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
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Processor class for performing different document processing actions.
class ASPOSE_WORDS_SHARED_CLASS Processor : public System::Object
{
    typedef Processor ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies input document for processing.
    /// 
    /// @param input Input document file name.
    /// 
    /// @return Returns processor with specified input file.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> From(const System::String& input);
    /// Specifies input document for processing.
    /// 
    /// @param input Input document file name.
    /// @param loadOptions Optional load options used to load the document.
    /// 
    /// @return Returns processor with specified input file.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> From(const System::String& input, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);
    /// Specifies input document for processing.
    /// 
    /// @param input Input document stream.
    /// 
    /// @return Returns processor with specified input file stream.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> From(const System::SharedPtr<System::IO::Stream>& input);
    /// Specifies input document for processing.
    /// 
    /// @param input Input document stream.
    /// @param loadOptions Optional load options used to load the document.
    /// 
    /// @return Returns processor with specified input file stream.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> From(const System::SharedPtr<System::IO::Stream>& input, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);
    /// Specifies output file for the processor.
    /// 
    /// @param output Output file name.
    /// 
    /// @return Returns processor with specified output file.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::String& output);
    /// Specifies output file for the processor.
    /// 
    /// @param output Output file name.
    /// @param saveOptions Optional save options. If not specified, save format is determined by the file extension.
    /// 
    /// @return Returns processor with specified output file.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::String& output, System::SharedPtr<Aspose::Words::Saving::SaveOptions> saveOptions);
    /// Specifies output file for the processor.
    /// 
    /// @param output Output file name.
    /// @param saveFormat Save format. If not specified, save format is determined by the file extension.
    /// 
    /// @return Returns processor with specified output file.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::String& output, Aspose::Words::SaveFormat saveFormat);
    /// Specifies output stream for the processor.
    /// 
    /// @param output Output stream.
    /// @param saveOptions Save options.
    /// 
    /// @return Returns processor with specified output stream.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::SharedPtr<System::IO::Stream>& output, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Specifies output stream for the processor.
    /// 
    /// @param output Output stream.
    /// @param saveFormat Save format.
    /// 
    /// @return Returns processor with specified output stream.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::SharedPtr<System::IO::Stream>& output, Aspose::Words::SaveFormat saveFormat);
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<System::IO::Stream>>>& output, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Processor> To(const System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<System::IO::Stream>>>& output, Aspose::Words::SaveFormat saveFormat);
    /// Execute the processor action.
    ASPOSE_WORDS_SHARED_API void Execute();

protected:

    System::SharedPtr<System::Object> mField0;

    virtual ASPOSE_WORDS_SHARED_API void ExecuteCore();
    virtual ASPOSE_WORDS_SHARED_API void CheckArgumentsSet();
    virtual ASPOSE_WORDS_SHARED_API void AddOutput(System::SharedPtr<Aspose::Words::LowCode::OutputDocument> );

    virtual ASPOSE_WORDS_SHARED_API ~Processor();

private:

    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
}
