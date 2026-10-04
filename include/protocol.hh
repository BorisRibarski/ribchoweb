#pragma once

#include <cstdint>
#include <type_traits>

namespace proto {
/*
 * Bit Mapping (8-bit total):
 * +-------------------+---------------+---------------+
 * |  System Indexing  |   Node Type   |    Node ID    |
 * |    [Bits 0..2]    |  [Bits 3..4]  |  [Bits 5..7]  |
 * +-------------------+---------------+---------------+
 * | 000: Power Windows| 00: CONTROLLER| 0..7: Unique  |
 * | 001: Central Lock | 01: EXECUTOR  |       Node ID |
 * | 010: Lights       | 10: ROUTER    |               |
 * | 011..111: Reserved| 11: TRIGGER   |               |
 * +-------------------+---------------+---------------+
 */
using bit = uint8_t;
struct nid { // Network identification
    bit id : 3;
    bit type : 2;
    bit system : 3;
};

struct header {
    bit src_id;
    bit src_system;
    bit dst_id;
    bit dst_system;
    bit pld : 6;
};

// 1. Enforce exact 1-byte footprint (Critical for ESP-NOW radio payloads)
static_assert(sizeof(nid) == 1, "nid size not 1!");

// 2. Ensure layout is trivially copyable (Safe for raw memcpy
// esp_now_send)
static_assert(std::is_trivially_copyable<nid>::value,
              "nid not trivially copyable!");

enum class type : uint8_t {
    CONTROLLER = 0x00,
    EXECUTOR = 0x01,
    ROUTER = 0x02,
    TRIGGER = 0x03,
};
enum class system : uint8_t {
    POWER_WINDOWS = 0x00,
    CENTRAL_LOCKING = 0x01,
    LIGHTS = 0x02,
    // else 5 are Reserved
};

using id = bit;

nid build_nid(system s, type t, id i) {
    return {
        .id = static_cast<bit>(i),
        .type = static_cast<bit>(t),
        .system = static_cast<bit>(s),
    };
}

/**
 * [sys_src][sys_dst][type_src][type_dst][id_src][id_dst][event]
 * [src][dst][payload]
 */

} // namespace proto