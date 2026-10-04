#pragma once

#include <cstdint>

#include "esp_now.h"

using peer_info_t = esp_now_peer_info_t;

struct mac_t {
    uint8_t addr[6];
};
struct msg_t {
    int b;
};