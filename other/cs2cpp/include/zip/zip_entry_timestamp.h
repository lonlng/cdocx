#ifndef _aspose_zip_zip_entry_timestamp_h_
#define _aspose_zip_zip_entry_timestamp_h_

#include <system/enum_helpers.h>

namespace Aspose { namespace Zip {

// An enum that specifies the type of timestamp available on the ZipEntry.

enum class ZipEntryTimestamp
{
    None = 0,
    DOS = 1,
    Windows = 2,
    Unix = 4,
    InfoZip1 = 8
};

/// @cond
/// Declaration of template arithmetic operators for values of the ZipEntryTimestamp enum type.
DECLARE_ENUM_OPERATORS(Aspose::Zip::ZipEntryTimestamp);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}} // namespace Aspose::Zip

/// Inserts using declaratios for arithmetic operators declared in namespace Aspose::Zip.
DECLARE_USING_ENUM_OPERATORS(Aspose::Zip);

#endif // _aspose_zip_zip_entry_timestamp_h_

