#ifndef _aspose_zip_events_h_
#define _aspose_zip_events_h_

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/exceptions.h>
#include <system/eventargs.h>
#include <functional>

namespace Aspose { namespace Zip {

class ZipEntry;
class ZipFile;

typedef std::function<bool(int64_t, int64_t, System::String)> ReReadApprovalCallback;
typedef std::function<bool(System::String, System::String)> WantCompressionCallback;

/// In an EventArgs type, indicates which sort of progress event is being reported.
/// There are events for reading, events for saving, and events for extracting.

enum class ZipProgressEventType
{
    Adding_Started,
    Adding_AfterAddEntry,
    Adding_Completed,
    Reading_Started,
    Reading_BeforeReadEntry,
    Reading_AfterReadEntry,
    Reading_Completed,
    Reading_ArchiveBytesRead,
    Saving_Started,
    Saving_BeforeWriteEntry,
    Saving_AfterWriteEntry,
    Saving_Completed,
    Saving_AfterSaveTempArchive,
    Saving_BeforeRenameTempArchive,
    Saving_AfterRenameTempArchive,
    Saving_AfterCompileSelfExtractor,
    Saving_EntryBytesRead,
    Extracting_BeforeExtractEntry,
    Extracting_AfterExtractEntry,
    Extracting_ExtractEntryWouldOverwrite,
    Extracting_EntryBytesWritten,
    Extracting_BeforeExtractAll,
    Extracting_AfterExtractAll,
    Error_Saving
};

/// Provides information about the progress of a save, read, or extract operation.
/// This is a base class; you will probably use one of the classes derived from this one.

class ASPOSECPP_SHARED_CLASS ZipProgressEventArgs : public System::EventArgs
{
    typedef ZipProgressEventArgs ThisType;
    typedef System::EventArgs BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class ZipFile;

public:

    ASPOSECPP_SHARED_API int get_EntriesTotal();
    ASPOSECPP_SHARED_API void set_EntriesTotal(int value);
    ASPOSECPP_SHARED_API System::SharedPtr<ZipEntry> get_CurrentEntry();
    ASPOSECPP_SHARED_API void set_CurrentEntry(const System::SharedPtr<ZipEntry>& value);
    ASPOSECPP_SHARED_API bool get_Cancel();
    ASPOSECPP_SHARED_API void set_Cancel(bool value);
    ASPOSECPP_SHARED_API ZipProgressEventType get_EventType();
    ASPOSECPP_SHARED_API void set_EventType(ZipProgressEventType value);
    ASPOSECPP_SHARED_API System::String get_ArchiveName();
    ASPOSECPP_SHARED_API void set_ArchiveName(const System::String& value);
    ASPOSECPP_SHARED_API int64_t get_BytesTransferred();
    ASPOSECPP_SHARED_API void set_BytesTransferred(int64_t value);
    ASPOSECPP_SHARED_API int64_t get_TotalBytesToTransfer();
    ASPOSECPP_SHARED_API void set_TotalBytesToTransfer(int64_t value);

protected:

    ASPOSECPP_SHARED_API ZipProgressEventArgs();
    ASPOSECPP_SHARED_API ZipProgressEventArgs(const System::String& archiveName, ZipProgressEventType flavor);
    MEMBER_FUNCTION_MAKE_OBJECT(ZipProgressEventArgs, CODEPORTING_ARGS(const System::String& archiveName, ZipProgressEventType flavor), CODEPORTING_ARGS(archiveName, flavor));

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(System::DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "ZipProgressEventArgs"; }
#endif

private:

    int _entriesTotal;
    bool _cancel;
    System::SharedPtr<ZipEntry> _latestEntry;
    ZipProgressEventType _flavor;
    System::String _archiveName;
    int64_t _bytesTransferred;
    int64_t _totalBytesToTransfer;
};

/// Provides information about the progress of a Read operation.

class ASPOSECPP_SHARED_CLASS ReadProgressEventArgs : public ZipProgressEventArgs
{
    typedef ReadProgressEventArgs ThisType;
    typedef ZipProgressEventArgs BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class ZipFile;

protected:

    ASPOSECPP_SHARED_API ReadProgressEventArgs();

    static ASPOSECPP_SHARED_API System::SharedPtr<ReadProgressEventArgs> Before(const System::String& archiveName, int entriesTotal);
    static ASPOSECPP_SHARED_API System::SharedPtr<ReadProgressEventArgs> After(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, int entriesTotal);
    static ASPOSECPP_SHARED_API System::SharedPtr<ReadProgressEventArgs> Started(const System::String& archiveName);
    static ASPOSECPP_SHARED_API System::SharedPtr<ReadProgressEventArgs> ByteUpdate(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, int64_t bytesXferred, int64_t totalBytes);
    static ASPOSECPP_SHARED_API System::SharedPtr<ReadProgressEventArgs> Completed(const System::String& archiveName);

private:

    ASPOSECPP_SHARED_API ReadProgressEventArgs(System::String archiveName, ZipProgressEventType flavor);
    MEMBER_FUNCTION_MAKE_OBJECT(ReadProgressEventArgs, CODEPORTING_ARGS(const System::String& archiveName, ZipProgressEventType flavor), CODEPORTING_ARGS(archiveName, flavor));
};

/// Provides information about the progress of a Add operation.

class ASPOSECPP_SHARED_CLASS AddProgressEventArgs : public ZipProgressEventArgs
{
    typedef AddProgressEventArgs ThisType;
    typedef ZipProgressEventArgs BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class ZipFile;

protected:

    ASPOSECPP_SHARED_API AddProgressEventArgs();

    static ASPOSECPP_SHARED_API System::SharedPtr<AddProgressEventArgs> AfterEntry(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, int entriesTotal);
    static ASPOSECPP_SHARED_API System::SharedPtr<AddProgressEventArgs> Started(const System::String& archiveName);
    static ASPOSECPP_SHARED_API System::SharedPtr<AddProgressEventArgs> Completed(const System::String& archiveName);

private:

    ASPOSECPP_SHARED_API AddProgressEventArgs(System::String archiveName, ZipProgressEventType flavor);
    MEMBER_FUNCTION_MAKE_OBJECT(AddProgressEventArgs, CODEPORTING_ARGS(const System::String& archiveName, ZipProgressEventType flavor), CODEPORTING_ARGS(archiveName, flavor));
};

/// Provides information about the progress of a save operation.

class ASPOSECPP_SHARED_CLASS SaveProgressEventArgs : public ZipProgressEventArgs
{
    typedef SaveProgressEventArgs ThisType;
    typedef ZipProgressEventArgs BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class ZipFile;

public:

    ASPOSECPP_SHARED_API int get_EntriesSaved();

protected:

    ASPOSECPP_SHARED_API SaveProgressEventArgs(const System::String& archiveName, bool before, int entriesTotal, int entriesSaved, const System::SharedPtr<ZipEntry>& entry);
    MEMBER_FUNCTION_MAKE_OBJECT(SaveProgressEventArgs, CODEPORTING_ARGS(const System::String& archiveName, bool before, int entriesTotal, int entriesSaved, const System::SharedPtr<ZipEntry>& entry), CODEPORTING_ARGS(archiveName, before, entriesTotal, entriesSaved, entry));
    ASPOSECPP_SHARED_API SaveProgressEventArgs();
    ASPOSECPP_SHARED_API SaveProgressEventArgs(const System::String& archiveName, ZipProgressEventType flavor);
    MEMBER_FUNCTION_MAKE_OBJECT(SaveProgressEventArgs, CODEPORTING_ARGS(const System::String& archiveName, ZipProgressEventType flavor), CODEPORTING_ARGS(archiveName, flavor));

    static ASPOSECPP_SHARED_API System::SharedPtr<SaveProgressEventArgs> ByteUpdate(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, int64_t bytesXferred, int64_t totalBytes);
    static ASPOSECPP_SHARED_API System::SharedPtr<SaveProgressEventArgs> Started(const System::String& archiveName);
    static ASPOSECPP_SHARED_API System::SharedPtr<SaveProgressEventArgs> Completed(const System::String& archiveName);

private:

    int _entriesSaved;
};

/// Provides information about the progress of the extract operation.

class ASPOSECPP_SHARED_CLASS ExtractProgressEventArgs : public ZipProgressEventArgs
{
    typedef ExtractProgressEventArgs ThisType;
    typedef ZipProgressEventArgs BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class ZipFile;

public:

    ASPOSECPP_SHARED_API int get_EntriesExtracted();
    ASPOSECPP_SHARED_API System::String get_ExtractLocation();

protected:

    ASPOSECPP_SHARED_API ExtractProgressEventArgs(const System::String& archiveName, bool before, int entriesTotal, int entriesExtracted, const System::SharedPtr<ZipEntry>& entry, System::String extractLocation);
    MEMBER_FUNCTION_MAKE_OBJECT(
        ExtractProgressEventArgs,
        CODEPORTING_ARGS(
            const System::String& archiveName,
            bool before,
            int entriesTotal,
            int entriesExtracted,
            const System::SharedPtr<ZipEntry>& entry, System::String extractLocation
        ),
        CODEPORTING_ARGS(
            archiveName,
            before,
            entriesTotal,
            entriesExtracted,
            entry,
            extractLocation
        )
    );

    ASPOSECPP_SHARED_API ExtractProgressEventArgs(const System::String& archiveName, ZipProgressEventType flavor);
    MEMBER_FUNCTION_MAKE_OBJECT(ExtractProgressEventArgs, CODEPORTING_ARGS(const System::String& archiveName, ZipProgressEventType flavor), CODEPORTING_ARGS(archiveName, flavor));
    ASPOSECPP_SHARED_API ExtractProgressEventArgs();

    static ASPOSECPP_SHARED_API System::SharedPtr<ExtractProgressEventArgs> BeforeExtractEntry(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, System::String extractLocation);
    static ASPOSECPP_SHARED_API System::SharedPtr<ExtractProgressEventArgs> ExtractExisting(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, System::String extractLocation);
    static ASPOSECPP_SHARED_API System::SharedPtr<ExtractProgressEventArgs> AfterExtractEntry(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, System::String extractLocation);
    static ASPOSECPP_SHARED_API System::SharedPtr<ExtractProgressEventArgs> ExtractAllStarted(const System::String& archiveName, System::String extractLocation);
    static ASPOSECPP_SHARED_API System::SharedPtr<ExtractProgressEventArgs> ExtractAllCompleted(const System::String& archiveName, System::String extractLocation);
    static ASPOSECPP_SHARED_API System::SharedPtr<ExtractProgressEventArgs> ByteUpdate(const System::String& archiveName, const System::SharedPtr<ZipEntry>& entry, int64_t bytesWritten, int64_t totalBytes);

private:

    int _entriesExtracted;
    System::String _target;
};

/// Provides information about the an error that occurred while zipping.

class ASPOSECPP_SHARED_CLASS ZipErrorEventArgs : public ZipProgressEventArgs
{
    typedef ZipErrorEventArgs ThisType;
    typedef ZipProgressEventArgs BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class ZipFile;

public:

    ASPOSECPP_SHARED_API System::Exception get_Exception();
    ASPOSECPP_SHARED_API System::String get_FileName();

    static ASPOSECPP_SHARED_API System::SharedPtr<ZipErrorEventArgs> Saving(System::String archiveName, const System::SharedPtr<ZipEntry>& entry, System::Exception exception);

private:

    System::Exception _exc;

    ASPOSECPP_SHARED_API ZipErrorEventArgs();
    MEMBER_FUNCTION_MAKE_OBJECT(ZipErrorEventArgs, CODEPORTING_ARGS(), CODEPORTING_ARGS());
};

}} // namespace Aspose::Zip

#endif // _aspose_zip_events_h_

