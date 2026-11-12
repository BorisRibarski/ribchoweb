#pragma once

#include <esp_now.h>

#include <cstdint>

class esp_now_manager {
  public:
    void init();
    void set_recv_cb(esp_now_recv_cb_t);
    void set_send_cb(esp_now_send_cb_t);
    void add_peer(const uint8_t*);
    void add_broadcast_peer();
    void rem_broadcast_peer();
    esp_err_t has_peer(uint8_t* addr);
    void send(uint8_t* addr, char* data, int data_len);

  private:
    void make_peer_info(esp_now_peer_info_t*, const uint8_t*);
};