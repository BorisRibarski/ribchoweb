#pragma once

#include <cstdint>
#include <queue>
#include <variant>

struct NewPeer {
    uint8_t addr[6];
};
struct Light {
    bool on;
};
// REMOVE
struct Input {
    bool on;
};
struct IData {
    bool up;
    bool down;
    bool autoUp;
    bool autoDown;
};
struct OData {
    bool up;
    bool down;
    bool autoUp;
    bool autoDown;
};
struct IMessage {
    char text[64];
};
struct OMessage {
    char text[64];
};

using event =
    std::variant<NewPeer, Input, IData, OData, IMessage, OMessage>;
using queue = std::queue<event>;