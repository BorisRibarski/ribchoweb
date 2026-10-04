#pragma once

#include <cstring>

#include "esp_now.h"

namespace web {
static mac_t get_mac_controller() {
    mac_t ret{};
    util::parse_mac_string(MAC_Controller, ret.addr);
    return ret;
}
static mac_t get_mac_executor() {
    mac_t ret{};
    util::parse_mac_string(MAC_EXECUTOR, ret.addr);
    return ret;
}
static mac_t get_mac_router() {
    mac_t ret{};
    util::parse_mac_string(MAC_ROUTER, ret.addr);
    return ret;
}
static mac_t get_mac_trigger() {
    mac_t ret{};
    util::parse_mac_string(MAC_TRIGGER, ret.addr);
    return ret;
}
static esp_now_peer_info_t make_peer_info(const char *lmk, dev_type type) {
    esp_now_peer_info_t peerInfo = {};
    peerInfo.channel = 1;
    peerInfo.encrypt = true;
    std::memcpy(peerInfo.lmk, lmk, 16);
    std::memcpy(peerInfo.peer_addr, get_mac(type).addr, 6);
    return peerInfo;
}
} // namespace web