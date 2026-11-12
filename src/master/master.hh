#pragma once

#include <esp_now.h>

#include <cstdint>

#include <event.hh>

#include "ESP_NOW_Manager.hh"

class master_t {
    static master_t* instance;

    uint8_t slave_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    queue event_queue;

    esp_now_manager esp_now_mgr;

  public:
    master_t();
    void begin();
    void proceed_events();
    void loop() {
        proceed_events();
    }

  private:
    void set_slave(uint8_t* addr);
    static void setInstance(master_t* master) {
        instance = master;
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
    void push_OMsg(const char* text);
};