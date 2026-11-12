#pragma once

#include <esp_now.h>

#include <cstdint>

#include "ESP_NOW_Manager.hh"
#include "event.hh"

class Slave {
  protected:
    static Slave* instance;

  protected:
    uint8_t master_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    queue event_queue;

    esp_now_manager esp_now_mgr;

  public:
    void begin();
    void find_master();
    bool master_found();
    virtual void loop() = 0;
    virtual void proceed_events() = 0;

  protected:
    static void setInstance(Slave* slave) {
        instance = slave;
    }
    static void onRecv(const esp_now_recv_info_t* info,
                       const uint8_t* data,
                       int data_len) {
        if (instance) {
            instance->onRecvImpl(info, data, data_len);
        }
    }
    virtual void onRecvImpl(const esp_now_recv_info_t* info,
                            const uint8_t* data,
                            int data_len) = 0;

    static void onSent(const esp_now_send_info_t* info,
                       esp_now_send_status_t status) {
        if (instance) {
            instance->onSentImpl(info, status);
        }
    }
    virtual void onSentImpl(const esp_now_send_info_t* info,
                            esp_now_send_status_t status) = 0;

  protected:
    void set_master(uint8_t* addr);
    bool check_broadcast(const uint8_t* addr);

    void push_NewPeer(uint8_t* mac);
    void push_IMsg(const char* text);
    void push_OMsg(const char* text);
};