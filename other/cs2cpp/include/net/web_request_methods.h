/// @file net/web_request_methods.h
#pragma once

#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net {

/// Represents the string constants of web requests.
class ASPOSECPP_SHARED_API WebRequestMethods
{
public:
    /// Represents the string constants of FTP.
    class ASPOSECPP_SHARED_CLASS Ftp
    {
    public:
        /// The string representation of the 'RETR' method of FTP.
        static ASPOSECPP_SHARED_API const String DownloadFile;
        /// The string representation of the 'NLST' method of FTP.
        static ASPOSECPP_SHARED_API const String ListDirectory;
        /// The string representation of the 'STOR' method of FTP.
        static ASPOSECPP_SHARED_API const String UploadFile;
        /// The string representation of the 'DELE' method of FTP.
        static ASPOSECPP_SHARED_API const String DeleteFile;
        /// The string representation of the 'APPE' method of FTP.
        static ASPOSECPP_SHARED_API const String AppendFile;
        /// The string representation of the 'SIZE' method of FTP.
        static ASPOSECPP_SHARED_API const String GetFileSize;
        /// The string representation of the 'STOU' method of FTP.
        static ASPOSECPP_SHARED_API const String UploadFileWithUniqueName;
        /// The string representation of the 'MKD' method of FTP.
        static ASPOSECPP_SHARED_API const String MakeDirectory;
        /// The string representation of the 'RMD' method of FTP.
        static ASPOSECPP_SHARED_API const String RemoveDirectory;
        /// The string representation of the 'LIST' method of FTP.
        static ASPOSECPP_SHARED_API const String ListDirectoryDetails;
        /// The string representation of the 'MDTM' method of FTP.
        static ASPOSECPP_SHARED_API const String GetDateTimestamp;
        /// The string representation of the 'PWD' method of FTP.
        static ASPOSECPP_SHARED_API const String PrintWorkingDirectory;
        /// The string representation of the 'RENAME' method of FTP.
        static ASPOSECPP_SHARED_API const String Rename;

        /// The deleted default constructor.
        Ftp() = delete;
    };

    /// Represents the string constants of HTTP.
    class ASPOSECPP_SHARED_CLASS Http
    {
    public:
        /// The string representation of the 'GET' method of HTTP.
        static ASPOSECPP_SHARED_API const String Get;
        /// The string representation of the 'CONNECT' method of HTTP.
        static ASPOSECPP_SHARED_API const String Connect;
        /// The string representation of the 'HEAD' method of HTTP.
        static ASPOSECPP_SHARED_API const String Head;
        /// The string representation of the 'PUT' method of HTTP.
        static ASPOSECPP_SHARED_API const String Put;
        /// The string representation of the 'POST' method of HTTP.
        static ASPOSECPP_SHARED_API const String Post;
        /// The string representation of the 'MKCOL' method of HTTP.
        static ASPOSECPP_SHARED_API const String MkCol;

        /// The deleted default constructor.
        Http() = delete;
    };

    /// Represents the string constants for downloading and uploading a file.
    class ASPOSECPP_SHARED_CLASS File
    {
    public:
        /// The string representation of the 'GET' method of FILE.
        static ASPOSECPP_SHARED_API const String DownloadFile;
        /// The string representation of the 'PUT' method of FILE.
        static ASPOSECPP_SHARED_API const String UploadFile;

        /// The deleted default constructor.
        File() = delete;
    };
};

}} // namespace System::Net
