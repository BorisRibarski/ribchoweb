#pragma once

#include <esp_now.h>

#include <cstdint>
#include <cstring>

#include <event.hh>

#include "ESP_NOW_Manager.hh"

class minion_t {
    static minion_t* instance;

    uint8_t master_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    queue event_queue;

    esp_now_manager esp_now_mgr;

  public:
    minion_t();
    void begin();
    void find_master();
    bool master_found();
    void proceed_events();
    void loop() {
        if (!master_found()) {
            find_master();
        }
        proceed_events();
    }

  private:
    void set_master(uint8_t* addr);
    static void setInstance(minion_t* minion) {
        instance = minion;
    }
    static void onRecv(const esp_now_recv_info_t* info,
                       const uint8_t* data,
                       int data_len) {
        if (instance) {
            instance->onRecvImpl(info, data, data_len);
        }
    }
    void onRecvImpl(const esp_now_recv_info_t* info,
                    const uint8_t* data,
                    int data_len);
    void push_NewPeer(uint8_t* mac);
    void push_IMsg(const char* text);

  public:
    void push_OMsg(const char* text);
};