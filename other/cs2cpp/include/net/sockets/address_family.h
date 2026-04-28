/// @file net/sockets/address_family.h
#pragma once

#include <system/enum_helpers.h>

namespace System {
namespace Net {
namespace Sockets {

/// Enumerates the address families.
enum class AddressFamily
{
    /// The unknown address family.
    Unknown = -1,
    /// The unspecified address family.
    Unspecified = 0,
    /// The Unix local to host the address family.
    Unix = 1,
    /// The address for IPv4.
    InterNetwork = 2,
    /// The ARPANET IMP address.
    ImpLink = 3,
    /// The address for the PUP protocols.
    Pup = 4,
    /// The address for the MIT CHAOS protocols.
    Chaos = 5,
    /// The address for the Xerox NS protocols.
    NS = 6,
    /// The IPX or SPX address.
    Ipx = NS,
    /// The address for the ISO protocols.
    Iso = 7,
    /// The address for the OSI protocols.
    Osi = Iso,
    /// The European Computer Manufacturers Association (ECMA) address.
    Ecma = 8,
    /// The address for the Datakit protocols.
    DataKit = 9,
    /// Addresses for the CCITT protocols, e.g. X.25.
    Ccitt = 10,
    /// The IBM SNA address.
    Sna = 11,
    /// The DECnet address.
    DecNet = 12,
    /// The direct data-link interface address.
    DataLink = 13,
    /// The LAT address.
    Lat = 14,
    /// The NSC Hyperchannel address.
    HyperChannel = 15,
    /// The AppleTalk address.
    AppleTalk = 16,
    /// The NetBios address.
    NetBios = 17,
    /// The VoiceView address.
    VoiceView = 18,
    /// The FireFox address.
    FireFox = 19,
    /// The Banyan address.
    Banyan = 21,
    /// The native ATM services address.
    Atm = 22,
    /// The address for IPv6.
    InterNetworkV6 = 23,
    /// The address for the Microsoft cluster products.
    Cluster = 24,
    /// The IEEE 1284.4 workgroup address.
    Ieee12844 = 25,
    /// The IrDA address.
    Irda = 26,
    /// The address for the Network Designers OSI gateway-enabled protocols.
    NetworkDesigners = 28,
    /// The MAX address.
    Max = 29
};

/// @cond
/// Declaration of template arithmetic operators for values of the AddressFamily enum type.
DECLARE_ENUM_OPERATORS(System::Net::Sockets::AddressFamily);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
} // namespace Sockets
} // namespace Net
} // namespace System

/// Inserts using declarations for arithmetic operators declared in namespace System::Net::Sockets.
DECLARE_USING_ENUM_OPERATORS(System::Net::Sockets);
