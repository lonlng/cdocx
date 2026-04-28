/// @file net/sockets/protocol_family.h
#pragma once

#include <net/sockets/address_family.h>

#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Enumerates the protocol families.
enum class ProtocolFamily
{
    /// An unknown protocol.
    Unknown = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Unknown),
    /// An unspecified protocol.
    Unspecified = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Unspecified),
    /// The Unix local to host protocol.
    Unix = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Unix),
    /// IPv4.
    InterNetwork = static_cast<int32_t>(System::Net::Sockets::AddressFamily::InterNetwork),
    /// The ARPANET IMP protocol.
    ImpLink = static_cast<int32_t>(System::Net::Sockets::AddressFamily::ImpLink),
    /// The PUP protocol.
    Pup = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Pup),
    /// The MIT CHAOS protocol.
    Chaos = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Chaos),
    /// The Xerox NS protocol.
    NS = static_cast<int32_t>(System::Net::Sockets::AddressFamily::NS),
    /// The IPX or SPX protocol.
    Ipx = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Ipx),
    /// The ISO protocol.
    Iso = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Iso),
    /// The OSI protocol.
    Osi = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Osi),
    /// The European Computer Manufacturers Association (ECMA) protocol.
    Ecma = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Ecma),
    /// The DataKit protocol.
    DataKit = static_cast<int32_t>(System::Net::Sockets::AddressFamily::DataKit),
    /// The CCITT protocol, such as X.25.
    Ccitt = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Ccitt),
    /// The IBM SNA protocol.
    Sna = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Sna),
    /// The DECNet protocol.
    DecNet = static_cast<int32_t>(System::Net::Sockets::AddressFamily::DecNet),
    /// The direct data link protocol.
    DataLink = static_cast<int32_t>(System::Net::Sockets::AddressFamily::DataLink),
    /// The LAT protocol.
    Lat = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Lat),
    /// The NSC HyperChannel protocol.
    HyperChannel = static_cast<int32_t>(System::Net::Sockets::AddressFamily::HyperChannel),
    /// The AppleTalk protocol.
    AppleTalk = static_cast<int32_t>(System::Net::Sockets::AddressFamily::AppleTalk),
    /// The NetBIOS protocol.
    NetBios = static_cast<int32_t>(System::Net::Sockets::AddressFamily::NetBios),
    /// The VoiceView protocol.
    VoiceView = static_cast<int32_t>(System::Net::Sockets::AddressFamily::VoiceView),
    /// The FireFox protocol.
    FireFox = static_cast<int32_t>(System::Net::Sockets::AddressFamily::FireFox),
    /// The Banyan protocol.
    Banyan = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Banyan),
    /// The native ATM services protocol.
    Atm = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Atm),
    /// IPv6.
    InterNetworkV6 = static_cast<int32_t>(System::Net::Sockets::AddressFamily::InterNetworkV6),
    /// The Microsoft Cluster products protocol.
    Cluster = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Cluster),
    /// The IEEE 1284.4 workgroup protocol.
    Ieee12844 = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Ieee12844),
    /// The IrDA protocol.
    Irda = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Irda),
    /// The Network Designers OSI gateway enabled protocol.
    NetworkDesigners = static_cast<int32_t>(System::Net::Sockets::AddressFamily::NetworkDesigners),
    /// The MAX protocol.
    Max = static_cast<int32_t>(System::Net::Sockets::AddressFamily::Max)
};
} // namespace Sockets
} // namespace Net
} // namespace System
