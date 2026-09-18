#pragma once

#include <esp_now.h>

#include <functional>
#include <vector>

class device {
  public:
    void begin();
    using send_cb = void (*)(const uint8_t *, esp_now_send_status_t);
    using recv_cb = void (*)(const unsigned char *, const uint8_t *, int);

  protected:
    static std::vector<esp_now_peer_info_t> peers;

    virtual send_cb get_send_cb() = 0;
    virtual recv_cb get_recv_cb() = 0;
};