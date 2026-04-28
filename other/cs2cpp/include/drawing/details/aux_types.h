#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <utility>

namespace System { namespace Drawing { namespace Details {

using tag_t = uint32_t;

using GaspTableData = std::vector<std::pair<uint16_t, uint16_t>>;
using MetaTableData = std::vector<std::pair<tag_t, std::string>>;

}}}
