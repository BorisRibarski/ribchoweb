#pragma once

#include <cstdint>
#include <queue>
#include <variant>

struct NewPeer {
    uint8_t addr[6];
};
struct IMessage {
    char text[64];
};
struct OMessage {
    char text[64];
};

using event = std::variant<NewPeer, IMessage, OMessage>;
using queue = std::queue<event>;