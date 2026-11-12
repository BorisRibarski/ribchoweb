#pragma once

#include "Slave.hh"

class WatchDog : public Slave {
  public:
    WatchDog();
    void loop() override;
    void proceed_events() override;

  protected:
    void onRecvImpl(const esp_now_recv_info_t* info,
                    const uint8_t* data,
                    int data_len) override;
    void onSentImpl(const esp_now_send_info_t* info,
                    esp_now_send_status_t status) override;
};