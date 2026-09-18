#pragma once

#include <stdio.h>

namespace util {
inline bool parse_mac_string(const char *mac_str, uint8_t *mac_array) {
    int bytes[6];
    if (sscanf(mac_str,
               "%x:%x:%x:%x:%x:%x",
               &bytes[0],
               &bytes[1],
               &bytes[2],
               &bytes[3],
               &bytes[4],
               &bytes[5]) == 6) {
        for (int i = 0; i < 6; i++) {
            mac_array[i] = (uint8_t)bytes[i];
        }
        return true;
    }
    return false;
}
} // namespace util