#pragma once

#include <cstdint>

#include "utils.hh"

namespace net {
struct mac_t {
    uint8_t addr[6];
};
struct msg_t {
    int b;
};
class web {
  public:
    const mac_t mac_cont = get_mac_controller();
    const mac_t mac_exec = get_mac_executor();
    const mac_t mac_rout = get_mac_router();
    const mac_t mac_trig = get_mac_trigger();

  public: // Remove public:
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
    static mac_t get_mac_executor() {
        mac_t ret{};
        util::parse_mac_string(MAC_EXECUTOR, ret.addr);
        return ret;
    }
    static mac_t get_mac_controller() {
        mac_t ret{};
        util::parse_mac_string(MAC_Controller, ret.addr);
        return ret;
    }
};
enum class dev_type {
    // BUG
    // FIXME
    // todo
    //  Note
    //  warning
    CONTROLLER,
    EXECUTOR,
    ROUTER,
    TRIGGER,
};
// FutureFeature more than one system
enum class system {
    Power_windows,
    Central_locking,
    Lights,
};
// FutureFeature add location of device
enum class location {
    FrontLeft,
    FrontRight,
    RearLeft,
    RearRight,
    Central,
};
static mac_t get_mac(dev_type type) {
    switch (type) {
    case dev_type::CONTROLLER:
        return web::get_mac_controller();
    case dev_type::EXECUTOR:
        return web::get_mac_executor();
    case dev_type::ROUTER:
        return web::get_mac_router();
    case dev_type::TRIGGER:
        return web::get_mac_trigger();

    default:
        return {};
    }
}
static esp_now_peer_info_t make_peer_info(const char *lmk, dev_type type) {
    esp_now_peer_info_t peerInfo = {};
    peerInfo.channel = 1;
    peerInfo.encrypt = true;
    memcpy(peerInfo.lmk, lmk, 16);
    memcpy(peerInfo.peer_addr, get_mac(type).addr, 6);
}
} // namespace net